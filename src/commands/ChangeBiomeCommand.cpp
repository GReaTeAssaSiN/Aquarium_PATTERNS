#include "commands/ChangeBiomeCommand.h"

ChangeBiomeCommand::ChangeBiomeCommand(Scene& scene, const AquariumFactory& newFactory)
    : scene_(scene), newFactory_(newFactory) {}

void ChangeBiomeCommand::Execute()
{
    previousFactory_ = &scene_.GetActiveFactory();
    scene_.SwitchBiome(newFactory_);
}

bool ChangeBiomeCommand::Undo()
{
    scene_.SwitchBiome(*previousFactory_);
    return true; // switching biome back always succeeds - nothing for the ecosystem to have destroyed
}

std::string ChangeBiomeCommand::Description() const
{
    return std::string("Switched biome from ") + previousFactory_->GetName() + " to " + newFactory_.GetName();
}
