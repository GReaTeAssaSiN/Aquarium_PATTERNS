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

void Scene::RemoveEntity(AquaticEntity* entity)
{
    entities_.erase(
        std::remove_if(entities_.begin(), entities_.end(),
            [entity](const std::unique_ptr<AquaticEntity>& e) { return e.get() == entity; }),
        entities_.end());
}

void Scene::RemoveFood(Food* food)
{
    food_.erase(
        std::remove_if(food_.begin(), food_.end(),
            [food](const std::unique_ptr<Food>& f) { return f.get() == food; }),
        food_.end());
}

void Scene::RemoveWeed(Weed* weed)
{
    weed_.erase(
        std::remove_if(weed_.begin(), weed_.end(),
            [weed](const std::unique_ptr<Weed>& w) { return w.get() == weed; }),
        weed_.end());
}

void Scene::RemoveDecoration(Decoration* decoration)
{
    decoration_.erase(
        std::remove_if(decoration_.begin(), decoration_.end(),
            [decoration](const std::unique_ptr<Decoration>& d) { return d.get() == decoration; }),
        decoration_.end());
}

void Scene::Update(float dt)
{
    // Built fresh every frame, unfiltered, and shared by every fish (even ones
    // nested inside a Shoal) — each handler filters by distance from its own
    // fish's actual position, so one shared snapshot is enough and correct.
    FishContext context;
    context.bounds = bounds_;

    std::vector<FishInfo> allFish;
    for (const auto& entity : entities_)
        entity->CollectFishInfo(allFish);
    context.neighbors = allFish;

    for (const auto& fish : allFish)
    {
        if (fish.species == Species::Predator)
            context.predatorPositions.push_back(fish.position);
    }
    for (const auto& food : food_)
        context.food.push_back({food->GetPosition(), food->GetFamilyName()});
    for (const auto& weed : weed_)
        context.weedPositions.push_back(weed->GetPosition());
    for (const auto& entity : entities_)
    {
        if (Fish* fish = entity->AsFish(); fish && fish->GetSpecies() != Species::Predator)
            context.huntablePrey.push_back(fish->GetPosition());
    }

    for (auto& entity : entities_)
        entity->Update(dt, context);

    HandleEating();
}

void Scene::HandleEating()
{
    // A fish (any species) eats food from its own biome by swimming onto it.
    for (const auto& entity : entities_)
    {
        Fish* fish = entity->AsFish();
        if (!fish)
            continue;

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
    for (const auto& entity : entities_)
    {
        if (Fish* fish = entity->AsFish(); fish && fish->GetSpecies() == Species::Predator)
            predatorPositions.push_back(fish->GetPosition());
    }

    entities_.erase(
        std::remove_if(entities_.begin(), entities_.end(),
            [&predatorPositions](const std::unique_ptr<AquaticEntity>& entity)
            {
                Fish* fish = entity->AsFish();
                if (!fish || fish->GetSpecies() == Species::Predator)
                    return false;
                for (const auto& predatorPosition : predatorPositions)
                {
                    if ((predatorPosition - fish->GetPosition()).Length() < kPredatorEatRadius)
                        return true;
                }
                return false;
            }),
        entities_.end());
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
