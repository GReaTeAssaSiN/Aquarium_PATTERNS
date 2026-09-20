#include "builders/TxtReportBuilder.h"

void TxtReportBuilder::BuildHeader(const std::string& biomeName, const std::string& date)
{
    txt_ += "AQUARIUM REPORT\n";
    txt_ += "Date: " + date + "\n";
    txt_ += "Biome: " + biomeName + "\n\n";
}

void TxtReportBuilder::BuildBody(const std::vector<FishInfo>& fish)
{
    txt_ += "Fish (" + std::to_string(fish.size()) + "):\n";
    for (const auto& f : fish)
    {
        txt_ += "- " + std::string(SpeciesName(f.species)) + " at (" +
                FormatCoordinate(f.position.x) + ", " + FormatCoordinate(f.position.y) + ")\n";
    }
    txt_ += "\n";
}

void TxtReportBuilder::BuildFooter(std::size_t foodCount, std::size_t weedCount, std::size_t decorationCount)
{
    txt_ += "Food: " + std::to_string(foodCount) + "\n";
    txt_ += "Weed: " + std::to_string(weedCount) + "\n";
    txt_ += "Decorations: " + std::to_string(decorationCount) + "\n";
}
