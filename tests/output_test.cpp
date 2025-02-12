#include "sum/output.hpp"

#include "doctest/doctest.h"

#include <sstream> // ostringstream

TEST_CASE("output of std::vector<double>")
{
    auto os = std::ostringstream{};
    SUBCASE("empty vector")
    {
        os << std::vector<double>{};
        const auto res = os.str();
        CHECK(res == "");
    }
    SUBCASE("one element")
    {
        os << std::vector{1.0};
        const auto res = os.str();
        CHECK(res == "1");
    }
    SUBCASE("two elements")
    {
        os << std::vector{1.0, 2.0};
        const auto res = os.str();
        CHECK(res == "1, 2");
    }
    SUBCASE("several elements")
    {
        os << std::vector{1.0, 2.0, 3.0, 4.0, 5.0};
        const auto res = os.str();
        CHECK(res == "1, 2, 3, 4, 5");
    }
}
