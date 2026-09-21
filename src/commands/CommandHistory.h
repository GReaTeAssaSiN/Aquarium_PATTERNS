#ifndef COMMAND_HISTORY_H_
#define COMMAND_HISTORY_H_

#include <memory>
#include <string>

#include "adapters/StackAdapter.h"
#include "commands/ICommand.h"

// Undo/redo stacks built on the Lab 4 StackAdapter. Executing a new
// command clears the redo stack, matching standard undo/redo semantics.
class CommandHistory
{
public:
    void Execute(std::unique_ptr<ICommand> command);

    // Returns the undone/redone command's Description(), or an empty string
    // if there was nothing to undo/redo.
    std::string Undo();
    std::string Redo();

    bool CanUndo() const { return !undoStack_.IsEmpty(); }
    bool CanRedo() const { return !redoStack_.IsEmpty(); }

private:
    StackAdapter<std::unique_ptr<ICommand>> undoStack_;
    StackAdapter<std::unique_ptr<ICommand>> redoStack_;
};

#endif // COMMAND_HISTORY_H_
