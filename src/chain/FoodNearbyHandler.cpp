#include "chain/FoodNearbyHandler.h"

namespace
{
constexpr float kDetectionRadius = 100.f;
}

bool FoodNearbyHandler::CanHandle(const Fish& fish, const FishContext& context) const
{
    for (const auto& food : context.food)
    {
        if (food.biomeName != fish.GetFamilyName())
            continue;
        if ((food.position - fish.GetPosition()).Length() < kDetectionRadius)
            return true;
    }
    return false;
}

Vector2 FoodNearbyHandler::Decide(const Fish& fish, const FishContext& context) const
{
    Vector2 nearest;
    float nearestDistance = -1.f;
    for (const auto& food : context.food)
    {
        if (food.biomeName != fish.GetFamilyName())
            continue;
        const float distance = (food.position - fish.GetPosition()).Length();
        if (nearestDistance < 0.f || distance < nearestDistance)
        {
            nearestDistance = distance;
            nearest = food.position;
        }
    }
    const Vector2 toward = (nearest - fish.GetPosition()).Normalized();
    // Already sitting right on the food (it never gets eaten/removed, so this
    // can genuinely happen): don't collapse to a zero-length freeze, keep
    // drifting the way it was already going.
    return toward.Length() > 0.01f ? toward : fish.GetHeading();
}
