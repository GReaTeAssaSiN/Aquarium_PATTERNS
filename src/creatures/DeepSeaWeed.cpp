#include "creatures/DeepSeaWeed.h"

DeepSeaWeed::DeepSeaWeed(Vector2 position) : Weed(position) {}

void DeepSeaWeed::Draw(sf::RenderWindow& window) const
{
    sf::RectangleShape shape({8.f, 35.f});
    shape.setFillColor(sf::Color(200, 90, 40));
    shape.setOrigin({4.f, 35.f});
    shape.setPosition({position_.x, position_.y});
    window.draw(shape);
}
