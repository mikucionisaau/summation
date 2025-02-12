#include "sum/sum.hpp"
#include <functional> // plus
#include <numeric> // reduce
#include <execution> // par_unseq

/** Computes a sum of numbers using std::reduce with parallel execution policy */
double sum(const std::vector<double>& inp)
{
    return std::reduce(std::execution::par_unseq,
                       inp.begin(), inp.end(), 0., std::plus<>{});
}
