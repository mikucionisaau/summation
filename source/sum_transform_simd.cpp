#include "sum/sum.hpp"
#include <eve/module/core.hpp> // plus
#include <eve/module/algo.hpp> // transform
#include <span>

/** Computes a sum of numbers using SIMD EVE library */
double sum(const std::vector<double>& data)
{
    if (data.empty())
        return 0;
    auto inp = data;
    auto size = inp.size();
    auto d = std::lldiv(size, 2);
    auto b = std::begin(inp);
    while (d.quot > 0) {
        auto xs = std::span{b, b + d.quot};
        auto ys = std::span{b + d.quot, b + 2*d.quot};
        eve::algo::transform_to(
            eve::views::zip(xs, ys), inp,
            [](auto xy) { return get<0>(xy) + get<1>(xy); });
        if (d.rem == 1)
            *b += inp[size - 1];
        size = d.quot;
        d = std::lldiv(size, 2);
    }
    return inp.front();
}
