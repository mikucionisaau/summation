#include "sum/sum.hpp"
#include "kahan.hpp"

double sum(const std::vector<double>& inp)
{
    auto res = KahanSum<long double>{};
    for (auto& n : inp)
        res += n;
    return res;
}
