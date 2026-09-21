#include "composite/Shoal.h"

#include "chain/FishContext.h"

void Shoal::Add(std::unique_ptr<AquaticEntity> entity)
{
    members_.push_back(std::move(entity));
}

void Shoal::Update(float dt, const FishContext& context)
{
    for (auto& member : members_)
        member->Update(dt, context);
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
