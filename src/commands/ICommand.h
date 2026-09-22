#ifndef I_COMMAND_H_
#define I_COMMAND_H_

#include <string>

// Command: wraps a single user action as an object, so it can be executed
// and later reversed without the caller (Invoker) knowing what it does.
class ICommand
{
public:
    virtual ~ICommand() = default;

    virtual void Execute() = 0;

    // Returns false if there was nothing left to undo (the target - a fish
    // or food - was already removed by the ecosystem itself, e.g. eaten,
    // rather than by this command). CommandHistory uses this to report
    // honestly and to avoid resurrecting a brand new object on a later Redo.
    virtual bool Undo() = 0;

    // Human-readable label for this command's action (e.g. "Spawned food"),
    // used to annotate undo/redo history. Does not change with direction -
    // the caller prefixes it with "Undo:"/"Redo:" as needed.
    virtual std::string Description() const = 0;
};

#endif // I_COMMAND_H_
