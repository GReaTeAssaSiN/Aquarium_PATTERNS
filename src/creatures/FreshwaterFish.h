#ifndef FRESHWATER_FISH_H_
#define FRESHWATER_FISH_H_

#include "creatures/Fish.h"

// Concrete product: fish belonging to the Freshwater family.
class FreshwaterFish : public Fish
{
public:
    FreshwaterFish(Species species, Vector2 position);

    void Update(float dt, Vector2 bounds) override;
    void Draw(sf::RenderWindow& window) const override;

private:
    float radius_;
    float speed_;
};

#endif // FRESHWATER_FISH_H_
