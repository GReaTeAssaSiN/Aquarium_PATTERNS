#include "builders/TxtReportBuilder.h"

void TxtReportBuilder::BuildHeader(const std::string& activeBiomeName, const std::string& date)
{
    txt_ += "AQUARIUM REPORT\n";
    txt_ += "Date: " + date + "\n";
    txt_ += "Active biome: " + activeBiomeName + "\n\n";
}

void TxtReportBuilder::BuildBody(const std::vector<FishInfo>& fish)
{
    txt_ += "Fish (" + std::to_string(fish.size()) + "):\n";
    for (const auto& f : fish)
    {
        txt_ += "- " + std::string(SpeciesName(f.species)) + " (" + f.biomeName + ") at (" +
                FormatCoordinate(f.position.x) + ", " + FormatCoordinate(f.position.y) + ")\n";
    }
    txt_ += "\n";
}

void TxtReportBuilder::BuildFooter(const std::vector<BiomeCounts>& biomeCounts)
{
    txt_ += "By biome:\n";
    for (const auto& counts : biomeCounts)
    {
        txt_ += counts.biomeName + ":\n";
        txt_ += "  Fish: " + std::to_string(counts.commonFish) + " Common, " +
                std::to_string(counts.predatorFish) + " Predator, " +
                std::to_string(counts.preyFish) + " Prey\n";
        txt_ += "  Food: " + std::to_string(counts.foodCount) +
                ", Weed: " + std::to_string(counts.weedCount) +
                ", Decorations: " + std::to_string(counts.decorationCount) + "\n";
    }
}
