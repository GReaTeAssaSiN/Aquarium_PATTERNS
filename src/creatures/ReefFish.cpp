#include "creatures/ReefFish.h"

namespace
{
float SizeForSpecies(Species species)
{
    switch (species)
    {
        case Species::Predator: return 24.f;
        case Species::Prey: return 10.f;
        default: return 16.f;
    }
}
}

ReefFish::ReefFish(Species species, Vector2 position)
    : Fish(species, position, 35.f), size_(SizeForSpecies(species)) {}

void ReefFish::Draw(sf::RenderWindow& window) const
{
    sf::ConvexShape triangle(3);
    triangle.setPoint(0, {size_, 0.f});
    triangle.setPoint(1, {-size_, -size_ * 0.6f});
    triangle.setPoint(2, {-size_, size_ * 0.6f});
    triangle.setFillColor(sf::Color(0, 200, 210));
    triangle.setPosition({position_.x, position_.y});
    window.draw(triangle);
}

std::unique_ptr<Fish> ReefFish::Clone(Vector2 position) const
{
    auto copy = std::make_unique<ReefFish>(*this);
    copy->position_ = position;
    return copy;
}
