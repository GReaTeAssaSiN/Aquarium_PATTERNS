#ifndef FRESHWATER_FOOD_H_
#define FRESHWATER_FOOD_H_

#include "creatures/Food.h"

// Concrete product: food belonging to the Freshwater family.
class FreshwaterFood : public Food
{
public:
    explicit FreshwaterFood(Vector2 position);

    void Draw(sf::RenderWindow& window) const override;
};

#endif // FRESHWATER_FOOD_H_
