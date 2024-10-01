#include "../headers/native_boids.h"
#include "../headers/fixed_buffer.h"
#include <fmt/core.h>
#include <glm/gtc/quaternion.hpp>

namespace Game {

    BoidsManager::BoidsManager(uint32_t capacity)
    {
        string msg = fmt::format("Initializing the internal capacity to {}.", capacity);
        this->logger = &Logger::Instance();
        this->logger->Log(LogLevel::INFO, msg);

        this->entities = new FixedBuffer<BoidEntity>(capacity);
        this->transforms = new FixedBuffer<Transform>(capacity);
    }

    BoidsManager::~BoidsManager()
    {
        this->logger->Log(LogLevel::DEBUG, "Releasing boids manager");
        delete this->entities;
        delete this->transforms;
    }

    uint32_t BoidsManager::RequestEntity(vec3 position, vec3 eulerRotation)
    {
        // Do this in reverse order so we get a valid handle
        quat rotation(eulerRotation);
        uint32_t handle = this->transforms->Push(Transform(position, rotation));
        this->entities->Push(BoidEntity(0, handle));
        return handle;
    }
}
