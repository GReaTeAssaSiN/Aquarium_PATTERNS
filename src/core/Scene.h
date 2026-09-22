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

    // Removes a Fish or a Shoal. If `entity` isn't a top-level entity (e.g. a
    // Fish grouped into a Shoal), falls back to asking each entity to remove
    // it from its own children (AquaticEntity::RemoveMember). Returns false
    // if `entity` wasn't found anywhere - e.g. a Command's Undo() calling
    // this on a fish the ecosystem already ate itself.
    bool RemoveEntity(AquaticEntity* entity);
    bool RemoveFood(Food* food);
    bool RemoveWeed(Weed* weed);
    bool RemoveDecoration(Decoration* decoration);

    void Update(float dt);
    void Draw(sf::RenderWindow& window) const;

    ReportData GetReportData() const;

private:
    // Fish eat same-biome food and predators eat non-predator fish on contact,
    // whether the fish is a top-level entity or grouped into a Shoal - the
    // caller (Update) already collected every live Fish* via CollectFish.
    void HandleEating(const std::vector<Fish*>& allFish);

    // True if a fish at this position is close enough to any weed to count
    // as hidden (matches WeedHidingHandler's own shelter radius). Hidden
    // fish are excluded from hunting (FishContext::huntablePrey) and from
    // eating (HandleEating) - otherwise WeedHidingHandler's "swim to weed"
    // would be pure decoration with no actual protection.
    bool IsSheltered(Vector2 position) const;

    Vector2 bounds_;
    const AquariumFactory* activeFactory_;
    std::vector<std::unique_ptr<AquaticEntity>> entities_;
    std::vector<std::unique_ptr<Food>> food_;
    std::vector<std::unique_ptr<Weed>> weed_;
    std::vector<std::unique_ptr<Decoration>> decoration_;
};

#endif // SCENE_H_