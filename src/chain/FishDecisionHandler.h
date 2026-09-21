#ifndef FISH_DECISION_HANDLER_H_
#define FISH_DECISION_HANDLER_H_

#include <memory>

#include "chain/FishContext.h"
#include "creatures/Fish.h"

// Handler: each concrete handler decides "is this my case?" (CanHandle) and,
// if so, "which direction should the fish move?" (Decide). Handle() itself
// just walks the chain until one of them says yes — concrete handlers never
// deal with forwarding themselves.
class FishDecisionHandler
{
public:
    virtual ~FishDecisionHandler() = default;
    void SetNext(std::unique_ptr<FishDecisionHandler> next) { next_ = std::move(next); }

    Vector2 Handle(const Fish& fish, const FishContext& context) const
    {
        if (CanHandle(fish, context))
            return Decide(fish, context);
        if (next_)
            return next_->Handle(fish, context);
        return {0.f, 0.f};
    }

protected:
    virtual bool CanHandle(const Fish& fish, const FishContext& context) const = 0;
    virtual Vector2 Decide(const Fish& fish, const FishContext& context) const = 0;

private:
    std::unique_ptr<FishDecisionHandler> next_;
};

#endif // FISH_DECISION_HANDLER_H_
