#include "builders/XmlReportBuilderCreator.h"

#include "builders/XmlReportBuilder.h"

std::unique_ptr<IReportBuilder> XmlReportBuilderCreator::CreateBuilder() const
{
    return std::make_unique<XmlReportBuilder>();
}
