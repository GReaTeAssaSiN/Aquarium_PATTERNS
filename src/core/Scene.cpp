#include "core/Scene.h"

Scene::Scene(Vector2 bounds, const AquariumFactory& initialFactory)
    : bounds_(bounds), activeFactory_(&initialFactory) {}

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
