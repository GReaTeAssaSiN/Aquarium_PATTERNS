#include "factories/DeepSeaFactory.h"

#include "creatures/DeepSeaDecoration.h"
#include "creatures/DeepSeaFish.h"
#include "creatures/DeepSeaFood.h"
#include "creatures/DeepSeaWeed.h"

std::unique_ptr<Fish> DeepSeaFactory::MakeFish(Species species, Vector2 position) const
{
    return std::make_unique<DeepSeaFish>(species, position);
}

std::unique_ptr<Food> DeepSeaFactory::MakeFood(Vector2 position) const
{
    return std::make_unique<DeepSeaFood>(position);
}

std::unique_ptr<Weed> DeepSeaFactory::MakeWeed(Vector2 position) const
{
    return std::make_unique<DeepSeaWeed>(position);
}

std::unique_ptr<Decoration> DeepSeaFactory::MakeDecoration(Vector2 position) const
{
    return std::make_unique<DeepSeaDecoration>(position);
}
