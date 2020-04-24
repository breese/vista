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
        vista::heap::push(heap.begin(), heap.end(), std::less<int>());
        ++k;
    }
}

BENCHMARK_TEMPLATE(vista_heap_push, int, 64);
BENCHMARK_TEMPLATE(vista_heap_push, int, 256);
BENCHMARK_TEMPLATE(vista_heap_push, int, 1024);

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
        vista::heap::push(heap.begin(), heap.end(), std::less<int>());
        vista::heap::pop(heap.begin(), heap.end(), std::less<int>());
        ++k;
    }
}

BENCHMARK_TEMPLATE(vista_heap_push_pop, int, 64);
BENCHMARK_TEMPLATE(vista_heap_push_pop, int, 256);
BENCHMARK_TEMPLATE(vista_heap_push_pop, int, 1024);

BENCHMARK_MAIN();
