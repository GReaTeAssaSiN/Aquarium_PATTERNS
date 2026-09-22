#include "creatures/DeepSeaFish.h"

namespace
{
float SizeForSpecies(Species species)
{
    switch (species)
    {
        case Species::Predator: return 22.f;
        case Species::Prey: return 8.f;
        default: return 13.f;
    }
}

// Same purple family for every DeepSea fish, shaded by species: darker for
// Predator, paler for Prey, plain for Common.
sf::Color ColorForSpecies(Species species)
{
    switch (species)
    {
        case Species::Predator: return sf::Color(110, 20, 160);
        case Species::Prey: return sf::Color(210, 160, 240);
        default: return sf::Color(160, 60, 220);
    }
}
}

DeepSeaFish::DeepSeaFish(Species species, Vector2 position)
    : Fish(species, position, 25.f), size_(SizeForSpecies(species)) {}

void DeepSeaFish::Draw(sf::RenderWindow& window) const
{
    sf::ConvexShape diamond(4);
    diamond.setPoint(0, {0.f, -size_});
    diamond.setPoint(1, {size_ * 0.6f, 0.f});
    diamond.setPoint(2, {0.f, size_});
    diamond.setPoint(3, {-size_ * 0.6f, 0.f});
    diamond.setFillColor(ColorForSpecies(species_));
    diamond.setPosition({position_.x, position_.y});
    window.draw(diamond);
}

std::unique_ptr<Fish> DeepSeaFish::Clone(Vector2 position) const
{
    auto copy = std::make_unique<DeepSeaFish>(*this);
    copy->position_ = position;
    return copy;
}
