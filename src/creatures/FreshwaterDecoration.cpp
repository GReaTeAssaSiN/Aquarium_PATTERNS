#include "creatures/FreshwaterDecoration.h"

FreshwaterDecoration::FreshwaterDecoration(Vector2 position) : Decoration(position) {}

void FreshwaterDecoration::Draw(sf::RenderWindow& window) const
{
    sf::CircleShape shape(12.f);
    shape.setFillColor(sf::Color(120, 115, 110));
    shape.setOrigin({12.f, 12.f});
    shape.setScale({1.4f, 0.8f});
    shape.setPosition({position_.x, position_.y});
    window.draw(shape);
}

std::unique_ptr<Decoration> FreshwaterDecoration::Clone(Vector2 position) const
{
    auto copy = std::make_unique<FreshwaterDecoration>(*this);
    copy->position_ = position;
    return copy;
}
