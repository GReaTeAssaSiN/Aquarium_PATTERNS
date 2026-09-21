#ifndef WEED_HIDING_HANDLER_H_
#define WEED_HIDING_HANDLER_H_

#include "chain/FishDecisionHandler.h"

// If a predator is nearby and this fish isn't one itself, and there's weed
// within reach, swim toward the weed instead of just fleeing into open
// water. Takes priority over PredatorNearbyHandler: shelter beats panic.
class WeedHidingHandler : public FishDecisionHandler
{
protected:
    bool CanHandle(const Fish& fish, const FishContext& context) const override;
    Vector2 Decide(const Fish& fish, const FishContext& context) const override;
};

#endif // WEED_HIDING_HANDLER_H_
