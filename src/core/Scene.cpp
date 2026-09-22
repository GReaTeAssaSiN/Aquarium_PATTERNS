#include "core/Scene.h"

#include <algorithm>
#include <cstdlib>

#include "chain/FishContext.h"
#include "render/TextureCache.h"

namespace
{
const char* BackgroundPathForBiome(const char* biomeName)
{
    const std::string name = biomeName;
    if (name == "Freshwater")
        return "sprites/freshwater_background.png";
    if (name == "Reef")
        return "sprites/reef_background.png";
    return "sprites/deepsea_background.png";
}

BiomeCounts& FindOrCreateBiomeCounts(std::vector<BiomeCounts>& counts, const std::string& biomeName)
{
    for (auto& entry : counts)
    {
        if (entry.biomeName == biomeName)
            return entry;
    }
    counts.push_back({biomeName});
    return counts.back();
}

// A small random offset in [-range, range], used to cluster a shoal's fish around one point.
float RandomOffset(float range)
{
    return (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 2.f - 1.f) * range;
}

constexpr float kFoodEatRadius = 25.f;
constexpr float kPredatorEatRadius = 35.f;
// Keep in sync with WeedHidingHandler's own kShelterRadius: a fish this
// close to any weed counts as hidden.
constexpr float kWeedShelterRadius = 120.f;
}

Scene::Scene(Vector2 bounds, const AquariumFactory& initialFactory)
    : bounds_(bounds), activeFactory_(&initialFactory) {}

void Scene::HandleResize(Vector2 newBounds)
{
    const float scaleX = newBounds.x / bounds_.x;
    const float scaleY = newBounds.y / bounds_.y;

    for (auto& entity : entities_)
        entity->RescalePosition(scaleX, scaleY);
    for (auto& food : food_)
        food->SetPosition({food->GetPosition().x * scaleX, food->GetPosition().y * scaleY});
    for (auto& weed : weed_)
        weed->SetPosition({weed->GetPosition().x * scaleX, weed->GetPosition().y * scaleY});
    for (auto& decoration : decoration_)
        decoration->SetPosition({decoration->GetPosition().x * scaleX, decoration->GetPosition().y * scaleY});

    bounds_ = newBounds;
}

void Scene::SwitchBiome(const AquariumFactory& factory)
{
    activeFactory_ = &factory;
}

Fish* Scene::SpawnFish(Species species, Vector2 position)
{
    entities_.push_back(activeFactory_->MakeFish(species, position));
    return static_cast<Fish*>(entities_.back().get());
}

Shoal* Scene::SpawnShoal(Species species, Vector2 center, int count)
{
    auto shoal = std::make_unique<Shoal>();
    for (int i = 0; i < count; ++i)
    {
        const Vector2 position{center.x + RandomOffset(20.f), center.y + RandomOffset(20.f)};
        shoal->Add(activeFactory_->MakeFish(species, position));
    }
    Shoal* shoalPtr = shoal.get();
    entities_.push_back(std::move(shoal));
    return shoalPtr;
}

Food* Scene::SpawnFood(Vector2 position)
{
    food_.push_back(activeFactory_->MakeFood(position));
    return food_.back().get();
}

Weed* Scene::SpawnWeed(Vector2 position)
{
    weed_.push_back(activeFactory_->MakeWeed(position));
    return weed_.back().get();
}

Decoration* Scene::SpawnDecoration(Vector2 position)
{
    decoration_.push_back(activeFactory_->MakeDecoration(position));
    return decoration_.back().get();
}

bool Scene::RemoveEntity(AquaticEntity* entity)
{
    const auto it = std::remove_if(entities_.begin(), entities_.end(),
        [entity](const std::unique_ptr<AquaticEntity>& e) { return e.get() == entity; });
    if (it != entities_.end())
    {
        entities_.erase(it, entities_.end());
        return true;
    }
    // Not a top-level entity - it may be a Fish grouped into a Shoal.
    for (auto& e : entities_)
    {
        if (e->RemoveMember(entity))
            return true;
    }
    return false;
}

bool Scene::RemoveFood(Food* food)
{
    const auto before = food_.size();
    food_.erase(
        std::remove_if(food_.begin(), food_.end(),
            [food](const std::unique_ptr<Food>& f) { return f.get() == food; }),
        food_.end());
    return food_.size() != before;
}

bool Scene::RemoveWeed(Weed* weed)
{
    const auto before = weed_.size();
    weed_.erase(
        std::remove_if(weed_.begin(), weed_.end(),
            [weed](const std::unique_ptr<Weed>& w) { return w.get() == weed; }),
        weed_.end());
    return weed_.size() != before;
}

bool Scene::RemoveDecoration(Decoration* decoration)
{
    const auto before = decoration_.size();
    decoration_.erase(
        std::remove_if(decoration_.begin(), decoration_.end(),
            [decoration](const std::unique_ptr<Decoration>& d) { return d.get() == decoration; }),
        decoration_.end());
    return decoration_.size() != before;
}

