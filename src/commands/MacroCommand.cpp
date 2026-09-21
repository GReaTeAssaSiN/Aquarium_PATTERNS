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

void MacroCommand::Undo()
{
    for (auto it = commands_.rbegin(); it != commands_.rend(); ++it)
    {
        (*it)->Undo();
    }
}

std::string MacroCommand::Description() const
{
    return description_;
}
