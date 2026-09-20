#include "builders/ReportDirector.h"

std::string ReportDirector::BuildReport(IReportBuilder& builder, const ReportData& data, const std::string& date) const
{
    builder.BuildHeader(data.activeBiomeName, date);
    builder.BuildBody(data.fish);
    builder.BuildFooter(data.biomeCounts);
    builder.BuildSessionLog(data.exportedReports);
    return builder.GetResult();
}
