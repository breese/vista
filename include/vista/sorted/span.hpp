#ifndef VISTA_SORTED_SPAN_HPP
#define VISTA_SORTED_SPAN_HPP

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
#include <vista/detail/config.hpp>
#include <vista/detail/type_traits.hpp>

namespace vista
{
namespace sorted
{

//! @brief Sorted span.
//!
//! A view that maintains a sorted sequence in contiguous memory.
//!
//! The memory is not owned by the span. The owner must ensure that the span is
//! destroyed before the memory is released.
//!
//! Violation of any precondition results in undefined behavior.

template <typename T,
          std::size_t Extent = dynamic_extent,
          typename Compare = std::less<T>>
class span
{
    static_assert(std::is_move_assignable<T>::value, "T must be move assignable");

public:
    using value_type = T;
    using size_type = std::size_t;
    using compare = Compare;
    using pointer = typename std::add_pointer<value_type>::type;
    using const_pointer = typename std::add_pointer<typename std::add_const<value_type>::type>::type;
    using iterator = pointer; // RandomAccessIterator
    using const_iterator = const_pointer; // RandomAccessIterator

    //! @brief Creates empty sorted span.
    //!
    //! @post capacity() == 0 if Extent == dynamic_extent
    //! @post capacity() == Extent otherwise
    //! @post size() == 0

    constexpr span() noexcept;

    //! @brief Creates sorted span by moving.

    constexpr span(span&&) noexcept = default;

    //! @brief Creates sorted span from array.
    //!
    //! @post capacity() == N
    //! @post size() == 0

    template <std::size_t N,
              typename std::enable_if<(Extent == N || Extent == dynamic_extent), int>::type = 0>
    explicit constexpr span(value_type (&array)[N]) noexcept;

    //! @brief Creates sorted span from iterators.
    //!
    //! @pre Extent == std::distance(begin, end) or Extent == dynamic_extent
    //! @post capacity() == std::distance(begin, end)
    //! @post size() == 0

    template <typename ContiguousIterator>
    constexpr span(ContiguousIterator begin,
                   ContiguousIterator end) noexcept;

    //! @brief Recreates sorted span by moving.
    //!
    //! State of moved-from span is valid but unspecified.

    VISTA_CXX14_CONSTEXPR
    span& operator=(span&&) noexcept = default;

    //! @brief Checks if span is empty.

    constexpr bool empty() const noexcept;

    //! @brief Checks if span is full.

    constexpr bool full() const noexcept;

    //! @brief Returns the number of elements in span.

    constexpr size_type size() const noexcept;

    //! @brief Returns the maximum possible number of elements in span.

    constexpr size_type capacity() const noexcept;

    //! @brief Clears the span.
    //!
    //! The cleared elements in the underlying storage are not destroyed.
    //!
    //! @post size() == 0

    VISTA_CXX14_CONSTEXPR
    void clear() noexcept;

    //! @brief Inserts element into sorted position.
    //!
    //! Linear time complexity.
    //!
    //! @returns Iterator to inserted element, or end() if span already is full.

    VISTA_CXX14_CONSTEXPR
    iterator push(value_type) noexcept(std::is_nothrow_move_assignable<value_type>::value && vista::detail::is_nothrow_swappable<value_type>::value);

    //! @brief Removes the given element.
    //!
    //! When there are duplicated elements, only the first matching element is removed.
    //!
    //! The removed element in the underlying storage is not destroyed.
    //!
    //! Linear time complexity.
    //!
    //! @pre !empty()
    //! @pre position != end()

    VISTA_CXX14_CONSTEXPR
    void pop(const value_type&)  noexcept(vista::detail::is_nothrow_swappable<value_type>::value);

    //! @brief Removes the given position.
    //!
    //! The removed element in the underlying storage is not destroyed.
    //!
    //! Linear time complexity.
    //!
    //! @pre !empty()
    //! @pre position != end()

    VISTA_CXX14_CONSTEXPR
    void pop(iterator position)  noexcept(vista::detail::is_nothrow_swappable<value_type>::value);

    //! @brief Returns iterator to element with given key.
    //!
    //! If key not found, then returns iterator to the entry at the position where
    //! the searched-for entry should have been, or the end iterator.
    //!
    //! Logarithmic time complexity.

    VISTA_CXX14_CONSTEXPR
    iterator lower_bound(const value_type&) noexcept;

    VISTA_CXX14_CONSTEXPR
    const_iterator lower_bound(const value_type&) const noexcept;

    //! @brief Returns iterator to the beginning of the span.

    VISTA_CXX14_CONSTEXPR iterator begin() noexcept;
    constexpr const_iterator begin() const noexcept;
    constexpr const_iterator cbegin() const noexcept;

    //! @brief Returns iterator to the ending of the span.

    VISTA_CXX14_CONSTEXPR iterator end() noexcept;
    constexpr const_iterator end() const noexcept;
    constexpr const_iterator cend() const noexcept;

    //! @brief Returns function that compares values.

    constexpr compare comp() const noexcept;

public:
    // Span is non-copyable because more spans operating on the same storage
    // with their own internal state would cause invariants to break.
    span(const span&) = delete;
    span& operator=(const span&) = delete;

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
            return end - begin;
        }

        iterator begin;
        iterator end;
        iterator tail;
    };

    struct member_storage<T, Extent> member;
};

} // namespace sorted
} // namespace vista

#include <vista/sorted/detail/span.ipp>

#endif // VISTA_SORTED_SPAN_HPP
