#include "creatures/Fish.h"

#include "builders/ReportData.h"

void Fish::CollectFishInfo(std::vector<FishInfo>& out) const
{
    out.push_back({species_, position_, GetFamilyName()});
}
