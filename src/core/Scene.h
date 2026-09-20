#ifndef SCENE_H_
#define SCENE_H_

#include <memory>
#include <vector>

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

    void SwitchBiome(const AquariumFactory& factory);
    const char* ActiveBiomeName() const { return activeFactory_->GetName(); }

    void SpawnFish(Species species, Vector2 position);
    void SpawnFood(Vector2 position);
    void SpawnWeed(Vector2 position);
    void SpawnDecoration(Vector2 position);

    void Update(float dt);
    void Draw(sf::RenderWindow& window) const;

private:
    Vector2 bounds_;
    const AquariumFactory* activeFactory_;
    std::vector<std::unique_ptr<Fish>> fish_;
    std::vector<std::unique_ptr<Food>> food_;
    std::vector<std::unique_ptr<Weed>> weed_;
    std::vector<std::unique_ptr<Decoration>> decoration_;
};

#endif // SCENE_H_