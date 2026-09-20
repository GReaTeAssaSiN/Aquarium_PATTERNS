#include "factories/ReefFactory.h"

#include "creatures/ReefDecoration.h"
#include "creatures/ReefFish.h"
#include "creatures/ReefFood.h"
#include "creatures/ReefWeed.h"

std::unique_ptr<Fish> ReefFactory::MakeFish(Species species, Vector2 position) const
{
    return std::make_unique<ReefFish>(species, position);
}

std::unique_ptr<Food> ReefFactory::MakeFood(Vector2 position) const
{
    return std::make_unique<ReefFood>(position);
}

std::unique_ptr<Weed> ReefFactory::MakeWeed(Vector2 position) const
{
    return std::make_unique<ReefWeed>(position);
}

std::unique_ptr<Decoration> ReefFactory::MakeDecoration(Vector2 position) const
{
    return std::make_unique<ReefDecoration>(position);
}
