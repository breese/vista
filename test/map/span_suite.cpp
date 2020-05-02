///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <tuple>
#include <boost/detail/lightweight_test.hpp>
#include <vista/map/span.hpp>

using namespace vista;

//-----------------------------------------------------------------------------

namespace dynamic_api_suite
{

void api_ctor_default()
{
    map::span<int, int> span;
    BOOST_TEST_EQ(span.capacity(), 0);
    BOOST_TEST_EQ(span.size(), 0);
}

void api_ctor_move()
{
    map::span<int, int> span;
    BOOST_TEST_EQ(span.capacity(), 0);
    BOOST_TEST_EQ(span.size(), 0);
    map::span<int, int> clone(std::move(span));
    BOOST_TEST_EQ(clone.capacity(), 0);
    BOOST_TEST_EQ(clone.size(), 0);
}

void api_ctor_array()
{
    map::pair<int, int> array[4] = {};
    map::span<int, int> span(array);
    BOOST_TEST_EQ(span.capacity(), 4);
    BOOST_TEST_EQ(span.size(), 0);
}

void api_ctor_iterator()
{
    std::array<map::pair<int, int>, 4> array = {};
    map::span<int, int> span(array.begin(), array.end());
    BOOST_TEST_EQ(span.capacity(), 4);
    BOOST_TEST_EQ(span.size(), 0);
}

void api_empty()
{
    map::span<int, int> span;
    BOOST_TEST(span.empty());
}

void api_full()
{
    map::span<int, int> span;
    BOOST_TEST(span.full());
}

void api_size()
{
    map::span<int, int> span;
    BOOST_TEST_EQ(span.size(), 0);
}

void api_capacity()
{
    map::span<int, int> span;
    BOOST_TEST_EQ(span.capacity(), 0);
}

void api_clear()
{
    map::pair<int, int> array[4] = {};
    map::span<int, int> span(array);
    span.insert({ 11, 1 });
    BOOST_TEST_EQ(span.size(), 1);
    span.clear();
    BOOST_TEST_EQ(span.size(), 0);
}

void api_insert_value()
{
    map::pair<int, int> array[4] = {};
    map::span<int, int> span(array);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.insert({ 11, 1 }), span.begin());
    BOOST_TEST_EQ(span.size(), 1);
}

void api_remove_iterator()
{
    map::pair<int, int> array[4] = {};
    map::span<int, int> span(array);
    BOOST_TEST_EQ(span.insert({ 11, 1 }), span.begin());
    BOOST_TEST_EQ(span.size(), 1);
    // Split into two lines because remove() does not preserve iterator stability
    auto where = span.remove(span.begin());
    BOOST_TEST_EQ(where, span.end());
    BOOST_TEST_EQ(span.size(), 0);
}

void api_lower_bound()
{
    map::pair<int, int> array[4] = {};
    map::span<int, int> span(array);
    span.insert({ 11, 1 });
    BOOST_TEST_EQ(span.lower_bound(10), span.begin());
    BOOST_TEST_EQ(span.lower_bound(11), span.begin());
    BOOST_TEST_EQ(span.lower_bound(12), span.end());
}

void api_begin_end()
{
    map::pair<int, int> array[4] = {};
    map::span<int, int> span(array);
    BOOST_TEST_EQ(span.begin(), span.end());
}

void api_begin_end_const()
{
    map::pair<int, int> array[4] = {};
    const map::span<int, int> span(array);
    BOOST_TEST_EQ(span.begin(), span.end());
}

void api_cbegin_cend()
{
    map::pair<int, int> array[4] = {};
    map::span<int, int> span(array);
    BOOST_TEST_EQ(span.cbegin(), span.cend());
}

void api_key_comp()
{
    map::pair<int, int> array[4] = {};
    map::span<int, int> span(array);
    BOOST_TEST(!span.key_comp()(11, 10));
    BOOST_TEST(!span.key_comp()(11, 11));
    BOOST_TEST(span.key_comp()(11, 12));
}

void run()
{
    api_ctor_default();
    api_ctor_move();
    api_ctor_array();
    api_ctor_iterator();
    api_empty();
    api_full();
    api_size();
    api_capacity();
    api_clear();
    api_insert_value();
    api_remove_iterator();
    api_lower_bound();
    api_begin_end();
    api_begin_end_const();
    api_cbegin_cend();
    api_key_comp();
}

} // namespace dynamic_api_suite

//-----------------------------------------------------------------------------

