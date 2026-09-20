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
    : Fish(species, position), radius_(RadiusForSpecies(species)), speed_(40.f) {}

void FreshwaterFish::Update(float dt, Vector2 bounds)
{
    position_.x += speed_ * dt;
    if (position_.x - radius_ > bounds.x)
        position_.x = -radius_;
}

void FreshwaterFish::Draw(sf::RenderWindow& window) const
{
    sf::CircleShape shape(radius_);
    shape.setFillColor(sf::Color(255, 165, 0));
    shape.setOrigin({radius_, radius_});
    shape.setPosition({position_.x, position_.y});
    window.draw(shape);
}
