#ifndef FRESHWATER_FACTORY_H_
#define FRESHWATER_FACTORY_H_

#include <unordered_map>

#include "factories/AquariumFactory.h"

// Concrete factory producing the Freshwater biome family of products.
// Singleton: only one instance exists, reachable via GetInstance().
// Creates products by cloning pre-built prototypes (Prototype pattern)
// instead of constructing them directly.
class FreshwaterFactory : public AquariumFactory
{
public:
    static FreshwaterFactory& GetInstance();

    FreshwaterFactory(const FreshwaterFactory&) = delete;
    FreshwaterFactory& operator=(const FreshwaterFactory&) = delete;

    std::unique_ptr<Fish> MakeFish(Species species, Vector2 position) const override;
    std::unique_ptr<Food> MakeFood(Vector2 position) const override;
    std::unique_ptr<Weed> MakeWeed(Vector2 position) const override;
    std::unique_ptr<Decoration> MakeDecoration(Vector2 position) const override;

    const char* GetName() const override { return "Freshwater"; }

protected:
    FreshwaterFactory();

private:
    static FreshwaterFactory* instance_;

    std::unordered_map<Species, std::unique_ptr<Fish>> fishPrototypes_;
    std::unique_ptr<Food> foodPrototype_;
    std::unique_ptr<Weed> weedPrototype_;
    std::unique_ptr<Decoration> decorationPrototype_;
};

#endif // FRESHWATER_FACTORY_H_
