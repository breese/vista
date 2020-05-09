///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vista/constexpr/functional.hpp> // constexpr_less
#include <vista/constexpr/utility.hpp> // constexpr_swap

namespace vista
{

template <typename RandomAccessIterator>
VISTA_CXX14_CONSTEXPR
void push_heap(RandomAccessIterator first,
               RandomAccessIterator last)
{
    push_heap<false>(std::move(first),
                     std::move(last),
                     constexpr_less<decltype(*first)>{});
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
             constexpr_less<decltype(*first)>{});
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

} // namespace vista
