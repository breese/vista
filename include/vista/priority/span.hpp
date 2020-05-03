#ifndef VISTA_PRIORITY_SPAN_HPP
#define VISTA_PRIORITY_SPAN_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <functional> // std::less
#include <vista/span.hpp>

namespace vista
{
namespace priority
{
//! @brief Priority span.
//!
//! A view that turns contiguous memory into a priority queue.
//!
//! Constant time lookup of the largest (by default) element.
//!
//! The default ordering can be changed with a user-provided compare predicate.
//!
//! Violation of any precondition results in undefined behavior.

template <typename T,
          std::size_t Extent = dynamic_extent,
          typename Compare = std::less<T>>
class span
{
public:
    using element_type = T;
    using value_type = typename std::remove_cv<element_type>::type;
    using value_compare = Compare;
    using size_type = std::size_t;
    using pointer = T*;

    //! @brief Creates empty priority span.

    constexpr span() noexcept = default;

    //! @brief Creates priority span by copying.

    constexpr span(const span&) noexcept = default;

    //! @brief Creates priority span by moving.

    constexpr span(span&&) noexcept = default;

    //! @brief Creates priority span from array.

    template <std::size_t N,
              typename std::enable_if<(Extent == N || Extent == dynamic_extent), int>::type = 0>
    explicit constexpr span(element_type (&array)[N]) noexcept;

    //! @brief Creates priority span from pointer and size.
    //!
    //! The span covers the range from @c begin and @c size elements forwards.

    constexpr span(pointer data, size_type size) noexcept;

    //! @brief Creates priority span from iterators.
    //!
    //! The span covers the range from @c begin to @c end.

    template <typename ContiguousIterator>
    constexpr span(ContiguousIterator begin,
                   ContiguousIterator end) noexcept;

    //! @brief Checks if priority span is empty.

    constexpr bool empty() const noexcept;

    //! @brief Checks if priority span is full.

    constexpr bool full() const noexcept;

    //! @brief Returns the number of elements in priority span.

    constexpr size_type size() const noexcept;

    //! @brief Returns the maximum possible number of elements in priority span.

    constexpr size_type capacity() const noexcept;

    //! @brief Returns reference to topmost element in priority span.
    //!
    //! @pre size() > 0

    constexpr const value_type& top() const noexcept;

    //! @brief Inserts element and reorganizes the underlying storage.
    //!
    //! @pre capacity() > 0
    //! @pre !full()

    VISTA_CXX14_CONSTEXPR
    void push(value_type input) noexcept(std::is_nothrow_move_constructible<value_type>::value && std::is_nothrow_move_assignable<value_type>::value);

    //! @brief Removes the topmost element from the priority span.
    //!
    //! @pre capacity() > 0
    //! @pre !empty()

    VISTA_CXX14_CONSTEXPR
    void pop() noexcept (std::is_nothrow_move_constructible<value_type>::value && std::is_nothrow_move_assignable<value_type>::value);

private:
    struct member
    {
        constexpr member() noexcept = default;

        constexpr member(pointer begin, pointer end) noexcept
            : span(begin, end),
              last(begin)
        {
        }

        Compare comparator;
        vista::span<T, Extent> span;
        pointer last = nullptr;
    } member;
};

} // namespace priority
} // namespace vista

#include <vista/priority/detail/span.ipp>

#endif // VISTA_PRIORITY_SPAN_HPP
