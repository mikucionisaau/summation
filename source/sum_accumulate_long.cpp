#include "sum/sum.hpp"
#include <numeric> // accumulate
#include <functional> // plus

/** Computes a sum of numbers using std::accumulate */
double sum(const std::vector<double>& inp)
{
    long double res = 0;
    res = std::accumulate(inp.begin(), inp.end(), res, std::plus<>{});
    return res;
}
