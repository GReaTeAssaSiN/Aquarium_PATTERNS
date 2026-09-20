#ifndef TXT_REPORT_BUILDER_CREATOR_H_
#define TXT_REPORT_BUILDER_CREATOR_H_

#include "builders/ReportBuilderCreator.h"

// Concrete creator: produces TxtReportBuilder instances.
class TxtReportBuilderCreator : public ReportBuilderCreator
{
public:
    std::unique_ptr<IReportBuilder> CreateBuilder() const override;
    const char* GetFormatName() const override { return "TXT"; }
    const char* GetFileExtension() const override { return "txt"; }
};

#endif // TXT_REPORT_BUILDER_CREATOR_H_