namespace fixed_api_suite
{

void api_ctor_default()
{
    map::span<int, int, 0> span;
    BOOST_TEST_EQ(span.capacity(), 0);
    BOOST_TEST_EQ(span.size(), 0);
}

void api_ctor_move()
{
    map::span<int, int, 4> span;
    BOOST_TEST_EQ(span.capacity(), 0); // No underlying storage
    BOOST_TEST_EQ(span.size(), 0);
    map::span<int, int, 4> clone(std::move(span));
    BOOST_TEST_EQ(clone.capacity(), 0);
    BOOST_TEST_EQ(clone.size(), 0);
}

void api_ctor_array()
{
    map::pair<int, int> array[4] = {};
    map::span<int, int, 4> span(array);
    BOOST_TEST_EQ(span.capacity(), 4);
    BOOST_TEST_EQ(span.size(), 0);
}

void api_ctor_iterator()
{
    std::array<map::pair<int, int>, 4> array = {};
    map::span<int, int, 4> span(array.begin(), array.end());
    BOOST_TEST_EQ(span.capacity(), 4);
    BOOST_TEST_EQ(span.size(), 0);
}

void api_empty()
{
    map::span<int, int, 0> span;
    BOOST_TEST(span.empty());
}

void api_full()
{
    map::span<int, int, 0> span;
    BOOST_TEST(span.full());
}

void api_size()
{
    map::span<int, int, 0> span;
    BOOST_TEST_EQ(span.size(), 0);
}

void api_capacity()
{
    map::span<int, int, 0> span;
    BOOST_TEST_EQ(span.capacity(), 0);
}

void api_clear()
{
    map::pair<int, int> array[4] = {};
    map::span<int, int, 4> span(array);
    span.insert({ 11, 1 });
    BOOST_TEST_EQ(span.size(), 1);
    span.clear();
    BOOST_TEST_EQ(span.size(), 0);
}

void api_insert_value()
{
    map::pair<int, int> array[4] = {};
    map::span<int, int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.insert({ 11, 1 }), span.begin());
    BOOST_TEST_EQ(span.size(), 1);
}

void api_remove_iterator()
{
    map::pair<int, int> array[4] = {};
    map::span<int, int, 4> span(array);
    BOOST_TEST_EQ(span.insert({ 11, 1 }), span.begin());
    BOOST_TEST_EQ(span.size(), 1);
    // Split into two lines because remove() does not preserve iterator stability
    auto where = span.remove(span.begin());
    BOOST_TEST_EQ(where, span.end());
    BOOST_TEST_EQ(span.size(), 0);
}

void api_lower_bound()
{
    map::pair<int, int> array[4] = {};
    map::span<int, int, 4> span(array);
    span.insert({ 11, 1 });
    BOOST_TEST_EQ(span.lower_bound(10), span.begin());
    BOOST_TEST_EQ(span.lower_bound(11), span.begin());
    BOOST_TEST_EQ(span.lower_bound(12), span.end());
}

void api_begin_end()
{
    map::pair<int, int> array[4] = {};
    map::span<int, int, 4> span(array);
    BOOST_TEST_EQ(span.begin(), span.end());
}

void api_begin_end_const()
{
    map::pair<int, int> array[4] = {};
    const map::span<int, int, 4> span(array);
    BOOST_TEST_EQ(span.begin(), span.end());
}

void api_cbegin_cend()
{
    map::pair<int, int> array[4] = {};
    map::span<int, int, 4> span(array);
    BOOST_TEST_EQ(span.cbegin(), span.cend());
}

void api_key_comp()
{
    map::pair<int, int> array[4] = {};
    map::span<int, int, 4> span(array);
    BOOST_TEST(!span.key_comp()(11, 10));
    BOOST_TEST(!span.key_comp()(11, 11));
    BOOST_TEST(span.key_comp()(11, 12));
}

void run()
{
    api_ctor_default();
    api_ctor_move();
    api_ctor_array();
    api_ctor_iterator();
    api_empty();
    api_full();
    api_size();
    api_capacity();
    api_clear();
    api_insert_value();
    api_remove_iterator();
    api_lower_bound();
    api_begin_end();
    api_begin_end_const();
    api_cbegin_cend();
    api_key_comp();
}

} // namespace fixed_api_suite

//-----------------------------------------------------------------------------

int main()
{
    dynamic_api_suite::run();
    fixed_api_suite::run();

    return boost::report_errors();
}
