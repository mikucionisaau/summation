#include "sum/sum.hpp"
#include <eve/module/core.hpp> // plus
#include <eve/module/algo.hpp> // reduce

/** Computes a sum of numbers using eve::algo::reduce (SIMD) */
double sum(const std::vector<double>& inp)
{
    return eve::algo::reduce(inp, std::pair{eve::plus, 0.}, 0.);
}
