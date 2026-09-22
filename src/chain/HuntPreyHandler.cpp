#include "chain/HuntPreyHandler.h"

namespace
{
constexpr float kDetectionRadius = 160.f;
}

bool HuntPreyHandler::CanHandle(const Fish& fish, const FishContext& context) const
{
    if (fish.GetSpecies() != Species::Predator)
        return false;

    for (const auto& preyPosition : context.huntablePrey)
    {
        if ((preyPosition - fish.GetPosition()).Length() < kDetectionRadius)
            return true;
    }
    return false;
}

Vector2 HuntPreyHandler::Decide(const Fish& fish, const FishContext& context) const
{
    Vector2 nearest;
    float nearestDistance = -1.f;
    for (const auto& preyPosition : context.huntablePrey)
    {
        const float distance = (preyPosition - fish.GetPosition()).Length();
        if (nearestDistance < 0.f || distance < nearestDistance)
        {
            nearestDistance = distance;
            nearest = preyPosition;
        }
    }
    const Vector2 toward = (nearest - fish.GetPosition()).Normalized();
    // Same freeze-guard as every other Decide(): if the predator is already
    // sitting exactly on its target, keep drifting instead of locking to {0,0}.
    return toward.Length() > 0.01f ? toward : fish.GetHeading();
}
