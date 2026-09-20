#include "builders/XmlReportBuilder.h"

void XmlReportBuilder::BuildHeader(const std::string& activeBiomeName, const std::string& date)
{
    xml_ += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    xml_ += "<report>\n";
    xml_ += "  <date>" + date + "</date>\n";
    xml_ += "  <activeBiome>" + activeBiomeName + "</activeBiome>\n";
}

void XmlReportBuilder::BuildBody(const std::vector<FishInfo>& fish)
{
    xml_ += "  <fish count=\"" + std::to_string(fish.size()) + "\">\n";
    for (const auto& f : fish)
    {
        xml_ += "    <entry species=\"" + std::string(SpeciesName(f.species)) + "\" biome=\"" + f.biomeName +
                "\" x=\"" + FormatCoordinate(f.position.x) + "\" y=\"" + FormatCoordinate(f.position.y) + "\"/>\n";
    }
    xml_ += "  </fish>\n";
}

void XmlReportBuilder::BuildFooter(const std::vector<BiomeCounts>& biomeCounts)
{
    xml_ += "  <biomes>\n";
    for (const auto& counts : biomeCounts)
    {
        xml_ += "    <biome name=\"" + counts.biomeName + "\">\n";
        xml_ += "      <commonFish>" + std::to_string(counts.commonFish) + "</commonFish>\n";
        xml_ += "      <predatorFish>" + std::to_string(counts.predatorFish) + "</predatorFish>\n";
        xml_ += "      <preyFish>" + std::to_string(counts.preyFish) + "</preyFish>\n";
        xml_ += "      <foodCount>" + std::to_string(counts.foodCount) + "</foodCount>\n";
        xml_ += "      <weedCount>" + std::to_string(counts.weedCount) + "</weedCount>\n";
        xml_ += "      <decorationCount>" + std::to_string(counts.decorationCount) + "</decorationCount>\n";
        xml_ += "    </biome>\n";
    }
    xml_ += "  </biomes>\n";
    xml_ += "</report>\n";
}
