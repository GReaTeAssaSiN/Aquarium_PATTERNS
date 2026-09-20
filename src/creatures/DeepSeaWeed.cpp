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

std::unique_ptr<Weed> DeepSeaWeed::Clone(Vector2 position) const
{
    auto copy = std::make_unique<DeepSeaWeed>(*this);
    copy->position_ = position;
    return copy;
}
