#include "commands/AddWeedCommand.h"

AddWeedCommand::AddWeedCommand(Scene& scene, Vector2 position)
    : scene_(scene), position_(position) {}

void AddWeedCommand::Execute()
{
    biomeName_ = scene_.ActiveBiomeName();
    weed_ = scene_.SpawnWeed(position_);
}

void AddWeedCommand::Undo()
{
    scene_.RemoveWeed(weed_);
    weed_ = nullptr;
}

std::string AddWeedCommand::Description() const
{
    return "Spawned weed in " + biomeName_;
}
