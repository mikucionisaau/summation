#include "sum/output.hpp"
#include "sum/sum.hpp"
#include <algorithm> // generate
#include <vector>
#include <random>
#include <iostream> // cout

/** Creates N floating values from interval [min,max)
 * @param N the number of values
 * @param min the minimal value
 * @param max the upper bound
 * @returns vector */
std::vector<double> make_data(size_t N, double min, double max)
{
    // pseudo random number generator seeded from true random device:
    static auto gen = std::default_random_engine{std::random_device{}()};
    auto dist = std::uniform_real_distribution{min, max};
    auto res = std::vector<double>{}; // empty container
    res.reserve(N + 3); // allocate array a bit bigger than needed (N) just for fun
    res.resize(N, 0); // resize from 0 to N by filling with zeroes
    std::ranges::generate(res, [&]{ return dist(gen); });
    return res;
}

int main()
{
    using namespace std; // import all symbols from std:: namespace
    cout << "sizeof(intptr_t): " << sizeof(intptr_t) << " bytes\n"; // integer of pointer size
    cout << "sizeof(int*): " << sizeof(int*) << " bytes\n"; // pointer
    cout << "sizeof(int): " << sizeof(int) << " bytes\n"; // integer
    cout << "sizeof(double): " << sizeof(double) << " bytes\n"; // double precision floating point
    cout << "sizeof(vector<int>): " << sizeof(vector<int>) << " bytes\n";
    cout << "sizeof(vector<int>::value_type): " << sizeof(vector<int>::value_type) << " bytes\n";
    cout << "sizeof(vector<double>): " << sizeof(vector<double>) << " bytes\n";
    cout << "sizeof(vector<double>::value_type): " << sizeof(vector<double>::value_type) << " bytes\n";
    auto vd = make_data(10, -1, 1);
    cout << "sizeof(vd): " << sizeof(vd) << " bytes\n";
    cout << "vd.capacity(): " << vd.capacity() << '\n';
    cout << "vd.size(): " << vd.size() << '\n';
    cout << "vd values: " << vd << '\n';
    cout << "sum(vd): " << sum(vd) << '\n';
    return 0;
}
