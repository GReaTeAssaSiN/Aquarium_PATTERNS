#include "builders/HtmlReportBuilder.h"

void HtmlReportBuilder::BuildHeader(const std::string& activeBiomeName, const std::string& date)
{
    html_ += "<html><head><title>Aquarium Report</title></head><body>";
    html_ += "<h1>Aquarium Report</h1>";
    html_ += "<p>Date: " + date + "</p>";
    html_ += "<p>Active biome: " + activeBiomeName + "</p>";
}

void HtmlReportBuilder::BuildBody(const std::vector<FishInfo>& fish)
{
    html_ += "<h2>Fish (" + std::to_string(fish.size()) + ")</h2><ul>";
    for (const auto& f : fish)
    {
        html_ += "<li>" + std::string(SpeciesName(f.species)) + " (" + f.biomeName + ") at (" +
                 FormatCoordinate(f.position.x) + ", " + FormatCoordinate(f.position.y) + ")</li>";
    }
    html_ += "</ul>";
}

void HtmlReportBuilder::BuildFooter(const std::vector<BiomeCounts>& biomeCounts)
{
    html_ += "<h2>By biome</h2>";
    for (const auto& counts : biomeCounts)
    {
        html_ += "<h3>" + counts.biomeName + "</h3>";
        html_ += "<p>Fish: " + std::to_string(counts.commonFish) + " Common, " +
                 std::to_string(counts.predatorFish) + " Predator, " +
                 std::to_string(counts.preyFish) + " Prey</p>";
        html_ += "<p>Food: " + std::to_string(counts.foodCount) +
                 ", Weed: " + std::to_string(counts.weedCount) +
                 ", Decorations: " + std::to_string(counts.decorationCount) + "</p>";
    }
}

void HtmlReportBuilder::BuildSessionLog(const std::vector<std::string>& exportedReports)
{
    html_ += "<h2>Reports exported this session</h2><ol>";
    for (const auto& filename : exportedReports)
        html_ += "<li>" + filename + "</li>";
    html_ += "</ol>";
    html_ += "</body></html>";
}
