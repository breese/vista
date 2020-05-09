///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>
#include <vista/circular_view.hpp>

void dynamic_empty(benchmark::State& state)
{
    int storage[8];
    vista::circular_view<int> window(storage);
    window.assign({ 1, 2, 3, 4, 5, 6, 7, 8 });

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(window.empty());
    }
}

BENCHMARK(dynamic_empty);

void fixed_empty(benchmark::State& state)
{
    int storage[8];
    vista::circular_view<int, 8> window(storage);
    window.assign({ 1, 2, 3, 4, 5, 6, 7, 8 });

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(window.empty());
    }
}

BENCHMARK(fixed_empty);

void dynamic_full(benchmark::State& state)
{
    int storage[8];
    vista::circular_view<int> window(storage);
    window.assign({ 1, 2, 3, 4, 5, 6, 7, 8 });

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(window.full());
    }
}

BENCHMARK(dynamic_full);

void fixed_full(benchmark::State& state)
{
    int storage[8];
    vista::circular_view<int, 8> window(storage);
    window.assign({ 1, 2, 3, 4, 5, 6, 7, 8 });

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(window.full());
    }
}

BENCHMARK(fixed_full);

void dynamic_push_back(benchmark::State& state)
{
    int storage[256];
    vista::circular_view<int> window(storage);

    for (auto _ : state)
    {
        window.push_back(42);
    }
}

BENCHMARK(dynamic_push_back);

void fixed_push_back(benchmark::State& state)
{
    int storage[256];
    vista::circular_view<int, 256> window(storage);

    for (auto _ : state)
    {
        window.push_back(42);
    }
}

BENCHMARK(fixed_push_back);

void dynamic_push_front(benchmark::State& state)
{
    int storage[256];
    vista::circular_view<int> window(storage);

    for (auto _ : state)
    {
        window.push_front(42);
    }
}

BENCHMARK(dynamic_push_front);

void fixed_push_front(benchmark::State& state)
{
    int storage[256];
    vista::circular_view<int, 256> window(storage);

    for (auto _ : state)
    {
        window.push_front(42);
    }
}

BENCHMARK(fixed_push_front);

void dynamic_push_back_pop_front(benchmark::State& state)
{
    int storage[256];
    vista::circular_view<int> window(storage);
    window.assign({1, 2, 3, 4, 5});

    for (auto _ : state)
    {
        window.push_back(42);
        window.pop_front();
    }
}

BENCHMARK(dynamic_push_back_pop_front);

void fixed_push_back_pop_front(benchmark::State& state)
{
    int storage[256];
    vista::circular_view<int, 256> window(storage);
    window.assign({1, 2, 3, 4, 5});

    for (auto _ : state)
    {
        window.push_back(42);
        window.pop_front();
    }
}

BENCHMARK(fixed_push_back_pop_front);

void dynamic_push_front_pop_back(benchmark::State& state)
{
    int storage[256];
    vista::circular_view<int> window(storage);
    window.assign({1, 2, 3, 4, 5});

    for (auto _ : state)
    {
        window.push_front(42);
        window.pop_back();
    }
}

BENCHMARK(dynamic_push_front_pop_back);

void fixed_push_front_pop_back(benchmark::State& state)
{
    int storage[256];
    vista::circular_view<int, 256> window(storage);
    window.assign({1, 2, 3, 4, 5});

    for (auto _ : state)
    {
        window.push_front(42);
        window.pop_back();
    }
}

BENCHMARK(fixed_push_front_pop_back);

BENCHMARK_MAIN();
