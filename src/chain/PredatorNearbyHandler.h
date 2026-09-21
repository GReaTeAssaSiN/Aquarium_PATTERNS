#ifndef PREDATOR_NEARBY_HANDLER_H_
#define PREDATOR_NEARBY_HANDLER_H_

#include "chain/FishDecisionHandler.h"

// If a predator is within range and this fish isn't a predator itself,
// flee from the nearest one. Ends the chain when it fires.
class PredatorNearbyHandler : public FishDecisionHandler
{
protected:
    bool CanHandle(const Fish& fish, const FishContext& context) const override;
    Vector2 Decide(const Fish& fish, const FishContext& context) const override;
};

#endif // PREDATOR_NEARBY_HANDLER_H_
