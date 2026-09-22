#ifndef CHANGE_BIOME_COMMAND_H_
#define CHANGE_BIOME_COMMAND_H_

#include "commands/ICommand.h"
#include "core/Scene.h"

// Wraps Scene::SwitchBiome, remembering the previous factory to undo into.
class ChangeBiomeCommand : public ICommand
{
public:
    ChangeBiomeCommand(Scene& scene, const AquariumFactory& newFactory);

    void Execute() override;
    bool Undo() override;
    std::string Description() const override;

private:
    Scene& scene_;
    const AquariumFactory& newFactory_;
    const AquariumFactory* previousFactory_ = nullptr;
};

#endif // CHANGE_BIOME_COMMAND_H_
