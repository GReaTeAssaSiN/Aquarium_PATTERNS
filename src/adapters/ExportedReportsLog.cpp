#include "adapters/ExportedReportsLog.h"

void ExportedReportsLog::Record(std::string filename)
{
    queue_.Push(std::move(filename));
}

std::vector<std::string> ExportedReportsLog::GetAll()
{
    std::vector<std::string> all;
    while (!queue_.IsEmpty())
        all.push_back(queue_.Pop());

    // Restore the queue to its original order.
    for (const auto& filename : all)
        queue_.Push(filename);

    return all;
}
