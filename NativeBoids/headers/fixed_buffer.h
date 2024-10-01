#ifndef FIXED_BUFFER_H
#define FIXED_BUFFER_H

#include <cstdint>
#include <vector>
#include <tuple>

using namespace std;

namespace Game
{
    template <typename T>
    using has_equal_to = decltype(std::declval<T>() == std::declval<T>());

    template <typename T,
        typename = enable_if_t<is_constructible<bool, has_equal_to<T>>::value>>
    struct FixedBuffer
    {
    public:
        FixedBuffer(uint32_t capacity)
        {
            this->capacity = capacity;
            this->head = (T*)malloc(sizeof(T) * capacity);
            this->freeIndices.reserve(capacity - 1);
            
            // The first index will always be considered null
            for (int32_t i = (int32_t)capacity - 1; i > 0; i--)
            {
                freeIndices.push_back(i);
            }
        }

        ~FixedBuffer()
        {
            free(this->head);
        }

        void Flush()
        {
            freeIndices.clear();
            for (int32_t i = (int32_t)capacity - 1; i > 0; i--)
            {
                freeIndices.push_back(i);
            }
        }

        tuple<bool, T> At(uint32_t handle)
        {
            if (handle >= capacity)
            {
                return make_tuple(false, T());
            }
            return make_tuple(true, this->head[handle]);
        }

        uint32_t Push(T value)
        {
            if (freeIndices.size() == 0)
            {
                return 0;
            }

            auto freeIndexIt = this->freeIndices.end() - 1;
            uint32_t freeIndex = *freeIndexIt;
            this->freeIndices.erase(freeIndexIt);
            this->head[freeIndex] = value;
            return freeIndex;
        }

        void RemoveAt(uint32_t handle)
        {
            this->head[handle] = T();
            this->freeIndices.push_back(handle);
        }

        uint32_t Length()
        {
            return this->capacity - this->freeIndices.size() - 1;
        }

        uint32_t Capacity()
        {
            return this->capacity;
        }
    private:
        T* head;
        uint32_t capacity;
        vector<uint32_t> freeIndices;
    };
}

#endif
