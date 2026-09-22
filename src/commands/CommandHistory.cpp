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
    const bool succeeded = command->Undo();
    const std::string description = command->Description();
    if (succeeded)
    {
        redoStack_.Push(std::move(command));
        return description;
    }
    // Target already gone (e.g. eaten) - nothing left to redo either, so
    // the command is simply dropped here instead of moving to redoStack_.
    return description + " (already gone, nothing to undo)";
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
