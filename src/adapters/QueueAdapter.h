#ifndef QUEUE_ADAPTER_H_
#define QUEUE_ADAPTER_H_

#include <cstddef>
#include <list>
#include <utility>

// Adapter: narrows std::list's wide interface down to strict FIFO
// push/pop, so client code cannot accidentally use it as anything else.
template <typename T>
class QueueAdapter
{
public:
    void Push(T value) { data_.push_back(std::move(value)); }

    T Pop()
    {
        T value = std::move(data_.front());
        data_.pop_front();
        return value;
    }

    const T& Front() const { return data_.front(); }
    bool IsEmpty() const { return data_.empty(); }
    std::size_t Size() const { return data_.size(); }

private:
    std::list<T> data_;
};

#endif // QUEUE_ADAPTER_H_
