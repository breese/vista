///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <utility> // std::swap

namespace vista
{
namespace heap
{

template <typename RandomAccessIterator>
VISTA_CXX14_CONSTEXPR
void push(RandomAccessIterator first, RandomAccessIterator last)
{
    using type = decltype(*first);
    push(std::move(first),
         std::move(last),
         [] (const type& lhs, const type& rhs) { return lhs < rhs; });
}

template <typename RandomAccessIterator, typename Compare>
VISTA_CXX14_CONSTEXPR
inline void push(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
    auto position = last - first;
    auto parent = position >> 1;
    while (parent > 0 && comp(first[parent - 1], first[position - 1]))
    {
        using std::swap;
        swap(first[parent - 1], first[position - 1]);
        position = parent;
        parent = position >> 1;
    }
}

template <typename RandomAccessIterator>
VISTA_CXX14_CONSTEXPR
void pop(RandomAccessIterator first, RandomAccessIterator last)
{
    using type = decltype(*first);
    pop(std::move(first),
        std::move(last),
        [] (const type& lhs, const type& rhs) { return lhs < rhs; });
}

template <typename RandomAccessIterator, typename Compare>
VISTA_CXX14_CONSTEXPR
void pop(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
    --last;
    using std::swap;
    swap(*first, *last);

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
        swap(first[position], first[selected]);
        position = selected;
    }
}

} // namespace heap
} // namespace vista
