#ifndef DEEP_SEA_DECORATION_H_
#define DEEP_SEA_DECORATION_H_

#include "creatures/Decoration.h"

// Concrete product: a dark vent rock belonging to the DeepSea family.
class DeepSeaDecoration : public Decoration
{
public:
    explicit DeepSeaDecoration(Vector2 position);

    void Draw(sf::RenderWindow& window) const override;
    std::unique_ptr<Decoration> Clone(Vector2 position) const override;
};

#endif // DEEP_SEA_DECORATION_H_
