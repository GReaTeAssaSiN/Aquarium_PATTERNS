#include "creatures/ReefDecoration.h"

#include "render/TextureCache.h"

ReefDecoration::ReefDecoration(Vector2 position) : Decoration(position) {}

void ReefDecoration::Draw(sf::RenderWindow& window) const
{
    const sf::Texture& texture = render::GetTexture("sprites/reef_rock.png");
    const sf::Vector2u texSize = texture.getSize();
    constexpr float kTargetWidth = 26.f; // close to the old fan's ~22px span
    const float scale = kTargetWidth / static_cast<float>(texSize.x);

    sf::Sprite sprite(texture);
    sprite.setOrigin({texSize.x / 2.f, texSize.y / 2.f});
    sprite.setScale({scale, scale});
    sprite.setPosition({position_.x, position_.y});
    window.draw(sprite);
}

std::unique_ptr<Decoration> ReefDecoration::Clone(Vector2 position) const
{
    auto copy = std::make_unique<ReefDecoration>(*this);
    copy->position_ = position;
    return copy;
}
