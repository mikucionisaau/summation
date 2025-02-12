#include "sum/sum.hpp"
#include "sum/output.hpp" // operator<<(ostream, vector<double>)

#include <doctest/doctest.h>

#include <iostream>
#include <algorithm> // permutation
#include <numeric> // iota
#include <numbers> // pi
#include <cmath> // fabs
#include <cassert> // assert

TEST_SUITE_BEGIN("Summation");

TEST_CASE("Empty list")
{
    const auto inp = std::vector<double>{};
    CHECK(sum(inp) == 0);
}

TEST_CASE("One value")
{
    const auto inp = std::vector{std::numbers::pi};
    CHECK(sum(inp) == std::numbers::pi);
}

TEST_CASE("Two values")
{
    const auto inp = std::vector{3.141, 2.718};
    CHECK(sum(inp) == 5.859);
}

TEST_CASE("Ten 0.1 values")
{
    const auto inp = std::vector(10, 0.1);
    CHECK(sum(inp) == 1);
}

TEST_CASE("Arithmetic increasing sequence")
{
    const auto inp = std::vector{0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 };
    CHECK(sum(inp) == 4.5);
}

TEST_CASE("Arithmetic decreasing sequence")
{
    const auto inp = std::vector{0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1};
    CHECK(sum(inp) == 4.5);
}

TEST_CASE("Geometric increasing sequence")
{
    const auto inp = std::vector{0.1, 0.2, 0.4, 0.8, 1.6, 3.2, 6.4, 12.8, 25.6};
    CHECK(sum(inp) == 51.1);
}

TEST_CASE("Geometric decreasing sequence")
{
    const auto inp = std::vector{25.6, 12.8, 6.4, 3.2, 1.6, 0.8, 0.4, 0.2, 0.1};
    CHECK(sum(inp) == 51.1);
}

TEST_SUITE_END();
