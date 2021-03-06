#include <random>
#include <algorithm>
#include <string>
#include <benchmark/benchmark.h>

template <typename T, int Amount>
void std_sort(benchmark::State& state)
{
    T input[Amount];
    std::random_device device;
    std::default_random_engine generator(device());
    std::uniform_int_distribution<T> distribution;
    for (auto i = 0U; i < Amount; ++i)
    {
        input[i] = distribution(generator);
     }

    for (auto _ : state)
    {
        auto storage = input;
        std::sort(storage, storage + Amount);
        benchmark::DoNotOptimize(storage);
    }
}

BENCHMARK_TEMPLATE(std_sort, int, 64);
BENCHMARK_TEMPLATE(std_sort, int, 128);
BENCHMARK_TEMPLATE(std_sort, int, 256);
BENCHMARK_TEMPLATE(std_sort, int, 512);
BENCHMARK_TEMPLATE(std_sort, int, 1024);
BENCHMARK_TEMPLATE(std_sort, int, 2048);
BENCHMARK_TEMPLATE(std_sort, int, 4096);
BENCHMARK_TEMPLATE(std_sort, int, 8192);
BENCHMARK_TEMPLATE(std_sort, int, 16384);
BENCHMARK_TEMPLATE(std_sort, int, 32768);


template <int Amount>
void string_std_sort(benchmark::State& state)
{
    constexpr const char * mapping[] = {
        "alpha", "bravo", "charlie", "delta", "echo", "foxtrot", "golf", "hotel",
        "india", "juliet", "kilo", "lima", "mike", "november", "oscar", "papa",
        "quebec", "radio", "siera", "tango", "uniform", "victor", "whisky", "xray",
        "yankee", "zulu"
    };

    std::size_t input[Amount];
    std::random_device device;
    std::default_random_engine generator(device());
    std::uniform_int_distribution<std::size_t> distribution;
    for (auto i = 0U; i < Amount; ++i)
    {
        input[i] = distribution(generator);
    }
    std::string string_input[Amount];
    for (auto i = 0U; i < Amount; ++i)
    {
        string_input[i] = mapping[input[i] % (sizeof(mapping) / sizeof(mapping[0]))];
    }

    for (auto _ : state)
    {
        auto storage = string_input;
        std::sort(storage, storage + Amount);
        benchmark::DoNotOptimize(storage);
    }
}

BENCHMARK_TEMPLATE(string_std_sort, 64);
BENCHMARK_TEMPLATE(string_std_sort, 128);
BENCHMARK_TEMPLATE(string_std_sort, 256);
BENCHMARK_TEMPLATE(string_std_sort, 512);
BENCHMARK_TEMPLATE(string_std_sort, 1024);
BENCHMARK_TEMPLATE(string_std_sort, 2048);
BENCHMARK_TEMPLATE(string_std_sort, 4096);
BENCHMARK_TEMPLATE(string_std_sort, 8192);
BENCHMARK_TEMPLATE(string_std_sort, 16384);
BENCHMARK_TEMPLATE(string_std_sort, 32768);

BENCHMARK_MAIN();
