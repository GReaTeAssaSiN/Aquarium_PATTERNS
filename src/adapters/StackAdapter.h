#ifndef STACK_ADAPTER_H_
#define STACK_ADAPTER_H_

#include <cstddef>
#include <utility>
#include <vector>

// Adapter: narrows std::vector's wide interface down to strict LIFO
// push/pop, so client code cannot accidentally use it as anything else.
template <typename T>
class StackAdapter
{
public:
    void Push(T value) { data_.push_back(std::move(value)); }

    T Pop()
    {
        T value = std::move(data_.back());
        data_.pop_back();
        return value;
    }

    const T& Top() const { return data_.back(); }
    bool IsEmpty() const { return data_.empty(); }
    std::size_t Size() const { return data_.size(); }

private:
    std::vector<T> data_;
};

#endif // STACK_ADAPTER_H_
