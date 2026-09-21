#include "core/Scene.h"

#include <algorithm>
#include <cstdlib>

#include "chain/FishContext.h"

namespace
{
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
        context.foodPositions.push_back(food->GetPosition());
    for (const auto& weed : weed_)
        context.weedPositions.push_back(weed->GetPosition());

    for (auto& entity : entities_)
        entity->Update(dt, context);
}

void Scene::Draw(sf::RenderWindow& window) const
{
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
