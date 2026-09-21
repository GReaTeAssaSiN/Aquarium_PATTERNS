#include "creatures/FreshwaterFish.h"

namespace
{
float RadiusForSpecies(Species species)
{
    switch (species)
    {
        case Species::Predator: return 20.f;
        case Species::Prey: return 9.f;
        default: return 14.f;
    }
}
}

FreshwaterFish::FreshwaterFish(Species species, Vector2 position)
    : Fish(species, position, 40.f), radius_(RadiusForSpecies(species)) {}

void FreshwaterFish::Draw(sf::RenderWindow& window) const
{
    sf::CircleShape shape(radius_);
    shape.setFillColor(sf::Color(255, 165, 0));
    shape.setOrigin({radius_, radius_});
    shape.setPosition({position_.x, position_.y});
    window.draw(shape);
}

std::unique_ptr<Fish> FreshwaterFish::Clone(Vector2 position) const
{
    auto copy = std::make_unique<FreshwaterFish>(*this);
    copy->position_ = position;
    return copy;
}
