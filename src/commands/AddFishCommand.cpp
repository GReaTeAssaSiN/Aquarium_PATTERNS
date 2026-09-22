#include "commands/AddFishCommand.h"

#include "builders/ReportData.h"

AddFishCommand::AddFishCommand(Scene& scene, Species species, Vector2 position)
    : scene_(scene), species_(species), position_(position) {}

void AddFishCommand::Execute()
{
    biomeName_ = scene_.ActiveBiomeName();
    fish_ = scene_.SpawnFish(species_, position_);
}

bool AddFishCommand::Undo()
{
    const bool removed = scene_.RemoveEntity(fish_);
    fish_ = nullptr;
    return removed;
}

std::string AddFishCommand::Description() const
{
    return std::string("Spawned ") + SpeciesName(species_) + " fish in " + biomeName_;
}
