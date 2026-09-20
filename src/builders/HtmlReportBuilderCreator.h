#ifndef HTML_REPORT_BUILDER_CREATOR_H_
#define HTML_REPORT_BUILDER_CREATOR_H_

#include "builders/ReportBuilderCreator.h"

// Concrete creator: produces HtmlReportBuilder instances.
class HtmlReportBuilderCreator : public ReportBuilderCreator
{
public:
    std::unique_ptr<IReportBuilder> CreateBuilder() const override;
    const char* GetFormatName() const override { return "HTML"; }
    const char* GetFileExtension() const override { return "html"; }
};

#endif // HTML_REPORT_BUILDER_CREATOR_H_
