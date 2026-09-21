#include "commands/ChangeBiomeCommand.h"

ChangeBiomeCommand::ChangeBiomeCommand(Scene& scene, const AquariumFactory& newFactory)
    : scene_(scene), newFactory_(newFactory) {}

void ChangeBiomeCommand::Execute()
{
    previousFactory_ = &scene_.GetActiveFactory();
    scene_.SwitchBiome(newFactory_);
}

void ChangeBiomeCommand::Undo()
{
    scene_.SwitchBiome(*previousFactory_);
}

std::string ChangeBiomeCommand::Description() const
{
    return std::string("Switched biome from ") + previousFactory_->GetName() + " to " + newFactory_.GetName();
}
