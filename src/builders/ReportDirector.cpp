#include "builders/ReportDirector.h"

std::string ReportDirector::BuildReport(IReportBuilder& builder, const ReportData& data, const std::string& date) const
{
    builder.BuildHeader(data.biomeName, date);
    builder.BuildBody(data.fish);
    builder.BuildFooter(data.foodCount, data.weedCount, data.decorationCount);
    return builder.GetResult();
}
