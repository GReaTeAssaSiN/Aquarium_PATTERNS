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
};

struct ReportData
{
    std::string biomeName;
    std::vector<FishInfo> fish;
    std::size_t foodCount = 0;
    std::size_t weedCount = 0;
    std::size_t decorationCount = 0;
};

const char* SpeciesName(Species species);
std::string FormatCoordinate(float value);

#endif // REPORT_DATA_H_
