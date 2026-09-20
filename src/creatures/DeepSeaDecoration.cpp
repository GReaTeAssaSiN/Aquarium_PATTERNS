#include "creatures/DeepSeaDecoration.h"

DeepSeaDecoration::DeepSeaDecoration(Vector2 position) : Decoration(position) {}

void DeepSeaDecoration::Draw(sf::RenderWindow& window) const
{
    sf::CircleShape shape(14.f);
    shape.setFillColor(sf::Color(35, 30, 45));
    shape.setOrigin({14.f, 14.f});
    shape.setScale({1.3f, 0.9f});
    shape.setPosition({position_.x, position_.y});
    window.draw(shape);
}

std::unique_ptr<Decoration> DeepSeaDecoration::Clone(Vector2 position) const
{
    auto copy = std::make_unique<DeepSeaDecoration>(*this);
    copy->position_ = position;
    return copy;
}
