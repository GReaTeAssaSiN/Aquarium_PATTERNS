#include "commands/MacroCommand.h"

MacroCommand::MacroCommand(std::vector<std::unique_ptr<ICommand>> commands, std::string description)
    : commands_(std::move(commands)), description_(std::move(description)) {}

void MacroCommand::Execute()
{
    for (auto& command : commands_)
    {
        command->Execute();
    }
}

bool MacroCommand::Undo()
{
    bool allSucceeded = true;
    for (auto it = commands_.rbegin(); it != commands_.rend(); ++it)
    {
        // (*it)->Undo() must run unconditionally, so don't let && short-circuit it.
        const bool succeeded = (*it)->Undo();
        allSucceeded = allSucceeded && succeeded;
    }
    return allSucceeded;
}

std::string MacroCommand::Description() const
{
    return description_;
}
