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
#include <vista/detail/type_traits.hpp>

namespace vista
{

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

template <typename T>
struct swap_overloader<true, T>
{
    static VISTA_CXX14_CONSTEXPR
    void swap(T& lhs, T& rhs) noexcept(vista::detail::is_nothrow_swappable<T>::value)
    {
#if __cpp_constexpr_dynamic_alloc >= 201907L
        using std::swap;
        swap(lhs, rhs);
#else
        // Does not handle std::swap specializations
        T temp = std::move(lhs);
        lhs = std::move(rhs);
        rhs = std::move(temp);
#endif
    }
};

} // namespace detail

template <bool WithConstexpr, typename T>
VISTA_CXX14_CONSTEXPR
void swap(T& lhs, T& rhs) noexcept(vista::detail::is_nothrow_swappable<T>::value)
{
    detail::swap_overloader<WithConstexpr, T>::swap(lhs, rhs);
}

} // namespace vista

#endif // VISTA_CONSTEXPR_UTILITY_HPP
