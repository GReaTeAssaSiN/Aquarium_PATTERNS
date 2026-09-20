#ifndef REPORT_BUILDER_CREATOR_H_
#define REPORT_BUILDER_CREATOR_H_

#include <memory>

#include "builders/IReportBuilder.h"

// Factory Method: defers the choice of concrete IReportBuilder to subclasses,
// so the caller can pick a format at runtime without naming concrete classes.
class ReportBuilderCreator
{
public:
    virtual ~ReportBuilderCreator() = default;

    virtual std::unique_ptr<IReportBuilder> CreateBuilder() const = 0;
    virtual const char* GetFormatName() const = 0;
    virtual const char* GetFileExtension() const = 0;
};

#endif // REPORT_BUILDER_CREATOR_H_
