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
    // if there was nothing to undo/redo (empty undo/redo stack). Undo()'s
    // description gets a "(already gone, nothing to undo)" suffix if the
    // command's own Undo() reported it had nothing left to reverse - its
    // target (a fish or food) was already removed by the ecosystem itself
    // (eaten) before the user pressed Undo. Such a command is discarded
    // rather than pushed to the redo stack, since redoing it would just
    // spawn a brand new object out of nowhere, not restore anything.
    std::string Undo();
    std::string Redo();

    bool CanUndo() const { return !undoStack_.IsEmpty(); }
    bool CanRedo() const { return !redoStack_.IsEmpty(); }

private:
    StackAdapter<std::unique_ptr<ICommand>> undoStack_;
    StackAdapter<std::unique_ptr<ICommand>> redoStack_;
};

#endif // COMMAND_HISTORY_H_
