#ifndef FISH_H_
#define FISH_H_

#include <memory>

#include <SFML/Graphics.hpp>
#include "core/Vector2.h"

enum class Species
{
    Common,
    Predator,
    Prey
};

// Abstract product of AquariumFactory.
class Fish
{
public:
    Fish(Species species, Vector2 position) : species_(species), position_(position) {}
    virtual ~Fish() = default;

    virtual void Update(float dt, Vector2 bounds) = 0;
    virtual void Draw(sf::RenderWindow& window) const = 0;
    // Prototype: returns a copy of this object placed at `position`.
    virtual std::unique_ptr<Fish> Clone(Vector2 position) const = 0;

    Species GetSpecies() const { return species_; }
    Vector2 GetPosition() const { return position_; }

protected:
    Species species_;
    Vector2 position_;
};

#endif // FISH_H_