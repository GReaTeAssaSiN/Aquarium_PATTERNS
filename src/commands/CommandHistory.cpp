#include "commands/CommandHistory.h"

void CommandHistory::Execute(std::unique_ptr<ICommand> command)
{
    command->Execute();
    undoStack_.Push(std::move(command));
    redoStack_ = StackAdapter<std::unique_ptr<ICommand>>();
}

std::string CommandHistory::Undo()
{
    if (!CanUndo())
    {
        return "";
    }
    std::unique_ptr<ICommand> command = undoStack_.Pop();
    command->Undo();
    const std::string description = command->Description();
    redoStack_.Push(std::move(command));
    return description;
}

std::string CommandHistory::Redo()
{
    if (!CanRedo())
    {
        return "";
    }
    std::unique_ptr<ICommand> command = redoStack_.Pop();
    command->Execute();
    const std::string description = command->Description();
    undoStack_.Push(std::move(command));
    return description;
}
