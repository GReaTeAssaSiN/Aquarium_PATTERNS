#ifndef DEEP_SEA_WEED_H_
#define DEEP_SEA_WEED_H_

#include "creatures/Weed.h"

// Concrete product: a tube worm colony belonging to the DeepSea family.
class DeepSeaWeed : public Weed
{
public:
    explicit DeepSeaWeed(Vector2 position);

    void Draw(sf::RenderWindow& window) const override;
};

#endif // DEEP_SEA_WEED_H_
