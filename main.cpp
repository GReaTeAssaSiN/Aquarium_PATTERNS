#include <SFML/Graphics.hpp>
#include <array>
#include <cstdlib>
#include <string>

#include "core/Scene.h"
#include "factories/DeepSeaFactory.h"
#include "factories/FreshwaterFactory.h"
#include "factories/ReefFactory.h"

namespace
{
std::string MakeTitle(const char* biomeName)
{
    return "Aquarium Ecosystem Simulator - " + std::string(biomeName) +
           " (B: switch biome, Space: fish, F: food, W: weed, D: decoration)";
}

float RandomInRange(float max)
{
    return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * max;
}
}

int main()
{
    const Vector2 bounds{800.f, 600.f};
    sf::RenderWindow window(
        sf::VideoMode({static_cast<unsigned>(bounds.x), static_cast<unsigned>(bounds.y)}),
        "Aquarium Ecosystem Simulator");
    window.setFramerateLimit(60);

    FreshwaterFactory freshwaterFactory;
    ReefFactory reefFactory;
    DeepSeaFactory deepSeaFactory;
    const std::array<const AquariumFactory*, 3> biomes{
        &freshwaterFactory, &reefFactory, &deepSeaFactory};
    std::size_t activeBiomeIndex = 0;

    Scene scene(bounds, *biomes[activeBiomeIndex]);
    scene.SpawnFish(Species::Common, {200.f, 200.f});
    scene.SpawnFish(Species::Predator, {500.f, 350.f});
    scene.SpawnFish(Species::Prey, {300.f, 450.f});
    scene.SpawnFood({400.f, 100.f});
    scene.SpawnWeed({100.f, bounds.y});
    scene.SpawnWeed({700.f, bounds.y});
    scene.SpawnDecoration({300.f, bounds.y});
    scene.SpawnDecoration({600.f, bounds.y});

    window.setTitle(MakeTitle(scene.ActiveBiomeName()));

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::B)
                {
                    activeBiomeIndex = (activeBiomeIndex + 1) % biomes.size();
                    scene.SwitchBiome(*biomes[activeBiomeIndex]);
                    window.setTitle(MakeTitle(scene.ActiveBiomeName()));
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
            }
        }

        const float dt = clock.restart().asSeconds();
        scene.Update(dt);

        window.clear(sf::Color(10, 40, 80));
        scene.Draw(window);
        window.display();
    }

    return 0;
}