#ifndef VISTA_DETAIL_MEMORY_HPP
#define VISTA_DETAIL_MEMORY_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <vista/detail/config.hpp>

namespace vista
{
namespace detail
{

#if __cplusplus >= 202002L

template <typename T, typename... Args>
using construct_at = std::construct_at<T, Args...>;

#else

template <typename T, typename... Args>
constexpr T * construct_at(T *p, Args&&... args)
{
    return new (p) T{ std::forward<Args>(args)... };
}

#endif

#if __cplusplus >= 201703L

template <typename T>
using destroy_at = std::destroy_at<T>;

#else

// Return type void is not allowed in C++11 constexpr functions

template <typename T>
VISTA_CXX14_CONSTEXPR
void destroy_at(T *p)
{
    p->~T();
}

#endif

} // namespace detail
} // namespace vista

#endif // VISTA_DETAIL_MEMORY_HPP
