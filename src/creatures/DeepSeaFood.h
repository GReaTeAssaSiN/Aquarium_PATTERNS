#ifndef DEEP_SEA_FOOD_H_
#define DEEP_SEA_FOOD_H_

#include "creatures/Food.h"

// Concrete product: food belonging to the DeepSea family.
class DeepSeaFood : public Food
{
public:
    explicit DeepSeaFood(Vector2 position);

    void Draw(sf::RenderWindow& window) const override;
    std::unique_ptr<Food> Clone(Vector2 position) const override;
};

#endif // DEEP_SEA_FOOD_H_
