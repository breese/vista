#ifndef VISTA_CIRCULAR_ARRAY_HPP
#define VISTA_CIRCULAR_ARRAY_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <array>
#include <vista/circular_view.hpp>

namespace vista
{

//! @brief Fixed-sized circular buffer.
//!
//! Size is the current number of elements in the buffer.
//!
//! Capacity is the maximum number of elements that can be inserted without
//! overwriting old elements. Capacity cannot be changed.
//!
//! Violation of any precondition results in undefined behavior.

template <typename T, std::size_t N>
class circular_array
    : private std::array<T, N>,
      private circular_view<T, N>
{
    using storage = std::array<T, N>;
    using view = circular_view<T, N>;

    static_assert(std::is_destructible<T>::value, "T must be Erasable");
    static_assert(std::is_default_constructible<T>::value, "T must be DefaultConstructible");
    static_assert(N != dynamic_extent, "N cannot be dynamic_extent");

public:
    using element_type = typename view::element_type;
    using value_type = typename view::value_type;
    using size_type = typename view::size_type;
    using reference = typename view::reference;
    using const_reference = typename view::const_reference;
    using iterator = typename view::iterator;
    using const_iterator = typename view::const_iterator;
    using reverse_iterator = typename view::reverse_iterator;
    using const_reverse_iterator = typename view::const_reverse_iterator;
    using segment = typename view::segment;
    using const_segment = typename view::const_segment;

    //! @brief Creates empty circular array.
    //!
    //! @post capacity() == N
    //! @post size() == 0

    constexpr circular_array() noexcept;

    //! @brief Creates circular array by copying.
    //!
    //! @pre T must be copy constructible.
    //!
    //! @post capacity() == N
    //! @post size() == other.size()

    constexpr circular_array(const circular_array& other) noexcept(std::is_nothrow_copy_constructible<value_type>::value);

    //! @brief Recreates circular array by copying.
    //!
    //! @pre T must be copy assignable.
    //!
    //! @post capacity() == N
    //! @post size() == other.size()

    VISTA_CXX14_CONSTEXPR
    circular_array& operator=(const circular_array& other) noexcept(std::is_nothrow_copy_assignable<value_type>::value);

    //! @brief Creates circular array by moving.
    //!
    //! @post capacity() == N
    //! @post size() == other.size()

    constexpr circular_array(circular_array&& other) noexcept(std::is_nothrow_move_constructible<value_type>::value) = default;

    //! @brief Recreates circular array by moving.
    //!
    //! @post capacity() == N
    //! @post size() == other.size()

    VISTA_CXX14_CONSTEXPR
    circular_array& operator=(circular_array&& other) noexcept(std::is_nothrow_move_assignable<value_type>::value) = default;

    //! @brief Creates circular array with element from initializer list.
    //!
    //! All elements are inserted, but if input.size() > N then only the last N
    //! input elements will remain in the circular array.
    //!
    //! @post capacity() == N
    //! @post size() == input.size()

    template <typename... Args>
    constexpr circular_array(value_type, Args&&...) noexcept(std::is_nothrow_move_assignable<value_type>::value);

    //! @brief Recreates circular array with element from initializer list.
    //!
    //! All elements are inserted, but if input.size() > N then only the last N
    //! input elements will remain in the circular array.
    //!
    //! @post capacity() == N
    //! @post size() == input.size()

    VISTA_CXX14_CONSTEXPR
    circular_array& operator=(std::initializer_list<value_type> input) noexcept(std::is_nothrow_move_assignable<value_type>::value);

    //! @brief Checks if circular array is empty.
    using view::empty;

    //! @brief Checks if circular array is full.
    using view::full;

    //! @brief Returns the maximum possible number of elements in circular array.
    using view::capacity;

    //! @brief Returns the number of elements in circular array.
    using view::size;

    //! @brief Returns the maximum number of possible elements in circular array.
    constexpr size_type max_size() const noexcept;

    //! @brief Returns reference to first element in circular array.
    using view::front;

    //! @brief Returns reference to last element in view.
    using view::back;

    //! @brief Returns reference to element at position.
    using view::operator[];

    //! @brief Clears the circular array.
    using view::clear;

    //! @brief Clears circular array and inserts element at end of circular array.
    using view::assign;

    //! @brief Inserts element at beginning of circular array.
    using view::push_front;

    //! @brief Removes and returns element at end of circular array.
    using view::push_back;

    //! @brief Removes and returns element from beginning of circular array.
    using view::pop_front;

    //! @brief Moves element from end of circular array.
    using view::pop_back;

    //! @brief Inserts unspecified elements at beginning of circular array.
    using view::expand_front;

    //! @brief Inserts unspecified elements at end of circular array.
    using view::expand_back;

    //! @brief Removes elements from beginning of circular array.
    using view::remove_front;

    //! @brief Removes elements from end of circular array.
    using view::remove_back;

    //! @brief Returns iterator to beginning of circular array.
    using view::begin;

    //! @brief Returns iterator to ending of circular array.
    using view::end;

    //! @brief Returns const iterator to beginning of circular array.
    using view::cbegin;

    //! @brief Returns const iterator to ending of circular array.
    using view::cend;

    //! @brief Returns reverse iterator to beginning of circular array.
    using view::rbegin;

    //! @brief Returns reverse iterator to ending of circular array.
    using view::rend;

    //! @brief Returns const reverse iterator to beginning of circular array.
    using view::crbegin;

    //! @brief Returns const reverse iterator to ending of circular array.
    using view::crend;

    //! @brief Returns first contiguous segment of circular array.
    using view::first_segment;

    //! @brief Returns last contiguous segment of circular array.
    using view::last_segment;

    //! @brief Returns first contiguous unused segment of circular array.
    using view::first_unused_segment;

    //! @brief Returns last contiguous unused segment of circular array.
    using view::last_unused_segment;
};

} // namespace vista

#include <vista/detail/circular_array.ipp>

#endif // VISTA_CIRCULAR_ARRAY_HPP
