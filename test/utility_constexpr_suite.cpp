///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vista/utility.hpp>

//-----------------------------------------------------------------------------

namespace pair_suite
{

constexpr vista::pair<int, int> alpha(1, 2);

static_assert(alpha.first == 1, "");
static_assert(alpha.second == 2, "");

constexpr vista::pair<int, int> bravo(1, 2);

static_assert(alpha == bravo, "");

} // namespace pair_suite

//-----------------------------------------------------------------------------

namespace get_pair_suite
{

constexpr vista::pair<int, int> alpha(1, 2);

static_assert(vista::get<0>(alpha) == 1, "");
static_assert(vista::get<1>(alpha) == 2, "");

} // namespace get_pair_suite

//-----------------------------------------------------------------------------

#if __cplusplus >= 201402L

namespace swap_suite
{

struct swap_helper
{
    template <typename T1, typename T2>
    static constexpr auto swap(const vista::pair<T1, T2>& other) -> vista::pair<T1, T2>
    {
        vista::pair<T1, T2> result{ other.first, other.second };
        vista::swap<true>(result.first, result.second);
        return result;
    }
};

constexpr vista::pair<int, int> alpha(1, 2);
constexpr vista::pair<int, int> bravo(swap_helper::swap(alpha));

static_assert(bravo.first == alpha.second, "");
static_assert(bravo.second == alpha.first, "");

} // namespace swap_suite

#endif
