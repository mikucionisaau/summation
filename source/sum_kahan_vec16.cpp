#include "sum/sum.hpp"
#include "kahan.hpp"

double sum(const std::vector<double>& inp)
{
    auto res = KahanSum{};
    auto i = std::size_t{0};
    for (; i+15 < inp.size(); i += 16) {
        auto s1 = KahanSum{inp[i], inp[i+1]};
        auto s2 = KahanSum{inp[i+2], inp[i+3]};
        auto s3 = KahanSum{inp[i+4], inp[i+5]};
        auto s4 = KahanSum{inp[i+6], inp[i+7]};
        auto s5 = KahanSum{inp[i+8], inp[i+9]};
        auto s6 = KahanSum{inp[i+10], inp[i+11]};
        auto s7 = KahanSum{inp[i+12], inp[i+13]};
        auto s8 = KahanSum{inp[i+14], inp[i+15]};
        s1 += s2;
        s3 += s4;
        s5 += s6;
        s7 += s8;
        s1 += s3;
        s5 += s7;
        s1 += s5;
        res += s1;
    }
    for (; i < inp.size(); ++i)
        res += inp[i];
    return res;
}
