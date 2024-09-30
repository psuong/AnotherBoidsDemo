#include "../headers/native_boids.h"
#include <fmt/core.h>

namespace Game {
    BoidsManager::BoidsManager()
    {
        this->logger = new Logger("game.log");
    }

    BoidsManager::~BoidsManager()
    {
        this->logger->~Logger();
    }

    void BoidsManager::Init(int32_t capacity) {
        string msg = fmt::format("Initializing the internal capacity to {}.", capacity);
        this->logger->Log(LogLevel::INFO, msg);
    }
}
