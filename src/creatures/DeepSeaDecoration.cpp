#include "creatures/DeepSeaDecoration.h"

#include "render/TextureCache.h"

DeepSeaDecoration::DeepSeaDecoration(Vector2 position) : Decoration(position) {}

void DeepSeaDecoration::Draw(sf::RenderWindow& window) const
{
    const sf::Texture& texture = render::GetTexture("sprites/deepsea_rock.png");
    const sf::Vector2u texSize = texture.getSize();
    constexpr float kTargetWidth = 36.f; // close to the old circle's ~36.4px scaled width
    const float scale = kTargetWidth / static_cast<float>(texSize.x);

    sf::Sprite sprite(texture);
    sprite.setOrigin({texSize.x / 2.f, texSize.y / 2.f});
    sprite.setScale({scale, scale});
    sprite.setPosition({position_.x, position_.y});
    window.draw(sprite);
}

std::unique_ptr<Decoration> DeepSeaDecoration::Clone(Vector2 position) const
{
    auto copy = std::make_unique<DeepSeaDecoration>(*this);
    copy->position_ = position;
    return copy;
}
