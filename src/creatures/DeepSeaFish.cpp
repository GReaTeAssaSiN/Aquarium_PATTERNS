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
}

DeepSeaFish::DeepSeaFish(Species species, Vector2 position)
    : Fish(species, position), size_(SizeForSpecies(species)), speed_(25.f) {}

void DeepSeaFish::Update(float dt, Vector2 bounds)
{
    position_.y -= speed_ * dt;
    if (position_.y + size_ < 0.f)
        position_.y = bounds.y + size_;
}

void DeepSeaFish::Draw(sf::RenderWindow& window) const
{
    sf::ConvexShape diamond(4);
    diamond.setPoint(0, {0.f, -size_});
    diamond.setPoint(1, {size_ * 0.6f, 0.f});
    diamond.setPoint(2, {0.f, size_});
    diamond.setPoint(3, {-size_ * 0.6f, 0.f});
    diamond.setFillColor(sf::Color(160, 60, 220));
    diamond.setPosition({position_.x, position_.y});
    window.draw(diamond);
}
