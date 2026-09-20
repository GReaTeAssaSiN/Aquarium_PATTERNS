#include "core/Scene.h"

Scene::Scene(Vector2 bounds, const AquariumFactory& initialFactory)
    : bounds_(bounds), activeFactory_(&initialFactory) {}

void Scene::HandleResize(Vector2 newBounds)
{
    const float scaleX = newBounds.x / bounds_.x;
    const float scaleY = newBounds.y / bounds_.y;

    for (auto& fish : fish_)
        fish->SetPosition({fish->GetPosition().x * scaleX, fish->GetPosition().y * scaleY});
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

void Scene::SpawnFish(Species species, Vector2 position)
{
    fish_.push_back(activeFactory_->MakeFish(species, position));
}

void Scene::SpawnFood(Vector2 position)
{
    food_.push_back(activeFactory_->MakeFood(position));
}

void Scene::SpawnWeed(Vector2 position)
{
    weed_.push_back(activeFactory_->MakeWeed(position));
}

void Scene::SpawnDecoration(Vector2 position)
{
    decoration_.push_back(activeFactory_->MakeDecoration(position));
}

void Scene::Update(float dt)
{
    for (auto& fish : fish_)
        fish->Update(dt, bounds_);
}

void Scene::Draw(sf::RenderWindow& window) const
{
    for (const auto& decoration : decoration_)
        decoration->Draw(window);
    for (const auto& weed : weed_)
        weed->Draw(window);
    for (const auto& food : food_)
        food->Draw(window);
    for (const auto& fish : fish_)
        fish->Draw(window);
}

ReportData Scene::GetReportData() const
{
    ReportData data;
    data.biomeName = activeFactory_->GetName();
    for (const auto& fish : fish_)
        data.fish.push_back({fish->GetSpecies(), fish->GetPosition()});
    data.foodCount = food_.size();
    data.weedCount = weed_.size();
    data.decorationCount = decoration_.size();
    return data;
}
