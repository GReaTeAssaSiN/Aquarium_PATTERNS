#ifndef TXT_REPORT_BUILDER_H_
#define TXT_REPORT_BUILDER_H_

#include "builders/IReportBuilder.h"

// Concrete builder: renders the report as plain text.
class TxtReportBuilder : public IReportBuilder
{
public:
    void BuildHeader(const std::string& activeBiomeName, const std::string& date) override;
    void BuildBody(const std::vector<FishInfo>& fish) override;
    void BuildFooter(const std::vector<BiomeCounts>& biomeCounts) override;
    std::string GetResult() const override { return txt_; }

private:
    std::string txt_;
};

#endif // TXT_REPORT_BUILDER_H_
