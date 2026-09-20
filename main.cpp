#include <SFML/Graphics.hpp>
#include <array>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

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

std::string BuildHudText(const char* biomeName, const char* reportFormat)
{
    return "Biome: " + std::string(biomeName) + "   Report format: " + reportFormat +
           "\n\n"
           "B - switch biome\n"
           "Space - spawn fish\n"
           "F - spawn food\n"
           "W - spawn weed\n"
           "D - spawn decoration\n"
           "E - switch report format\n"
           "R - export report";
}

float RandomInRange(float max)
{
    return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * max;
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

    const std::array<const AquariumFactory*, 3> biomes{
        &FreshwaterFactory::GetInstance(), &ReefFactory::GetInstance(), &DeepSeaFactory::GetInstance()};
    std::size_t activeBiomeIndex = 0;

    const std::array<std::unique_ptr<ReportBuilderCreator>, 3> reportCreators{
        std::make_unique<HtmlReportBuilderCreator>(),
        std::make_unique<TxtReportBuilderCreator>(),
        std::make_unique<XmlReportBuilderCreator>()};
    std::size_t activeFormatIndex = 0;
    const ReportDirector reportDirector;

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
        hudText.setString(BuildHudText(biomeName, reportFormat));
        const sf::FloatRect textBounds = hudText.getLocalBounds();
        hudBackground.setPosition({6.f, 6.f});
        hudBackground.setSize({textBounds.size.x + 20.f, textBounds.size.y + 24.f});
    };

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

            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                bounds.x = static_cast<float>(resized->size.x);
                bounds.y = static_cast<float>(resized->size.y);
                window.setView(sf::View({bounds.x / 2.f, bounds.y / 2.f}, {bounds.x, bounds.y}));
                scene.HandleResize(bounds);
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::B)
                {
                    activeBiomeIndex = (activeBiomeIndex + 1) % biomes.size();
                    scene.SwitchBiome(*biomes[activeBiomeIndex]);
                    refreshHud(scene.ActiveBiomeName(), reportCreators[activeFormatIndex]->GetFormatName());
                }
                else if (keyPressed->code == sf::Keyboard::Key::Space)
                {
                    scene.SpawnFish(Species::Common, {RandomInRange(bounds.x), RandomInRange(bounds.y)});
                }
                else if (keyPressed->code == sf::Keyboard::Key::F)
                {
                    scene.SpawnFood({RandomInRange(bounds.x), RandomInRange(bounds.y)});
                }
                else if (keyPressed->code == sf::Keyboard::Key::W)
                {
                    scene.SpawnWeed({RandomInRange(bounds.x), bounds.y});
                }
                else if (keyPressed->code == sf::Keyboard::Key::D)
                {
                    scene.SpawnDecoration({RandomInRange(bounds.x), bounds.y});
                }
                else if (keyPressed->code == sf::Keyboard::Key::E)
                {
                    activeFormatIndex = (activeFormatIndex + 1) % reportCreators.size();
                    refreshHud(scene.ActiveBiomeName(), reportCreators[activeFormatIndex]->GetFormatName());
                }
                else if (keyPressed->code == sf::Keyboard::Key::R)
                {
                    const ReportBuilderCreator& creator = *reportCreators[activeFormatIndex];
                    auto builder = creator.CreateBuilder();
                    const std::string timestamp = CurrentTimestamp();
                    const std::string report =
                        reportDirector.BuildReport(*builder, scene.GetReportData(), timestamp);

                    std::filesystem::create_directories("Reports");
                    const std::string filename = "Reports/aquarium_report_" + timestamp +
                                                  "." + std::string(creator.GetFileExtension());
                    std::ofstream file(filename);
                    file << report;
                }
            }
        }

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