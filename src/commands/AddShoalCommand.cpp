#include "commands/AddShoalCommand.h"

#include "builders/ReportData.h"

AddShoalCommand::AddShoalCommand(Scene& scene, Species species, Vector2 center, int count)
    : scene_(scene), species_(species), center_(center), count_(count) {}

void AddShoalCommand::Execute()
{
    biomeName_ = scene_.ActiveBiomeName();
    shoal_ = scene_.SpawnShoal(species_, center_, count_);
}

bool AddShoalCommand::Undo()
{
    const bool removed = scene_.RemoveEntity(shoal_);
    shoal_ = nullptr;
    return removed;
}

std::string AddShoalCommand::Description() const
{
    return "Spawned a shoal of " + std::to_string(count_) + " " + SpeciesName(species_) + " fish in " + biomeName_;
}
