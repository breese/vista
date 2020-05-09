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
#include <vista/priority_view.hpp>

using namespace vista;

//-----------------------------------------------------------------------------

namespace api_dynamic_suite
{

void dynamic_ctor_default()
{
    priority_view<int> span;
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 0);
}

void dynamic_predicate_ctor_default()
{
    priority_view<int, vista::dynamic_extent, std::greater<int>> span;
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 0);
}

void dynamic_ctor_copy()
{
    priority_view<int> span;
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 0);
    priority_view<int> clone(span);
    BOOST_TEST_EQ(clone.size(), 0);
    BOOST_TEST_EQ(clone.capacity(), 0);
}

void dynamic_ctor_move()
{
    priority_view<int> span;
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 0);
    priority_view<int> clone(std::move(span));
    BOOST_TEST_EQ(clone.size(), 0);
    BOOST_TEST_EQ(clone.capacity(), 0);
}

void dynamic_ctor_array()
{
    int array[4] = {};
    priority_view<int> span(array);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void dynamic_ctor_pointer_size()
{
    std::array<int, 4> array = { 11, 22, 33, 44 };
    priority_view<int> span(array.data(), array.size());
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void dynamic_ctor_iterator()
{
    std::array<int, 4> array = { 11, 22, 33, 44 };
    priority_view<int> span(array.begin(), array.end());
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void dynamic_empty()
{
    int array[4] = {};
    priority_view<int> span(array);
    BOOST_TEST(span.empty());
    span.push(11);
    BOOST_TEST(!span.empty());
}

void dynamic_full()
{
    int array[4] = {};
    priority_view<int> span(array);
    BOOST_TEST(!span.full());
    span.push(11);
    span.push(22);
    span.push(33);
    BOOST_TEST(!span.full());
    span.push(44);
    BOOST_TEST(span.full());
}

void dynamic_size()
{
    int array[4] = {};
    priority_view<int> span(array);
    BOOST_TEST_EQ(span.size(), 0);
    span.push(11);
    BOOST_TEST_EQ(span.size(), 1);
    span.push(22);
    BOOST_TEST_EQ(span.size(), 2);
    span.push(33);
    BOOST_TEST_EQ(span.size(), 3);
    span.push(44);
    BOOST_TEST_EQ(span.size(), 4);
}

void dynamic_capacity()
{
    int array[4] = {};
    priority_view<int> span(array);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void dynamic_top()
{
    int array[4] = {};
    priority_view<int> span(array);
    span.push(11);
    BOOST_TEST_EQ(span.top(), 11);
}

void dynamic_top_const()
{
    int array[4] = {};
    priority_view<int> span(array);
    span.push(11);
    BOOST_TEST_EQ(const_cast<const priority_view<int>&>(span).top(), 11);
}

void dynamic_push()
{
    int array[4] = {};
    priority_view<int> span(array);
    BOOST_TEST_EQ(span.size(), 0);
    span.push(11);
    BOOST_TEST_EQ(span.size(), 1);
}

void dynamic_pop()
{
    int array[4] = {};
    priority_view<int> span(array);
    BOOST_TEST_EQ(span.size(), 0);
    span.push(11);
    BOOST_TEST_EQ(span.size(), 1);
    span.pop();
    BOOST_TEST_EQ(span.size(), 0);
}

void run()
{
    dynamic_ctor_default();
    dynamic_predicate_ctor_default();
    dynamic_ctor_copy();
    dynamic_ctor_move();
    dynamic_ctor_array();
    dynamic_ctor_pointer_size();
    dynamic_ctor_iterator();
    dynamic_empty();
    dynamic_full();
    dynamic_size();
    dynamic_capacity();
    dynamic_top();
    dynamic_top_const();
    dynamic_push();
    dynamic_pop();
}

} // namespace api_dynamic_suite

//-----------------------------------------------------------------------------

namespace api_fixed_suite
{

void fixed_ctor_default()
{
    priority_view<int, 0> span;
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 0);
}

void fixed_predicate_ctor_default()
{
    priority_view<int, 0, std::greater<int>> span;
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 0);
}

void fixed_ctor_copy()
{
    priority_view<int, 0> span;
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 0);
    priority_view<int, 0> clone(span);
    BOOST_TEST_EQ(clone.size(), 0);
    BOOST_TEST_EQ(clone.capacity(), 0);
}

void fixed_ctor_move()
{
    priority_view<int, 0> span;
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 0);
    priority_view<int, 0> clone(std::move(span));
    BOOST_TEST_EQ(clone.size(), 0);
    BOOST_TEST_EQ(clone.capacity(), 0);
}

