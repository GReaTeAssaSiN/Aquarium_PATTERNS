#include "creatures/DeepSeaFood.h"

#include "render/TextureCache.h"

DeepSeaFood::DeepSeaFood(Vector2 position) : Food(position) {}

void DeepSeaFood::Draw(sf::RenderWindow& window) const
{
    const sf::Texture& texture = render::GetTexture("sprites/deepsea_food.png");
    const sf::Vector2u texSize = texture.getSize();
    constexpr float kTargetWidth = 12.f; // a bit bigger than the old circle's 8px so the sprite reads
    const float scale = kTargetWidth / static_cast<float>(texSize.x);

    sf::Sprite sprite(texture);
    sprite.setOrigin({texSize.x / 2.f, texSize.y / 2.f});
    sprite.setScale({scale, scale});
    sprite.setPosition({position_.x, position_.y});
    window.draw(sprite);
}

std::unique_ptr<Food> DeepSeaFood::Clone(Vector2 position) const
{
    auto copy = std::make_unique<DeepSeaFood>(*this);
    copy->position_ = position;
    return copy;
}
