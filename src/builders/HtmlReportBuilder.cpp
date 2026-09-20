#include "builders/HtmlReportBuilder.h"

void HtmlReportBuilder::BuildHeader(const std::string& biomeName, const std::string& date)
{
    html_ += "<html><head><title>Aquarium Report</title></head><body>";
    html_ += "<h1>Aquarium Report</h1>";
    html_ += "<p>Date: " + date + "</p>";
    html_ += "<p>Biome: " + biomeName + "</p>";
}

void HtmlReportBuilder::BuildBody(const std::vector<FishInfo>& fish)
{
    html_ += "<h2>Fish (" + std::to_string(fish.size()) + ")</h2><ul>";
    for (const auto& f : fish)
    {
        html_ += "<li>" + std::string(SpeciesName(f.species)) + " at (" +
                 FormatCoordinate(f.position.x) + ", " + FormatCoordinate(f.position.y) + ")</li>";
    }
    html_ += "</ul>";
}

void HtmlReportBuilder::BuildFooter(std::size_t foodCount, std::size_t weedCount, std::size_t decorationCount)
{
    html_ += "<h2>Other inhabitants</h2>";
    html_ += "<p>Food: " + std::to_string(foodCount) + "</p>";
    html_ += "<p>Weed: " + std::to_string(weedCount) + "</p>";
    html_ += "<p>Decorations: " + std::to_string(decorationCount) + "</p>";
    html_ += "</body></html>";
}
