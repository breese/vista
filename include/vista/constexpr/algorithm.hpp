#ifndef VISTA_CONSTEXPR_ALGORITHM_HPP
#define VISTA_CONSTEXPR_ALGORITHM_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

// Selected set of constexpr algorithms

#if __cpp_lib_constexpr_algorithm

#include <algorithm>

namespace vista
{

template <typename InputIterator, typename OutputIterator>
using constexpr_copy = std::copy<InputIterator, OutputIterator>;

} // namespace vista

#else

#include <vista/detail/config.hpp>

namespace vista
{

template <typename InputIterator, typename OutputIterator>
VISTA_CXX14_CONSTEXPR
OutputIterator constexpr_copy(InputIterator first,
                              InputIterator last,
                              OutputIterator output)
{
    while (first != last)
    {
        *output++ = *first++;
    }
    return output;
}

} // namespace vista

#endif

#endif // VISTA_CONSTEXPR_ALGORITHM_HPP
