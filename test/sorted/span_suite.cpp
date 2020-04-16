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
#include <vector>
#include <boost/detail/lightweight_test.hpp>
#include <vista/sorted/span.hpp>

using namespace vista;

//-----------------------------------------------------------------------------

namespace api_dynamic_suite
{

void api_ctor_default()
{
    sorted::span<int> span;
    BOOST_TEST_EQ(span.capacity(), 0);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST(span.empty());
    BOOST_TEST(span.full());
}

void api_ctor_iterator()
{
    std::array<int, 4> storage = {};
    sorted::span<int> span(storage.begin(), storage.end());
    BOOST_TEST_EQ(span.capacity(), 4);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST(span.empty());
    BOOST_TEST(!span.full());
}

void api_capacity()
{
    sorted::span<int> span;
    BOOST_TEST_EQ(span.capacity(), 0);
}

void api_size()
{
    sorted::span<int> span;
    BOOST_TEST_EQ(span.size(), 0);
}

void api_empty()
{
    sorted::span<int> span;
    BOOST_TEST(span.empty());
}

void api_full()
{
    sorted::span<int> span;
    BOOST_TEST(span.full());
}

void api_push()
{
    std::array<int, 4> storage = {};
    sorted::span<int> span(storage.begin(), storage.end());
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.push(11), span.begin());
    BOOST_TEST_EQ(span.size(), 1);
}

void api_pop_value()
{
    std::array<int, 4> storage = {};
    sorted::span<int> span(storage.begin(), storage.end());
    BOOST_TEST_EQ(span.push(11), span.begin());
    BOOST_TEST_EQ(span.size(), 1);
    span.pop(11);
    BOOST_TEST_EQ(span.size(), 0);
}

void api_pop_iterator()
{
    std::array<int, 4> storage = {};
    sorted::span<int> span(storage.begin(), storage.end());
    BOOST_TEST_EQ(span.push(11), span.begin());
    BOOST_TEST_EQ(span.size(), 1);
    span.pop(span.begin());
    BOOST_TEST_EQ(span.size(), 0);
}

void api_begin_end()
{
    std::array<int, 4> storage = {};
    sorted::span<int> span(storage.begin(), storage.end());
    BOOST_TEST_EQ(span.begin(), span.end());
}

void api_begin_end_const()
{
    std::array<int, 4> storage = {};
    sorted::span<int> span(storage.begin(), storage.end());
    BOOST_TEST_EQ(span.begin(), span.end());
}

void api_cbegin_cend()
{
    std::array<int, 4> storage = {};
    sorted::span<int> span(storage.begin(), storage.end());
    BOOST_TEST_EQ(span.cbegin(), span.cend());
}

void api_comp()
{
    sorted::span<int> span;
    BOOST_TEST(span.comp()(11, 22));
}

void run()
{
    api_ctor_default();
    api_ctor_iterator();
    api_capacity();
    api_size();
    api_empty();
    api_full();
    api_push();
    api_pop_value();
    api_pop_iterator();
    api_begin_end();
    api_begin_end_const();
    api_cbegin_cend();
    api_comp();
}

} // namespace api_dynamic_suite

//-----------------------------------------------------------------------------

namespace api_fixed_suite
{

void api_ctor_default()
{
    sorted::span<int, 4> span;
    BOOST_TEST_EQ(span.capacity(), 4);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST(span.empty());
    BOOST_TEST(!span.full());
}

void api_ctor_iterator()
{
    std::array<int, 4> storage = {};
    sorted::span<int, 4> span(storage.begin(), storage.end());
    BOOST_TEST_EQ(span.capacity(), 4);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST(span.empty());
    BOOST_TEST(!span.full());
}

void api_capacity()
{
    sorted::span<int, 4> span;
    BOOST_TEST_EQ(span.capacity(), 4);
}

void api_size()
{
    sorted::span<int, 4> span;
    BOOST_TEST_EQ(span.size(), 0);
}

void api_empty()
{
    sorted::span<int, 4> span;
    BOOST_TEST(span.empty());
}

void api_full()
{
    sorted::span<int, 4> span;
    BOOST_TEST(!span.full());
}

void api_push()
{
    std::array<int, 4> storage = {};
    sorted::span<int, 4> span(storage.begin(), storage.end());
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.push(11), span.begin());
    BOOST_TEST_EQ(span.size(), 1);
}

void api_pop_value()
{
    std::array<int, 4> storage = {};
    sorted::span<int, 4> span(storage.begin(), storage.end());
    BOOST_TEST_EQ(span.push(11), span.begin());
    BOOST_TEST_EQ(span.size(), 1);
    span.pop(11);
    BOOST_TEST_EQ(span.size(), 0);
}

