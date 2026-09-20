#include "factories/ReefFactory.h"

#include "creatures/ReefDecoration.h"
#include "creatures/ReefFish.h"
#include "creatures/ReefFood.h"
#include "creatures/ReefWeed.h"

ReefFactory* ReefFactory::instance_ = nullptr;

ReefFactory& ReefFactory::GetInstance()
{
    if (!instance_)
        instance_ = new ReefFactory();
    return *instance_;
}

ReefFactory::ReefFactory()
{
    fishPrototypes_[Species::Common] = std::make_unique<ReefFish>(Species::Common, Vector2{});
    fishPrototypes_[Species::Predator] = std::make_unique<ReefFish>(Species::Predator, Vector2{});
    fishPrototypes_[Species::Prey] = std::make_unique<ReefFish>(Species::Prey, Vector2{});
    foodPrototype_ = std::make_unique<ReefFood>(Vector2{});
    weedPrototype_ = std::make_unique<ReefWeed>(Vector2{});
    decorationPrototype_ = std::make_unique<ReefDecoration>(Vector2{});
}

std::unique_ptr<Fish> ReefFactory::MakeFish(Species species, Vector2 position) const
{
    return fishPrototypes_.at(species)->Clone(position);
}

std::unique_ptr<Food> ReefFactory::MakeFood(Vector2 position) const
{
    return foodPrototype_->Clone(position);
}

std::unique_ptr<Weed> ReefFactory::MakeWeed(Vector2 position) const
{
    return weedPrototype_->Clone(position);
}

std::unique_ptr<Decoration> ReefFactory::MakeDecoration(Vector2 position) const
{
    return decorationPrototype_->Clone(position);
}
