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
#include <vista/circular_view.hpp>
#include <vista/algorithm.hpp>

template <typename T, int Amount>
void vista_push_heap(benchmark::State& state)
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
    vista::circular_view<T, Amount> heap(storage);

    auto k = 0U;
    for (auto _ : state)
    {
        heap.push_back(input[k % Amount]);
        vista::push_heap(heap.begin(), heap.end(), std::less<T>());
        ++k;
    }
}

BENCHMARK_TEMPLATE(vista_push_heap, int, 64);
BENCHMARK_TEMPLATE(vista_push_heap, int, 256);
BENCHMARK_TEMPLATE(vista_push_heap, int, 1024);

template <int Amount>
void vista_push_heap_string(benchmark::State& state)
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
    vista::circular_view<std::string, Amount> heap(storage);

    auto k = 0U;
    for (auto _ : state)
    {
        heap.push_back(mapping[input[k % Amount] % (sizeof(mapping) / sizeof(mapping[0]))]);
        vista::push_heap(heap.begin(), heap.end(), std::less<std::string>());
        ++k;
    }
}

BENCHMARK_TEMPLATE(vista_push_heap_string, 64);
BENCHMARK_TEMPLATE(vista_push_heap_string, 256);
BENCHMARK_TEMPLATE(vista_push_heap_string, 1024);

template <typename T, int Amount>
void vista_push_pop_heap(benchmark::State& state)
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
    vista::circular_view<T, Amount> heap(storage);

    auto k = 0U;
    for (auto _ : state)
    {
        heap.push_back(input[k % Amount]);
        vista::push_heap(heap.begin(), heap.end(), std::less<T>());
        vista::pop_heap(heap.begin(), heap.end(), std::less<T>());
        ++k;
    }
}

BENCHMARK_TEMPLATE(vista_push_pop_heap, int, 64);
BENCHMARK_TEMPLATE(vista_push_pop_heap, int, 256);
BENCHMARK_TEMPLATE(vista_push_pop_heap, int, 1024);

template <int Amount>
void vista_push_pop_heap_string(benchmark::State& state)
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
    vista::circular_view<std::string, Amount> heap(storage);

    auto k = 0U;
    for (auto _ : state)
    {
        heap.push_back(mapping[input[k % Amount] % (sizeof(mapping) / sizeof(mapping[0]))]);
        vista::push_heap(heap.begin(), heap.end(), std::less<std::string>());
        vista::pop_heap(heap.begin(), heap.end(), std::less<std::string>());
        ++k;
    }
}

BENCHMARK_TEMPLATE(vista_push_pop_heap_string, 64);
BENCHMARK_TEMPLATE(vista_push_pop_heap_string, 256);
BENCHMARK_TEMPLATE(vista_push_pop_heap_string, 1024);

BENCHMARK_MAIN();
