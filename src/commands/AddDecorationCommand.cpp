#include "commands/AddDecorationCommand.h"

AddDecorationCommand::AddDecorationCommand(Scene& scene, Vector2 position)
    : scene_(scene), position_(position) {}

void AddDecorationCommand::Execute()
{
    biomeName_ = scene_.ActiveBiomeName();
    decoration_ = scene_.SpawnDecoration(position_);
}

void AddDecorationCommand::Undo()
{
    scene_.RemoveDecoration(decoration_);
    decoration_ = nullptr;
}

std::string AddDecorationCommand::Description() const
{
    return "Spawned decoration in " + biomeName_;
}
