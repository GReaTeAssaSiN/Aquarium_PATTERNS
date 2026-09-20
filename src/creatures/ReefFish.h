#ifndef REEF_FISH_H_
#define REEF_FISH_H_

#include "creatures/Fish.h"

// Concrete product: fish belonging to the Reef family.
class ReefFish : public Fish
{
public:
    ReefFish(Species species, Vector2 position);

    void Update(float dt, Vector2 bounds) override;
    void Draw(sf::RenderWindow& window) const override;
    std::unique_ptr<Fish> Clone(Vector2 position) const override;

private:
    float size_;
    float speed_;
};

#endif // REEF_FISH_H_
