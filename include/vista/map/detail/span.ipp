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

namespace vista
{
namespace map
{

namespace
{

//! @brief Returns position where element is or would have been.
//!
//! @pre is_sorted(begin, end)
//! @pre begin != end

template <typename RandomAccessIterator, typename T, typename Compare>
VISTA_CXX14_CONSTEXPR
RandomAccessIterator lower_bound(RandomAccessIterator begin, RandomAccessIterator end, const T& needle, Compare compare)
{
    auto step = end - begin;
    if (step == 0)
        return end;
    // Branchless binary search
    while (const auto half = step >> 1)
    {
        begin += compare(begin[half], needle) ? half : 0;
        step -= half;
    }
    return begin + compare(*begin, needle);
}

} // anonymous namespace

template <typename K, typename T, std::size_t E, typename C>
constexpr span<K, T, E, C>::span() noexcept
    : member{ nullptr, nullptr, nullptr }
{
}

template <typename K, typename T, std::size_t E, typename C>
template <typename ContiguousIterator>
constexpr span<K, T, E, C>::span(ContiguousIterator begin,
                                 ContiguousIterator end) noexcept
    : member{ &*begin, &*end, &*begin }
{
    VISTA_CXX14(assert(size_type(end - begin) == capacity()));
}

template <typename K, typename T, std::size_t E, typename C>
template <std::size_t N,
          typename std::enable_if<(E == N || E == dynamic_extent), int>::type>
constexpr span<K, T, E, C>::span(value_type (&array)[N]) noexcept
    : span(array, array + N)
{
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto span<K, T, E, C>::capacity() const noexcept -> size_type
{
    return member.capacity();
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto span<K, T, E, C>::size() const noexcept -> size_type
{
    return member.tail - member.begin;
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
VISTA_CXX14_CONSTEXPR
void span<K, T, E, C>::clear() noexcept(std::is_trivially_destructible<value_type>::value || std::is_nothrow_default_constructible<value_type>::value)
{
    if (!std::is_trivially_destructible<value_type>::value)
    {
        for (auto current = member.begin; current != member.tail; ++current)
        {
            // Overwrite with default-constructed instance
            destroy_at(current);
            current = construct_at(current);
        }
    }
    member.tail = member.begin;
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::insert(value_type input) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value) -> iterator
{
    return emplace(std::move(input));
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::insert(iterator, value_type input) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value) -> iterator
{
    // Ignores hint
    return emplace(std::move(input));
}

template <typename K, typename T, std::size_t E, typename C>
template <typename... Args>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::emplace(Args&&... args) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value) -> iterator
{
    auto current = end();
    if (full())
        return current;

    // Construct at end and bubble into correct position

    destroy_at(member.tail);
    member.tail = construct_at(member.tail, std::forward<Args>(args)...);
    ++member.tail;
    while ((current != begin()) && key_comp()(current[0].first, current[-1].first))
    {
        using std::swap;
        swap(current[0], current[-1]);
        --current;
    }
    return current;
}

template <typename K, typename T, std::size_t E, typename C>
template <typename... Args>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::emplace_hint(iterator, Args&&... args) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value) -> iterator
{
    // Ignores hint
    return emplace(std::forward<Args>(args)...);
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::erase(const key_type& key) noexcept(std::is_nothrow_move_assignable<value_type>::value) -> size_type
{
    size_type count = 0;
    auto where = lower_bound(key);
    while (!(where == member.tail || key_comp()(key, where->first)))
    {
        where = erase(where);
        ++count;
    }
    return count;
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::erase(iterator position) noexcept(std::is_nothrow_move_assignable<value_type>::value) -> iterator
{
    assert(!empty());
    assert(position != end());

    destroy_at(position);
    position = construct_at(position);

    // Move elements after erased element backwards

    for (auto current = position; current != member.tail - 1; ++current)
    {
        current[0] = std::move(current[1]);
    }
    --member.tail;
    return position;
}

template <typename K, typename T, std::size_t E, typename C>
constexpr bool span<K, T, E, C>::contains(const key_type& key) const noexcept
{
    return find(key) != end();
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::find(const key_type& key) noexcept -> iterator
{
    auto where = lower_bound(key);
    if (where == member.tail || key_comp()(key, where->first))
        return end();
    return where;
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::find(const key_type& key) const noexcept -> const_iterator
{
    auto where = lower_bound(key);
    if (where == member.tail || key_comp()(key, where->first))
        return end();
    return where;
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::lower_bound(const key_type& key) noexcept -> iterator
{
    return map::lower_bound(begin(),
                            end(),
                            key,
                            [] (const value_type& lhs, const key_type& rhs)
                            {
                                return key_compare{}(lhs.first, rhs);
                            });
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::lower_bound(const key_type& key) const noexcept -> const_iterator
{
    return map::lower_bound(begin(),
                            end(),
                            key,
                            [] (const value_type& lhs, const key_type& rhs)
                            {
                                return key_compare{}(lhs.first, rhs);
                            });
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::operator[](const key_type& key) noexcept -> mapped_type&
{
    auto where = lower_bound(key);
    if (where == member.tail || key_comp()(key, where->first))
    {
        where = insert(where, value_type{ key, mapped_type{} });
    }
    return where->second;
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::operator[](key_type&& key) noexcept -> mapped_type&
{
    auto where = lower_bound(key);
    if (where == member.tail || key_comp()(key, where->first))
    {
        where = insert(where, value_type{ std::move(key), mapped_type{} });
    }
    return where->second;
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::begin() noexcept -> iterator
{
    return member.begin;
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto span<K, T, E, C>::begin() const noexcept -> const_iterator
{
    return member.begin;
}

template <typename K, typename T, std::size_t E, typename C>
constexpr auto span<K, T, E, C>::cbegin() const noexcept -> const_iterator
{
    return member.begin;
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
template <typename... Args>
VISTA_CXX14_CONSTEXPR
auto span<K, T, E, C>::construct_at(pointer storage, Args&&... args) -> pointer
{
    return new (storage) value_type{std::forward<Args>(args)...};
}

template <typename K, typename T, std::size_t E, typename C>
VISTA_CXX14_CONSTEXPR
void span<K, T, E, C>::destroy_at(pointer storage)
{
    storage->~value_type();
}

} // namespace map
} // namespace vista
