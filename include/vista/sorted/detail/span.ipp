///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <vista/sorted/algorithm.hpp>

namespace vista
{
namespace sorted
{

template <typename T, std::size_t E, typename C>
constexpr span<T, E, C>::span() noexcept
    : member{ nullptr, nullptr, nullptr }
{
}

template <typename T, std::size_t E, typename C>
template <typename ContiguousIterator>
constexpr span<T, E, C>::span(ContiguousIterator begin,
                              ContiguousIterator end) noexcept
    : member{ &*begin, &*end, &*begin }
{
    VISTA_CXX14(assert(size_type(end - begin) == capacity()));
}

template <typename T, std::size_t E, typename C>
constexpr auto span<T, E, C>::capacity() const noexcept -> size_type
{
    return member.capacity();
}

template <typename T, std::size_t E, typename C>
constexpr auto span<T, E, C>::size() const noexcept -> size_type
{
    return member.tail - member.begin;
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
VISTA_CXX14_CONSTEXPR
void span<T, E, C>::clear() noexcept
{
    member.tail = member.begin;
}

template <typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<T, E, C>::push(value_type input) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value) -> iterator
{
    assert(!full());

    *member.tail++ = std::move(input);
    return sorted::push(member.begin, member.tail, comp());
}

template <typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
void span<T, E, C>::pop(const value_type& input) noexcept(vista::detail::is_nothrow_swappable<value_type>::value)
{
    auto position = lower_bound(input);
    if (position == member.tail || comp()(input, *position))
        return;
    pop(position);
}

template <typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
void span<T, E, C>::pop(iterator position)  noexcept(vista::detail::is_nothrow_swappable<value_type>::value)
{
    member.tail = sorted::pop(position, member.tail);
}

template <typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<T, E, C>::lower_bound(const value_type& value) noexcept -> iterator
{
    return sorted::lower_bound(begin(),
                               end(),
                               value,
                               comp());
}

template <typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<T, E, C>::lower_bound(const value_type& value) const noexcept -> const_iterator
{
    return sorted::lower_bound(begin(),
                               end(),
                               value,
                               comp());
}

template <typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<T, E, C>::begin() noexcept -> iterator
{
    return member.begin;
}

template <typename T, std::size_t E, typename C>
constexpr auto span<T, E, C>::begin() const noexcept -> const_iterator
{
    return member.begin;
}

template <typename T, std::size_t E, typename C>
constexpr auto span<T, E, C>::cbegin() const noexcept -> const_iterator
{
    return member.begin;
}

template <typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<T, E, C>::end() noexcept -> iterator
{
    return member.tail;
}

template <typename T, std::size_t E, typename C>
constexpr auto span<T, E, C>::end() const noexcept -> const_iterator
{
    return member.tail;
}

template <typename T, std::size_t E, typename C>
constexpr auto span<T, E, C>::cend() const noexcept -> const_iterator
{
    return member.tail;
}

template <typename T, std::size_t E, typename C>
constexpr auto span<T, E, C>::comp() const noexcept -> compare
{
    return compare{};
}

} // namespace sorted
} // namespace vista