void Scene::Update(float dt)
{
    // Built fresh every frame, unfiltered, and shared by every fish (even ones
    // nested inside a Shoal) — each handler filters by distance from its own
    // fish's actual position, so one shared snapshot is enough and correct.
    FishContext context;
    context.bounds = bounds_;

    std::vector<FishInfo> allFishInfo;
    for (const auto& entity : entities_)
        entity->CollectFishInfo(allFishInfo);
    context.neighbors = allFishInfo;

    // Live pointers (not snapshots) to every fish, including ones grouped
    // into a Shoal - needed so hunting/eating can act on them directly.
    std::vector<Fish*> allFish;
    for (const auto& entity : entities_)
        entity->CollectFish(allFish);

    for (Fish* fish : allFish)
    {
        if (fish->GetSpecies() == Species::Predator)
            context.predatorPositions.push_back(fish->GetPosition());
    }
    for (const auto& food : food_)
        context.food.push_back({food->GetPosition(), food->GetFamilyName()});
    for (const auto& weed : weed_)
        context.weedPositions.push_back(weed->GetPosition());
    for (Fish* fish : allFish)
    {
        if (fish->GetSpecies() != Species::Predator && !IsSheltered(fish->GetPosition()))
            context.huntablePrey.push_back(fish->GetPosition());
    }

    for (auto& entity : entities_)
        entity->Update(dt, context);

    HandleEating(allFish);
}

void Scene::HandleEating(const std::vector<Fish*>& allFish)
{
    // A fish (any species) eats food from its own biome by swimming onto it -
    // whether it's a top-level entity or grouped into a Shoal.
    for (Fish* fish : allFish)
    {
        food_.erase(
            std::remove_if(food_.begin(), food_.end(),
                [fish](const std::unique_ptr<Food>& food)
                {
                    return std::string(food->GetFamilyName()) == fish->GetFamilyName() &&
                           (food->GetPosition() - fish->GetPosition()).Length() < kFoodEatRadius;
                }),
            food_.end());
    }

    // Predators hunt any non-predator fish in range, regardless of biome
    // (see the comment on FishContext::predatorPositions for why).
    std::vector<Vector2> predatorPositions;
    for (Fish* fish : allFish)
    {
        if (fish->GetSpecies() == Species::Predator)
            predatorPositions.push_back(fish->GetPosition());
    }

    // Collected first, then removed one at a time (via RemoveEntity, which
    // reaches into a Shoal if needed) - unlike food_ above, entities_ can't
    // use one erase-remove pass here, since a caught fish might live inside
    // a Shoal rather than directly in entities_.
    for (Fish* fish : allFish)
    {
        if (fish->GetSpecies() == Species::Predator)
            continue;
        if (IsSheltered(fish->GetPosition())) // hiding in weed protects from being eaten too
            continue;
        for (const auto& predatorPosition : predatorPositions)
        {
            if ((predatorPosition - fish->GetPosition()).Length() < kPredatorEatRadius)
            {
                RemoveEntity(fish);
                break;
            }
        }
    }
}

bool Scene::IsSheltered(Vector2 position) const
{
    for (const auto& weed : weed_)
    {
        if ((weed->GetPosition() - position).Length() < kWeedShelterRadius)
            return true;
    }
    return false;
}

void Scene::Draw(sf::RenderWindow& window) const
{
    // Stretched to exactly fill the current window bounds, so it stays
    // correct across resizes without needing its own rescale bookkeeping.
    const sf::Texture& background = render::GetTexture(BackgroundPathForBiome(activeFactory_->GetName()));
    const sf::Vector2u backgroundSize = background.getSize();
    sf::Sprite backgroundSprite(background);
    backgroundSprite.setScale(
        {bounds_.x / static_cast<float>(backgroundSize.x), bounds_.y / static_cast<float>(backgroundSize.y)});
    window.draw(backgroundSprite);

    for (const auto& decoration : decoration_)
        decoration->Draw(window);
    for (const auto& weed : weed_)
        weed->Draw(window);
    for (const auto& food : food_)
        food->Draw(window);
    for (const auto& entity : entities_)
        entity->Draw(window);
}

ReportData Scene::GetReportData() const
{
    ReportData data;
    data.activeBiomeName = activeFactory_->GetName();

    for (const auto& entity : entities_)
        entity->CollectFishInfo(data.fish);

    for (const auto& fish : data.fish)
    {
        BiomeCounts& counts = FindOrCreateBiomeCounts(data.biomeCounts, fish.biomeName);
        switch (fish.species)
        {
            case Species::Predator: counts.predatorFish++; break;
            case Species::Prey: counts.preyFish++; break;
            default: counts.commonFish++; break;
        }
    }
    for (const auto& food : food_)
        FindOrCreateBiomeCounts(data.biomeCounts, food->GetFamilyName()).foodCount++;
    for (const auto& weed : weed_)
        FindOrCreateBiomeCounts(data.biomeCounts, weed->GetFamilyName()).weedCount++;
    for (const auto& decoration : decoration_)
        FindOrCreateBiomeCounts(data.biomeCounts, decoration->GetFamilyName()).decorationCount++;

    return data;
}
