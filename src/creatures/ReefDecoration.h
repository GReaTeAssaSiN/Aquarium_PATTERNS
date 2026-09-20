#ifndef REEF_DECORATION_H_
#define REEF_DECORATION_H_

#include "creatures/Decoration.h"

// Concrete product: a seashell belonging to the Reef family.
class ReefDecoration : public Decoration
{
public:
    explicit ReefDecoration(Vector2 position);

    void Draw(sf::RenderWindow& window) const override;
    std::unique_ptr<Decoration> Clone(Vector2 position) const override;
};

#endif // REEF_DECORATION_H_
