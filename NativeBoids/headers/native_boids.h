#ifndef NATIVE_BOIDS_H
#define NATIVE_BOIDS_H

#include <cstdint>
#include <vector>
#include "simple_logger.h"
#include "fixed_buffer.h"
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace std;
using namespace glm;

namespace Game {

    struct BoidEntity {
    public:
        BoidEntity() : generation(), handle() { }
        BoidEntity(uint32_t generation, uint32_t handle) : generation(generation), handle(handle) { }
        uint32_t generation;
        uint32_t handle;

        bool operator==(const BoidEntity& other) const {
            return other.generation == this->generation && other.handle == this->handle;
        }
    };

    struct Transform {
    public:
        Transform() : position(), rotation() { }
        Transform(vec3 position, quat rotation) : position(position), rotation(rotation) { }
        vec3 position;
        quat rotation;

        bool operator==(const Transform& other) {
            return other.position == this->position && other.rotation == this->rotation;
        }
    };

    class BoidsManager {
    public:
        BoidsManager(uint32_t capacity);
        ~BoidsManager();
        uint32_t RequestEntity(vec3 position, vec3 eulerRotation);
    private:
        Logger* logger;

        // For now just have a fixed buffer size we initialize
        FixedBuffer<BoidEntity>* entities;
        FixedBuffer<Transform>* transforms;
    };
}

#endif
