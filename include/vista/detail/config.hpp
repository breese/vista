#ifndef VISTA_DETAIL_CONFIG_HPP
#define VISTA_DETAIL_CONFIG_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef> // std::size_t

#if __cplusplus >= 201402L
# define VISTA_CXX14(x) x
#else
# define VISTA_CXX14(x)
#endif

#if (__cpp_constexpr >= 201304L)
# define VISTA_CXX14_CONSTEXPR constexpr
#else
# define VISTA_CXX14_CONSTEXPR
#endif

namespace vista
{

enum : std::size_t { dynamic_extent = std::size_t(0) };

} // namespace vista

#endif // VISTA_DETAIL_CONFIG_HPP
