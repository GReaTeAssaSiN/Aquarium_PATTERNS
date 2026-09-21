#ifndef SCENE_H_
#define SCENE_H_

#include <memory>
#include <vector>

#include "builders/ReportData.h"
#include "composite/Shoal.h"
#include "core/AquaticEntity.h"
#include "core/Vector2.h"
#include "creatures/Decoration.h"
#include "creatures/Fish.h"
#include "creatures/Food.h"
#include "creatures/Weed.h"
#include "factories/AquariumFactory.h"

// Client of AquariumFactory: creates and owns aquarium inhabitants
// without knowing their concrete classes.
class Scene
{
public:
    Scene(Vector2 bounds, const AquariumFactory& initialFactory);

    // Rescales every existing inhabitant's position to fit the new bounds
    // proportionally, then adopts the new bounds for future spawns/updates.
    void HandleResize(Vector2 newBounds);
    void SwitchBiome(const AquariumFactory& factory);
    const char* ActiveBiomeName() const { return activeFactory_->GetName(); }
    const AquariumFactory& GetActiveFactory() const { return *activeFactory_; }

    // Each Spawn* returns the created object so a Command (Lab 7) can later
    // remove that exact instance again via the matching Remove*.
    Fish* SpawnFish(Species species, Vector2 position);
    Shoal* SpawnShoal(Species species, Vector2 center, int count);
    Food* SpawnFood(Vector2 position);
    Weed* SpawnWeed(Vector2 position);
    Decoration* SpawnDecoration(Vector2 position);

    void RemoveEntity(AquaticEntity* entity); // removes a Fish or a Shoal
    void RemoveFood(Food* food);
    void RemoveWeed(Weed* weed);
    void RemoveDecoration(Decoration* decoration);

    void Update(float dt);
    void Draw(sf::RenderWindow& window) const;

    ReportData GetReportData() const;

private:
    Vector2 bounds_;
    const AquariumFactory* activeFactory_;
    std::vector<std::unique_ptr<AquaticEntity>> entities_;
    std::vector<std::unique_ptr<Food>> food_;
    std::vector<std::unique_ptr<Weed>> weed_;
    std::vector<std::unique_ptr<Decoration>> decoration_;
};

#endif // SCENE_H_