#ifndef FISH_CONTEXT_H_
#define FISH_CONTEXT_H_

#include <string>
#include <vector>

#include "builders/ReportData.h"
#include "core/Vector2.h"

// A food item's position plus which biome family it belongs to, so
// FoodNearbyHandler can tell whether a given fish may eat it.
struct FoodInfo
{
    Vector2 position;
    std::string biomeName;
};

// Snapshot of the whole aquarium's fish and food for this frame, handed to
// every fish's decision chain unfiltered. Each handler does its own distance
// (and, for food, biome) check against the fish it was called for, so one
// shared FishContext correctly serves every fish, including ones nested
// inside a Shoal.
struct FishContext
{
    Vector2 bounds;
    // Predators are deliberately NOT biome-filtered: a predator can hunt
    // any fish regardless of biome, so prey must be able to detect (and
    // flee from) any predator too, not just ones from its own biome.
    std::vector<Vector2> predatorPositions;
    std::vector<FoodInfo> food;
    std::vector<Vector2> weedPositions;
    std::vector<FishInfo> neighbors; // every fish in the aquarium (species+position+heading)
    // Non-predator fish a predator could actually eat on contact - unlike
    // `neighbors`, this excludes fish grouped into a Shoal (Scene::HandleEating
    // can't reach them), so HuntPreyHandler never chases a target it can never
    // catch.
    std::vector<Vector2> huntablePrey;
};

#endif // FISH_CONTEXT_H_
