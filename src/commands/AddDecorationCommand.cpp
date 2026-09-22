#include "commands/AddDecorationCommand.h"

AddDecorationCommand::AddDecorationCommand(Scene& scene, Vector2 position)
    : scene_(scene), position_(position) {}

void AddDecorationCommand::Execute()
{
    biomeName_ = scene_.ActiveBiomeName();
    decoration_ = scene_.SpawnDecoration(position_);
}

bool AddDecorationCommand::Undo()
{
    const bool removed = scene_.RemoveDecoration(decoration_);
    decoration_ = nullptr;
    return removed;
}

std::string AddDecorationCommand::Description() const
{
    return "Spawned decoration in " + biomeName_;
}
