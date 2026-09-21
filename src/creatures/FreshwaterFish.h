#ifndef FRESHWATER_FISH_H_
#define FRESHWATER_FISH_H_

#include "creatures/Fish.h"

// Concrete product: fish belonging to the Freshwater family.
class FreshwaterFish : public Fish
{
public:
    FreshwaterFish(Species species, Vector2 position);

    void Draw(sf::RenderWindow& window) const override;
    std::unique_ptr<Fish> Clone(Vector2 position) const override;
    const char* GetFamilyName() const override { return "Freshwater"; }

private:
    float radius_;
};

#endif // FRESHWATER_FISH_H_
