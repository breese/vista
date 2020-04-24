///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <random>
#include <string>
#include <benchmark/benchmark.h>
#include <vista/circular/span.hpp>
#include <vista/heap/algorithm.hpp>

template <typename T, int Amount>
void vista_heap_push(benchmark::State& state)
{
    T input[Amount];
    std::random_device device;
    std::default_random_engine generator(device());
    std::uniform_int_distribution<T> distribution;
    for (auto i = 0U; i < Amount; ++i)
    {
        input[i] = distribution(generator);
     }

    T storage[Amount];
    vista::circular::span<T, Amount> heap(storage);

    auto k = 0U;
    for (auto _ : state)
    {
        heap.push_back(input[k % Amount]);
        vista::heap::push(heap.begin(), heap.end(), std::less<T>());
        ++k;
    }
}

BENCHMARK_TEMPLATE(vista_heap_push, int, 64);
BENCHMARK_TEMPLATE(vista_heap_push, int, 256);
BENCHMARK_TEMPLATE(vista_heap_push, int, 1024);

template <int Amount>
void vista_heap_push_string(benchmark::State& state)
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

    std::string storage[Amount];
    vista::circular::span<std::string, Amount> heap(storage);

    auto k = 0U;
    for (auto _ : state)
    {
        heap.push_back(mapping[input[k % Amount] % (sizeof(mapping) / sizeof(mapping[0]))]);
        vista::heap::push(heap.begin(), heap.end(), std::less<std::string>());
        ++k;
    }
}

BENCHMARK_TEMPLATE(vista_heap_push_string, 64);
BENCHMARK_TEMPLATE(vista_heap_push_string, 256);
BENCHMARK_TEMPLATE(vista_heap_push_string, 1024);

template <typename T, int Amount>
void vista_heap_push_pop(benchmark::State& state)
{
    T input[Amount];
    std::random_device device;
    std::default_random_engine generator(device());
    std::uniform_int_distribution<T> distribution;
    for (auto i = 0U; i < Amount; ++i)
    {
        input[i] = distribution(generator);
     }

    T storage[Amount];
    vista::circular::span<T, Amount> heap(storage);

    auto k = 0U;
    for (auto _ : state)
    {
        heap.push_back(input[k % Amount]);
        vista::heap::push(heap.begin(), heap.end(), std::less<T>());
        vista::heap::pop(heap.begin(), heap.end(), std::less<T>());
        ++k;
    }
}

BENCHMARK_TEMPLATE(vista_heap_push_pop, int, 64);
BENCHMARK_TEMPLATE(vista_heap_push_pop, int, 256);
BENCHMARK_TEMPLATE(vista_heap_push_pop, int, 1024);

template <int Amount>
void vista_heap_push_pop_string(benchmark::State& state)
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

    std::string storage[Amount];
    vista::circular::span<std::string, Amount> heap(storage);

    auto k = 0U;
    for (auto _ : state)
    {
        heap.push_back(mapping[input[k % Amount] % (sizeof(mapping) / sizeof(mapping[0]))]);
        vista::heap::push(heap.begin(), heap.end(), std::less<std::string>());
        vista::heap::pop(heap.begin(), heap.end(), std::less<std::string>());
        ++k;
    }
}

BENCHMARK_TEMPLATE(vista_heap_push_pop_string, 64);
BENCHMARK_TEMPLATE(vista_heap_push_pop_string, 256);
BENCHMARK_TEMPLATE(vista_heap_push_pop_string, 1024);

BENCHMARK_MAIN();
