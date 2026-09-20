#ifndef REPORT_DATA_H_
#define REPORT_DATA_H_

#include <string>
#include <vector>

#include "core/Vector2.h"
#include "creatures/Fish.h"

// A snapshot of Scene's state, decoupled from the live Fish/Food/Weed/Decoration
// objects, so report builders never touch Scene's owned objects directly.
struct FishInfo
{
    Species species;
    Vector2 position;
    std::string biomeName;
};

// Per-biome breakdown: how many of each inhabitant currently belong to one family.
struct BiomeCounts
{
    std::string biomeName;
    std::size_t commonFish = 0;
    std::size_t predatorFish = 0;
    std::size_t preyFish = 0;
    std::size_t foodCount = 0;
    std::size_t weedCount = 0;
    std::size_t decorationCount = 0;
};

struct ReportData
{
    std::string activeBiomeName;
    std::vector<FishInfo> fish;
    std::vector<BiomeCounts> biomeCounts;
};

const char* SpeciesName(Species species);
std::string FormatCoordinate(float value);

#endif // REPORT_DATA_H_
