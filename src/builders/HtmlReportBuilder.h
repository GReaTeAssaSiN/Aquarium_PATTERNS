#ifndef HTML_REPORT_BUILDER_H_
#define HTML_REPORT_BUILDER_H_

#include "builders/IReportBuilder.h"

// Concrete builder: renders the report as an HTML document.
class HtmlReportBuilder : public IReportBuilder
{
public:
    void BuildHeader(const std::string& biomeName, const std::string& date) override;
    void BuildBody(const std::vector<FishInfo>& fish) override;
    void BuildFooter(std::size_t foodCount, std::size_t weedCount, std::size_t decorationCount) override;
    std::string GetResult() const override { return html_; }

private:
    std::string html_;
};

#endif // HTML_REPORT_BUILDER_H_
