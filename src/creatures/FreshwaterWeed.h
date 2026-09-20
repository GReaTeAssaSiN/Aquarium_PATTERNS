#ifndef FRESHWATER_WEED_H_
#define FRESHWATER_WEED_H_

#include "creatures/Weed.h"

// Concrete product: weed belonging to the Freshwater family.
class FreshwaterWeed : public Weed
{
public:
    explicit FreshwaterWeed(Vector2 position);

    void Draw(sf::RenderWindow& window) const override;
    std::unique_ptr<Weed> Clone(Vector2 position) const override;
};

#endif // FRESHWATER_WEED_H_
