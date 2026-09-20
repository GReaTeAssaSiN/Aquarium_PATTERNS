#ifndef REEF_FACTORY_H_
#define REEF_FACTORY_H_

#include <unordered_map>

#include "factories/AquariumFactory.h"

// Concrete factory producing the Reef biome family of products.
// Singleton: only one instance exists, reachable via GetInstance().
// Creates products by cloning pre-built prototypes (Prototype pattern)
// instead of constructing them directly.
class ReefFactory : public AquariumFactory
{
public:
    static ReefFactory& GetInstance();

    ReefFactory(const ReefFactory&) = delete;
    ReefFactory& operator=(const ReefFactory&) = delete;

    std::unique_ptr<Fish> MakeFish(Species species, Vector2 position) const override;
    std::unique_ptr<Food> MakeFood(Vector2 position) const override;
    std::unique_ptr<Weed> MakeWeed(Vector2 position) const override;
    std::unique_ptr<Decoration> MakeDecoration(Vector2 position) const override;

    const char* GetName() const override { return "Reef"; }

protected:
    ReefFactory();

private:
    static ReefFactory* instance_;

    std::unordered_map<Species, std::unique_ptr<Fish>> fishPrototypes_;
    std::unique_ptr<Food> foodPrototype_;
    std::unique_ptr<Weed> weedPrototype_;
    std::unique_ptr<Decoration> decorationPrototype_;
};

#endif // REEF_FACTORY_H_
