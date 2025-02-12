#include "sum/sum.hpp"

double sum(const std::vector<double>& inp)
{
    auto res = double{0};
    auto i = std::size_t{0};
    for (; i+3 < inp.size(); i += 4) {
        auto s1 = inp[i+0] + inp[i+1];
        auto s2 = inp[i+2] + inp[i+3];
        s1 += s2;
        res += s1;
    }
    for (; i < inp.size(); ++i)
        res += inp[i];
    return res;
}
