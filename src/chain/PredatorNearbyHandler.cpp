#include "chain/PredatorNearbyHandler.h"

namespace
{
constexpr float kDetectionRadius = 150.f;
}

bool PredatorNearbyHandler::CanHandle(const Fish& fish, const FishContext& context) const
{
    if (fish.GetSpecies() == Species::Predator)
        return false;

    for (const auto& predatorPosition : context.predatorPositions)
    {
        if ((predatorPosition - fish.GetPosition()).Length() < kDetectionRadius)
            return true;
    }
    return false;
}

Vector2 PredatorNearbyHandler::Decide(const Fish& fish, const FishContext& context) const
{
    Vector2 nearest;
    float nearestDistance = -1.f;
    for (const auto& predatorPosition : context.predatorPositions)
    {
        const float distance = (predatorPosition - fish.GetPosition()).Length();
        if (nearestDistance < 0.f || distance < nearestDistance)
        {
            nearestDistance = distance;
            nearest = predatorPosition;
        }
    }
    const Vector2 away = (fish.GetPosition() - nearest).Normalized();
    // Extremely unlikely (fish and predator at the exact same spot), but
    // guard against freezing instead of fleeing in some direction anyway.
    return away.Length() > 0.01f ? away : fish.GetHeading();
}
