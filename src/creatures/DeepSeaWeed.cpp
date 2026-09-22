#include "creatures/DeepSeaWeed.h"

#include "render/TextureCache.h"

DeepSeaWeed::DeepSeaWeed(Vector2 position) : Weed(position) {}

void DeepSeaWeed::Draw(sf::RenderWindow& window) const
{
    const sf::Texture& texture = render::GetTexture("sprites/deepsea_weed.png");
    const sf::Vector2u texSize = texture.getSize();
    constexpr float kTargetHeight = 35.f; // matches the old rectangle's height
    const float scale = kTargetHeight / static_cast<float>(texSize.y);

    sf::Sprite sprite(texture);
    // Origin at bottom-center, like the old rectangle: weed grows up from position_.
    sprite.setOrigin({texSize.x / 2.f, static_cast<float>(texSize.y)});
    sprite.setScale({scale, scale});
    sprite.setPosition({position_.x, position_.y});
    window.draw(sprite);
}

std::unique_ptr<Weed> DeepSeaWeed::Clone(Vector2 position) const
{
    auto copy = std::make_unique<DeepSeaWeed>(*this);
    copy->position_ = position;
    return copy;
}
