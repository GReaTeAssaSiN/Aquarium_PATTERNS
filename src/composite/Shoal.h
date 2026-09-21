#ifndef SHOAL_H_
#define SHOAL_H_

#include <memory>
#include <vector>

#include "core/AquaticEntity.h"

// Composite: a group of AquaticEntity (usually Fish) that Scene treats
// exactly like a single one — every call here just forwards to each member.
class Shoal : public AquaticEntity
{
public:
    void Add(std::unique_ptr<AquaticEntity> entity);

    void Update(float dt, const FishContext& context) override;
    void Draw(sf::RenderWindow& window) const override;
    void RescalePosition(float scaleX, float scaleY) override;
    void CollectFishInfo(std::vector<FishInfo>& out) const override;

private:
    std::vector<std::unique_ptr<AquaticEntity>> members_;
};

#endif // SHOAL_H_
