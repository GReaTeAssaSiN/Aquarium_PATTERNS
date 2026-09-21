#ifndef FEED_COMMAND_H_
#define FEED_COMMAND_H_

#include "commands/ICommand.h"
#include "core/Scene.h"

// Wraps Scene::SpawnFood/RemoveFood.
class FeedCommand : public ICommand
{
public:
    FeedCommand(Scene& scene, Vector2 position);

    void Execute() override;
    void Undo() override;
    std::string Description() const override;

private:
    Scene& scene_;
    Vector2 position_;
    Food* food_ = nullptr;
    std::string biomeName_;
};

#endif // FEED_COMMAND_H_
