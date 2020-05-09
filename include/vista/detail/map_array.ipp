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
#include <vista/detail/memory.hpp>

namespace vista
{

template <typename K, typename T, std::size_t N, typename C>
constexpr map_array<K, T, N, C>::map_array() noexcept
    : span(storage::begin(), storage::end())
{
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
void map_array<K, T, E, C>::clear() noexcept(std::is_trivially_destructible<value_type>::value || std::is_nothrow_default_constructible<value_type>::value)
{
    if (!std::is_trivially_destructible<value_type>::value)
    {
        for (auto current = begin(); current != end(); ++current)
        {
            // Overwrite with default-constructed instance
            vista::detail::destroy_at(current);
            current = vista::detail::construct_at(current);
        }
    }
    span::clear();
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto map_array<K, T, E, C>::insert(iterator, value_type input) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value) -> iterator
{
    // Ignore hint
    return insert(std::move(input));
}

template <typename K, typename T, std::size_t E, typename C>
template <typename... Args>
VISTA_CXX14_CONSTEXPR
auto map_array<K, T, E, C>::emplace(Args&&... args) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value) -> iterator
{
    assert(!full());

    // Expand span with available slot
    auto position = span::expand_back();

    // Construct value in-place at available slot
    vista::detail::destroy_at(position);
    vista::detail::construct_at(position, std::forward<Args>(args)...);

    // Push into sorted position
    return span::reorder_back();
}

template <typename K, typename T, std::size_t E, typename C>
template <typename... Args>
VISTA_CXX14_CONSTEXPR
auto map_array<K, T, E, C>::emplace_hint(iterator, Args&&... args) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value) -> iterator
{
    // Ignores hint
    return emplace(std::forward<Args>(args)...);
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto map_array<K, T, E, C>::erase(const key_type& key) noexcept(std::is_nothrow_move_assignable<value_type>::value) -> size_type
{
    size_type count = 0;
    auto where = lower_bound(key);
    while (!(where == end() || key_comp()(key, where->first)))
    {
        where = erase(where);
        ++count;
    }
    return count;
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto map_array<K, T, E, C>::erase(iterator position) noexcept(std::is_nothrow_move_assignable<value_type>::value) -> iterator
{
    if (position == end())
        return position;

    // Replace entry with default-constructed value
    vista::detail::destroy_at(position);
    position = vista::detail::construct_at(position);

    return span::remove(position);
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
bool map_array<K, T, E, C>::contains(const key_type& key) const noexcept
{
    return find(key) != end();
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto map_array<K, T, E, C>::find(const key_type& key) noexcept -> iterator
{
    auto where = lower_bound(key);
    if (where == end() || key_comp()(key, where->first))
        return end();
    return where;
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto map_array<K, T, E, C>::find(const key_type& key) const noexcept -> const_iterator
{
    auto where = lower_bound(key);
    if (where == end() || key_comp()(key, where->first))
        return end();
    return where;
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto map_array<K, T, E, C>::operator[](const key_type& key) noexcept -> mapped_type&
{
    auto where = lower_bound(key);
    if (where == end() || key_comp()(key, where->first))
    {
        where = insert(where, value_type{ key, mapped_type{} });
    }
    return where->second;
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto map_array<K, T, E, C>::operator[](key_type&& key) noexcept -> mapped_type&
{
    auto where = lower_bound(key);
    if (where == end() || key_comp()(key, where->first))
    {
        where = insert(where, value_type{ std::move(key), mapped_type{} });
    }
    return where->second;
}

} // namespace vista
