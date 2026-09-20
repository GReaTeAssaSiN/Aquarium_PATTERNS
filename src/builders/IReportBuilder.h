#ifndef I_REPORT_BUILDER_H_
#define I_REPORT_BUILDER_H_

#include <string>

#include "builders/ReportData.h"

// Builder: declares the ordered steps of assembling a report, without
// prescribing how each step renders. ReportDirector calls these steps;
// concrete builders decide the output format.
class IReportBuilder
{
public:
    virtual ~IReportBuilder() = default;

    virtual void BuildHeader(const std::string& activeBiomeName, const std::string& date) = 0;
    virtual void BuildBody(const std::vector<FishInfo>& fish) = 0;
    virtual void BuildFooter(const std::vector<BiomeCounts>& biomeCounts) = 0;
    virtual void BuildSessionLog(const std::vector<std::string>& exportedReports) = 0;
    virtual std::string GetResult() const = 0;
};

#endif // I_REPORT_BUILDER_H_
