#ifndef VISTA_MAP_SPAN_HPP
#define VISTA_MAP_SPAN_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef> // std::size_t
#include <functional> // std::less
#include <utility> // std::pair
#include <vista/detail/config.hpp>
#include <vista/detail/type_traits.hpp>

namespace vista
{
namespace map
{

template <typename T1, typename T2>
using pair = std::pair<T1, T2>;

//! @brief Associative span.
//!
//! A view that turens contiguous memory into an associative array.
//!
//! The memory is not owned by the span. The owner must ensure that the span is
//! destroyed before the memory is released.
//!
//! The view is non-copyable to avoid having two views with different states
//! that manipulate the same memory.
//!
//! Violation of any precondition results in undefined behavior.

template <typename Key,
          typename T,
          std::size_t Extent = dynamic_extent,
          typename Compare = std::less<Key>>
class span
{
    static_assert(std::is_default_constructible<Key>::value, "Key must be default constructible");
    static_assert(std::is_move_assignable<Key>::value, "Key must be move assignable");
    static_assert(std::is_default_constructible<T>::value, "T must be default constructible");
    static_assert(std::is_move_assignable<T>::value, "T must be move assignable");

public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = pair<Key, T>;
    using size_type = std::size_t;
    using key_compare = Compare;
    using pointer = typename std::add_pointer<value_type>::type;
    using const_pointer = typename std::add_pointer<typename std::add_const<value_type>::type>::type;
    using iterator = pointer; // RandomAccessIterator
    using const_iterator = const_pointer; // RandomAccessIterator

    //! @brief Creates empty associative span.
    //!
    //! When Extent == dynamic_extent the snap also has zero capacity. No
    //! elements can be inserted into a zero capacity span. The span must
    //! therefore be recreated before use.
    //!
    //! @post capacity() == 0 if Extent == dynamic_extent
    //! @post capacity() == Extent otherwise
    //! @post size() == 0

    constexpr span() noexcept;

    //! @brief Creates associative span by moving.
    //!
    //! State of moved-from span is valid but unspecified.

    constexpr span(span&&) noexcept = default;

    //! @brief Creates associative span from iterators.
    //!
    //! @pre Extent == std::distance(begin, end) or Extent == dynamic_extent
    //! @post capacity() == std::distance(begin, end)
    //! @post size() == 0

    template <typename ContiguousIterator>
    constexpr span(ContiguousIterator begin,
                   ContiguousIterator end) noexcept;

    //! @brief Creates associative span from array.
    //!
    //! @post capacity() == N
    //! @post size() == 0

    template <std::size_t N,
              typename std::enable_if<(Extent == N || Extent == dynamic_extent), int>::type = 0>
    explicit constexpr span(value_type (&array)[N]) noexcept;

    //! @brief Recreates associative span by moving.
    //!
    //! State of moved-from span is valid but unspecified.

    VISTA_CXX14_CONSTEXPR
    span& operator=(span&&) noexcept = default;

    //! @brief Returns the maximum possible number of elements in span.

    constexpr size_type capacity() const noexcept;

    //! @brief Returns the number of elements in span.

    constexpr size_type size() const noexcept;

    //! @brief Checks if span is empty.
    //!
    //! Span is empty when size() == 0

    constexpr bool empty() const noexcept;

    //! @brief Checks if span is full.
    //!
    //! Span is full when size() == capacity()

    constexpr bool full() const noexcept;

    //! @brief Clears the span.
    //!
    //! Elements are destroyed.
    //!
    //! @post size() == 0

    VISTA_CXX14_CONSTEXPR
    void clear() noexcept(std::is_trivially_destructible<value_type>::value || std::is_nothrow_default_constructible<value_type>::value);

    //! @brief Inserts element with given key.
    //!
    //! Notice that the return type differs from std::map.
    //!
    //! Linear time complexity.
    //!
    //! @returns Iterator to inserted element, or end() if span already is full.

    VISTA_CXX14_CONSTEXPR
    iterator insert(value_type) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value);

    //! @brief Inserts element with given key.
    //!
    //! Linear time complexity.
    //!
    //! @returns Iterator to inserted element, or end() if span already is full.

