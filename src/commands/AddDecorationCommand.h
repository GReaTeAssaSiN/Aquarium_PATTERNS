#ifndef ADD_DECORATION_COMMAND_H_
#define ADD_DECORATION_COMMAND_H_

#include "commands/ICommand.h"
#include "core/Scene.h"

// Wraps Scene::SpawnDecoration/RemoveDecoration.
class AddDecorationCommand : public ICommand
{
public:
    AddDecorationCommand(Scene& scene, Vector2 position);

    void Execute() override;
    bool Undo() override;
    std::string Description() const override;

private:
    Scene& scene_;
    Vector2 position_;
    Decoration* decoration_ = nullptr;
    std::string biomeName_;
};

#endif // ADD_DECORATION_COMMAND_H_
