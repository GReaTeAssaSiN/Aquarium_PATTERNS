#ifndef ADD_WEED_COMMAND_H_
#define ADD_WEED_COMMAND_H_

#include "commands/ICommand.h"
#include "core/Scene.h"

// Wraps Scene::SpawnWeed/RemoveWeed.
class AddWeedCommand : public ICommand
{
public:
    AddWeedCommand(Scene& scene, Vector2 position);

    void Execute() override;
    void Undo() override;
    std::string Description() const override;

private:
    Scene& scene_;
    Vector2 position_;
    Weed* weed_ = nullptr;
    std::string biomeName_;
};

#endif // ADD_WEED_COMMAND_H_
