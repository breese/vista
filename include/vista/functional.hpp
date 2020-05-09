#ifndef VISTA_FUNCTIONAL_HPP
#define VISTA_FUNCTIONAL_HPP

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

using std::less;
using std::greater;

} // namespace vista

#else

namespace vista
{

template <typename T>
struct less
{
    constexpr bool operator()(const T& lhs, const T& rhs) const noexcept
    {
        return lhs < rhs;
    }
};

template <typename T>
struct greater
{
    constexpr bool operator()(const T& lhs, const T& rhs) const noexcept
    {
        return lhs > rhs;
    }
};

} // namespace vista

#endif

#endif // VISTA_FUNCTIONAL_HPP
