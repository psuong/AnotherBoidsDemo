#include <catch2/catch_test_macros.hpp>

int AddStuff(int a, int b) {
    return a + b;
}

TEST_CASE( "Basic Ass Test", "[adding]") {
    REQUIRE(AddStuff(1, 1) == 2);
}