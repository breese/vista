///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <array>
#include <boost/detail/lightweight_test.hpp>
#include <vista/constant_map.hpp>

using namespace vista;

//-----------------------------------------------------------------------------

namespace std
{

template <typename Key, typename T>
std::ostream& operator<<(std::ostream& stream, const vista::pair<Key, T>& data)
{
    stream << '{' << data.first << ',' << data.second << '}';
    return stream;
}

} // namespace std

//-----------------------------------------------------------------------------

namespace api_suite
{

void api_ctor_default()
{
    constant_map<int, int, 4> map;
    BOOST_TEST_EQ(map.size(), 4);
}

void api_ctor_array()
{
    pair<int, int> input[4] = { { 22, 2 }, { 44, 4 }, { 33, 3 }, { 11, 1 } };
    constant_map<int, int, 4> map(std::move(input));
    {
        std::array<pair<int, int>, 4> expect = {
            pair<int, int>{ 11, 1 },
            pair<int, int>{ 22, 2 },
            pair<int, int>{ 33, 3 },
            pair<int, int>{ 44, 4 }
        };
        BOOST_TEST_ALL_EQ(map.begin(), map.end(),
                          expect.begin(), expect.end());
    }
}

void api_make()
{
    auto map = make_constant_map<int, int>(
        {
            { 22, 2 },
            { 44, 4 },
            { 33, 3 },
            { 11, 1 }
        });
    {
        std::array<pair<int, int>, 4> expect = {
            pair<int, int>{ 11, 1 },
            pair<int, int>{ 22, 2 },
            pair<int, int>{ 33, 3 },
            pair<int, int>{ 44, 4 }
        };
        BOOST_TEST_ALL_EQ(map.begin(), map.end(),
                          expect.begin(), expect.end());
    }
}

void api_size()
{
    auto map = make_constant_map<int, int>(
        {
            { 22, 2 },
            { 44, 4 },
            { 33, 3 },
            { 11, 1 }
        });
    BOOST_TEST_EQ(map.size(), 4);
}

void api_contains()
{
    auto map = make_constant_map<int, int>(
        {
            { 22, 2 },
            { 44, 4 },
            { 33, 3 },
            { 11, 1 }
        });
    BOOST_TEST(!map.contains(10));
    BOOST_TEST(map.contains(11));
    BOOST_TEST(!map.contains(12));
    BOOST_TEST(map.contains(22));
    BOOST_TEST(!map.contains(23));
    BOOST_TEST(map.contains(33));
    BOOST_TEST(!map.contains(34));
    BOOST_TEST(map.contains(44));
    BOOST_TEST(!map.contains(45));
}

void api_lower_bound()
{
    auto map = make_constant_map<int, int>(
        {
            { 22, 2 },
            { 44, 4 },
            { 33, 3 },
            { 11, 1 }
        });
    BOOST_TEST(map.lower_bound(10) == map.begin());
    BOOST_TEST(map.lower_bound(11) == map.begin());
    BOOST_TEST(map.lower_bound(12) == map.begin() + 1);
    BOOST_TEST(map.lower_bound(22) == map.begin() + 1);
    BOOST_TEST(map.lower_bound(23) == map.begin() + 2);
    BOOST_TEST(map.lower_bound(33) == map.begin() + 2);
    BOOST_TEST(map.lower_bound(34) == map.begin() + 3);
    BOOST_TEST(map.lower_bound(44) == map.begin() + 3);
    BOOST_TEST(map.lower_bound(45) == map.end());
}

void api_find()
{
    auto map = make_constant_map<int, int>(
        {
            { 22, 2 },
            { 44, 4 },
            { 33, 3 },
            { 11, 1 }
        });
    BOOST_TEST(map.find(10) == map.end());
    BOOST_TEST(map.find(11) == map.begin());
    BOOST_TEST(map.find(12) == map.end());
    BOOST_TEST(map.find(22) == map.begin() + 1);
    BOOST_TEST(map.find(23) == map.end());
    BOOST_TEST(map.find(33) == map.begin() + 2);
    BOOST_TEST(map.find(34) == map.end());
    BOOST_TEST(map.find(44) == map.begin() + 3);
    BOOST_TEST(map.find(45) == map.end());
}

void run()
{
    api_ctor_default();
    api_ctor_array();
    api_make();
    api_size();
    api_contains();
    api_lower_bound();
    api_find();
}

} // namespace api_suite

//-----------------------------------------------------------------------------

int main()
{
    api_suite::run();

    return boost::report_errors();
}
