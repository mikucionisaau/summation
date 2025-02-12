#include "sum/sum.hpp"

/** Computes a sum of numbers using vectorization of 2 */
double sum(const std::vector<double>& inp)
{
    auto res = double{0};
    auto i = std::size_t{0};
    for (; i+1 < inp.size(); i += 2) {
        auto s = inp[i+0] + inp[i+1];
        res += s;
    }
    for (; i < inp.size(); ++i)
        res += inp[i];
    return res;
}
