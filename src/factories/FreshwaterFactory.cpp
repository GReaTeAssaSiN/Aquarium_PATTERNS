#include "factories/FreshwaterFactory.h"

#include "creatures/FreshwaterDecoration.h"
#include "creatures/FreshwaterFish.h"
#include "creatures/FreshwaterFood.h"
#include "creatures/FreshwaterWeed.h"

std::unique_ptr<Fish> FreshwaterFactory::MakeFish(Species species, Vector2 position) const
{
    return std::make_unique<FreshwaterFish>(species, position);
}

std::unique_ptr<Food> FreshwaterFactory::MakeFood(Vector2 position) const
{
    return std::make_unique<FreshwaterFood>(position);
}

std::unique_ptr<Weed> FreshwaterFactory::MakeWeed(Vector2 position) const
{
    return std::make_unique<FreshwaterWeed>(position);
}

std::unique_ptr<Decoration> FreshwaterFactory::MakeDecoration(Vector2 position) const
{
    return std::make_unique<FreshwaterDecoration>(position);
}
