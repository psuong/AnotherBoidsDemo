#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <fmt/core.h>
#include <cstdint>
#include "../headers/simple_logger.h"
#include "../headers/fixed_buffer.h"

using namespace Game;
using namespace std;

bool FileExists(const string& fileName)
{
    ifstream file(fileName);
    bool good = file.good();
    file.close();
    return good;
}

uint16_t CountLines(const string& fileName)
{
    ifstream file(fileName);
    return count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n');
}

TEST_CASE("Logger Tests", "[loggers]")
{
    const string boidsLog = "boids.log";
    Logger& logger = Logger::Instance();
    REQUIRE(FileExists(boidsLog));
    REQUIRE(CountLines(boidsLog) == 0);
    logger.Log(LogLevel::INFO, "An entry was logged!");
    REQUIRE(CountLines(boidsLog) == 1);
    for (int i = 0; i < 4; i++)
    {
        LogLevel level = (LogLevel)i;
        logger.Log(level, fmt::format("%d", i));
    }
    REQUIRE(CountLines(boidsLog) == 5);
}

struct A
{
public:
    int16_t x;
    int16_t y;
    A() : x(), y() { }
    A(int16_t x, int16_t y) {
        this->x = x;
        this->y = y;
    }

    bool operator==(const A& other) const {
        return other.x == this->x && other.y == this->y;
    }
};

TEST_CASE("Fixed Buffer Tests", "[fixed-buffers]")
{
    uint32_t capacity = 32;
    FixedBuffer<A> buffer(32);
    REQUIRE(buffer.Capacity() == 32);
    REQUIRE(buffer.Length() == 0);
    A value(16, 32);
    uint32_t handle = buffer.Push(value);
    REQUIRE(handle == 1);
    REQUIRE(buffer.Length() == 1);

    auto [success, retVal] = buffer.At(handle);
    REQUIRE(success);
    REQUIRE(value == retVal);

    // Adding a second value
    uint32_t secondHandle = buffer.Push(value);
    REQUIRE(secondHandle == 2);
    REQUIRE(buffer.Length() == 2);

    // Remove the first handle
    buffer.RemoveAt(handle);
    REQUIRE(buffer.Length() == 1);

    buffer.Flush();
    REQUIRE(buffer.Length() == 0);

    for (uint32_t i = 0; i < buffer.Capacity() - 1; i++)
    {
        REQUIRE(i + 1 == buffer.Push(A()));
    }

    REQUIRE(0 == buffer.Push(A()));
}
