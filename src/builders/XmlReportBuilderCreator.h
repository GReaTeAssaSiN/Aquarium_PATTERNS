#ifndef XML_REPORT_BUILDER_CREATOR_H_
#define XML_REPORT_BUILDER_CREATOR_H_

#include "builders/ReportBuilderCreator.h"

// Concrete creator: produces XmlReportBuilder instances.
class XmlReportBuilderCreator : public ReportBuilderCreator
{
public:
    std::unique_ptr<IReportBuilder> CreateBuilder() const override;
    const char* GetFormatName() const override { return "XML"; }
    const char* GetFileExtension() const override { return "xml"; }
};

#endif // XML_REPORT_BUILDER_CREATOR_H_
