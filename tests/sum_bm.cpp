#include "sum/sum.hpp"
#include <benchmark/benchmark.h>

#include <random>

std::vector<double> make_data(size_t N, double min, double max)
{
    static auto rnd = std::random_device{};
    static auto gen = std::default_random_engine{rnd()};
    auto dist = std::uniform_real_distribution(min, max);
    auto res = std::vector<double>(N);
    std::generate(res.begin(), res.end(), [&]{ return dist(gen); });
    return res;
}

#ifndef FN_NAME
#error "Please define FN_NAME to be used as a benchmark name"
#endif // FN_NAME

static void FN_NAME(benchmark::State& state)
{
    const auto inp = make_data(state.range(0), -1000, 1000);
    for (auto _ : state) {
        auto res = sum(inp);
        benchmark::DoNotOptimize(res);
        benchmark::ClobberMemory();
    }
}

#define FN_BENCHMARK(name) BENCHMARK(name)
FN_BENCHMARK(FN_NAME)->RangeMultiplier(1<<4)->Range(1<<10, 1<<26);
