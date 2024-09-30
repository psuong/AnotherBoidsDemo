#ifndef FIXED_BUFFER_H
#define FIXED_BUFFER_H

#include <cstdint>
#include <vector>

using namespace std;

namespace Game {

    template <typename T>
    struct FixedBuffer {
    public:
        FixedBuffer(uint32_t capacity);
        ~FixedBuffer();
        void Push(T value);
        void RemoveAt(uint32_t handle);
        uint32_t Length();
    private:
        T* head;
        uint32_t counter;
        vector<uint32_t> freeIndices;
    };
}

#endif