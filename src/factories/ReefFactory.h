#ifndef REEF_FACTORY_H_
#define REEF_FACTORY_H_

#include "factories/AquariumFactory.h"

// Concrete factory producing the Reef biome family of products.
class ReefFactory : public AquariumFactory
{
public:
    std::unique_ptr<Fish> MakeFish(Species species, Vector2 position) const override;
    std::unique_ptr<Food> MakeFood(Vector2 position) const override;
    std::unique_ptr<Weed> MakeWeed(Vector2 position) const override;
    std::unique_ptr<Decoration> MakeDecoration(Vector2 position) const override;

    const char* GetName() const override { return "Reef"; }
};

#endif // REEF_FACTORY_H_
