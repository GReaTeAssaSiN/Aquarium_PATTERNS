#include "creatures/FreshwaterWeed.h"

FreshwaterWeed::FreshwaterWeed(Vector2 position) : Weed(position) {}

void FreshwaterWeed::Draw(sf::RenderWindow& window) const
{
    sf::RectangleShape shape({6.f, 60.f});
    shape.setFillColor(sf::Color(40, 130, 60));
    shape.setOrigin({3.f, 60.f});
    shape.setPosition({position_.x, position_.y});
    window.draw(shape);
}

std::unique_ptr<Weed> FreshwaterWeed::Clone(Vector2 position) const
{
    auto copy = std::make_unique<FreshwaterWeed>(*this);
    copy->position_ = position;
    return copy;
}
