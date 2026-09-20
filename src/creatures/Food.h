#ifndef FOOD_H_
#define FOOD_H_

#include <SFML/Graphics.hpp>

#include "core/Vector2.h"

// Abstract product of AquariumFactory.
class Food
{
public:
    explicit Food(Vector2 position) : position_(position) {}
    virtual ~Food() = default;

    virtual void Draw(sf::RenderWindow& window) const = 0;

protected:
    Vector2 position_;
};

#endif // FOOD_H_