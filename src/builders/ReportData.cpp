#include "builders/ReportData.h"

#include <iomanip>
#include <sstream>

const char* SpeciesName(Species species)
{
    switch (species)
    {
        case Species::Predator: return "Predator";
        case Species::Prey: return "Prey";
        default: return "Common";
    }
}

std::string FormatCoordinate(float value)
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << value;
    return stream.str();
}
