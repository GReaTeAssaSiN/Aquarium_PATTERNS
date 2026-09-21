#ifndef FISH_CONTEXT_H_
#define FISH_CONTEXT_H_

#include <vector>

#include "builders/ReportData.h"
#include "core/Vector2.h"

// Snapshot of the whole aquarium's fish and food for this frame, handed to
// every fish's decision chain unfiltered. Each handler does its own distance
// check against the fish it was called for, so one shared FishContext
// correctly serves every fish, including ones nested inside a Shoal.
struct FishContext
{
    Vector2 bounds;
    std::vector<Vector2> predatorPositions;
    std::vector<Vector2> foodPositions;
    std::vector<Vector2> weedPositions;
    std::vector<FishInfo> neighbors; // every fish in the aquarium (species+position+heading)
};

#endif // FISH_CONTEXT_H_
