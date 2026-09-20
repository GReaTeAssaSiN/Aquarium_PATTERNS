#ifndef DEEP_SEA_FACTORY_H_
#define DEEP_SEA_FACTORY_H_

#include "factories/AquariumFactory.h"

// Concrete factory producing the DeepSea biome family of products.
class DeepSeaFactory : public AquariumFactory
{
public:
    std::unique_ptr<Fish> MakeFish(Species species, Vector2 position) const override;
    std::unique_ptr<Food> MakeFood(Vector2 position) const override;
    std::unique_ptr<Weed> MakeWeed(Vector2 position) const override;
    std::unique_ptr<Decoration> MakeDecoration(Vector2 position) const override;

    const char* GetName() const override { return "DeepSea"; }
};

#endif // DEEP_SEA_FACTORY_H_
