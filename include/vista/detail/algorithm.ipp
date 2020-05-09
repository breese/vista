///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vista/functional.hpp> // less
#include <vista/constexpr/utility.hpp> // swap

namespace vista
{

//-----------------------------------------------------------------------------
// Constexpr modifying sequence operations
//-----------------------------------------------------------------------------

#if __cpp_lib_constexpr_algorithm

using std::copy;

#else

template <typename InputIterator, typename OutputIterator>
VISTA_CXX14_CONSTEXPR
OutputIterator copy(InputIterator first,
                    InputIterator last,
                    OutputIterator output)
{
    while (first != last)
    {
        *output++ = *first++;
    }
    return output;
}

#endif

//-----------------------------------------------------------------------------
// Heap algorithms
//-----------------------------------------------------------------------------

template <typename RandomAccessIterator>
VISTA_CXX14_CONSTEXPR
void push_heap(RandomAccessIterator first,
               RandomAccessIterator last)
{
    push_heap<false>(std::move(first),
                     std::move(last),
                     vista::less<decltype(*first)>{});
}

template <typename RandomAccessIterator,
          typename Compare>
VISTA_CXX14_CONSTEXPR
inline void push_heap(RandomAccessIterator first,
                      RandomAccessIterator last,
                      Compare comp)
{
    push_heap<false>(std::move(first), std::move(last), std::move(comp));
}

template <bool WithConstexpr,
          typename RandomAccessIterator,
          typename Compare>
VISTA_CXX14_CONSTEXPR
inline void push_heap(RandomAccessIterator first,
                      RandomAccessIterator last, Compare comp)
{
    auto position = last - first;
    auto parent = position >> 1;
    while (parent > 0 && comp(first[parent - 1], first[position - 1]))
    {
        vista::swap<WithConstexpr>(first[parent - 1], first[position - 1]);
        position = parent;
        parent = position >> 1;
    }
}

template <typename RandomAccessIterator>
VISTA_CXX14_CONSTEXPR
void pop_heap(RandomAccessIterator first,
              RandomAccessIterator last)
{
    pop_heap(std::move(first),
             std::move(last),
             vista::less<decltype(*first)>{});
}

template <typename RandomAccessIterator,
          typename Compare>
VISTA_CXX14_CONSTEXPR
void pop_heap(RandomAccessIterator first,
              RandomAccessIterator last, Compare comp)
{
    pop_heap<false>(std::move(first), std::move(last), std::move(comp));
}

template <bool WithConstexpr,
          typename RandomAccessIterator,
          typename Compare>
VISTA_CXX14_CONSTEXPR
void pop_heap(RandomAccessIterator first,
              RandomAccessIterator last,
              Compare comp)
{
    --last;
    vista::swap<WithConstexpr>(*first, *last);

    auto size = last - first;
    auto position = 0;
    while (2 * position + 1 < size)
    {
        const auto left = 2 * position + 1;
        const auto right = left + 1;
        auto selected = comp(first[position], first[left]) ? left : position;
        selected = (right < size && comp(first[selected], first[right])) ? right : selected;
        if (selected == position)
            break;
        vista::swap<WithConstexpr>(first[position], first[selected]);
        position = selected;
    }
}

//-----------------------------------------------------------------------------
// Sorted algorithms
//-----------------------------------------------------------------------------

template <typename RandomAccessIterator, typename T>
VISTA_CXX14_CONSTEXPR
RandomAccessIterator lower_bound_sorted(RandomAccessIterator first,
                                        RandomAccessIterator last,
                                        const T& needle) noexcept
{
    return lower_bound_sorted(std::move(first),
                              std::move(last),
                              needle,
                              vista::less<T>{});
}

template <typename RandomAccessIterator, typename T, typename Compare>
VISTA_CXX14_CONSTEXPR
RandomAccessIterator lower_bound_sorted(RandomAccessIterator first,
                                        RandomAccessIterator last,
                                        const T& needle,
                                        Compare compare) noexcept
{
    if (first == last)
        return last;

    // Branchless binary search
    auto step = last - first;
    do
    {
        const auto half = step >> 1;
        first += compare(first[half], needle) ? half : 0;
        step -= half;
    } while (step > 1);

    return first + compare(*first, needle);
}

template <typename RandomAccessIterator>
VISTA_CXX14_CONSTEXPR
RandomAccessIterator push_sorted(RandomAccessIterator first,
                                 RandomAccessIterator last) noexcept(detail::is_nothrow_swappable<decltype(*first)>::value)
{
    return push_sorted<false>(std::move(first),
                              std::move(last),
                              vista::less<decltype(*first)>{});
}

template <typename RandomAccessIterator, typename Compare>
VISTA_CXX14_CONSTEXPR
RandomAccessIterator push_sorted(RandomAccessIterator first,
                                 RandomAccessIterator last,
                                 Compare compare) noexcept(detail::is_nothrow_swappable<decltype(*first)>::value)
{
    return push_sorted<false>(std::move(first),
                              std::move(last),
                              std::move(compare));
}

template <bool WithConstexpr, typename RandomAccessIterator, typename Compare>
VISTA_CXX14_CONSTEXPR
RandomAccessIterator push_sorted(RandomAccessIterator first,
                                 RandomAccessIterator last,
                                 Compare compare) noexcept(detail::is_nothrow_swappable<decltype(*first)>::value)
{
    if (first == last)
        return last;

    auto current = last - 1;
    while ((current != first) && compare(current[0], current[-1]))
    {
        vista::swap<WithConstexpr>(current[0], current[-1]);
        --current;
    }
    return current;
}

template <typename RandomAccessIterator>
VISTA_CXX14_CONSTEXPR
RandomAccessIterator pop_sorted(RandomAccessIterator first,
                                RandomAccessIterator last) noexcept(detail::is_nothrow_swappable<decltype(*first)>::value)
{
    return pop_sorted<false>(std::move(first), std::move(last));
}

template <bool WithConstexpr,
          typename RandomAccessIterator>
VISTA_CXX14_CONSTEXPR
RandomAccessIterator pop_sorted(RandomAccessIterator first,
                                RandomAccessIterator last) noexcept(detail::is_nothrow_swappable<decltype(*first)>::value)
{
    if (first == last)
        return last;

    for (auto current = first; current != last - 1; ++current)
    {
        vista::swap<WithConstexpr>(current[0], current[1]);
    }
    return last - 1;
}

} // namespace vista
