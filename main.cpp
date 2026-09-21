#include <SFML/Graphics.hpp>
#include <array>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "adapters/ActionHistory.h"
#include "adapters/ExportedReportsLog.h"
#include "builders/HtmlReportBuilderCreator.h"
#include "builders/ReportDirector.h"
#include "builders/TxtReportBuilderCreator.h"
#include "builders/XmlReportBuilderCreator.h"
#include "core/Scene.h"
#include "factories/DeepSeaFactory.h"
#include "factories/FreshwaterFactory.h"
#include "factories/ReefFactory.h"

namespace
{
const char* kFontPath = "/System/Library/Fonts/Supplemental/Arial.ttf";

std::string BuildHudText(const char* biomeName, const char* reportFormat,
                          const std::vector<std::string>& recentActions)
{
    std::string text = "Biome: " + std::string(biomeName) + "   Report format: " + reportFormat +
           "\n\n"
           "B - switch biome\n"
           "Space - spawn fish\n"
           "F - spawn food\n"
           "W - spawn weed\n"
           "D - spawn decoration\n"
           "S - spawn shoal of 5 fish\n"
           "E - switch report format\n"
           "R - export report";

    if (!recentActions.empty())
    {
        text += "\n\nLast actions:";
        for (const auto& action : recentActions)
            text += "\n- " + action;
    }
    return text;
}

float RandomInRange(float max)
{
    return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * max;
}

Species RandomSpecies()
{
    switch (std::rand() % 3)
    {
        case 0: return Species::Predator;
        case 1: return Species::Prey;
        default: return Species::Common;
    }
}

// Used both as the report's "generated at" timestamp and as part of its filename,
// so a report's content and its filename always agree on when it was made.
std::string CurrentTimestamp()
{
    std::time_t now = std::time(nullptr);
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", std::localtime(&now));
    return buffer;
}
}

