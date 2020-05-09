///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vista/array.hpp>
#include <vista/constexpr/functional.hpp>
#include <vista/algorithm.hpp>

using namespace vista;

//-----------------------------------------------------------------------------
// Heap algorithms
//-----------------------------------------------------------------------------

namespace heap_suite
{

template <typename T, typename Compare = constexpr_less<T>>
class heap_factory
{
public:
    template <typename... Args>
    static constexpr auto make(Args&&... args) -> vista::array<T, sizeof...(args)>
    {
        vista::array<T, sizeof...(args)> result{};
        insert(result.begin(), result.begin(), std::forward<Args>(args)...);
        return result;
    }

    template <std::size_t N>
    static constexpr auto pop(vista::array<T, N> original)
    {
        vista::pop_heap<true>(original.begin(), original.end(), Compare{});
        vista::array<T, N - 1> result{};
        vista::copy(original.begin(), original.end() - 1, result.begin());
        return result;
    }

    template <std::size_t N, typename... Args>
    static constexpr auto append(const vista::array<T, N>& original,
                                 Args&&... args) -> vista::array<T, N + sizeof...(args)>
    {
        vista::array<T, N + sizeof...(args)> result{};
        vista::copy(original.begin(), original.end(), result.begin());
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

} // namespace heap_suite

//-----------------------------------------------------------------------------
// Sorted algorithms
//-----------------------------------------------------------------------------

namespace sorted_suite
{

template <typename T, typename Compare = constexpr_less<T>>
struct sorted_factory
{
    template <typename Array, typename Arg>
    static constexpr void emplace(Array& array, std::size_t index, Arg&& arg)
    {
        array[index] = arg;
        push_sorted<true>(array.begin(), array.begin() + index + 1, Compare{});
    }

    template <typename... Args>
    static constexpr auto make(Args&&... args) -> vista::array<T, sizeof...(args)>
    {
        vista::array<T, sizeof...(args)> result{};
        auto k = 0U;
        int expander[] = { 0, ((void)emplace(result, k++, std::forward<Args>(args)), 0)... };
        (void)expander;
        return result;
    }

    template <typename... Args>
    static constexpr auto make_with_99(Args&&... args) -> vista::array<T, sizeof...(args)>
    {
        auto result = make(std::forward<Args>(args)...);
        // Replace front with 99
        pop_sorted<true>(result.begin(), result.end());
        result[result.size() - 1] = 99;
        push_sorted<true>(result.begin(), result.end(), Compare{});
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

} // namespace sorted_suite
