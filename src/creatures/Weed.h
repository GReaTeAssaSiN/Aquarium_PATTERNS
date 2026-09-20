#ifndef WEED_H_
#define WEED_H_

#include <memory>

#include <SFML/Graphics.hpp>

#include "core/Vector2.h"

// Abstract product of AquariumFactory.
class Weed
{
public:
    explicit Weed(Vector2 position) : position_(position) {}
    virtual ~Weed() = default;

    virtual void Draw(sf::RenderWindow& window) const = 0;
    // Prototype: returns a copy of this object placed at `position`.
    virtual std::unique_ptr<Weed> Clone(Vector2 position) const = 0;

    Vector2 GetPosition() const { return position_; }
    void SetPosition(Vector2 position) { position_ = position; }

protected:
    Vector2 position_;
};

#endif // WEED_H_
