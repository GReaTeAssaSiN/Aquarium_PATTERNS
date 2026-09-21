#include "chain/FlockingHandler.h"

namespace
{
constexpr float kNeighborRadius = 80.f;
// Comfortably bigger than two Predator circles touching (up to radius 24 each,
// see ReefFish) so fish start repelling before they visually overlap.
constexpr float kSeparationRadius = 55.f;
}

bool FlockingHandler::CanHandle(const Fish&, const FishContext&) const
{
    return true; // default handler: always ends the chain here
}

Vector2 FlockingHandler::Decide(const Fish& fish, const FishContext& context) const
{
    Vector2 cohesionSum;
    Vector2 alignmentSum;
    Vector2 separationSum;
    int neighborCount = 0;
    bool tooClose = false;

    for (const auto& neighbor : context.neighbors)
    {
        if (neighbor.species != fish.GetSpecies() || neighbor.biomeName != fish.GetFamilyName())
            continue;

        const Vector2 offset = neighbor.position - fish.GetPosition();
        const float distance = offset.Length();
        if (distance < 0.001f || distance > kNeighborRadius)
            continue; // too far, or this is the fish itself (distance ~0)

        cohesionSum = cohesionSum + neighbor.position;
        alignmentSum = alignmentSum + neighbor.heading;
        if (distance < kSeparationRadius)
        {
            separationSum = separationSum - offset;
            tooClose = true;
        }
        ++neighborCount;
    }

    // Personal space wins outright: if anyone is too close, separation is the
    // only thing that matters this frame — no tug-of-war with cohesion that
    // could cancel out and leave the fish stuck overlapping its neighbor.
    if (tooClose)
    {
        const Vector2 separation = separationSum.Normalized();
        return separation.Length() > 0.01f ? separation : fish.GetHeading();
    }

    if (neighborCount == 0)
        return fish.GetHeading(); // no flockmates nearby: keep swimming the same way

    const Vector2 cohesionCenter = cohesionSum * (1.f / static_cast<float>(neighborCount));
    const Vector2 cohesion = (cohesionCenter - fish.GetPosition()).Normalized();
    const Vector2 alignment = alignmentSum.Normalized();

    const Vector2 blended = (cohesion + alignment).Normalized();
    return blended.Length() > 0.01f ? blended : fish.GetHeading();
}
