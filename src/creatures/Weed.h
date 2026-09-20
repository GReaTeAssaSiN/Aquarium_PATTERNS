#ifndef WEED_H_
#define WEED_H_

#include <SFML/Graphics.hpp>

#include "core/Vector2.h"

// Abstract product of AquariumFactory.
class Weed
{
public:
    explicit Weed(Vector2 position) : position_(position) {}
    virtual ~Weed() = default;

    virtual void Draw(sf::RenderWindow& window) const = 0;

protected:
    Vector2 position_;
};

#endif // WEED_H_
