#include "creatures/ReefDecoration.h"

ReefDecoration::ReefDecoration(Vector2 position) : Decoration(position) {}

void ReefDecoration::Draw(sf::RenderWindow& window) const
{
    sf::ConvexShape fan(5);
    fan.setPoint(0, {0.f, 14.f});
    fan.setPoint(1, {-11.f, 4.f});
    fan.setPoint(2, {-6.f, -10.f});
    fan.setPoint(3, {6.f, -10.f});
    fan.setPoint(4, {11.f, 4.f});
    fan.setFillColor(sf::Color(245, 235, 225));
    fan.setPosition({position_.x, position_.y});
    window.draw(fan);
}
