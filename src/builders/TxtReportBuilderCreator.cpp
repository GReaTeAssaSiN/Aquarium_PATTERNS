#include "builders/TxtReportBuilderCreator.h"

#include "builders/TxtReportBuilder.h"

std::unique_ptr<IReportBuilder> TxtReportBuilderCreator::CreateBuilder() const
{
    return std::make_unique<TxtReportBuilder>();
}
