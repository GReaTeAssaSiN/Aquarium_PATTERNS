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

// Same teal family for every Reef fish, shaded by species: darker for
// Predator, paler for Prey, plain for Common.
sf::Color ColorForSpecies(Species species)
{
    switch (species)
    {
        case Species::Predator: return sf::Color(0, 130, 150);
        case Species::Prey: return sf::Color(150, 235, 235);
        default: return sf::Color(0, 200, 210);
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
    triangle.setFillColor(ColorForSpecies(species_));
    triangle.setPosition({position_.x, position_.y});
    window.draw(triangle);
}

std::unique_ptr<Fish> ReefFish::Clone(Vector2 position) const
{
    auto copy = std::make_unique<ReefFish>(*this);
    copy->position_ = position;
    return copy;
}