void api_pop_iterator()
{
    std::array<int, 4> storage = {};
    sorted::span<int, 4> span(storage.begin(), storage.end());
    BOOST_TEST_EQ(span.push(11), span.begin());
    BOOST_TEST_EQ(span.size(), 1);
    span.pop(span.begin());
    BOOST_TEST_EQ(span.size(), 0);
}

void api_begin_end()
{
    std::array<int, 4> storage = {};
    sorted::span<int, 4> span(storage.begin(), storage.end());
    BOOST_TEST_EQ(span.begin(), span.end());
}

void api_begin_end_const()
{
    std::array<int, 4> storage = {};
    sorted::span<int, 4> span(storage.begin(), storage.end());
    BOOST_TEST_EQ(span.begin(), span.end());
}

void api_cbegin_cend()
{
    std::array<int, 4> storage = {};
    sorted::span<int, 4> span(storage.begin(), storage.end());
    BOOST_TEST_EQ(span.cbegin(), span.cend());
}

void api_comp()
{
    sorted::span<int, 4> span;
    BOOST_TEST(span.comp()(11, 22));
}

void run()
{
    api_ctor_default();
    api_ctor_iterator();
    api_capacity();
    api_size();
    api_empty();
    api_full();
    api_push();
    api_pop_value();
    api_pop_iterator();
    api_begin_end();
    api_begin_end_const();
    api_cbegin_cend();
    api_comp();
}

} // namespace api_fixed_suite

//-----------------------------------------------------------------------------

namespace push_suite
{

void push_increasing()
{
    std::array<int, 4> storage = {};
    sorted::span<int> span(storage.begin(), storage.end());
    span.push(11);
    {
        std::vector<int> expect = { 11 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.push(22);
    {
        std::vector<int> expect = { 11, 22 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.push(33);
    {
        std::vector<int> expect = { 11, 22, 33 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.push(44);
    {
        std::vector<int> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
}

void push_decreasing()
{
    std::array<int, 4> storage = {};
    sorted::span<int> span(storage.begin(), storage.end());
    span.push(44);
    {
        std::vector<int> expect = { 44 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.push(33);
    {
        std::vector<int> expect = { 33, 44 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.push(22);
    {
        std::vector<int> expect = { 22, 33, 44 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.push(11);
    {
        std::vector<int> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
}

void push_alternating()
{
    std::array<int, 4> storage = {};
    sorted::span<int> span(storage.begin(), storage.end());
    span.push(11);
    {
        std::vector<int> expect = { 11 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.push(44);
    {
        std::vector<int> expect = { 11, 44 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.push(22);
    {
        std::vector<int> expect = { 11, 22, 44 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.push(33);
    {
        std::vector<int> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
}

void run()
{
    push_increasing();
    push_decreasing();
    push_alternating();
}

} // namespace push_suite

//-----------------------------------------------------------------------------

namespace pop_suite
{

void pop_increasing()
{
    std::array<int, 4> storage = {};
    sorted::span<int> span(storage.begin(), storage.end());
    span.push(11);
    span.push(22);
    span.push(33);
    span.push(44);
    {
        std::vector<int> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }

    span.pop(11);
    {
        std::vector<int> expect = { 22, 33, 44 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.pop(22);
    {
        std::vector<int> expect = { 33, 44 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.pop(33);
    {
        std::vector<int> expect = { 44 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.pop(44);
    {
        std::vector<int> expect = { };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
}

void pop_decreasing()
{
    std::array<int, 4> storage = {};
    sorted::span<int> span(storage.begin(), storage.end());
    span.push(11);
    span.push(22);
    span.push(33);
    span.push(44);
    {
        std::vector<int> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }

    span.pop(44);
    {
        std::vector<int> expect = { 11, 22, 33 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.pop(33);
    {
        std::vector<int> expect = { 11, 22 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.pop(22);
    {
        std::vector<int> expect = { 11 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.pop(11);
    {
        std::vector<int> expect = { };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
}

void pop_alternating()
{
    std::array<int, 4> storage = {};
    sorted::span<int> span(storage.begin(), storage.end());
    span.push(11);
    span.push(22);
    span.push(33);
    span.push(44);
    {
        std::vector<int> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }

    span.pop(11);
    {
        std::vector<int> expect = { 22, 33, 44 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.pop(44);
    {
        std::vector<int> expect = { 22, 33 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.pop(22);
    {
        std::vector<int> expect = { 33 };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
    span.pop(33);
    {
        std::vector<int> expect = { };
        BOOST_TEST_ALL_EQ(span.begin(), span.end(),
                          expect.begin(), expect.end());
    }
}

void run()
{
    pop_increasing();
    pop_decreasing();
    pop_alternating();
}

} // namespace pop_suite

//-----------------------------------------------------------------------------

int main()
{
    api_dynamic_suite::run();
    api_fixed_suite::run();
    push_suite::run();
    pop_suite::run();
 
    return boost::report_errors();
}
