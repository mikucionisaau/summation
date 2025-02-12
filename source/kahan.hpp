#ifndef SUM_KAHAN_HPP
#define SUM_KAHAN_HPP

/// Kahan's online summation algorithm wrapped into a struct
template <typename T = double>
struct KahanSum
{
    static_assert(std::is_floating_point_v<T>, "only floating point types are supported");
    KahanSum() = default;
    KahanSum(T value): sum{value} {}  // conversion op.
    KahanSum(T val1, T val2): sum{val1} { *this += val2; }
    operator T() const { return sum + carry; }  // conversion op.
    KahanSum& operator+=(T number)
    {
        number -= carry;
        volatile auto t = sum + number;
        volatile auto t2 = t - sum;
        carry = t2 - number;
        sum = t;
        return *this;
    }
    KahanSum& operator+=(const KahanSum& other)
    {
        sum += other.sum;
        carry += other.carry;
        return *this;
    }
    KahanSum operator+(const KahanSum& other)
    {
        auto res = *this;  // create a copy
        res += other;
        return res;
    }

private:
    T sum{0}, carry{0};
};

#endif  // SUM_KAHAN_HPP
