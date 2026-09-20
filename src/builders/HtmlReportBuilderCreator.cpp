#include "builders/HtmlReportBuilderCreator.h"

#include "builders/HtmlReportBuilder.h"

std::unique_ptr<IReportBuilder> HtmlReportBuilderCreator::CreateBuilder() const
{
    return std::make_unique<HtmlReportBuilder>();
}
