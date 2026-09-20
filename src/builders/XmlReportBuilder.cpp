#include "builders/XmlReportBuilder.h"

void XmlReportBuilder::BuildHeader(const std::string& biomeName, const std::string& date)
{
    xml_ += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    xml_ += "<report>\n";
    xml_ += "  <date>" + date + "</date>\n";
    xml_ += "  <biome>" + biomeName + "</biome>\n";
}

void XmlReportBuilder::BuildBody(const std::vector<FishInfo>& fish)
{
    xml_ += "  <fish count=\"" + std::to_string(fish.size()) + "\">\n";
    for (const auto& f : fish)
    {
        xml_ += "    <entry species=\"" + std::string(SpeciesName(f.species)) + "\" x=\"" +
                FormatCoordinate(f.position.x) + "\" y=\"" + FormatCoordinate(f.position.y) + "\"/>\n";
    }
    xml_ += "  </fish>\n";
}

void XmlReportBuilder::BuildFooter(std::size_t foodCount, std::size_t weedCount, std::size_t decorationCount)
{
    xml_ += "  <foodCount>" + std::to_string(foodCount) + "</foodCount>\n";
    xml_ += "  <weedCount>" + std::to_string(weedCount) + "</weedCount>\n";
    xml_ += "  <decorationCount>" + std::to_string(decorationCount) + "</decorationCount>\n";
    xml_ += "</report>\n";
}
