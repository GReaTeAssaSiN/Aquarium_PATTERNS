#ifndef AQUATIC_ENTITY_H_
#define AQUATIC_ENTITY_H_

#include <vector>

#include <SFML/Graphics.hpp>

#include "core/Vector2.h"

// Defined in builders/ReportData.h. Only forward-declared here (not included)
// to avoid a cycle: ReportData.h -> Fish.h -> AquaticEntity.h -> ReportData.h.
struct FishInfo;
// Defined in chain/FishContext.h; forward-declared for the same reason
// (FishContext.h -> ReportData.h -> Fish.h -> AquaticEntity.h -> FishContext.h).
struct FishContext;

// Component of the Composite: implemented by both a single Fish (leaf)
// and a Shoal (composite), so Scene can treat either one uniformly.
class AquaticEntity
{
public:
    virtual ~AquaticEntity() = default;

    virtual void Update(float dt, const FishContext& context) = 0;
    virtual void Draw(sf::RenderWindow& window) const = 0;

    virtual void RescalePosition(float scaleX, float scaleY) = 0;
    virtual void CollectFishInfo(std::vector<FishInfo>& out) const = 0;
};

#endif // AQUATIC_ENTITY_H_