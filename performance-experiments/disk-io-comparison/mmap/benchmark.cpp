#include "fast_disk.hpp"
#include <benchmark/benchmark.h>
#include <vector>

template <class T> void fileio(const std::vector<T>& v)
{
    std::string path = "./temp.bin";
    save_vector<T>(v, path);
    std::vector<T> newV = read_vector<T>(v.size(), path);
    if (v.size() != newV.size())
    {
        throw std::runtime_error("Vector sizes are not equal");
    }
}

template <class T> static void file_io_benchmark(benchmark::State& state)
{
    auto n = state.range(0);
    std::vector<T> v(n, T(0));
    for (auto _ : state)
    {
        fileio<T>(v);
    }
}
BENCHMARK(file_io_benchmark<double>)->RangeMultiplier(2)->Range(64, 67108864);

BENCHMARK_MAIN();