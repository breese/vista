///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <functional> // std::less

namespace vista
{

template <typename RandomAccessIterator, typename T>
VISTA_CXX14_CONSTEXPR
RandomAccessIterator lower_bound_sorted(RandomAccessIterator first,
                                        RandomAccessIterator last,
                                        const T& needle) noexcept
{
    return lower_bound_sorted(std::move(first),
                              std::move(last),
                              needle,
                              std::less<T>{});
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
    return push_sorted(std::move(first),
                       std::move(last),
                       std::less<decltype(*first)>{});
}

template <typename RandomAccessIterator, typename Compare>
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
        using std::swap;
        swap(current[0], current[-1]);
        --current;
    }
    return current;
}

template <typename RandomAccessIterator>
VISTA_CXX14_CONSTEXPR
RandomAccessIterator pop_sorted(RandomAccessIterator first,
                                RandomAccessIterator last) noexcept(detail::is_nothrow_swappable<decltype(*first)>::value)
{
    if (first == last)
        return last;

    for (auto current = first; current != last - 1; ++current)
    {
        using std::swap;
        swap(current[0], current[1]);
    }
    return last - 1;
}

} // namespace vista
