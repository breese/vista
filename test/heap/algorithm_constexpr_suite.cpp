///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vista/constexpr/array.hpp>
#include <vista/heap/algorithm.hpp>

using namespace vista;

//-----------------------------------------------------------------------------

template <typename T, typename Compare = constexpr_less<T>>
struct heap_factory
{
    template <typename Array, typename Arg>
    static constexpr void emplace(Array& array, std::size_t index, Arg&& arg)
    {
        array[index] = arg;
        heap::push(array.begin(), array.begin() + index + 1, Compare{});
    }

    template <typename... Args>
    static constexpr auto make(Args&&... args) -> vista::constexpr_array<T, sizeof...(args)>
    {
        vista::constexpr_array<T, sizeof...(args)> result{};
        auto k = 0U;
        int expander[] = { 0, ((void)emplace(result, k++, std::forward<Args>(args)), 0)... };
        (void)expander;
        return result;
    }
};

//-----------------------------------------------------------------------------

constexpr auto increasing = heap_factory<int>::make(11, 22, 33, 44);

static_assert(increasing[0] == 44, "");
static_assert(increasing[1] == 33, "");
static_assert(increasing[2] == 22, "");
static_assert(increasing[3] == 11, "");

constexpr auto increasing_predicate = heap_factory<int, constexpr_greater<int>>::make(11, 22, 33, 44);

static_assert(increasing_predicate[0] == 11, "");
static_assert(increasing_predicate[1] == 22, "");
static_assert(increasing_predicate[2] == 33, "");
static_assert(increasing_predicate[3] == 44, "");

constexpr auto decreasing = heap_factory<int>::make(44, 33, 22, 11);

static_assert(decreasing[0] == 44, "");
static_assert(decreasing[1] == 33, "");
static_assert(decreasing[2] == 22, "");
static_assert(decreasing[3] == 11, "");

constexpr auto decreasing_predicate = heap_factory<int, constexpr_greater<int>>::make(44, 33, 22, 11);

static_assert(decreasing_predicate[0] == 11, "");
static_assert(decreasing_predicate[1] == 22, "");
static_assert(decreasing_predicate[2] == 33, "");
static_assert(decreasing_predicate[3] == 44, "");
