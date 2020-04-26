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
#include <boost/core/lightweight_test.hpp>
#include <vista/heap/algorithm.hpp>

using namespace vista;

//-----------------------------------------------------------------------------

// Permuted ordering with base 0x55555555
// 22 = 0x55555543
// 11 = 0x5555555E
// 55 = 0x55555562
// 33 = 0x55555574
// 44 = 0x55555579

template <typename T, T base>
struct xless
{
    constexpr bool operator()(const T& lhs, const T& rhs) noexcept
    {
        return std::less<T>{}(lhs ^ base, rhs ^ base);
    }
};

//-----------------------------------------------------------------------------

namespace push_suite
{

void push_increasing()
{
    std::array<int, 4> heap = {};
    auto last = heap.begin();
    *last++ = 11;
    heap::push(heap.begin(), last);
    {
        std::array<int, 4> expect = { 11, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 22;
    heap::push(heap.begin(), last);
    {
        std::array<int, 4> expect = { 22, 11, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 33;
    heap::push(heap.begin(), last);
    {
        std::array<int, 4> expect = { 33, 11, 22, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 44;
    heap::push(heap.begin(), last);
    {
        std::array<int, 4> expect = { 44, 33, 22, 11 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
}

void push_increasing_predicate()
{
    std::array<int, 4> heap = {};
    auto last = heap.begin();
    *last++ = 11;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 11, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 22;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 11, 22, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 33;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 11, 22, 33, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 44;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
}

void push_increasing_custom()
{
    xless<int, 0x55555555> custom;

    std::array<int, 5> heap = {};
    auto last = heap.begin();
    *last++ = 11;
    heap::push(heap.begin(), last, custom);
    {
        std::array<int, 5> expect = { 11, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 22;
    heap::push(heap.begin(), last, custom);
    {
        std::array<int, 5> expect = { 11, 22, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 33;
    heap::push(heap.begin(), last, custom);
    {
        std::array<int, 5> expect = { 33, 22, 11, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 44;
    heap::push(heap.begin(), last, custom);
    {
        std::array<int, 5> expect = { 44, 33, 11, 22, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 55;
    heap::push(heap.begin(), last, custom);
    {
        std::array<int, 5> expect = { 44, 33, 11, 22, 55 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
}

void push_decreasing()
{
    std::array<int, 4> heap = {};
    auto last = heap.begin();
    *last++ = 44;
    heap::push(heap.begin(), last);
    {
        std::array<int, 4> expect = { 44, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 33;
    heap::push(heap.begin(), last);
    {
        std::array<int, 4> expect = { 44, 33, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 22;
    heap::push(heap.begin(), last);
    {
        std::array<int, 4> expect = { 44, 33, 22, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 11;
    heap::push(heap.begin(), last);
    {
        std::array<int, 4> expect = { 44, 33, 22, 11 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
}

void push_decreasing_predicate()
{
    std::array<int, 4> heap = {};
    auto last = heap.begin();
    *last++ = 44;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 44, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 33;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 33, 44, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 22;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 22, 44, 33, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 11;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 4> expect = { 11, 22, 33, 44 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
}

void push_decreasing_custom()
{
    xless<int, 0x55555555> custom;

    std::array<int, 5> heap = {};
    auto last = heap.begin();
    *last++ = 55;
    heap::push(heap.begin(), last, custom);
    {
        std::array<int, 5> expect = { 55, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 44;
    heap::push(heap.begin(), last, custom);
    {
        std::array<int, 5> expect = { 44, 55, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 33;
    heap::push(heap.begin(), last, custom);
    {
        std::array<int, 5> expect = { 44, 55, 33, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 22;
    heap::push(heap.begin(), last, custom);
    {
        std::array<int, 5> expect = { 44, 55, 33, 22, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 11;
    heap::push(heap.begin(), last, custom);
    {
        std::array<int, 5> expect = { 44, 55, 33, 22, 11 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
}

void push_sequence()
{
    // 8 3 6 9 5 2 15 1 4 12 7 10 13 11 14

    std::array<int, 15> heap = {};
    auto last = heap.begin();
    *last++ = 8;
    heap::push(heap.begin(), last);
    {
        std::array<int, 15> expect = { 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 3;
    heap::push(heap.begin(), last);
    {
        std::array<int, 15> expect = { 8, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 6;
    heap::push(heap.begin(), last);
    {
        std::array<int, 15> expect = { 8, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 9;
    heap::push(heap.begin(), last);
    {
        std::array<int, 15> expect = { 9, 8, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 5;
    heap::push(heap.begin(), last);
    {
        std::array<int, 15> expect = { 9, 8, 6, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 2;
    heap::push(heap.begin(), last);
    {
        std::array<int, 15> expect = { 9, 8, 6, 3, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 15;
    heap::push(heap.begin(), last);
    {
        std::array<int, 15> expect = { 15, 8, 9, 3, 5, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 1;
    heap::push(heap.begin(), last);
    {
        std::array<int, 15> expect = { 15, 8, 9, 3, 5, 2, 6, 1, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 4;
    heap::push(heap.begin(), last);
    {
        std::array<int, 15> expect = { 15, 8, 9, 4, 5, 2, 6, 1, 3, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 12;
    heap::push(heap.begin(), last);
    {
        std::array<int, 15> expect = { 15, 12, 9, 4, 8, 2, 6, 1, 3, 5, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 7;
    heap::push(heap.begin(), last);
    {
        std::array<int, 15> expect = { 15, 12, 9, 4, 8, 2, 6, 1, 3, 5, 7, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 10;
    heap::push(heap.begin(), last);
    {
        std::array<int, 15> expect = { 15, 12, 10, 4, 8, 9, 6, 1, 3, 5, 7, 2, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 13;
    heap::push(heap.begin(), last);
    {
        std::array<int, 15> expect = { 15, 12, 13, 4, 8, 10, 6, 1, 3, 5, 7, 2, 9, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 11;
    heap::push(heap.begin(), last);
    {
        std::array<int, 15> expect = { 15, 12, 13, 4, 8, 10, 11, 1, 3, 5, 7, 2, 9, 6, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 14;
    heap::push(heap.begin(), last);
    {
        std::array<int, 15> expect = { 15, 12, 14, 4, 8, 10, 13, 1, 3, 5, 7, 2, 9, 6, 11 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
}

void push_sequence_predicate()
{
    // 8 3 6 9 5 2 15 1 4 12 7 10 13 11 14

    std::array<int, 15> heap = {};
    auto last = heap.begin();
    *last++ = 8;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 15> expect = { 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 3;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 15> expect = { 3, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 6;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 15> expect = { 3, 8, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 9;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 15> expect = { 3, 8, 6, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 5;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 15> expect = { 3, 5, 6, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 2;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 15> expect = { 2, 5, 3, 9, 8, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 15;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 15> expect = { 2, 5, 3, 9, 8, 6, 15, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 1;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 15> expect = { 1, 2, 3, 5, 8, 6, 15, 9, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 4;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 15> expect = { 1, 2, 3, 4, 8, 6, 15, 9, 5, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 12;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 15> expect = { 1, 2, 3, 4, 8, 6, 15, 9, 5, 12, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 7;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 15> expect = { 1, 2, 3, 4, 7, 6, 15, 9, 5, 12, 8, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 10;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 15> expect = { 1, 2, 3, 4, 7, 6, 15, 9, 5, 12, 8, 10, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 13;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 15> expect = { 1, 2, 3, 4, 7, 6, 15, 9, 5, 12, 8, 10, 13, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 11;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 15> expect = { 1, 2, 3, 4, 7, 6, 11, 9, 5, 12, 8, 10, 13, 15, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    *last++ = 14;
    heap::push(heap.begin(), last, std::greater<int>{});
    {
        std::array<int, 15> expect = { 1, 2, 3, 4, 7, 6, 11, 9, 5, 12, 8, 10, 13, 15, 14 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
}

void run()
{
    push_increasing();
    push_increasing_predicate();
    push_increasing_custom();
    push_decreasing();
    push_decreasing_predicate();
    push_decreasing_custom();
    push_sequence();
    push_sequence_predicate();
}

} // namespace push_suite

//-----------------------------------------------------------------------------

namespace pop_suite
{

void pop_increasing()
{
    std::array<int, 4> heap = { 44, 33, 22, 11 }; // Result of push_suite::push_increasing
    auto last = heap.end();
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 4> expect = { 33, 11, 22, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 4> expect = { 22, 11, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 4> expect = { 11, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 4> expect = { 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
}

void pop_increasing_predicate()
{
    std::array<int, 4> heap = { 11, 22, 33, 44 }; // Result of push_suite::push_increasing_predicate
    auto last = heap.end();
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 4> expect = { 22, 44, 33, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 4> expect = { 33, 44, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 4> expect = { 44, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 4> expect = { 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
}

void pop_increasing_custom()
{
    xless<int, 0x55555555> custom;

    std::array<int, 5> heap = { 44, 33, 11, 22, 55 }; // Result of push_suite::push_increasing_custom
    auto last = heap.end();
    heap::pop(heap.begin(), last, custom);
    *--last = 0;
    {
        std::array<int, 5> expect = { 33, 55, 11, 22, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, custom);
    *--last = 0;
    {
        std::array<int, 5> expect = { 55, 22, 11, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, custom);
    *--last = 0;
    {
        std::array<int, 5> expect = { 11, 22, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, custom);
    *--last = 0;
    {
        std::array<int, 5> expect = { 22, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, custom);
    *--last = 0;
    {
        std::array<int, 5> expect = { 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
}

void pop_decreasing()
{
    std::array<int, 4> heap = { 44, 33, 22, 11 }; // Result of push_suite::push_decreasing
    auto last = heap.end();
    heap::pop(heap.begin(), last, std::less<int>());
    *--last = 0;
    {
        std::array<int, 4> expect = { 33, 11, 22, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::less<int>());
    *--last = 0;
    {
        std::array<int, 4> expect = { 22, 11, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::less<int>());
    *--last = 0;
    {
        std::array<int, 4> expect = { 11, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::less<int>());
    *--last = 0;
    {
        std::array<int, 4> expect = { 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
}

void pop_decreasing_predicate()
{
    std::array<int, 4> heap = { 11, 22, 33, 44 }; // Result of push_suite::push_decreasing_predicate
    auto last = heap.end();
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 4> expect = { 22, 44, 33, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 4> expect = { 33, 44, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 4> expect = { 44, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 4> expect = { 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
}

void pop_decreasing_custom()
{
    xless<int, 0x55555555> custom;

    std::array<int, 5> heap = { 44, 55, 33, 22, 11 }; // Result of push_suite::push_decreasing_custom
    auto last = heap.end();
    heap::pop(heap.begin(), last, custom);
    *--last = 0;
    {
        std::array<int, 5> expect = { 33, 55, 11, 22, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, custom);
    *--last = 0;
    {
        std::array<int, 5> expect = { 55, 22, 11, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, custom);
    *--last = 0;
    {
        std::array<int, 5> expect = { 11, 22, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, custom);
    *--last = 0;
    {
        std::array<int, 5> expect = { 22, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, custom);
    *--last = 0;
    {
        std::array<int, 5> expect = { 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
}

void pop_sequence()
{
    std::array<int, 15> heap = { 15, 12, 14, 4, 8, 10, 13, 1, 3, 5, 7, 2, 9, 6, 11 }; // Result of push_suite::push_sequence
    auto last = heap.end();
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 15> expect = { 14, 12, 13, 4, 8, 10, 11, 1, 3, 5, 7, 2, 9, 6, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 15> expect = { 13, 12, 11, 4, 8, 10, 6, 1, 3, 5, 7, 2, 9, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 15> expect = { 12, 9, 11, 4, 8, 10, 6, 1, 3, 5, 7, 2, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 15> expect = { 11, 9, 10, 4, 8, 2, 6, 1, 3, 5, 7, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 15> expect = { 10, 9, 7, 4, 8, 2, 6, 1, 3, 5, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 15> expect = { 9, 8, 7, 4, 5, 2, 6, 1, 3, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 15> expect = { 8, 5, 7, 4, 3, 2, 6, 1, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 15> expect = { 7, 5, 6, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 15> expect = { 6, 5, 2, 4, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 15> expect = { 5, 4, 2, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 15> expect = { 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 15> expect = { 3, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 15> expect = { 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 15> expect = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last);
    *--last = 0;
    {
        std::array<int, 15> expect = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
}

void pop_sequence_predicate()
{
    std::array<int, 15> heap = { 1, 2, 3, 4, 7, 6, 11, 9, 5, 12, 8, 10, 13, 15, 14 }; // Result of push_suite::push_sequence_predicate
    auto last = heap.end();
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 15> expect = { 2, 4, 3, 5, 7, 6, 11, 9, 14, 12, 8, 10, 13, 15, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 15> expect = { 3, 4, 6, 5, 7, 10, 11, 9, 14, 12, 8, 15, 13, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 15> expect = { 4, 5, 6, 9, 7, 10, 11, 13, 14, 12, 8, 15, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 15> expect = { 5, 7, 6, 9, 8, 10, 11, 13, 14, 12, 15, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 15> expect = { 6, 7, 10, 9, 8, 15, 11, 13, 14, 12, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 15> expect = { 7, 8, 10, 9, 12, 15, 11, 13, 14, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 15> expect = { 8, 9, 10, 13, 12, 15, 11, 14, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 15> expect = { 9, 12, 10, 13, 14, 15, 11, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 15> expect = { 10, 12, 11, 13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 15> expect = { 11, 12, 15, 13, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 15> expect = { 12, 13, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 15> expect = { 13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 15> expect = { 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 15> expect = { 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
    heap::pop(heap.begin(), last, std::greater<int>());
    *--last = 0;
    {
        std::array<int, 15> expect = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOST_TEST_ALL_EQ(heap.begin(), heap.end(),
                          expect.begin(), expect.end());
    }
}

void run()
{
    pop_increasing();
    pop_increasing_predicate();
    pop_increasing_custom();
    pop_decreasing();
    pop_decreasing_predicate();
    pop_decreasing_custom();
    pop_sequence();
    pop_sequence_predicate();
}

} // namespace pop_suite

//-----------------------------------------------------------------------------

int main()
{
    push_suite::run();
    pop_suite::run();

    return boost::report_errors();
}
