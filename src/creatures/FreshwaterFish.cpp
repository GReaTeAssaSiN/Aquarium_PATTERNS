#include "creatures/FreshwaterFish.h"

#include "render/TextureCache.h"

namespace
{
float RadiusForSpecies(Species species)
{
    switch (species)
    {
        case Species::Predator: return 20.f;
        case Species::Prey: return 9.f;
        default: return 14.f;
    }
}

// Predator gets a real speed edge over its own biome's Prey/Common - without
// this they all move at the same top speed, so a fleeing fish can never
// actually be caught (see Scene::HandleEating's kPredatorEatRadius).
float SpeedForSpecies(Species species)
{
    return species == Species::Predator ? 50.f : 40.f;
}

// Sprite art already tells species apart (fin shape, expression) - no need
// for a separate per-species color on top of it.
const char* SpritePathForSpecies(Species species)
{
    switch (species)
    {
        case Species::Predator: return "sprites/freshwater_predator.png";
        case Species::Prey: return "sprites/freshwater_prey.png";
        default: return "sprites/freshwater_common.png";
    }
}
}

FreshwaterFish::FreshwaterFish(Species species, Vector2 position)
    : Fish(species, position, SpeedForSpecies(species)), radius_(RadiusForSpecies(species)) {}

void FreshwaterFish::Draw(sf::RenderWindow& window) const
{
    const sf::Texture& texture = render::GetTexture(SpritePathForSpecies(species_));
    const sf::Vector2u texSize = texture.getSize();
    // radius_ * 2 keeps the same on-screen footprint the old circle had
    // (its diameter), just now driving a sprite's width instead.
    const float scale = (radius_ * 2.f) / static_cast<float>(texSize.x);

    sf::Sprite sprite(texture);
    sprite.setOrigin({texSize.x / 2.f, texSize.y / 2.f});
    // Sprite faces right by default (matches heading_'s default {1,0});
    // mirror horizontally when swimming left so it doesn't look backwards.
    sprite.setScale({heading_.x < 0.f ? -scale : scale, scale});
    sprite.setPosition({position_.x, position_.y});
    window.draw(sprite);
}

std::unique_ptr<Fish> FreshwaterFish::Clone(Vector2 position) const
{
    auto copy = std::make_unique<FreshwaterFish>(*this);
    copy->position_ = position;
    return copy;
}
