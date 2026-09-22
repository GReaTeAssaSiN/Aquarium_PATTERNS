#ifndef FISH_H_
#define FISH_H_

#include <memory>

#include <SFML/Graphics.hpp>
#include "core/AquaticEntity.h"
#include "core/Vector2.h"

enum class Species
{
    Common,
    Predator,
    Prey
};

// Abstract product of AquariumFactory; also a Composite leaf (AquaticEntity)
// that does the real work itself, unlike Shoal, which only delegates.
class Fish : public AquaticEntity
{
public:
    Fish(Species species, Vector2 position, float speed)
        : species_(species), position_(position), speed_(speed) {}
    virtual ~Fish() = default;

    // Defined in Fish.cpp: runs the decision chain (Chain of Responsibility),
    // then moves and wraps this fish accordingly. Shared by every concrete
    // fish — none of them override Update anymore.
    void Update(float dt, const FishContext& context) override;
    void Draw(sf::RenderWindow& window) const override = 0;
    // Prototype: returns a copy of this object placed at `position`.
    virtual std::unique_ptr<Fish> Clone(Vector2 position) const = 0;
    // Name of the biome family this concrete product belongs to (e.g. "Freshwater").
    virtual const char* GetFamilyName() const = 0;

    void RescalePosition(float scaleX, float scaleY) override
    {
        position_.x *= scaleX;
        position_.y *= scaleY;
    }
    // Defined in Fish.cpp, not here: the body needs the complete FishInfo type
    // (builders/ReportData.h), which this header cannot include (see AquaticEntity.h).
    void CollectFishInfo(std::vector<FishInfo>& out) const override;
    Fish* AsFish() override { return this; }

    Species GetSpecies() const { return species_; }
    Vector2 GetPosition() const { return position_; }
    void SetPosition(Vector2 position) { position_ = position; }
    Vector2 GetHeading() const { return heading_; }

protected:
    Species species_;
    Vector2 position_;
    Vector2 heading_{1.f, 0.f};
    float speed_;
};

#endif // FISH_H_
