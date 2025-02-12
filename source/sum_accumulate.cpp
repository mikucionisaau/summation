#include "sum/sum.hpp"
#include <numeric> // accumulate
#include <functional> // plus

/** Computes a sum of numbers using std::accumulate */
double sum(const std::vector<double>& inp)
{
    return std::accumulate(inp.begin(), inp.end(), 0.0, std::plus<>{});
}
