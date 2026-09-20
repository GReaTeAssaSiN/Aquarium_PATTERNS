#include "creatures/ReefFood.h"

ReefFood::ReefFood(Vector2 position) : Food(position) {}

void ReefFood::Draw(sf::RenderWindow& window) const
{
    sf::CircleShape shape(4.f);
    shape.setFillColor(sf::Color(230, 80, 120));
    shape.setOrigin({4.f, 4.f});
    shape.setPosition({position_.x, position_.y});
    window.draw(shape);
}

std::unique_ptr<Food> ReefFood::Clone(Vector2 position) const
{
    auto copy = std::make_unique<ReefFood>(*this);
    copy->position_ = position;
    return copy;
}
