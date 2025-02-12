#include "sum/sum.hpp"
#include "kahan.hpp"

double sum(const std::vector<double>& inp)
{
    auto res = KahanSum{};
    auto i = std::size_t{0};
    for (; i+7 < inp.size(); i += 8) {
        auto s1 = KahanSum{inp[i], inp[i+1]};
        auto s2 = KahanSum{inp[i+2], inp[i+3]};
        auto s3 = KahanSum{inp[i+4], inp[i+5]};
        auto s4 = KahanSum{inp[i+6], inp[i+7]};
        s1 += s2;
        s3 += s4;
        s1 += s3;
        res += s1;
    }
    for (; i < inp.size(); ++i)
        res += inp[i];
    return res;
}
