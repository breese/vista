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

#include <utility> // std::pair
#include <functional> // std::less
#include <vista/span.hpp>

namespace vista
{
namespace map
{

template <typename T1, typename T2>
using pair = std::pair<T1, T2>;

//! @brief Fixed-capacity associative span.
//!
//! Violation of any precondition results in undefined behavior.

template <typename Key,
          typename T,
          std::size_t Extent = dynamic_extent,
          typename Compare = std::less<Key>>
class span
    : protected vista::span<map::pair<Key, T>, Extent>
{
    using super = vista::template span<map::pair<Key, T>, Extent>;

public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = typename super::element_type;
    using key_compare = Compare;
    struct value_compare
    {
        bool operator()(const value_type& lhs, const value_type& rhs)
        {
            return Compare{}(lhs.first, rhs.first);
        }
    };
    using size_type = typename super::size_type;
    using pointer = typename super::pointer;
    using iterator = typename super::iterator;
    using const_iterator = typename super::const_iterator;

    //! @brief Creates empty map span.
    //!
    //! No elements can be inserted into a zero-capacity span. The span must
    //! therefore be recreated before use.
    //!
    //! @pre Extent == 0 or Extent == dynamic_extent
    //!
    //! @post capacity() == 0
    //! @post size() == 0

    constexpr span() noexcept;

    //! @brief Creates sorted span by moving.

    constexpr span(span&&) noexcept = default;

    //! @brief Creates map span from array.
    //!
    //! @post capacity() == Extent
    //! @post size() == 0

    template <std::size_t N,
              typename std::enable_if<(Extent == N || Extent == dynamic_extent), int>::type = 0>
    explicit constexpr span(value_type (&array)[N]) noexcept;

    //! @brief Creates map span from iterators.
    //!
    //! @pre Extent == std::distance(begin, end) or Extent == dynamic_extent
    //! @post capacity() == std::distance(begin, end)
    //! @post size() == 0

    template <typename ContiguousIterator>
    constexpr span(ContiguousIterator begin,
                   ContiguousIterator end) noexcept;

    //! @brief Checks if span is empty.
    //!
    //! Span is empty when size() == 0

    constexpr bool empty() const noexcept;

    //! @brief Checks if span is full.
    //!
    //! Span is full when size() == capacity()

    constexpr bool full() const noexcept;

    //! @brief Returns the number of elements in span.

    constexpr size_type size() const noexcept;

    //! @brief Returns the maximum possible number of elements in span.

    using super::capacity;

    //! @brief Clears the span.
    //!
    //! The cleared elements in the underlying storage are not destroyed.
    //!
    //! @post size() == 0

    VISTA_CXX14_CONSTEXPR
    void clear() noexcept;

    //! @brief Inserts element with given key.
    //!
    //! Notice that the return type differs from std::map.
    //!
    //! Linear time complexity.
    //!
    //! @returns Iterator to inserted element, or end() if span already is full.

    VISTA_CXX14_CONSTEXPR
    iterator insert(value_type) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value);

    //! @brief Removes the element at given position.
    //!
    //! The removed element is not destroyed.
    //!
    //! Linear time complexity.

    VISTA_CXX14_CONSTEXPR
    iterator remove(iterator position) noexcept(vista::detail::is_nothrow_swappable<value_type>::value);

    //! @brief Inserts unspecified element at the end of the span.
    //!
    //! The span is extended to include the element in the underlying storage
    //! after the current end.
    //!
    //! The span may not be exteded beyond capacity.
    //!
    //! This function breaks the class invariants which must be restored with
    //! reorder_back(). The purpuse of these two functions is to enable the
    //! storage owner to create emplace() functionality.
    //!
    //!    auto last = expand_back();
    //!    std::construct_at(last, args...);
    //!    auto position = reorder_back();
    //!
    //! @pre !full()
    //!
    //! @returns iterator to inserted element.
    //!
    //! @sa reorder_back

    VISTA_CXX14_CONSTEXPR
    iterator expand_back() noexcept;

    //! @brief Moves the back element into its proper position.
    //!
    //! This function restores the class invariants broken by a single
    //! expand_back().
    //!
    //! Linear time complexity.
    //!
    //! @returns iterator to destination position of back element.
    //!
    //! @sa expand_back

    VISTA_CXX14_CONSTEXPR
    iterator reorder_back() noexcept(vista::detail::is_nothrow_swappable<value_type>::value);

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

    //! @brief Returns iterator to the beginning of the span.

    using super::begin;
    using super::cbegin;

    //! @brief Returns iterator to the ending of the span.

    VISTA_CXX14_CONSTEXPR iterator end() noexcept;
    constexpr const_iterator end() const noexcept;
    constexpr const_iterator cend() const noexcept;

    constexpr key_compare key_comp() const noexcept;
    constexpr value_compare value_comp() const noexcept;

protected:
    // Span is non-copyable because more spans operating on the same storage
    // with their own internal state would cause invariants to break.
    span(const span&) = delete;
    span& operator=(const span&) = delete;

protected:
    struct
    {
        iterator tail;
    } member;

private:
    static_assert(std::is_default_constructible<key_type>::value, "Key must be default constructible");
    static_assert(std::is_default_constructible<mapped_type>::value, "T must be default constructible");
    static_assert(std::is_move_assignable<value_type>::value, "value_type must be move assignable");
};

} // namespace map
} // namespace vista

#include <vista/map/detail/span.ipp>

#endif // VISTA_MAP_SPAN_HPP
