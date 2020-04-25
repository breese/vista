///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vista/heap/algorithm.hpp>

namespace vista
{
namespace priority
{

template <typename T, std::size_t E, typename C>
template <std::size_t N,
          typename std::enable_if<(E == N || E == dynamic_extent), int>::type>
constexpr span<T, E, C>::span(value_type (&array)[N]) noexcept
    : member(array, array + N)
{
}

template <typename T, std::size_t E, typename C>
constexpr span<T, E, C>::span(pointer data,
                              size_type size) noexcept
    : member(data, data + size)
{
}

template <typename T, std::size_t E, typename C>
template <typename ContiguousIterator>
constexpr span<T, E, C>::span(ContiguousIterator begin,
                              ContiguousIterator end) noexcept
    : member(&*begin, &*end)
{
}

template <typename T, std::size_t E, typename C>
constexpr bool span<T, E, C>::empty() const noexcept
{
    return size() == 0;
}

template <typename T, std::size_t E, typename C>
constexpr bool span<T, E, C>::full() const noexcept
{
    return size() == capacity();
}

template <typename T, std::size_t E, typename C>
constexpr auto span<T, E, C>::size() const noexcept -> size_type
{
    return member.last - member.span.data();
}

template <typename T, std::size_t E, typename C>
constexpr auto span<T, E, C>::capacity() const noexcept -> size_type
{
    return member.span.capacity();
}

template <typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<T, E, C>::top() noexcept -> value_type&
{
    assert(!empty());
    return member.span.front();
}

template <typename T, std::size_t E, typename C>
constexpr auto span<T, E, C>::top() const noexcept -> const value_type&
{
    VISTA_CXX14(assert(!empty()));
    return member.span.front();
}

template <typename T, std::size_t E, typename C>
void span<T, E, C>::push(value_type input) noexcept(std::is_nothrow_move_constructible<value_type>::value && std::is_nothrow_move_assignable<value_type>::value)
{
    assert(!full());
    *member.last = std::move(input);
    ++member.last;
    heap::push(member.span.data(), member.last, member.comparator);
}

template <typename T, std::size_t E, typename C>
void span<T, E, C>::pop() noexcept (std::is_nothrow_move_constructible<value_type>::value && std::is_nothrow_move_assignable<value_type>::value)
{
    assert(!empty());
    heap::pop(member.span.data(), member.last, member.comparator);
    --member.last;
}

} // namespace priority
} // namespace vista
