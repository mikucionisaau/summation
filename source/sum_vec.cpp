#include "sum/sum.hpp"

double sum(const std::vector<double>& inp)
{
    auto res = double{0};
    auto i = std::size_t{0};
    for (; i+15 < inp.size(); i += 16) {
        auto s1 = inp[i+0] + inp[i+1];
        auto s2 = inp[i+2] + inp[i+3];
        auto s3 = inp[i+4] + inp[i+5];
        auto s4 = inp[i+6] + inp[i+7];
        auto s5 = inp[i+8] + inp[i+9];
        auto s6 = inp[i+10] + inp[i+11];
        auto s7 = inp[i+12] + inp[i+13];
        auto s8 = inp[i+14] + inp[i+15];
        s1 += s2;
        s3 += s4;
        s5 += s6;
        s7 += s8;
        s1 += s3;
        s5 += s7;
        s1 += s5;
        res += s1;
    }
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
    for (; i+3 < inp.size(); i += 4) {
        auto s1 = inp[i+0] + inp[i+1];
        auto s2 = inp[i+2] + inp[i+3];
        s1 += s2;
        res += s1;
    }
    for (; i+1 < inp.size(); i += 2) {
        auto s = inp[i+0] + inp[i+1];
        res += s;
    }
    for (; i < inp.size(); ++i)
        res += inp[i];
    return res;
}
