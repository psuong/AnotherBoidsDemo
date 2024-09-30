#include "../headers/fixed_buffer.h"
#include "../headers/simple_logger.h"
#include <algorithm>
#include <cstdint>
#include <vector>
#include <fmt/core.h>

using namespace std;

namespace Game {

    template <typename T>
    uint32_t FixedBuffer<T>::Length() {
        return 0;
    }

    template<typename T>
    FixedBuffer<T>::FixedBuffer(uint32_t capacity)
    {
        this->head = malloc(sizeof(T) * capacity);
        this->freeIndices = vector(capacity);

        for (uint32_t i = 0; i < capacity; i++)
        {
            freeIndices.push_back(i);
        }
    }

    template<typename T>
    FixedBuffer<T>::~FixedBuffer()
    {
        ~freeIndices();
    }

    template <typename T>
    void FixedBuffer<T>::Push(T value) {
        if (freeIndices.empty())
        {
            Logger::Instance().Log(LogLevel::INFO, "Buffer capacity has been hit.")
            return;
        }

        this->head[this->counter] = value;
        auto begin = freeIndices.begin();
        auto it = find(begin, freeIndices.end(), counter);
        freeIndices.erase(it);

        this->counter++;
    }

    template<typename T>
    void FixedBuffer<T>::RemoveAt(uint32_t handle)
    {
        this->head[handle] = default(T);
        freeIndices.push_back(handle);
    }
}