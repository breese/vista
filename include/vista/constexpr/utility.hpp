#ifndef VISTA_CONSTEXPR_UTILITY_HPP
#define VISTA_CONSTEXPR_UTILITY_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <utility> // std::move
#include <vista/detail/config.hpp>
#include <vista/detail/type_traits.hpp>

namespace vista
{

//-----------------------------------------------------------------------------

#if __cpp_lib_constexpr_utility >= 201811L

using std::pair;

#else

template <typename T1, typename T2>
struct pair
{
    using first_type = T1;
    using second_type = T2;

    constexpr pair() noexcept = default;

    template <typename U1,
              typename U2,
              typename std::enable_if<std::is_constructible<first_type, U1&&>::value &&
                                      std::is_constructible<second_type, U2&&>::value, int>::type = 0>
    constexpr pair(U1&& first, U2&& second)
        : first(std::forward<U1>(first)),
          second(std::forward<U2>(second))
    {}

    first_type first;
    second_type second;
};

template <typename T1, typename T2>
constexpr bool operator==(const pair<T1, T2>& lhs,
                          const pair<T1, T2>& rhs)
{
    return (lhs.first == rhs.first) && (lhs.second == rhs.second);
}

#endif

//-----------------------------------------------------------------------------

// std::swap is not constexpr before C++20

namespace detail
{

template <bool, typename T>
struct swap_overloader
{
    static VISTA_CXX14_CONSTEXPR
    void swap(T& lhs, T& rhs) noexcept(vista::detail::is_nothrow_swappable<T>::value)
    {
        using std::swap;
        swap(lhs, rhs);
    }
};

#if __cpp_lib_constexpr_utility < 201811L

template <typename T>
struct swap_overloader<true, T>
{
    static VISTA_CXX14_CONSTEXPR
    void swap(T& lhs, T& rhs) noexcept(vista::detail::is_nothrow_swappable<T>::value)
    {
        // Does not handle std::swap specializations
        T temp = std::move(lhs);
        lhs = std::move(rhs);
        rhs = std::move(temp);
    }
};

#endif

} // namespace detail

template <bool WithConstexpr, typename T>
VISTA_CXX14_CONSTEXPR
void swap(T& lhs, T& rhs) noexcept(vista::detail::is_nothrow_swappable<T>::value)
{
    detail::swap_overloader<WithConstexpr, T>::swap(lhs, rhs);
}

} // namespace vista

#endif // VISTA_CONSTEXPR_UTILITY_HPP
