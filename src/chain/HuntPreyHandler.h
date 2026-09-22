#ifndef HUNT_PREY_HANDLER_H_
#define HUNT_PREY_HANDLER_H_

#include "chain/FishDecisionHandler.h"

// Predator-only: mirror of PredatorNearbyHandler, but from the hunter's side.
// If a huntable fish (any species, any biome - predators hunt across biome
// lines) is within range, swim toward the nearest one, ending the chain.
// Only targets FishContext::huntablePrey, not every neighbor - that list
// already excludes fish grouped into a Shoal, which Scene::HandleEating can
// never actually eat, so a predator never locks onto a target it can't
// catch. Actual eating on contact is Scene::HandleEating's job; this only
// supplies the steering that makes contact happen in the first place -
// without it, a predator never deliberately approaches prey, only bumps
// into one by coincidence while chasing food or flocking with other
// predators.
class HuntPreyHandler : public FishDecisionHandler
{
protected:
    bool CanHandle(const Fish& fish, const FishContext& context) const override;
    Vector2 Decide(const Fish& fish, const FishContext& context) const override;
};

#endif // HUNT_PREY_HANDLER_H_
