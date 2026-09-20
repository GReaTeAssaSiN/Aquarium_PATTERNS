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
