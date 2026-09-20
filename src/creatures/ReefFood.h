#ifndef REEF_FOOD_H_
#define REEF_FOOD_H_

#include "creatures/Food.h"

// Concrete product: food belonging to the Reef family.
class ReefFood : public Food
{
public:
    explicit ReefFood(Vector2 position);

    void Draw(sf::RenderWindow& window) const override;
};

#endif // REEF_FOOD_H_
