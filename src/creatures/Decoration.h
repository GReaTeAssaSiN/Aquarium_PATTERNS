#ifndef DECORATION_H_
#define DECORATION_H_

#include <SFML/Graphics.hpp>

#include "core/Vector2.h"

// Abstract product of AquariumFactory: inert bottom decor (rocks, shells),
// as opposed to Weed which represents living plants.
class Decoration
{
public:
    explicit Decoration(Vector2 position) : position_(position) {}
    virtual ~Decoration() = default;

    virtual void Draw(sf::RenderWindow& window) const = 0;

protected:
    Vector2 position_;
};

#endif // DECORATION_H_
