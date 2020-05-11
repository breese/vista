///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vista/utility.hpp> // get<I>
#include <vista/constant_map.hpp>

using namespace vista;

//-----------------------------------------------------------------------------

constexpr auto increasing = make_constant_map<int, int>(
    {
        { 11, 1 },
        { 22, 2 },
        { 33, 3 },
        { 44, 4 }
    }
);

static_assert(!increasing.contains(10), "");
static_assert(increasing.contains(11), "");
static_assert(increasing.contains(22), "");
static_assert(increasing.contains(33), "");
static_assert(increasing.contains(44), "");

static_assert(increasing.lower_bound(10) == increasing.begin() + 0, "");
static_assert(increasing.lower_bound(11) == increasing.begin() + 0, "");
static_assert(increasing.lower_bound(12) == increasing.begin() + 1, "");
static_assert(increasing.lower_bound(22) == increasing.begin() + 1, "");
static_assert(increasing.lower_bound(23) == increasing.begin() + 2, "");
static_assert(increasing.lower_bound(33) == increasing.begin() + 2, "");
static_assert(increasing.lower_bound(34) == increasing.begin() + 3, "");
static_assert(increasing.lower_bound(44) == increasing.begin() + 3, "");
static_assert(increasing.lower_bound(45) == increasing.end(), "");

static_assert(increasing.find(10) == increasing.end(), "");
static_assert(increasing.find(11) == increasing.begin() + 0, "");
static_assert(increasing.find(12) == increasing.end(), "");
static_assert(increasing.find(22) == increasing.begin() + 1, "");
static_assert(increasing.find(23) == increasing.end(), "");
static_assert(increasing.find(33) == increasing.begin() + 2, "");
static_assert(increasing.find(34) == increasing.end(), "");
static_assert(increasing.find(44) == increasing.begin() + 3, "");
static_assert(increasing.find(45) == increasing.end(), "");

static_assert(increasing.size() == 4, "");
static_assert(increasing[11] == 1, "");
static_assert(increasing[22] == 2, "");
static_assert(increasing[33] == 3, "");
static_assert(increasing[44] == 4, "");

static_assert(vista::get<1>(*increasing.find(11)) == 1, "");
static_assert(vista::get<1>(*increasing.find(22)) == 2, "");
static_assert(vista::get<1>(*increasing.find(33)) == 3, "");
static_assert(vista::get<1>(*increasing.find(44)) == 4, "");

//-----------------------------------------------------------------------------

constexpr auto decreasing = make_constant_map<int, int>(
    {
        { 44, 4 },
        { 33, 3 },
        { 22, 2 },
        { 11, 1 }
    }
);

static_assert(decreasing.size() == 4, "");
static_assert(decreasing[11] == 1, "");
static_assert(decreasing[22] == 2, "");
static_assert(decreasing[33] == 3, "");
static_assert(decreasing[44] == 4, "");
static_assert(decreasing.find(0) == decreasing.end(), "");
static_assert(decreasing.find(11) == decreasing.begin() + 0, "");
static_assert(decreasing.find(22) == decreasing.begin() + 1, "");
static_assert(decreasing.find(33) == decreasing.begin() + 2, "");
static_assert(decreasing.find(44) == decreasing.begin() + 3, "");
static_assert(vista::get<1>(*decreasing.find(11)) == 1, "");
static_assert(vista::get<1>(*decreasing.find(22)) == 2, "");
static_assert(vista::get<1>(*decreasing.find(33)) == 3, "");
static_assert(vista::get<1>(*decreasing.find(44)) == 4, "");
