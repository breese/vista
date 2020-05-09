///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vista/algorithm.hpp>

namespace vista
{

template <typename T, std::size_t E, typename C>
template <std::size_t N,
          typename std::enable_if<(E == N || E == dynamic_extent), int>::type>
constexpr priority_view<T, E, C>::priority_view(element_type (&array)[N]) noexcept
    : member(array, array + N)
{
}

template <typename T, std::size_t E, typename C>
constexpr priority_view<T, E, C>::priority_view(pointer data,
                                                size_type size) noexcept
    : member(data, data + size)
{
}

template <typename T, std::size_t E, typename C>
template <typename ContiguousIterator>
constexpr priority_view<T, E, C>::priority_view(ContiguousIterator begin,
                                                ContiguousIterator end) noexcept
    : member(&*begin, &*end)
{
}

template <typename T, std::size_t E, typename C>
constexpr bool priority_view<T, E, C>::empty() const noexcept
{
    return size() == 0;
}

template <typename T, std::size_t E, typename C>
constexpr bool priority_view<T, E, C>::full() const noexcept
{
    return size() == capacity();
}

template <typename T, std::size_t E, typename C>
constexpr auto priority_view<T, E, C>::size() const noexcept -> size_type
{
    return member.last - member.span.data();
}

template <typename T, std::size_t E, typename C>
constexpr auto priority_view<T, E, C>::capacity() const noexcept -> size_type
{
    return member.span.size();
}

template <typename T, std::size_t E, typename C>
constexpr auto priority_view<T, E, C>::top() const noexcept -> const value_type&
{
    VISTA_CXX14(assert(size() > 0));
    return member.span.front();
}

template <typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
void priority_view<T, E, C>::push(value_type input) noexcept(std::is_nothrow_move_constructible<value_type>::value && std::is_nothrow_move_assignable<value_type>::value)
{
    assert(!full());
    *member.last = std::move(input);
    ++member.last;
    vista::push_heap(member.span.data(), member.last, member.comparator);
}

template <typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
void priority_view<T, E, C>::pop() noexcept (std::is_nothrow_move_constructible<value_type>::value && std::is_nothrow_move_assignable<value_type>::value)
{
    assert(!empty());
    vista::pop_heap(member.span.data(), member.last, member.comparator);
    --member.last;
}

} // namespace vista
