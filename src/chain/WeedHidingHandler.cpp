#include "chain/WeedHidingHandler.h"

namespace
{
// Matches PredatorNearbyHandler's own detection radius: shelter only
// matters once a predator is actually close enough to be a threat.
constexpr float kPredatorDetectionRadius = 150.f;
constexpr float kShelterRadius = 120.f;
}

bool WeedHidingHandler::CanHandle(const Fish& fish, const FishContext& context) const
{
    if (fish.GetSpecies() == Species::Predator)
        return false;

    bool predatorNearby = false;
    for (const auto& predatorPosition : context.predatorPositions)
    {
        if ((predatorPosition - fish.GetPosition()).Length() < kPredatorDetectionRadius)
        {
            predatorNearby = true;
            break;
        }
    }
    if (!predatorNearby)
        return false;

    for (const auto& weedPosition : context.weedPositions)
    {
        if ((weedPosition - fish.GetPosition()).Length() < kShelterRadius)
            return true;
    }
    return false;
}

Vector2 WeedHidingHandler::Decide(const Fish& fish, const FishContext& context) const
{
    Vector2 nearest;
    float nearestDistance = -1.f;
    for (const auto& weedPosition : context.weedPositions)
    {
        const float distance = (weedPosition - fish.GetPosition()).Length();
        if (nearestDistance < 0.f || distance < nearestDistance)
        {
            nearestDistance = distance;
            nearest = weedPosition;
        }
    }

    const Vector2 toward = (nearest - fish.GetPosition()).Normalized();
    // Already tucked in right at the weed: pulling toward its exact center
    // would collapse to a zero-length vector and freeze the fish there
    // forever. Keep drifting the way it was already going instead.
    return toward.Length() > 0.01f ? toward : fish.GetHeading();
}
