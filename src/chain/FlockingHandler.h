#ifndef FLOCKING_HANDLER_H_
#define FLOCKING_HANDLER_H_

#include "chain/FishDecisionHandler.h"

// Default handler: always fires (last in the chain). Blends three simple
// boids rules over same-species, same-biome neighbors within range:
// cohesion (steer toward their center), alignment (match their heading),
// separation (steer away from ones too close).
class FlockingHandler : public FishDecisionHandler
{
protected:
    bool CanHandle(const Fish& fish, const FishContext& context) const override;
    Vector2 Decide(const Fish& fish, const FishContext& context) const override;
};

#endif // FLOCKING_HANDLER_H_
