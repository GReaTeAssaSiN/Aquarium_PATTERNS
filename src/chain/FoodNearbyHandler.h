#ifndef FOOD_NEARBY_HANDLER_H_
#define FOOD_NEARBY_HANDLER_H_

#include "chain/FishDecisionHandler.h"

// If food is within range, swim toward the nearest piece. Ends the chain
// when it fires. Only reached if PredatorNearbyHandler didn't handle it first.
class FoodNearbyHandler : public FishDecisionHandler
{
protected:
    bool CanHandle(const Fish& fish, const FishContext& context) const override;
    Vector2 Decide(const Fish& fish, const FishContext& context) const override;
};

#endif // FOOD_NEARBY_HANDLER_H_
