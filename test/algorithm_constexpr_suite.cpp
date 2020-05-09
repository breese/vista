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
#include <vista/constexpr/algorithm.hpp>
#include <vista/algorithm.hpp>

using namespace vista;

//-----------------------------------------------------------------------------

template <typename T, typename Compare = constexpr_less<T>>
class heap_factory
{
public:
    template <typename... Args>
    static constexpr auto make(Args&&... args) -> vista::constexpr_array<T, sizeof...(args)>
    {
        vista::constexpr_array<T, sizeof...(args)> result{};
        insert(result.begin(), result.begin(), std::forward<Args>(args)...);
        return result;
    }

    template <std::size_t N>
    static constexpr auto pop(vista::constexpr_array<T, N> original)
    {
        vista::pop_heap<true>(original.begin(), original.end(), Compare{});
        vista::constexpr_array<T, N - 1> result{};
        constexpr_copy(original.begin(), original.end() - 1, result.begin());
        return result;
    }

    template <std::size_t N, typename... Args>
    static constexpr auto append(const vista::constexpr_array<T, N>& original,
                                 Args&&... args) -> vista::constexpr_array<T, N + sizeof...(args)>
    {
        vista::constexpr_array<T, N + sizeof...(args)> result{};
        constexpr_copy(original.begin(), original.end(), result.begin());
        insert(result.begin(), result.begin() + N, std::forward<Args>(args)...);
        return result;
    }

private:
    template <typename RandomAccessIterator, typename Arg>
    static constexpr void insert(RandomAccessIterator first,
                                 RandomAccessIterator position,
                                 Arg&& arg)
    {
        *position = arg;
        vista::push_heap<true>(first, position + 1, Compare{});
    }

    template <typename RandomAccessIterator, typename... Args>
    static constexpr void insert(RandomAccessIterator first,
                                 RandomAccessIterator position,
                                 Args&&... args)
    {
        int expander[] = { 0, ((void)insert(first, position++, std::forward<Args>(args)), 0)... };
        (void)expander;
    }
};

//-----------------------------------------------------------------------------

constexpr auto increasing = heap_factory<int>::make(11, 22, 33, 44);

static_assert(increasing.size() == 4, "");
static_assert(increasing[0] == 44, "");
static_assert(increasing[1] == 33, "");
static_assert(increasing[2] == 22, "");
static_assert(increasing[3] == 11, "");

constexpr auto increasing_predicate = heap_factory<int, constexpr_greater<int>>::make(11, 22, 33, 44);

static_assert(increasing_predicate.size() == 4, "");
static_assert(increasing_predicate[0] == 11, "");
static_assert(increasing_predicate[1] == 22, "");
static_assert(increasing_predicate[2] == 33, "");
static_assert(increasing_predicate[3] == 44, "");

constexpr auto decreasing = heap_factory<int>::make(44, 33, 22, 11);

static_assert(decreasing.size() == 4, "");
static_assert(decreasing[0] == 44, "");
static_assert(decreasing[1] == 33, "");
static_assert(decreasing[2] == 22, "");
static_assert(decreasing[3] == 11, "");

constexpr auto decreasing_predicate = heap_factory<int, constexpr_greater<int>>::make(44, 33, 22, 11);

static_assert(decreasing_predicate.size() == 4, "");
static_assert(decreasing_predicate[0] == 11, "");
static_assert(decreasing_predicate[1] == 22, "");
static_assert(decreasing_predicate[2] == 33, "");
static_assert(decreasing_predicate[3] == 44, "");

//-----------------------------------------------------------------------------

constexpr auto increasing_popped = heap_factory<int>::pop(increasing);

static_assert(increasing_popped.size() == 3, "");
static_assert(increasing_popped[0] == 33, "");
static_assert(increasing_popped[1] == 11, "");
static_assert(increasing_popped[2] == 22, "");

constexpr auto increasing_predicate_popped = heap_factory<int, constexpr_greater<int>>::pop(increasing_predicate);

static_assert(increasing_predicate_popped.size() == 3, "");
static_assert(increasing_predicate_popped[0] == 22, "");
static_assert(increasing_predicate_popped[1] == 44, "");
static_assert(increasing_predicate_popped[2] == 33, "");

constexpr auto decreasing_popped = heap_factory<int>::pop(decreasing);

static_assert(decreasing_popped.size() == 3, "");
static_assert(decreasing_popped[0] == 33, "");
static_assert(decreasing_popped[1] == 11, "");
static_assert(decreasing_popped[2] == 22, "");

//-----------------------------------------------------------------------------

constexpr auto increasing_appended = heap_factory<int>::append(increasing, 55, 66);

static_assert(increasing_appended.size() == 6, "");
static_assert(increasing_appended[0] == 66, "");
static_assert(increasing_appended[1] == 44, "");
static_assert(increasing_appended[2] == 55, "");
static_assert(increasing_appended[3] == 11, "");
static_assert(increasing_appended[4] == 33, "");
static_assert(increasing_appended[5] == 22, "");
