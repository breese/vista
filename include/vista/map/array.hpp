#ifndef VISTA_MAP_ARRAY_HPP
#define VISTA_MAP_ARRAY_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vista/sorted/span.hpp>

namespace vista
{
namespace map
{

template <typename T1, typename T2>
using pair = std::pair<T1, T2>;

//! @brief Fixed-capacity associative array.
//!
//! Stores all values in-place in continguous memory embedded into the array.
//! Empty slots contains default constructed values. No dynamic memory is allocated.
//!
//! Violation of any precondition results in undefined behavior.

template <typename Key,
          typename T,
          std::size_t N,
          typename Compare = std::less<Key>>
class array
{
    static_assert(std::is_default_constructible<Key>::value, "Key must be default constructible");
    static_assert(std::is_default_constructible<T>::value, "T must be default constructible");

public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = map::pair<Key, T>;
    using key_compare = Compare;
    struct value_compare
    {
        bool operator()(const value_type& lhs, const value_type& rhs)
        {
            return Compare{}(lhs.first, rhs.first);
        }
    };
private:
    using span_type = sorted::template span<value_type, N, value_compare>;
public:
    using size_type = typename span_type::size_type;
    using pointer = typename span_type::pointer;
    using iterator = typename span_type::iterator;
    using const_iterator = typename span_type::const_iterator;

    //! @brief Creates empty associative array.
    //!
    //! @post capacity() == N
    //! @post size() == 0

    constexpr array() noexcept;

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
    //! The storage of the cleared elements will be left in a default-constructed state.
    //!
    //! @post size() == 0

    //! @brief Returns the maximum possible number of elements in span.

    constexpr size_type capacity() const noexcept;

    //! @brief Returns the number of elements in span.

    constexpr size_type size() const noexcept;

    //! @brief Clears the span.
    //!
    //! The storage of the cleared elements will be left in a default-constructed state.
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
    //! The storage of the erased element will be left in a default-constructed state.
    //!
    //! Linear time complexity.
    //!
    //! @pre !empty()

    VISTA_CXX14_CONSTEXPR
    size_type erase(const key_type&) noexcept(std::is_nothrow_move_assignable<value_type>::value);

    //! @brief Erases the element at given position.
    //!
    //! The storage of the erased element will be left in a default-constructed state.
    //!
    //! Linear time complexity.
    //!
    //! @pre !empty()
    //! @pre position != end()

    iterator erase(iterator position) noexcept(std::is_nothrow_move_assignable<value_type>::value);

    //! @brief Checks if span contains key.
    //!
    //! Logarithmic time complexity.

    VISTA_CXX14_CONSTEXPR
    bool contains(const key_type&) const noexcept;

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
    template <typename... Args>
    VISTA_CXX14_CONSTEXPR
    pointer construct_at(pointer, Args&&...);

    VISTA_CXX14_CONSTEXPR
    void destroy_at(pointer);

private:
    value_type storage[N];
    span_type span;
};

} // namespace map
} // namespace vista

#include <vista/map/detail/array.ipp>

#endif // VISTA_MAP_ARRAY_HPP
