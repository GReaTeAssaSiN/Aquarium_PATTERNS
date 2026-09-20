#include "adapters/ActionHistory.h"

void ActionHistory::Record(std::string description)
{
    stack_.Push(std::move(description));
}

std::vector<std::string> ActionHistory::GetRecent(std::size_t count)
{
    std::vector<std::string> popped;
    while (!stack_.IsEmpty() && popped.size() < count)
        popped.push_back(stack_.Pop());

    // Restore the stack to its original order (deepest-popped item goes back first).
    for (auto it = popped.rbegin(); it != popped.rend(); ++it)
        stack_.Push(*it);

    return popped;
}
