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
#include <vista/functional.hpp>

using namespace vista;

//-----------------------------------------------------------------------------

namespace api_suite
{

void api_less()
{
    vista::less<int> compare;
    BOOST_TEST(compare(0, 1));
    BOOST_TEST(!compare(1, 1));
    BOOST_TEST(!compare(1, 0));
}

void api_greater()
{
    vista::greater<int> compare;
    BOOST_TEST(!compare(0, 1));
    BOOST_TEST(!compare(1, 1));
    BOOST_TEST(compare(1, 0));
}

void run()
{
    api_less();
    api_greater();
}

} // namespace api_suite

//-----------------------------------------------------------------------------

int main()
{
    api_suite::run();

    return boost::report_errors();
}
