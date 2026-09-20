#ifndef DEEP_SEA_FISH_H_
#define DEEP_SEA_FISH_H_

#include "creatures/Fish.h"

// Concrete product: fish belonging to the DeepSea family.
class DeepSeaFish : public Fish
{
public:
    DeepSeaFish(Species species, Vector2 position);

    void Update(float dt, Vector2 bounds) override;
    void Draw(sf::RenderWindow& window) const override;
    std::unique_ptr<Fish> Clone(Vector2 position) const override;
    const char* GetFamilyName() const override { return "DeepSea"; }

private:
    float size_;
    float speed_;
};

#endif // DEEP_SEA_FISH_H_
