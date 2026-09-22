#include "creatures/FreshwaterFood.h"

#include "render/TextureCache.h"

FreshwaterFood::FreshwaterFood(Vector2 position) : Food(position) {}

void FreshwaterFood::Draw(sf::RenderWindow& window) const
{
    const sf::Texture& texture = render::GetTexture("sprites/freshwater_food.png");
    const sf::Vector2u texSize = texture.getSize();
    constexpr float kTargetWidth = 12.f; // a bit bigger than the old circle's 8px so the sprite reads
    const float scale = kTargetWidth / static_cast<float>(texSize.x);

    sf::Sprite sprite(texture);
    sprite.setOrigin({texSize.x / 2.f, texSize.y / 2.f});
    sprite.setScale({scale, scale});
    sprite.setPosition({position_.x, position_.y});
    window.draw(sprite);
}

std::unique_ptr<Food> FreshwaterFood::Clone(Vector2 position) const
{
    auto copy = std::make_unique<FreshwaterFood>(*this);
    copy->position_ = position;
    return copy;
}
