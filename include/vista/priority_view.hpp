#ifndef VISTA_PRIORITY_VIEW_HPP
#define VISTA_PRIORITY_VIEW_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vista/functional.hpp> // less
#include <vista/span.hpp>

namespace vista
{

//! @brief Priority view.
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
          typename Compare = vista::less<T>>
class priority_view
{
public:
    using element_type = T;
    using value_type = typename std::remove_cv<element_type>::type;
    using value_compare = Compare;
    using size_type = std::size_t;
    using pointer = T*;

    //! @brief Creates empty priority view.

    constexpr priority_view() noexcept = default;

    //! @brief Creates priority view by copying.

    constexpr priority_view(const priority_view&) noexcept = default;

    //! @brief Creates priority view by moving.

    constexpr priority_view(priority_view&&) noexcept = default;

    //! @brief Creates priority view from array.

    template <std::size_t N,
              typename std::enable_if<(Extent == N || Extent == dynamic_extent), int>::type = 0>
    explicit constexpr priority_view(element_type (&array)[N]) noexcept;

    //! @brief Creates priority view from pointer and size.
    //!
    //! The view covers the range from @c begin and @c size elements forwards.

    constexpr priority_view(pointer data, size_type size) noexcept;

    //! @brief Creates priority view from iterators.
    //!
    //! The view covers the range from @c begin to @c end.

    template <typename ContiguousIterator>
    constexpr priority_view(ContiguousIterator begin,
                            ContiguousIterator end) noexcept;

    //! @brief Checks if priority view is empty.

    constexpr bool empty() const noexcept;

    //! @brief Checks if priority view is full.

    constexpr bool full() const noexcept;

    //! @brief Returns the number of elements in priority view.

    constexpr size_type size() const noexcept;

    //! @brief Returns the maximum possible number of elements in priority view.

    constexpr size_type capacity() const noexcept;

    //! @brief Returns reference to topmost element in priority view.
    //!
    //! @pre size() > 0

    constexpr const value_type& top() const noexcept;

    //! @brief Inserts element and reorganizes the underlying storage.
    //!
    //! @pre capacity() > 0
    //! @pre !full()

    VISTA_CXX14_CONSTEXPR
    void push(value_type input) noexcept(std::is_nothrow_move_constructible<value_type>::value && std::is_nothrow_move_assignable<value_type>::value);

    //! @brief Removes the topmost element from the priority view.
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

} // namespace vista

#include <vista/detail/priority_view.ipp>

#endif // VISTA_PRIORITY_VIEW_HPP