int main()
{
    Vector2 bounds{800.f, 600.f};
    sf::RenderWindow window(
        sf::VideoMode({static_cast<unsigned>(bounds.x), static_cast<unsigned>(bounds.y)}),
        "Aquarium Ecosystem Simulator");
    window.setFramerateLimit(60);

    // Abstract Factory (Lab 1) + Singleton (Lab 2): one instance per biome family.
    const std::array<const AquariumFactory*, 3> biomes{
        &FreshwaterFactory::GetInstance(), &ReefFactory::GetInstance(), &DeepSeaFactory::GetInstance()};
    std::size_t activeBiomeIndex = 0;

    // Factory Method (Lab 3): one creator per report format, each knows which IReportBuilder to make.
    const std::array<std::unique_ptr<ReportBuilderCreator>, 3> reportCreators{
        std::make_unique<HtmlReportBuilderCreator>(),
        std::make_unique<TxtReportBuilderCreator>(),
        std::make_unique<XmlReportBuilderCreator>()};
    std::size_t activeFormatIndex = 0;
    const ReportDirector reportDirector;

    // Adapter (Lab 4): action journal (stack) and exported-report log (queue).
    ActionHistory actionHistory;
    ExportedReportsLog exportedReportsLog;

    // On-screen HUD (biome/format status + controls + recent actions).
    sf::Font hudFont;
    if (!hudFont.openFromFile(kFontPath))
        std::cerr << "Warning: could not load font at " << kFontPath << " - HUD text will not be visible\n";

    sf::Text hudText(hudFont);
    hudText.setCharacterSize(11);
    hudText.setFillColor(sf::Color::White);
    hudText.setPosition({16.f, 12.f});

    sf::RectangleShape hudBackground;
    hudBackground.setFillColor(sf::Color(0, 0, 0, 70));

    auto refreshHud = [&](const char* biomeName, const char* reportFormat)
    {
        hudText.setString(BuildHudText(biomeName, reportFormat, actionHistory.GetRecent(5)));
        const sf::FloatRect textBounds = hudText.getLocalBounds();
        hudBackground.setPosition({6.f, 6.f});
        hudBackground.setSize({textBounds.size.x + 20.f, textBounds.size.y + 24.f});
    };

    // Initial aquarium population.
    Scene scene(bounds, *biomes[activeBiomeIndex]);
    scene.SpawnFish(Species::Common, {200.f, 200.f});
    scene.SpawnFish(Species::Predator, {500.f, 350.f});
    scene.SpawnFish(Species::Prey, {300.f, 450.f});
    scene.SpawnFood({400.f, 100.f});
    scene.SpawnWeed({100.f, bounds.y});
    scene.SpawnWeed({700.f, bounds.y});
    scene.SpawnDecoration({300.f, bounds.y});
    scene.SpawnDecoration({600.f, bounds.y});

    refreshHud(scene.ActiveBiomeName(), reportCreators[activeFormatIndex]->GetFormatName());

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            // Window resize: view and scene bounds grow/shrink together, existing inhabitants rescale.
            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                bounds.x = static_cast<float>(resized->size.x);
                bounds.y = static_cast<float>(resized->size.y);
                window.setView(sf::View({bounds.x / 2.f, bounds.y / 2.f}, {bounds.x, bounds.y}));
                scene.HandleResize(bounds);
                actionHistory.Record("Resized window to " + std::to_string(resized->size.x) + "x" +
                                      std::to_string(resized->size.y));
                refreshHud(scene.ActiveBiomeName(), reportCreators[activeFormatIndex]->GetFormatName());
            }

            // Every branch below spawns/changes something, then records it and refreshes the HUD.
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::B)
                {
                    activeBiomeIndex = (activeBiomeIndex + 1) % biomes.size();
                    scene.SwitchBiome(*biomes[activeBiomeIndex]);
                    actionHistory.Record(std::string("Switched biome to ") + scene.ActiveBiomeName());
                    refreshHud(scene.ActiveBiomeName(), reportCreators[activeFormatIndex]->GetFormatName());
                }
                else if (keyPressed->code == sf::Keyboard::Key::Space)
                {
                    const Species species = RandomSpecies();
                    scene.SpawnFish(species, {RandomInRange(bounds.x), RandomInRange(bounds.y)});
                    actionHistory.Record(std::string("Spawned ") + SpeciesName(species) + " fish in " +
                                          scene.ActiveBiomeName());
                    refreshHud(scene.ActiveBiomeName(), reportCreators[activeFormatIndex]->GetFormatName());
                }
                else if (keyPressed->code == sf::Keyboard::Key::F)
                {
                    scene.SpawnFood({RandomInRange(bounds.x), RandomInRange(bounds.y)});
                    actionHistory.Record(std::string("Spawned food in ") + scene.ActiveBiomeName());
                    refreshHud(scene.ActiveBiomeName(), reportCreators[activeFormatIndex]->GetFormatName());
                }
                else if (keyPressed->code == sf::Keyboard::Key::W)
                {
                    scene.SpawnWeed({RandomInRange(bounds.x), bounds.y});
                    actionHistory.Record(std::string("Spawned weed in ") + scene.ActiveBiomeName());
                    refreshHud(scene.ActiveBiomeName(), reportCreators[activeFormatIndex]->GetFormatName());
                }
                else if (keyPressed->code == sf::Keyboard::Key::D)
                {
                    scene.SpawnDecoration({RandomInRange(bounds.x), bounds.y});
                    actionHistory.Record(std::string("Spawned decoration in ") + scene.ActiveBiomeName());
                    refreshHud(scene.ActiveBiomeName(), reportCreators[activeFormatIndex]->GetFormatName());
                }
                else if (keyPressed->code == sf::Keyboard::Key::S)
                {
                    scene.SpawnShoal(Species::Common, {RandomInRange(bounds.x), RandomInRange(bounds.y)}, 5);
                    actionHistory.Record(std::string("Spawned a shoal of 5 fish in ") + scene.ActiveBiomeName());
                    refreshHud(scene.ActiveBiomeName(), reportCreators[activeFormatIndex]->GetFormatName());
                }
                else if (keyPressed->code == sf::Keyboard::Key::E)
                {
                    activeFormatIndex = (activeFormatIndex + 1) % reportCreators.size();
                    actionHistory.Record(std::string("Switched report format to ") +
                                          reportCreators[activeFormatIndex]->GetFormatName());
                    refreshHud(scene.ActiveBiomeName(), reportCreators[activeFormatIndex]->GetFormatName());
                }
                else if (keyPressed->code == sf::Keyboard::Key::R)
                {
                    // Factory Method picks the builder; Builder assembles the report; Adapter
                    // (exportedReportsLog) supplies this session's export history for it.
                    const ReportBuilderCreator& creator = *reportCreators[activeFormatIndex];
                    const std::string timestamp = CurrentTimestamp();
                    const std::string filename = "Reports/aquarium_report_" + timestamp +
                                                  "." + std::string(creator.GetFileExtension());

                    exportedReportsLog.Record(filename);

                    ReportData data = scene.GetReportData();
                    data.exportedReports = exportedReportsLog.GetAll();

                    auto builder = creator.CreateBuilder();
                    const std::string report = reportDirector.BuildReport(*builder, data, timestamp);

                    std::filesystem::create_directories("Reports");
                    std::ofstream file(filename);
                    file << report;

                    actionHistory.Record("Exported report: " + filename);
                    refreshHud(scene.ActiveBiomeName(), reportCreators[activeFormatIndex]->GetFormatName());
                }
            }
        }

        // Update + render.
        const float dt = clock.restart().asSeconds();
        scene.Update(dt);

        window.clear(sf::Color(10, 40, 80));
        scene.Draw(window);
        window.draw(hudBackground);
        window.draw(hudText);
        window.display();
    }

    return 0;
}