///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <ratio>
#include "rank.hpp"

using minimum = std::ratio<0, 10>;
using middle = std::ratio<5, 10>;
using maximum = std::ratio<10, 10>;

int main()
{
    vista::sorted::example::rank<double, 4> rank;

    rank.push(11.0);
    assert(rank.value<minimum>() == 11.0);
    assert(rank.value<middle>() == 11.0);
    assert(rank.value<maximum>() == 11.0);

    rank.push(33.0);
    assert(rank.value<minimum>() == 11.0);
    assert(rank.value<middle>() == 11.0);
    assert(rank.value<maximum>() == 33.0);

    rank.push(22.0);
    assert(rank.value<minimum>() == 11.0);
    assert(rank.value<middle>() == 22.0);
    assert(rank.value<maximum>() == 33.0);

    rank.push(44.0);
    assert(rank.value<minimum>() == 11.0);
    assert(rank.value<middle>() == 22.0);
    assert(rank.value<maximum>() == 44.0);

    return 0;
}
