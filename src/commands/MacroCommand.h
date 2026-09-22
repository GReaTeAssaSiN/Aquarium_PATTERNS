#ifndef MACRO_COMMAND_H_
#define MACRO_COMMAND_H_

#include <memory>
#include <string>
#include <vector>

#include "commands/ICommand.h"

// Bundles several commands into one: Execute() runs them in order,
// Undo() reverses them in the opposite order (last executed, first undone).
class MacroCommand : public ICommand
{
public:
    MacroCommand(std::vector<std::unique_ptr<ICommand>> commands, std::string description);

    void Execute() override;
    // Every sub-command's Undo() always runs (best-effort), regardless of
    // whether an earlier one found nothing to undo. Returns true only if
    // every single one of them actually undid something.
    bool Undo() override;
    std::string Description() const override;

private:
    std::vector<std::unique_ptr<ICommand>> commands_;
    std::string description_;
};

#endif // MACRO_COMMAND_H_
