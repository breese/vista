///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vista/functional.hpp>

//-----------------------------------------------------------------------------

namespace less_suite
{

constexpr vista::less<int> compare;

static_assert(compare(0, 1), "");
static_assert(!compare(1, 1), "");
static_assert(!compare(1, 0), "");

} // namespace less_suite

//-----------------------------------------------------------------------------

namespace greater_suite
{

constexpr vista::greater<int> compare;

static_assert(!compare(0, 1), "");
static_assert(!compare(1, 1), "");
static_assert(compare(1, 0), "");

} // namespace greater_suite
