#ifndef ACTION_HISTORY_H_
#define ACTION_HISTORY_H_

#include <string>
#include <vector>

#include "adapters/StackAdapter.h"

// Journal of user actions, most-recent-on-top (LIFO) — the same shape
// a future undo stack (Command pattern) will need.
class ActionHistory
{
public:
    void Record(std::string description);

    // Returns up to `count` most recent actions, most-recent-first,
    // without altering the history.
    std::vector<std::string> GetRecent(std::size_t count);

private:
    StackAdapter<std::string> stack_;
};

#endif // ACTION_HISTORY_H_
