#include "creatures/DeepSeaFood.h"

DeepSeaFood::DeepSeaFood(Vector2 position) : Food(position) {}

void DeepSeaFood::Draw(sf::RenderWindow& window) const
{
    sf::CircleShape shape(4.f);
    shape.setFillColor(sf::Color(90, 210, 190));
    shape.setOrigin({4.f, 4.f});
    shape.setPosition({position_.x, position_.y});
    window.draw(shape);
}