    VISTA_CXX14_CONSTEXPR
    iterator insert(iterator hint, value_type) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value);

    //! @brief Inserts in-place constructed element.
    //!
    //! Linear time complexity.
    //!
    //! @returns Iterator to inserted element, or end() if span already is full.

    template <typename... Args>
    VISTA_CXX14_CONSTEXPR
    iterator emplace(Args&&...) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value);

    //! @brief Inserts in-place constructed element.
    //!
    //! Linear time complexity.
    //!
    //! @returns Iterator to inserted element, or end() if span already is full.

    template <typename... Args>
    VISTA_CXX14_CONSTEXPR
    iterator emplace_hint(iterator, Args&&...) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value);

    //! @brief Erases all elements with given key.
    //!
    //! The erased elements will be left in a moved-from state.
    //!
    //! Linear time complexity.
    //!
    //! @pre !empty()

    VISTA_CXX14_CONSTEXPR
    size_type erase(const key_type&) noexcept(std::is_nothrow_move_assignable<value_type>::value);

    //! @brief Erases the element at given position.
    //!
    //! The erased element will be left in a moved-from state.
    //!
    //! Linear time complexity.
    //!
    //! @pre !empty()
    //! @pre position != end()

    VISTA_CXX14_CONSTEXPR
    iterator erase(iterator position) noexcept(std::is_nothrow_move_assignable<value_type>::value);

    //! @brief Checks if span contains key.
    //!
    //! Logarithmic time complexity.

    constexpr bool contains(const key_type&) const noexcept;

    //! @brief Returns iterator to element with given key.
    //!
    //! If key not found, return end()
    //!
    //! Logarithmic time complexity.

    VISTA_CXX14_CONSTEXPR
    iterator find(const key_type&) noexcept;

    VISTA_CXX14_CONSTEXPR
    const_iterator find(const key_type&) const noexcept;

    //! @brief Returns iterator to element with given key.
    //!
    //! If key not found, then returns iterator to the entry at the position where
    //! the searched-for entry should have been, or the end iterator.
    //!
    //! Logarithmic time complexity.

    VISTA_CXX14_CONSTEXPR
    iterator lower_bound(const key_type&) noexcept;

    VISTA_CXX14_CONSTEXPR
    const_iterator lower_bound(const key_type&) const noexcept;

    //! @brief Returns reference to element with given key.
    //!
    //! If key not found, insert element with copied key and default-constructed value.
    //!
    //! Logarithmic time complexity.

    VISTA_CXX14_CONSTEXPR
    mapped_type& operator[](const key_type& key) noexcept;

    //! @brief Returns reference to element with given key.
    //!
    //! If key not found, insert element with moved key and default-constructed value.
    //!
    //! Logarithmic time complexity.

    VISTA_CXX14_CONSTEXPR
    mapped_type& operator[](key_type&& key) noexcept;

    //! @brief Returns iterator to the beginning of the span.

    VISTA_CXX14_CONSTEXPR iterator begin() noexcept;
    constexpr const_iterator begin() const noexcept;
    constexpr const_iterator cbegin() const noexcept;

    //! @brief Returns iterator to the ending of the span.

    VISTA_CXX14_CONSTEXPR iterator end() noexcept;
    constexpr const_iterator end() const noexcept;
    constexpr const_iterator cend() const noexcept;

    constexpr key_compare key_comp() const noexcept;

private:
    // Non-copyable
    span(const span&) = delete;
    span& operator=(const span&) = default;

private:
    template <typename, size_type E1>
    struct member_storage
    {
        constexpr size_type capacity() const noexcept
        {
            return E1;
        }

        iterator begin;
        iterator end;
        iterator tail;
    };

    template <typename T1>
    struct member_storage<T1, dynamic_extent>
    {
        constexpr size_type capacity() const noexcept
        {
            return end - tail;
        }

        iterator begin;
        iterator end;
        iterator tail;
    };

    struct member_storage<T, Extent> member;
};

} // namespace map
} // namespace vista

#include <vista/map/detail/span.ipp>

#endif // VISTA_MAP_SPAN_HPP