void fixed_ctor_array()
{
    int array[4] = {};
    priority_view<int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void fixed_ctor_pointer_size()
{
    std::array<int, 4> array = { 11, 22, 33, 44 };
    priority_view<int, 4> span(array.data(), array.size());
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void fixed_ctor_iterator()
{
    std::array<int, 4> array = { 11, 22, 33, 44 };
    priority_view<int, 4> span(array.begin(), array.end());
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void fixed_empty()
{
    int array[4] = {};
    priority_view<int, 4> span(array);
    BOOST_TEST(span.empty());
    span.push(11);
    BOOST_TEST(!span.empty());
}

void fixed_full()
{
    int array[4] = {};
    priority_view<int, 4> span(array);
    BOOST_TEST(!span.full());
    span.push(11);
    span.push(22);
    span.push(33);
    BOOST_TEST(!span.full());
    span.push(44);
    BOOST_TEST(span.full());
}

void fixed_size()
{
    int array[4] = {};
    priority_view<int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 0);
    span.push(11);
    BOOST_TEST_EQ(span.size(), 1);
    span.push(22);
    BOOST_TEST_EQ(span.size(), 2);
    span.push(33);
    BOOST_TEST_EQ(span.size(), 3);
    span.push(44);
    BOOST_TEST_EQ(span.size(), 4);
}

void fixed_capacity()
{
    int array[4] = {};
    priority_view<int, 4> span(array);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void fixed_top()
{
    int array[4] = {};
    priority_view<int, 4> span(array);
    span.push(11);
    BOOST_TEST_EQ(span.top(), 11);
}

void fixed_top_const()
{
    int array[4] = {};
    priority_view<int, 4> span(array);
    span.push(11);
    BOOST_TEST_EQ((const_cast<const priority_view<int, 4>&>(span).top()), 11);
}

void fixed_push()
{
    int array[4] = {};
    priority_view<int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 0);
    span.push(11);
    BOOST_TEST_EQ(span.size(), 1);
}

void fixed_pop()
{
    int array[4] = {};
    priority_view<int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 0);
    span.push(11);
    BOOST_TEST_EQ(span.size(), 1);
    span.pop();
    BOOST_TEST_EQ(span.size(), 0);
}

void run()
{
    fixed_ctor_default();
    fixed_predicate_ctor_default();
    fixed_ctor_copy();
    fixed_ctor_move();
    fixed_ctor_array();
    fixed_ctor_pointer_size();
    fixed_ctor_iterator();
    fixed_empty();
    fixed_full();
    fixed_size();
    fixed_capacity();
    fixed_top();
    fixed_top_const();
    fixed_push();
    fixed_pop();
}

} // namespace api_fixed_suite

//-----------------------------------------------------------------------------

