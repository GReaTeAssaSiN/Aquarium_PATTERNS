#include "creatures/Fish.h"

#include "builders/ReportData.h"
#include "chain/FishContext.h"
#include "chain/FishDecisionHandler.h"
#include "chain/FlockingHandler.h"
#include "chain/FoodNearbyHandler.h"
#include "chain/HuntPreyHandler.h"
#include "chain/PredatorNearbyHandler.h"
#include "chain/WeedHidingHandler.h"

namespace
{
// Built once, shared by every fish:
// WeedHidingHandler -> PredatorNearbyHandler -> HuntPreyHandler -> FoodNearbyHandler -> FlockingHandler.
// Shelter is checked before fleeing, so a fish near weed hides instead of
// panicking into open water. WeedHidingHandler/PredatorNearbyHandler both
// exclude predators (CanHandle is false for Species::Predator), so a
// predator's real chain is just HuntPreyHandler -> FoodNearbyHandler ->
// FlockingHandler: chase prey first, eat food if none nearby, otherwise flock.
const FishDecisionHandler& GetDecisionChain()
{
    static const std::unique_ptr<FishDecisionHandler> chain = []
    {
        auto hiding = std::make_unique<WeedHidingHandler>();
        auto predator = std::make_unique<PredatorNearbyHandler>();
        auto hunt = std::make_unique<HuntPreyHandler>();
        auto food = std::make_unique<FoodNearbyHandler>();
        auto flocking = std::make_unique<FlockingHandler>();
        food->SetNext(std::move(flocking));
        hunt->SetNext(std::move(food));
        predator->SetNext(std::move(hunt));
        hiding->SetNext(std::move(predator));
        return hiding;
    }();
    return *chain;
}

constexpr float kEdgeMargin = 20.f;

// Horizontal only: swimming off one side teleports the fish in from the other.
float WrapCoordinate(float value, float max)
{
    if (value < -kEdgeMargin)
        return max + kEdgeMargin;
    if (value > max + kEdgeMargin)
        return -kEdgeMargin;
    return value;
}

// Vertical: a hard stop at the top and bottom window edges, not a wrap - the
// sand at the bottom is purely a background image (fish can swim into it, so
// hiding in weed rooted there actually looks like hiding in it, not floating
// above it); this just stops fish leaving the window, and unlike the
// horizontal edges, never teleports from the bottom back up to the top.
// Also flips the vertical component of heading so the fish bounces back
// into view instead of pressing into the edge forever - without this, a fish
// whose heading still pointed down (e.g. flocking toward a group centered
// near the bottom) would stay pinned exactly on the edge every frame, only
// sliding sideways - visually a straight "shelf" of stuck fish.
void ClampToWaterColumn(Vector2& position, Vector2& heading, float maxY)
{
    if (position.y < 0.f)
    {
        position.y = 0.f;
        if (heading.y < 0.f)
            heading.y = -heading.y;
    }
    else if (position.y > maxY)
    {
        position.y = maxY;
        if (heading.y > 0.f)
            heading.y = -heading.y;
    }
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
    ClampToWaterColumn(position_, heading_, context.bounds.y);
}

void Fish::CollectFishInfo(std::vector<FishInfo>& out) const
{
    out.push_back({species_, position_, GetFamilyName(), heading_});
}
