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

// How fast heading_ turns toward the chain's desired direction, per second.
// Without this, heading_ would snap fully to whatever the chain decides each
// frame; when several same-species fish are packed tightly, FlockingHandler's
// separation/cohesion can flip which one it picks every frame (distance
// crosses the separation threshold back and forth by a pixel or two), and a
// fish that fully reverses direction every frame goes nowhere - it trembles
// in place instead of moving. Turning only partway each frame smooths that
// out into an actual curve.
constexpr float kTurnRate = 6.f;

Vector2 SteerToward(Vector2 current, Vector2 desired, float dt)
{
    const float turnFactor = kTurnRate * dt < 1.f ? kTurnRate * dt : 1.f;
    const Vector2 blended = (current + (desired - current) * turnFactor).Normalized();
    // Only degenerate case: current and desired point exactly opposite with
    // equal weight, cancelling to zero - keep the old heading instead of
    // freezing (same fallback pattern used by every handler's Decide()).
    return blended.Length() > 0.01f ? blended : current;
}
}

void Fish::Update(float dt, const FishContext& context)
{
    const Vector2 desired = GetDecisionChain().Handle(*this, context);
    heading_ = SteerToward(heading_, desired, dt);
    position_ = position_ + heading_ * (speed_ * dt);
    position_.x = WrapCoordinate(position_.x, context.bounds.x);
    position_.y = WrapCoordinate(position_.y, context.bounds.y);
}

void Fish::CollectFishInfo(std::vector<FishInfo>& out) const
{
    out.push_back({species_, position_, GetFamilyName(), heading_});
}
