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
namespace map
{

template <typename K, typename T, std::size_t E, typename C>
constexpr span<K, T, E, C>::span() noexcept
    : super(nullptr, nullptr),
      member{ nullptr }
{
}

template <typename K, typename T, std::size_t E, typename C>
template <std::size_t N,
          typename std::enable_if<(E == N || E == dynamic_extent), int>::type>
constexpr span<K, T, E, C>::span(value_type (&array)[N]) noexcept
    : super(array, array + N),
      member{ array }
{
}

template <typename K, typename T, std::size_t E, typename C>
template <typename ContiguousIterator>
constexpr span<K, T, E, C>::span(ContiguousIterator begin,
                                 ContiguousIterator end) noexcept
    : super(&*begin, &*end),
      member{ &*begin }
{
    VISTA_CXX14(assert(size_type(end - begin) == capacity()));
}

template <typename K, typename T, std::size_t E, typename C>
constexpr bool span<K, T, E, C>::empty() const noexcept
{
    return size() == 0;
}

template <typename K, typename T, std::size_t E, typename C>
constexpr bool span<K, T, E, C>::full() const noexcept
{
    return size() == capacity();
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto span<K, T, E, C>::size() const noexcept -> size_type
{
    return member.tail - begin();
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto span<K, T, E, C>::capacity() const noexcept -> size_type
{
    return super::size();
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
void span<K, T, E, C>::clear() noexcept
{
    member.tail = begin();
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::insert(value_type input) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value) -> iterator
{
    if (full())
        return end();

    auto position = expand_back();
    *position = std::move(input);
    return reorder_back();
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::remove(iterator position) noexcept(vista::detail::is_nothrow_swappable<value_type>::value) -> iterator
{
    if (position != member.tail)
    {
        // Move entry to end and decrease span size
        member.tail = pop_sorted(position, member.tail);
    }
    return position;
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::expand_back() noexcept -> iterator
{
    assert(!full());

    ++member.tail;
    return member.tail - 1;
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::reorder_back() noexcept(vista::detail::is_nothrow_swappable<value_type>::value) -> iterator
{
    return push_sorted(begin(), end(), value_comp());
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::lower_bound(const key_type& key) noexcept -> iterator
{
    return lower_bound_sorted(begin(),
                              end(),
                              key,
                              [this] (const value_type& value, const key_type& key)
                              {
                                  return key_comp()(value.first, key);
                              });
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::lower_bound(const key_type& key) const noexcept -> const_iterator
{
    return lower_bound_sorted(begin(),
                              end(),
                              key,
                              [this] (const value_type& value, const key_type& key)
                              {
                                  return key_comp()(value.first, key);
                              });
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::end() noexcept -> iterator
{
    return member.tail;
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto span<K, T, E, C>::end() const noexcept -> const_iterator
{
    return member.tail;
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto span<K, T, E, C>::cend() const noexcept -> const_iterator
{
    return member.tail;
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto span<K, T, E, C>::key_comp() const noexcept -> key_compare
{
    return key_compare{};
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto span<K, T, E, C>::value_comp() const noexcept -> value_compare
{
    return value_compare{};
}

} // namespace map
} // namespace vista
