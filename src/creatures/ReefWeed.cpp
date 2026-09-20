#include "creatures/ReefWeed.h"

ReefWeed::ReefWeed(Vector2 position) : Weed(position) {}

void ReefWeed::Draw(sf::RenderWindow& window) const
{
    sf::RectangleShape shape({10.f, 45.f});
    shape.setFillColor(sf::Color(190, 90, 170));
    shape.setOrigin({5.f, 45.f});
    shape.setPosition({position_.x, position_.y});
    window.draw(shape);
}

std::unique_ptr<Weed> ReefWeed::Clone(Vector2 position) const
{
    auto copy = std::make_unique<ReefWeed>(*this);
    copy->position_ = position;
    return copy;
}
