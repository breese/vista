///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/core/lightweight_test.hpp>
#include <vista/utility.hpp>

using namespace vista;

//-----------------------------------------------------------------------------

namespace pair_suite
{

void api_ctor_default()
{
    vista::pair<int, int> pair;
    BOOST_TEST_EQ(pair.first, decltype(pair)::first_type{});
    BOOST_TEST_EQ(pair.second, decltype(pair)::second_type{});
}

void api_ctor_value()
{
    vista::pair<int, int> pair(1, 2);
    BOOST_TEST_EQ(pair.first, 1);
    BOOST_TEST_EQ(pair.second, 2);
}

void api_ctor_operator_equal()
{
    vista::pair<int, int> alpha(1, 2);
    vista::pair<int, int> bravo(1, 2);
    BOOST_TEST(alpha == bravo);
}

void run()
{
    api_ctor_default();
    api_ctor_value();
    api_ctor_operator_equal();
}

} // namespace pair_suite

//-----------------------------------------------------------------------------

namespace swap_suite
{

void api_swap()
{
    int alpha = 1;
    int bravo = 2;
    vista::swap<false>(alpha, bravo);
    BOOST_TEST_EQ(alpha, 2);
    BOOST_TEST_EQ(bravo, 1);
}

void run()
{
    api_swap();
}

} // namespace swap_suite

//-----------------------------------------------------------------------------

int main()
{
    pair_suite::run();
    swap_suite::run();

    return boost::report_errors();
}
