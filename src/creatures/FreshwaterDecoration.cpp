#include "creatures/FreshwaterDecoration.h"

#include "render/TextureCache.h"

FreshwaterDecoration::FreshwaterDecoration(Vector2 position) : Decoration(position) {}

void FreshwaterDecoration::Draw(sf::RenderWindow& window) const
{
    const sf::Texture& texture = render::GetTexture("sprites/freshwater_rock.png");
    const sf::Vector2u texSize = texture.getSize();
    constexpr float kTargetWidth = 34.f; // close to the old circle's ~33.6px scaled width
    const float scale = kTargetWidth / static_cast<float>(texSize.x);

    sf::Sprite sprite(texture);
    sprite.setOrigin({texSize.x / 2.f, texSize.y / 2.f});
    sprite.setScale({scale, scale});
    sprite.setPosition({position_.x, position_.y});
    window.draw(sprite);
}

std::unique_ptr<Decoration> FreshwaterDecoration::Clone(Vector2 position) const
{
    auto copy = std::make_unique<FreshwaterDecoration>(*this);
    copy->position_ = position;
    return copy;
}
