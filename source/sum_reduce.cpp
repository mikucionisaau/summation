#include "sum/sum.hpp"
#include <functional> // plus
#include <numeric> // reduce

/** Computes a sum of numbers using std::reduce */
double sum(const std::vector<double>& inp)
{
    return std::reduce(inp.begin(), inp.end(), 0., std::plus<>{});
}
