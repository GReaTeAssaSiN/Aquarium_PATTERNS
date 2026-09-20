#include "factories/FreshwaterFactory.h"

#include "creatures/FreshwaterDecoration.h"
#include "creatures/FreshwaterFish.h"
#include "creatures/FreshwaterFood.h"
#include "creatures/FreshwaterWeed.h"

FreshwaterFactory* FreshwaterFactory::instance_ = nullptr;

FreshwaterFactory& FreshwaterFactory::GetInstance()
{
    if (!instance_)
        instance_ = new FreshwaterFactory();
    return *instance_;
}

FreshwaterFactory::FreshwaterFactory()
{
    fishPrototypes_[Species::Common] = std::make_unique<FreshwaterFish>(Species::Common, Vector2{});
    fishPrototypes_[Species::Predator] = std::make_unique<FreshwaterFish>(Species::Predator, Vector2{});
    fishPrototypes_[Species::Prey] = std::make_unique<FreshwaterFish>(Species::Prey, Vector2{});
    foodPrototype_ = std::make_unique<FreshwaterFood>(Vector2{});
    weedPrototype_ = std::make_unique<FreshwaterWeed>(Vector2{});
    decorationPrototype_ = std::make_unique<FreshwaterDecoration>(Vector2{});
}

std::unique_ptr<Fish> FreshwaterFactory::MakeFish(Species species, Vector2 position) const
{
    return fishPrototypes_.at(species)->Clone(position);
}

std::unique_ptr<Food> FreshwaterFactory::MakeFood(Vector2 position) const
{
    return foodPrototype_->Clone(position);
}

std::unique_ptr<Weed> FreshwaterFactory::MakeWeed(Vector2 position) const
{
    return weedPrototype_->Clone(position);
}

std::unique_ptr<Decoration> FreshwaterFactory::MakeDecoration(Vector2 position) const
{
    return decorationPrototype_->Clone(position);
}