namespace push_suite
{

void push_increasing()
{
    std::array<int, 4> array = {};
    priority_view<int> span(array.begin(), array.end());
    span.push(11);
    {
        std::array<int, 4> expect = { 11, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.push(22);
    {
        std::array<int, 4> expect = { 22, 11, 0, 0 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.push(33);
    {
        std::array<int, 4> expect = { 33, 11, 22, 0 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.push(44);
    {
        std::array<int, 4> expect = { 44, 33, 22, 11 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
}

void push_increasing_predicate()
{
    std::array<int, 4> array = {};
    priority_view<int, dynamic_extent, std::greater<int>> span(array.begin(), array.end());
    span.push(11);
    {
        std::array<int, 4> expect = { 11, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.push(22);
    {
        std::array<int, 4> expect = { 11, 22, 0, 0 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.push(33);
    {
        std::array<int, 4> expect = { 11, 22, 33, 0 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.push(44);
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
}

void push_decreasing()
{
    std::array<int, 4> array = {};
    priority_view<int> span(array.begin(), array.end());
    span.push(44);
    {
        std::array<int, 4> expect = { 44, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.push(33);
    {
        std::array<int, 4> expect = { 44, 33, 0, 0 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.push(22);
    {
        std::array<int, 4> expect = { 44, 33, 22, 0 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.push(11);
    {
        std::array<int, 4> expect = { 44, 33, 22, 11 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
}

void push_decreasing_predicate()
{
    std::array<int, 4> array = {};
    priority_view<int, dynamic_extent, std::greater<int>> span(array.begin(), array.end());
    span.push(44);
    {
        std::array<int, 4> expect = { 44, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.push(33);
    {
        std::array<int, 4> expect = { 33, 44, 0, 0 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.push(22);
    {
        std::array<int, 4> expect = { 22, 44, 33, 0 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.push(11);
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
}

void run()
{
    push_increasing();
    push_increasing_predicate();
    push_decreasing();
    push_decreasing_predicate();
}

} // namespace push_suite

//-----------------------------------------------------------------------------

namespace pop_suite
{

void pop_increasing()
{
    std::array<int, 4> array = {};
    priority_view<int> span(array.begin(), array.end());
    span.push(11);
    span.push(22);
    span.push(33);
    span.push(44);
    {
        std::array<int, 4> expect = { 44, 33, 22, 11 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }

    span.pop();
    {
        std::array<int, 4> expect = { 33, 11, 22, 44 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.pop();
    {
        std::array<int, 4> expect = { 22, 11, 33, 44 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.pop();
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.pop();
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
}

void pop_increasing_predicate()
{
    std::array<int, 4> array = {};
    priority_view<int, dynamic_extent, std::greater<int>> span(array.begin(), array.end());
    span.push(11);
    span.push(22);
    span.push(33);
    span.push(44);
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }

    span.pop();
    {
        std::array<int, 4> expect = { 22, 44, 33, 11 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.pop();
    {
        std::array<int, 4> expect = { 33, 44, 22, 11 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.pop();
    {
        std::array<int, 4> expect = { 44, 33, 22, 11 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.pop();
    {
        std::array<int, 4> expect = { 44, 33, 22, 11 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
}

void pop_decreasing()
{
    std::array<int, 4> array = {};
    priority_view<int> span(array.begin(), array.end());
    span.push(44);
    span.push(33);
    span.push(22);
    span.push(11);
    {
        std::array<int, 4> expect = { 44, 33, 22, 11 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }

    span.pop();
    {
        std::array<int, 4> expect = { 33, 11, 22, 44 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.pop();
    {
        std::array<int, 4> expect = { 22, 11, 33, 44 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.pop();
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.pop();
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
}

void pop_decreasing_predicate()
{
    std::array<int, 4> array = {};
    priority_view<int, dynamic_extent, std::greater<int>> span(array.begin(), array.end());
    span.push(44);
    span.push(33);
    span.push(22);
    span.push(11);
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }

    span.pop();
    {
        std::array<int, 4> expect = { 22, 44, 33, 11 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.pop();
    {
        std::array<int, 4> expect = { 33, 44, 22, 11 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.pop();
    {
        std::array<int, 4> expect = { 44, 33, 22, 11 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    span.pop();
    {
        std::array<int, 4> expect = { 44, 33, 22, 11 };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
}

void run()
{
    pop_increasing();
    pop_increasing_predicate();
    pop_decreasing();
    pop_decreasing_predicate();
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
