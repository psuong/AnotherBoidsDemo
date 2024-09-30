#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace std;
using namespace glm;

namespace Game {

    struct Entity {
    public:
        int32_t handle;
    };

    struct Transform {
    public:
        vec3 position;
        quat rotation;
    };
}

#endif
