#include "sum/sum.hpp"

double sum(const std::vector<double>& inp)
{
    auto res = double{0};
    auto i = std::size_t{0};
    for (; i+7 < inp.size(); i += 8) {
        auto s1 = inp[i+0] + inp[i+1];
        auto s2 = inp[i+2] + inp[i+3];
        auto s3 = inp[i+4] + inp[i+5];
        auto s4 = inp[i+6] + inp[i+7];
        s1 += s2;
        s3 += s4;
        s1 += s3;
        res += s1;
    }
    for (; i < inp.size(); ++i)
        res += inp[i];
    return res;
}
