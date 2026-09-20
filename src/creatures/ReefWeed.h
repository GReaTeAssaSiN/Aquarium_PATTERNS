#ifndef REEF_WEED_H_
#define REEF_WEED_H_

#include "creatures/Weed.h"

// Concrete product: weed (coral) belonging to the Reef family.
class ReefWeed : public Weed
{
public:
    explicit ReefWeed(Vector2 position);

    void Draw(sf::RenderWindow& window) const override;
    std::unique_ptr<Weed> Clone(Vector2 position) const override;
};

#endif // REEF_WEED_H_
