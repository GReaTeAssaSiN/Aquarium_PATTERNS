#ifndef AQUARIUM_FACTORY_H_
#define AQUARIUM_FACTORY_H_

#include <memory>

#include "core/Vector2.h"
#include "creatures/Decoration.h"
#include "creatures/Fish.h"
#include "creatures/Food.h"
#include "creatures/Weed.h"

// Abstract Factory: creates a whole family of related aquarium inhabitants
// without exposing their concrete classes to the client.
class AquariumFactory
{
public:
    virtual ~AquariumFactory() = default;

    virtual std::unique_ptr<Fish> MakeFish(Species species, Vector2 position) const = 0;
    virtual std::unique_ptr<Food> MakeFood(Vector2 position) const = 0;
    virtual std::unique_ptr<Weed> MakeWeed(Vector2 position) const = 0;
    virtual std::unique_ptr<Decoration> MakeDecoration(Vector2 position) const = 0;

    virtual const char* GetName() const = 0;
};

#endif // AQUARIUM_FACTORY_H_
