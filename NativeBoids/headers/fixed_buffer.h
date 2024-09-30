#ifndef ENTITY_BUFFER_H
#define ENTITY_BUFFER

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