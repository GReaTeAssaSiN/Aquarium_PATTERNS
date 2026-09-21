#include "commands/FeedCommand.h"

FeedCommand::FeedCommand(Scene& scene, Vector2 position)
    : scene_(scene), position_(position) {}

void FeedCommand::Execute()
{
    biomeName_ = scene_.ActiveBiomeName();
    food_ = scene_.SpawnFood(position_);
}

void FeedCommand::Undo()
{
    scene_.RemoveFood(food_);
    food_ = nullptr;
}

std::string FeedCommand::Description() const
{
    return "Spawned food in " + biomeName_;
}
