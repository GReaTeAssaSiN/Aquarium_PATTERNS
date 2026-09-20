#include "creatures/FreshwaterFood.h"

FreshwaterFood::FreshwaterFood(Vector2 position) : Food(position) {}

void FreshwaterFood::Draw(sf::RenderWindow& window) const
{
    sf::CircleShape shape(4.f);
    shape.setFillColor(sf::Color(150, 100, 50));
    shape.setOrigin({4.f, 4.f});
    shape.setPosition({position_.x, position_.y});
    window.draw(shape);
}

std::unique_ptr<Food> FreshwaterFood::Clone(Vector2 position) const
{
    auto copy = std::make_unique<FreshwaterFood>(*this);
    copy->position_ = position;
    return copy;
}
