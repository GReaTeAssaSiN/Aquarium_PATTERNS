#ifndef ADD_SHOAL_COMMAND_H_
#define ADD_SHOAL_COMMAND_H_

#include "commands/ICommand.h"
#include "core/Scene.h"

// Wraps Scene::SpawnShoal/RemoveEntity (Shoal upcasts to AquaticEntity).
class AddShoalCommand : public ICommand
{
public:
    AddShoalCommand(Scene& scene, Species species, Vector2 center, int count);

    void Execute() override;
    bool Undo() override;
    std::string Description() const override;

private:
    Scene& scene_;
    Species species_;
    Vector2 center_;
    int count_;
    Shoal* shoal_ = nullptr;
    std::string biomeName_;
};

#endif // ADD_SHOAL_COMMAND_H_
