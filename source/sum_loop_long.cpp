#include "sum/sum.hpp"

/** Computes the sum of numbers using simple loop and quadruple precision */
double sum(const std::vector<double>& inp)
{
    long double res = 0;
    for (auto&& n : inp)
        res += n;
    return static_cast<double>(res);
}
