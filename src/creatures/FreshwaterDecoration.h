#ifndef FRESHWATER_DECORATION_H_
#define FRESHWATER_DECORATION_H_

#include "creatures/Decoration.h"

// Concrete product: a river pebble belonging to the Freshwater family.
class FreshwaterDecoration : public Decoration
{
public:
    explicit FreshwaterDecoration(Vector2 position);

    void Draw(sf::RenderWindow& window) const override;
    std::unique_ptr<Decoration> Clone(Vector2 position) const override;
    const char* GetFamilyName() const override { return "Freshwater"; }
};

#endif // FRESHWATER_DECORATION_H_
