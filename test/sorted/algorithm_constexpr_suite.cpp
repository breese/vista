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
#include <vista/sorted/algorithm.hpp>

using namespace vista;

//-----------------------------------------------------------------------------

template <typename T, typename Compare = constexpr_less<T>>
struct sorted_factory
{
    template <typename Array, typename Arg>
    static constexpr void emplace(Array& array, std::size_t index, Arg&& arg)
    {
        array[index] = arg;
        sorted::push<true>(array.begin(), array.begin() + index + 1, Compare{});
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

    template <typename... Args>
    static constexpr auto make_with_99(Args&&... args) -> vista::constexpr_array<T, sizeof...(args)>
    {
        auto result = make(std::forward<Args>(args)...);
        // Replace front with 99
        sorted::pop<true>(result.begin(), result.end());
        result[result.size() - 1] = 99;
        sorted::push<true>(result.begin(), result.end(), Compare{});
        return result;
    }
};

//-----------------------------------------------------------------------------

constexpr auto increasing = sorted_factory<int>::make(11, 22, 33, 44);

static_assert(increasing[0] == 11, "");
static_assert(increasing[1] == 22, "");
static_assert(increasing[2] == 33, "");
static_assert(increasing[3] == 44, "");

constexpr auto increasing_predicate = sorted_factory<int, constexpr_greater<int>>::make(11, 22, 33, 44);

static_assert(increasing_predicate[0] == 44, "");
static_assert(increasing_predicate[1] == 33, "");
static_assert(increasing_predicate[2] == 22, "");
static_assert(increasing_predicate[3] == 11, "");

constexpr auto decreasing = sorted_factory<int>::make(44, 33, 22, 11);

static_assert(decreasing[0] == 11, "");
static_assert(decreasing[1] == 22, "");
static_assert(decreasing[2] == 33, "");
static_assert(decreasing[3] == 44, "");

constexpr auto decreasing_predicate = sorted_factory<int, constexpr_greater<int>>::make(44, 33, 22, 11);

static_assert(decreasing_predicate[0] == 44, "");
static_assert(decreasing_predicate[1] == 33, "");
static_assert(decreasing_predicate[2] == 22, "");
static_assert(decreasing_predicate[3] == 11, "");

//-----------------------------------------------------------------------------

constexpr auto increasing99 = sorted_factory<int>::make_with_99(11, 22, 33, 44);

static_assert(increasing99[0] == 22, "");
static_assert(increasing99[1] == 33, "");
static_assert(increasing99[2] == 44, "");
static_assert(increasing99[3] == 99, "");

constexpr auto increasing_predicate99 = sorted_factory<int, constexpr_greater<int>>::make_with_99(11, 22, 33, 44);

static_assert(increasing_predicate99[0] == 99, "");
static_assert(increasing_predicate99[1] == 33, "");
static_assert(increasing_predicate99[2] == 22, "");
static_assert(increasing_predicate99[3] == 11, "");

constexpr auto decreasing99 = sorted_factory<int>::make_with_99(44, 33, 22, 11);

static_assert(decreasing99[0] == 22, "");
static_assert(decreasing99[1] == 33, "");
static_assert(decreasing99[2] == 44, "");
static_assert(decreasing99[3] == 99, "");

constexpr auto decreasing_predicate99 = sorted_factory<int, constexpr_greater<int>>::make_with_99(44, 33, 22, 11);

static_assert(decreasing_predicate99[0] == 99, "");
static_assert(decreasing_predicate99[1] == 33, "");
static_assert(decreasing_predicate99[2] == 22, "");
static_assert(decreasing_predicate99[3] == 11, "");
