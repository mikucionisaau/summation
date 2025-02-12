#include "sum/sum.hpp"
#include <functional> // plus
#include <algorithm> // transform
#include <execution> // par_unseq

/** Computes a sum of numbers using std::transform with sequential execution policy */
double sum(const std::vector<double>& data)
{
    if (data.empty())
        return 0;
    auto inp = data;
    auto size = inp.size();
    auto d = std::lldiv(size, 2);
    auto b = std::begin(inp), e = std::end(inp);
    while (d.quot > 0) {
        std::transform(std::execution::seq,
                       b, b + d.quot, b + d.quot, b, std::plus<>{});
        if (d.rem == 1)
            *b += inp[size - 1];
        size = d.quot;
        d = std::lldiv(size, 2);
    }
    return inp.front();
}
