#ifndef REPORT_DIRECTOR_H_
#define REPORT_DIRECTOR_H_

#include "builders/IReportBuilder.h"

// Director: knows the fixed order of build steps, not how each step renders.
class ReportDirector
{
public:
    std::string BuildReport(IReportBuilder& builder, const ReportData& data, const std::string& date) const;
};

#endif // REPORT_DIRECTOR_H_
