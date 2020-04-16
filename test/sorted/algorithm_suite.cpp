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
#include <iterator>
#include <boost/detail/lightweight_test.hpp>
#include <vista/sorted/algorithm.hpp>

using namespace vista;

//-----------------------------------------------------------------------------

namespace lower_bound_suite
{

void find_even_first()
{
    std::array<int, 4> storage = { 11, 22, 33, 44 };
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 10),
                  storage.begin());
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 11),
                  storage.begin());
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 12),
                  std::next(storage.begin(), 1));
}

void find_even_first_predicate()
{
    std::array<int, 4> storage = { 44, 33, 22, 11 };
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 45, std::greater<int>{}),
                  storage.begin());
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 44, std::greater<int>{}),
                  storage.begin());
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 43, std::greater<int>{}),
                  std::next(storage.begin(), 1));
}

void find_even_last()
{
    std::array<int, 4> storage = { 11, 22, 33, 44 };
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 43),
                  std::next(storage.begin(), 3));
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 44),
                  std::next(storage.begin(), 3));
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 45),
                  storage.end());
}

void find_even_last_predicate()
{
    std::array<int, 4> storage = { 44, 33, 22, 11 };
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 12, std::greater<int>{}),
                  std::next(storage.begin(), 3));
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 11, std::greater<int>{}),
                  std::next(storage.begin(), 3));
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 10, std::greater<int>{}),
                  storage.end());
}

void find_odd_first()
{
    std::array<int, 5> storage = { 11, 22, 33, 44, 55 };
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 10),
                  storage.begin());
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 11),
                  storage.begin());
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 12),
                  std::next(storage.begin(), 1));
}

void find_odd_first_predicate()
{
    std::array<int, 5> storage = { 55, 44, 33, 22, 11 };
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 56, std::greater<int>{}),
                  storage.begin());
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 55, std::greater<int>{}),
                  storage.begin());
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 54, std::greater<int>{}),
                  std::next(storage.begin(), 1));
}

void find_odd_last()
{
    std::array<int, 5> storage = { 11, 22, 33, 44, 55 };
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 54),
                  std::next(storage.begin(), 4));
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 55),
                  std::next(storage.begin(), 4));
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 56),
                  storage.end());
}

void find_odd_last_predicate()
{
    std::array<int, 5> storage = { 55, 44, 33, 22, 11 };
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 12, std::greater<int>{}),
                  std::next(storage.begin(), 4));
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 11, std::greater<int>{}),
                  std::next(storage.begin(), 4));
    BOOST_TEST_EQ(sorted::lower_bound(storage.begin(), storage.end(), 10, std::greater<int>{}),
                  storage.end());
}

void run()
{
    find_even_first();
    find_even_first_predicate();
    find_even_last();
    find_even_last_predicate();
    find_odd_first();
    find_odd_first_predicate();
    find_odd_last();
    find_odd_last_predicate();
}

} // namespace lower_bound_suite

//-----------------------------------------------------------------------------

