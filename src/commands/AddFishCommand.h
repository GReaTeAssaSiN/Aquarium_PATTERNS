#ifndef ADD_FISH_COMMAND_H_
#define ADD_FISH_COMMAND_H_

#include "commands/ICommand.h"
#include "core/Scene.h"

// Wraps Scene::SpawnFish/RemoveEntity: spawns one fish, remembers exactly
// which one, and can remove that same fish again.
class AddFishCommand : public ICommand
{
public:
    AddFishCommand(Scene& scene, Species species, Vector2 position);

    void Execute() override;
    void Undo() override;
    std::string Description() const override;

private:
    Scene& scene_;
    Species species_;
    Vector2 position_;
    Fish* fish_ = nullptr;
    std::string biomeName_;
};

#endif // ADD_FISH_COMMAND_H_
