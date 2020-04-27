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
namespace map
{

template <typename K, typename T, std::size_t N, typename C>
constexpr array<K, T, N, C>::member_storage::member_storage() noexcept
    : span(storage, storage + N),
      tail(storage)
{
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto array<K, T, E, C>::capacity() const noexcept -> size_type
{
    return member.span.capacity();
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto array<K, T, E, C>::size() const noexcept -> size_type
{
    return member.tail - member.span.begin();
}

template <typename K, typename T, std::size_t E, typename C>
constexpr bool array<K, T, E, C>::empty() const noexcept
{
    return size() == 0;
}

template <typename K, typename T, std::size_t E, typename C>
constexpr bool array<K, T, E, C>::full() const noexcept
{
    return size() == capacity();
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
void array<K, T, E, C>::clear() noexcept(std::is_trivially_destructible<value_type>::value || std::is_nothrow_default_constructible<value_type>::value)
{
    if (!std::is_trivially_destructible<value_type>::value)
    {
        for (auto current = begin(); current != end(); ++current)
        {
            // Overwrite with default-constructed instance
            destroy_at(current);
            current = construct_at(current);
        }
    }
    member.tail = begin();
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto array<K, T, E, C>::insert(value_type input) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value) -> iterator
{
    assert(!full());

    *member.tail++ = std::move(input);
    return sorted::push(begin(), member.tail, value_comp());
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto array<K, T, E, C>::insert(iterator, value_type input) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value) -> iterator
{
    // Ignore hint
    return insert(std::move(input));
}

template <typename K, typename T, std::size_t E, typename C>
template <typename... Args>
VISTA_CXX14_CONSTEXPR
auto array<K, T, E, C>::emplace(Args&&... args) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value) -> iterator
{
    // FIXME: construct_at(end()) and push (like push_heap?)
    return insert(value_type{ std::forward<Args>(args)... });
}

template <typename K, typename T, std::size_t E, typename C>
template <typename... Args>
VISTA_CXX14_CONSTEXPR
auto array<K, T, E, C>::emplace_hint(iterator, Args&&... args) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value) -> iterator
{
    // Ignores hint
    return emplace(std::forward<Args>(args)...);
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto array<K, T, E, C>::erase(const key_type& key) noexcept(std::is_nothrow_move_assignable<value_type>::value) -> size_type
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
auto array<K, T, E, C>::erase(iterator position) noexcept(std::is_nothrow_move_assignable<value_type>::value) -> iterator
{
    assert(!empty());
    assert(position != end());

    // Replace entry with default-constructed value
    destroy_at(position);
    position = construct_at(position);

    // Move entry to end and decrease span size
    member.tail = sorted::pop(position, member.tail);

    return position;
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
bool array<K, T, E, C>::contains(const key_type& key) const noexcept
{
    return find(key) != end();
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto array<K, T, E, C>::find(const key_type& key) noexcept -> iterator
{
    auto where = lower_bound(key);
    if (where == end() || key_comp()(key, where->first))
        return end();
    return where;
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto array<K, T, E, C>::find(const key_type& key) const noexcept -> const_iterator
{
    auto where = lower_bound(key);
    if (where == end() || key_comp()(key, where->first))
        return end();
    return where;
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto array<K, T, E, C>::lower_bound(const key_type& key) noexcept -> iterator
{
    return sorted::lower_bound(begin(),
                               end(),
                               key,
                               [this] (const value_type& value, const key_type& key)
                               {
                                   return key_comp()(value.first, key);
                               });
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto array<K, T, E, C>::lower_bound(const key_type& key) const noexcept -> const_iterator
{
    return sorted::lower_bound(begin(),
                               end(),
                               key,
                               [this] (const value_type& value, const key_type& key)
                               {
                                   return key_comp()(value.first, key);
                               });
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto array<K, T, E, C>::operator[](const key_type& key) noexcept -> mapped_type&
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
auto array<K, T, E, C>::operator[](key_type&& key) noexcept -> mapped_type&
{
    auto where = lower_bound(key);
    if (where == end() || key_comp()(key, where->first))
    {
        where = insert(where, value_type{ std::move(key), mapped_type{} });
    }
    return where->second;
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto array<K, T, E, C>::begin() noexcept -> iterator
{
    return member.span.begin();
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto array<K, T, E, C>::begin() const noexcept -> const_iterator
{
    return member.span.begin();
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto array<K, T, E, C>::cbegin() const noexcept -> const_iterator
{
    return member.span.cbegin();
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto array<K, T, E, C>::end() noexcept -> iterator
{
    return member.tail;
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto array<K, T, E, C>::end() const noexcept -> const_iterator
{
    return member.tail;
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto array<K, T, E, C>::cend() const noexcept -> const_iterator
{
    return member.tail;
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto array<K, T, E, C>::key_comp() const noexcept -> key_compare
{
    return key_compare{};
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto array<K, T, E, C>::value_comp() const noexcept -> value_compare
{
    return value_compare{};
}

template <typename K, typename T, std::size_t E, typename C>
template <typename... Args>
VISTA_CXX14_CONSTEXPR
auto array<K, T, E, C>::construct_at(pointer storage, Args&&... args) -> pointer
{
    return new (storage) value_type{std::forward<Args>(args)...};
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
void array<K, T, E, C>::destroy_at(pointer storage)
{
    storage->~value_type();
}

} // namespace map
} // namespace vista
