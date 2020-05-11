#ifndef VISTA_CONSTANT_MAP_HPP
#define VISTA_CONSTANT_MAP_HPP

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
#include <vista/utility.hpp> // pair
#include <vista/array.hpp>

namespace vista
{

//! @brief Constant associative array.
//!
//! Suitable to build compile-time lookup tables.
//!
//!    constexpr auto table = make_constant_map<int, int>(
//!        {
//!            { 2, 42 },
//!            { 4, 44 }
//!        });
//!
//!    static_assert(table[2] == 42, "");
//!
//! Notice that the N template parameter is automatically chosen from the
//! input data when using the make_constant_map() factory functions.

template <typename Key,
          typename T,
          std::size_t N,
          typename Compare = vista::less<Key>>
class constant_map
    : protected vista::array<pair<Key, T>, N>
{
    using storage = vista::template array<pair<Key, T>, N>;

public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = pair<Key, T>;
    using size_type = typename storage::size_type;
    using const_iterator = typename storage::const_iterator;
    using key_compare = Compare;
    struct value_compare
    {
        constexpr bool operator()(const value_type& lhs, const value_type& rhs) const noexcept
        {
            return key_compare{}(lhs.first, rhs.first);
        }
    };

    //! @brief Creates empty associative array.

    constexpr constant_map() noexcept = default;

    //! @brief Creates associative array from unsorted array.

    explicit constexpr constant_map(value_type (&&input)[N]) noexcept(vista::detail::is_nothrow_swappable<value_type>::value);

    //! @brief Returns the number of elements in span.

    using storage::size;

    //! @brief Checks if span contains key.
    //!
    //! Logarithmic time complexity.

    VISTA_CXX14_CONSTEXPR
    bool contains(const key_type& key) const noexcept;

    //! @brief Returns iterator to element with given key.
    //!
    //! If key not found, then returns iterator to the entry at the position where
    //! the searched-for entry should have been, or the end iterator.
    //!
    //! Logarithmic time complexity.

    VISTA_CXX14_CONSTEXPR
    const_iterator lower_bound(const key_type& key) const noexcept;

    //! @brief Returns iterator to element with given key.
    //!
    //! If key not found, return end()
    //!
    //! Logarithmic time complexity.

    VISTA_CXX14_CONSTEXPR
    const_iterator find(const key_type& key) const noexcept;

    //! @brief Returns reference to element with given key.
    //!
    //! If key not found, generate compile-time error in constexpr context.
    //! Undefined behaviour in non-constexpr context.
    //!
    //! @pre contains(key)

    VISTA_CXX14_CONSTEXPR
    const mapped_type& operator[](const key_type& key) const noexcept;

    //! @brief Returns iterator to the beginning of the span.

    using storage::begin;
    using storage::cbegin;

    //! @brief Returns iterator to the ending of the span.

    using storage::end;
    using storage::cend;

    constexpr key_compare key_comp() const noexcept;
    constexpr value_compare value_comp() const noexcept;

private:
    static VISTA_CXX14_CONSTEXPR
    storage to_sorted(value_type (&&input)[N]) noexcept(vista::detail::is_nothrow_swappable<value_type>::value);

private:
    // Error functions deliberately left non-constexpr to trigger compile-time error.
    const mapped_type& error_key_not_found(const mapped_type& v) const noexcept { return v; }

    struct value_key_compare
    {
        constexpr bool operator()(const value_type& value, const key_type& key) const noexcept
        {
            return key_compare{}(value.first, key);
        }
    };
};

//! @brief Creates constant associative array with given input.

template <typename Key,
          typename T,
          std::size_t N,
          typename Compare = vista::less<Key>>
VISTA_CXX14_CONSTEXPR
auto make_constant_map(pair<Key, T> (&&input)[N]) noexcept(vista::detail::is_nothrow_swappable<decltype(*input)>::value) -> constant_map<Key, T, N, Compare>
{
    return constant_map<Key, T, N, Compare>{ std::forward<decltype(input)>(input) };
}

} // namespace vista

#include <vista/detail/constant_map.ipp>

#endif // VISTA_CONSTANT_MAP_HPP
