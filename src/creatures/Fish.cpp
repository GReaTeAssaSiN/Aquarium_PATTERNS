#include "creatures/Fish.h"

#include "builders/ReportData.h"
#include "chain/FishContext.h"
#include "chain/FishDecisionHandler.h"
#include "chain/FlockingHandler.h"
#include "chain/FoodNearbyHandler.h"
#include "chain/PredatorNearbyHandler.h"
#include "chain/WeedHidingHandler.h"

namespace
{
// Built once, shared by every fish:
// WeedHidingHandler -> PredatorNearbyHandler -> FoodNearbyHandler -> FlockingHandler.
// Shelter is checked before fleeing, so a fish near weed hides instead of
// panicking into open water.
const FishDecisionHandler& GetDecisionChain()
{
    static const std::unique_ptr<FishDecisionHandler> chain = []
    {
        auto hiding = std::make_unique<WeedHidingHandler>();
        auto predator = std::make_unique<PredatorNearbyHandler>();
        auto food = std::make_unique<FoodNearbyHandler>();
        auto flocking = std::make_unique<FlockingHandler>();
        food->SetNext(std::move(flocking));
        predator->SetNext(std::move(food));
        hiding->SetNext(std::move(predator));
        return hiding;
    }();
    return *chain;
}

constexpr float kEdgeMargin = 20.f;

float WrapCoordinate(float value, float max)
{
    if (value < -kEdgeMargin)
        return max + kEdgeMargin;
    if (value > max + kEdgeMargin)
        return -kEdgeMargin;
    return value;
}
}

void Fish::Update(float dt, const FishContext& context)
{
    heading_ = GetDecisionChain().Handle(*this, context);
    position_ = position_ + heading_ * (speed_ * dt);
    position_.x = WrapCoordinate(position_.x, context.bounds.x);
    position_.y = WrapCoordinate(position_.y, context.bounds.y);
}

void Fish::CollectFishInfo(std::vector<FishInfo>& out) const
{
    out.push_back({species_, position_, GetFamilyName(), heading_});
}
