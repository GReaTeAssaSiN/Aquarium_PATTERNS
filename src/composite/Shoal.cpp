#include "composite/Shoal.h"

void Shoal::Add(std::unique_ptr<AquaticEntity> entity)
{
    members_.push_back(std::move(entity));
}

void Shoal::Update(float dt, Vector2 bounds)
{
    for (auto& member : members_)
        member->Update(dt, bounds);
}

void Shoal::Draw(sf::RenderWindow& window) const
{
    for (const auto& member : members_)
        member->Draw(window);
}

void Shoal::RescalePosition(float scaleX, float scaleY)
{
    for (auto& member : members_)
        member->RescalePosition(scaleX, scaleY);
}

void Shoal::CollectFishInfo(std::vector<FishInfo>& out) const
{
    for (const auto& member : members_)
        member->CollectFishInfo(out);
}
