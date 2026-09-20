#ifndef EXPORTED_REPORTS_LOG_H_
#define EXPORTED_REPORTS_LOG_H_

#include <string>
#include <vector>

#include "adapters/QueueAdapter.h"

// Chronological (FIFO) record of report filenames exported this session.
class ExportedReportsLog
{
public:
    void Record(std::string filename);

    // Returns every recorded filename, oldest first, without altering the log.
    std::vector<std::string> GetAll();

private:
    QueueAdapter<std::string> queue_;
};

#endif // EXPORTED_REPORTS_LOG_H_
