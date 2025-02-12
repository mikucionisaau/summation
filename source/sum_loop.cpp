#include "sum/sum.hpp"

/** Computes the sum of numbers using simple loop */
double sum(const std::vector<double>& inp)
{
    auto res = double{0};
    for (auto&& n : inp)
        res += n;
    return res;
}
