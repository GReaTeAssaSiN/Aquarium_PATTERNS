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
// Defined in creatures/Fish.h; forward-declared so AsFish() below doesn't
// need the full definition (a pointer type is enough).
class Fish;

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

    // Live equivalent of CollectFishInfo: appends actual Fish* pointers (not
    // snapshots) that Scene can act on - eat, remove, etc. A single Fish
    // appends itself; a Shoal appends each of its members.
    virtual void CollectFish(std::vector<Fish*>& out) = 0;

    // Composite child-management, transparently on the base interface (GoF's
    // "transparent" Composite style): tries to remove `target` from this
    // entity's own children and reports whether it was found here. A leaf
    // (Fish) has no children, so it's always false. A Shoal searches its
    // members_ and erases a match. Lets Scene::RemoveEntity reach a fish
    // nested inside a Shoal without needing to know that's where it lives.
    virtual bool RemoveMember(AquaticEntity*) { return false; }
};

#endif // AQUATIC_ENTITY_H_