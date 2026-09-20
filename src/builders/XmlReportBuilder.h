#ifndef XML_REPORT_BUILDER_H_
#define XML_REPORT_BUILDER_H_

#include "builders/IReportBuilder.h"

// Concrete builder: renders the report as XML.
class XmlReportBuilder : public IReportBuilder
{
public:
    void BuildHeader(const std::string& activeBiomeName, const std::string& date) override;
    void BuildBody(const std::vector<FishInfo>& fish) override;
    void BuildFooter(const std::vector<BiomeCounts>& biomeCounts) override;
    std::string GetResult() const override { return xml_; }

private:
    std::string xml_;
};

#endif // XML_REPORT_BUILDER_H_
