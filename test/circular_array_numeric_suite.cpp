///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <numeric>
#include <boost/detail/lightweight_test.hpp>
#include <vista/circular_array.hpp>

using namespace vista;

// Algorithms that modify the input container via iterators are not supported.

//-----------------------------------------------------------------------------

namespace numeric_suite
{

void test_accumulate()
{
    circular_array<int, 4> data;
    BOOST_TEST_EQ(std::accumulate(data.begin(), data.end(), 0), 0);
    data = {11, 22, 33};
    BOOST_TEST_EQ(std::accumulate(data.begin(), data.end(), 0), 11 + 22 + 33);
    data.push_back(44);
    BOOST_TEST_EQ(std::accumulate(data.begin(), data.end(), 0), 11 + 22 + 33 + 44);
    data.push_back(55);
    BOOST_TEST_EQ(std::accumulate(data.begin(), data.end(), 0), 22 + 33 + 44 + 55);
}

void test_adjacent_difference()
{
    circular_array<int, 4> data = {11, 22, 33};
    std::vector<int> result(4);
    auto last = std::adjacent_difference(data.begin(), data.end(), result.begin());
    std::vector<int> expect = {11, 22 - 11, 33 - 22}; // First expected value is first input value
    BOOST_TEST_ALL_EQ(result.begin(), last, expect.begin(), expect.end());
}

void test_adjacent_difference_back_inserter()
{
    std::vector<int> data = {11, 22, 33, 44, 55};
    circular_array<int, 4> result;
    std::adjacent_difference(data.begin(), data.end(), std::back_inserter(result));
    std::vector<int> expect = {22 - 11, 33 - 22, 44 - 33, 55 - 44};
    BOOST_TEST_ALL_EQ(result.begin(), result.end(), expect.begin(), expect.end());
}

void test_inner_product()
{
    circular_array<int, 4> data;
    BOOST_TEST_EQ(std::inner_product(data.begin(), data.end(), data.begin(), 0),
                  0);
    data = {11, 22, 33};
    BOOST_TEST_EQ(std::inner_product(data.begin(), data.end(), data.begin(), 0),
                  11 * 11 + 22 * 22 + 33 * 33);
    data.push_back(44);
    BOOST_TEST_EQ(std::inner_product(data.begin(), data.end(), data.begin(), 0),
                  11 * 11 + 22 * 22 + 33 * 33 + 44 * 44);
    data.push_back(55);
    BOOST_TEST_EQ(std::inner_product(data.begin(), data.end(), data.begin(), 0),
                  22 * 22 + 33 * 33 + 44 * 44 + 55 * 55);
}

void test_partial_sum()
{
    circular_array<int, 4> data;
    std::vector<int> result(4);
    {
        auto last = std::partial_sum(data.begin(), data.end(), result.begin());
        std::vector<int> expect = {};
        BOOST_TEST_ALL_EQ(result.begin(), last, expect.begin(), expect.end());
    }
    data = {11, 22, 33};
    {
        auto last = std::partial_sum(data.begin(), data.end(), result.begin());
        std::vector<int> expect = {11, 11 + 22, 11 + 22 + 33};
        BOOST_TEST_ALL_EQ(result.begin(), last, expect.begin(), expect.end());
    }
    data.push_back(44);
    {
        auto last = std::partial_sum(data.begin(), data.end(), result.begin());
        std::vector<int> expect = {11, 11 + 22, 11 + 22 + 33, 11 + 22 + 33 + 44};
        BOOST_TEST_ALL_EQ(result.begin(), last, expect.begin(), expect.end());
    }
    data.push_back(55);
    {
        auto last = std::partial_sum(data.begin(), data.end(), result.begin());
        std::vector<int> expect = {22, 22 + 33, 22 + 33 + 44, 22 + 33 + 44 + 55};
        BOOST_TEST_ALL_EQ(result.begin(), last, expect.begin(), expect.end());
    }
}

void run()
{
    test_accumulate();
    test_adjacent_difference();
    test_adjacent_difference_back_inserter();
    test_inner_product();
    test_partial_sum();
}

} // namespace numeric_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    numeric_suite::run();

    return boost::report_errors();
}
