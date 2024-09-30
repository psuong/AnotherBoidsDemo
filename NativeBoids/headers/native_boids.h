#ifndef NATIVE_BOIDS_H
#define NATIVE_BOIDS_H

#include <cstdint>
#include "simple_logger.h"

namespace Game {

    class BoidsManager {
    public:
        BoidsManager();
        ~BoidsManager();
        void Init(int32_t capacity);
    private:
        Logger* logger;
    };
}

#endif // !NATIVE_BOIDS_H