namespace push_suite
{

void push_increasing()
{
    std::array<int, 4> storage = { 0, 0, 0, 0 };
    auto last = storage.begin();
    *last++ = 11;
    sorted::push(storage.begin(), last);
    {
        std::array<int, 4> expect = { 11, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 22;
    sorted::push(storage.begin(), last);
    {
        std::array<int, 4> expect = { 11, 22, 0, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 33;
    sorted::push(storage.begin(), last);
    {
        std::array<int, 4> expect = { 11, 22, 33, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 44;
    sorted::push(storage.begin(), last);
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
}

void push_increasing_predicate()
{
    std::array<int, 4> storage = { 0, 0, 0, 0 };
    auto last = storage.begin();
    *last++ = 11;
    sorted::push(storage.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 11, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 22;
    sorted::push(storage.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 22, 11, 0, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 33;
    sorted::push(storage.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 33, 22, 11, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 44;
    sorted::push(storage.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 44, 33, 22, 11 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
}

void push_decreasing()
{
    std::array<int, 4> storage = { 0, 0, 0, 0 };
    auto last = storage.begin();
    *last++ = 44;
    sorted::push(storage.begin(), last);
    {
        std::array<int, 4> expect = { 44, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 33;
    sorted::push(storage.begin(), last);
    {
        std::array<int, 4> expect = { 33, 44, 0, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 22;
    sorted::push(storage.begin(), last);
    {
        std::array<int, 4> expect = { 22, 33, 44, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 11;
    sorted::push(storage.begin(), last);
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
}

void push_decreasing_predicate()
{
    std::array<int, 4> storage = { 0, 0, 0, 0 };
    auto last = storage.begin();
    *last++ = 44;
    sorted::push(storage.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 44, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 33;
    sorted::push(storage.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 44, 33, 0, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 22;
    sorted::push(storage.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 44, 33, 22, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 11;
    sorted::push(storage.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 44, 33, 22, 11 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
}

void push_alternating()
{
    std::array<int, 4> storage = { 0, 0, 0, 0 };
    auto last = storage.begin();
    *last++ = 11;
    sorted::push(storage.begin(), last);
    {
        std::array<int, 4> expect = { 11, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 44;
    sorted::push(storage.begin(), last);
    {
        std::array<int, 4> expect = { 11, 44, 0, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 22;
    sorted::push(storage.begin(), last);
    {
        std::array<int, 4> expect = { 11, 22, 44, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 33;
    sorted::push(storage.begin(), last);
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
}

void push_alternating_predicate()
{
    std::array<int, 4> storage = { 0, 0, 0, 0 };
    auto last = storage.begin();
    *last++ = 11;
    sorted::push(storage.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 11, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 44;
    sorted::push(storage.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 44, 11, 0, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 22;
    sorted::push(storage.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 44, 22, 11, 0 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 33;
    sorted::push(storage.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 44, 33, 22, 11 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
}

void run()
{
    push_increasing();
    push_increasing_predicate();
    push_decreasing();
    push_decreasing_predicate();
    push_alternating();
    push_alternating_predicate();
}

} // namespace push_suite

//-----------------------------------------------------------------------------

namespace pop_suite
{

void pop_increasing()
{
    std::array<int, 4> storage = { 11, 22, 33, 44 };
    auto last = storage.end();
    sorted::pop(storage.begin(), last);
    {
        std::array<int, 4> expect = { 22, 33, 44, 11 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    --last;
    sorted::pop(storage.begin(), last);
    {
        std::array<int, 4> expect = { 33, 44, 22, 11 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    --last;
    sorted::pop(storage.begin(), last);
    {
        std::array<int, 4> expect = { 44, 33, 22, 11 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    --last;
    sorted::pop(storage.begin(), last);
    {
        std::array<int, 4> expect = { 44, 33, 22, 11 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
}

void pop_decreasing()
{
    std::array<int, 4> storage = { 11, 22, 33, 44 };
    auto last = storage.end();
    auto first = last - 1;
    sorted::pop(first, last);
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    --first;
    --last;
    sorted::pop(first, last);
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    --first;
    --last;
    sorted::pop(first, last);
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    --first;
    --last;
    sorted::pop(first, last);
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
}

void pop_alternating()
{
    std::array<int, 4> storage = { 11, 22, 33, 44 };
    auto last = storage.end();
    auto first = sorted::lower_bound(storage.begin(), last, 11);
    sorted::pop(first, last);
    {
        std::array<int, 4> expect = { 22, 33, 44, 11 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    --last;
    first = sorted::lower_bound(storage.begin(), last, 44);
    sorted::pop(first, last);
    {
        std::array<int, 4> expect = { 22, 33, 44, 11 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    --last;
    first = sorted::lower_bound(storage.begin(), last, 22);
    sorted::pop(first, last);
    {
        std::array<int, 4> expect = { 33, 22, 44, 11 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
                          expect.begin(), expect.end());
    }
    --last;
    first = sorted::lower_bound(storage.begin(), last, 33);
    sorted::pop(first, last);
    {
        std::array<int, 4> expect = { 33, 22, 44, 11 };
        BOOST_TEST_ALL_EQ(storage.begin(), storage.end(),
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
    lower_bound_suite::run();
    push_suite::run();
    pop_suite::run();
 
    return boost::report_errors();
}
