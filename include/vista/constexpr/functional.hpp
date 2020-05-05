#ifndef VISTA_CONSTEXPR_FUNCTIONAL_HPP
#define VISTA_CONSTEXPR_FUNCTIONAL_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if __cplusplus >= 201402L

#include <functional>

namespace vista
{

template <typename T>
using constexpr_less = std::less<T>;

template <typename T>
using constexpr_greater = std::greater<T>;

} // namespace vista

#else

namespace vista
{

template <typename T>
struct constexpr_less
{
    constexpr bool operator()(const T& lhs, const T& rhs) const noexcept
    {
        return lhs < rhs;
    }
};

template <typename T>
struct constexpr_greater
{
    constexpr bool operator()(const T& lhs, const T& rhs) const noexcept
    {
        return lhs > rhs;
    }
};

} // namespace vista

#endif

#endif // VISTA_CONSTEXPR_FUNCTIONAL_HPP
