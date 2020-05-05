#ifndef VISTA_UTILITY_HPP
#define VISTA_UTILITY_HPP

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

// Does not handle std::swap specializations

template<typename T>
constexpr void constexpr_swap(T& lhs, T& rhs) noexcept(vista::detail::is_nothrow_swappable<T>::value)
{
    T temp = std::move(lhs);
    lhs = std::move(rhs);
    rhs = std::move(temp);
}

} // namespace vista

#endif // VISTA_UTILITY_HPP
