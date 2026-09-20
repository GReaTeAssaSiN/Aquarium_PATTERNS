#include "factories/DeepSeaFactory.h"

#include "creatures/DeepSeaDecoration.h"
#include "creatures/DeepSeaFish.h"
#include "creatures/DeepSeaFood.h"
#include "creatures/DeepSeaWeed.h"

DeepSeaFactory* DeepSeaFactory::instance_ = nullptr;

DeepSeaFactory& DeepSeaFactory::GetInstance()
{
    if (!instance_)
        instance_ = new DeepSeaFactory();
    return *instance_;
}

DeepSeaFactory::DeepSeaFactory()
{
    fishPrototypes_[Species::Common] = std::make_unique<DeepSeaFish>(Species::Common, Vector2{});
    fishPrototypes_[Species::Predator] = std::make_unique<DeepSeaFish>(Species::Predator, Vector2{});
    fishPrototypes_[Species::Prey] = std::make_unique<DeepSeaFish>(Species::Prey, Vector2{});
    foodPrototype_ = std::make_unique<DeepSeaFood>(Vector2{});
    weedPrototype_ = std::make_unique<DeepSeaWeed>(Vector2{});
    decorationPrototype_ = std::make_unique<DeepSeaDecoration>(Vector2{});
}

std::unique_ptr<Fish> DeepSeaFactory::MakeFish(Species species, Vector2 position) const
{
    return fishPrototypes_.at(species)->Clone(position);
}

std::unique_ptr<Food> DeepSeaFactory::MakeFood(Vector2 position) const
{
    return foodPrototype_->Clone(position);
}

std::unique_ptr<Weed> DeepSeaFactory::MakeWeed(Vector2 position) const
{
    return weedPrototype_->Clone(position);
}

std::unique_ptr<Decoration> DeepSeaFactory::MakeDecoration(Vector2 position) const
{
    return decorationPrototype_->Clone(position);
}
