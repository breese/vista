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
#include <string>
#include <iterator>
#include <boost/detail/lightweight_test.hpp>
#include <vista/map/span.hpp>

using namespace vista;

namespace std
{

template <typename Key, typename T>
std::ostream& operator<<(std::ostream& stream, const vista::map::pair<Key, T>& data)
{
    stream << '{' << data.first << ',' << data.second << '}';
    return stream;
}

} // namespace std

//-----------------------------------------------------------------------------

namespace api_dynamic_suite
{

void api_ctor_default()
{
    map::span<int, int> span;
    BOOST_TEST_EQ(span.capacity(), 0);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST(span.empty());
    BOOST_TEST(span.full());
}

void api_ctor_move()
{
    map::span<int, int> span;
    BOOST_TEST_EQ(span.capacity(), 0);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST(span.empty());
    BOOST_TEST(span.full());
    map::span<int, int> clone(std::move(span));
    BOOST_TEST_EQ(clone.capacity(), 0);
    BOOST_TEST_EQ(clone.size(), 0);
    BOOST_TEST(clone.empty());
    BOOST_TEST(clone.full());
}

void api_ctor_move_assign()
{
    map::span<int, int> span;
    BOOST_TEST_EQ(span.capacity(), 0);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST(span.empty());
    BOOST_TEST(span.full());
    map::span<int, int> clone;
    BOOST_TEST_EQ(span.capacity(), 0);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST(span.empty());
    BOOST_TEST(span.full());
    clone = std::move(span);
    BOOST_TEST_EQ(clone.capacity(), 0);
    BOOST_TEST_EQ(clone.size(), 0);
    BOOST_TEST(clone.empty());
    BOOST_TEST(clone.full());
}

void api_ctor_iterator()
{
    std::array<map::pair<int, int>, 4> storage = {};
    map::span<int, int> span(storage.begin(), storage.end());
    BOOST_TEST_EQ(span.capacity(), 4);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST(span.empty());
    BOOST_TEST(!span.full());
}

void api_ctor_array()
{
    map::pair<int, int> storage[4];
    map::span<int, int> span(storage);
    BOOST_TEST_EQ(span.capacity(), 4);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST(span.empty());
    BOOST_TEST(!span.full());
}

void api_capacity()
{
    map::span<int, int> span;
    BOOST_TEST_EQ(span.capacity(), 0);
}

void api_size()
{
    map::span<int, int> span;
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

void api_clear()
{
    map::pair<int, int> storage[4];
    map::span<int, int> span(storage);
    span.insert({ 11, 1 });
    BOOST_TEST_EQ(span.size(), 1);
    span.clear();
    BOOST_TEST_EQ(span.size(), 0);
}

void api_insert_value()
{
    map::pair<int, int> storage[4];
    map::span<int, int> span(storage);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.insert({ 11, 1 }), span.begin());
    BOOST_TEST_EQ(span.size(), 1);
}

void api_insert_hint()
{
    map::pair<int, int> storage[4];
    map::span<int, int> span(storage);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.insert(span.begin(), { 11, 1 }), span.begin());
    BOOST_TEST_EQ(span.size(), 1);
}

void api_erase_key()
{
    map::pair<int, int> storage[4];
    map::span<int, int> span(storage);
    span.insert({ 11, 1 });
    BOOST_TEST_EQ(span.size(), 1);
    BOOST_TEST_EQ(span.erase(11), 1);
    BOOST_TEST_EQ(span.size(), 0);
}

void api_erase_iterator()
{
    map::pair<int, int> storage[4];
    map::span<int, int> span(storage);
    span.insert({ 11, 1 });
    BOOST_TEST_EQ(span.size(), 1);
    span.erase(span.begin());
    BOOST_TEST_EQ(span.size(), 0);
}

void api_contains()
{
    map::pair<int, int> storage[4];
    map::span<int, int> span(storage);
    span.insert({ 11, 1 });
    BOOST_TEST(!span.contains(10));
    BOOST_TEST(span.contains(11));
    BOOST_TEST(!span.contains(12));
}

void api_find()
{
    map::pair<int, int> storage[4];
    map::span<int, int> span(storage);
    span.insert({ 11, 1 });
    BOOST_TEST_EQ(span.find(10), span.end());
    BOOST_TEST_EQ(span.find(11), span.begin());
    BOOST_TEST_EQ(span.find(12), span.end());
}

void api_lower_bound()
{
    map::pair<int, int> storage[4];
    map::span<int, int> span(storage);
    BOOST_TEST_EQ(span.lower_bound(11), span.end());
    span.insert({ 11, 1 });
    BOOST_TEST_EQ(span.lower_bound(10), span.begin());
    BOOST_TEST_EQ(span.lower_bound(11), span.begin());
    BOOST_TEST_EQ(span.lower_bound(12), span.end());
}

void api_operator_index()
{
    map::pair<int, int> storage[4];
    map::span<int, int> span(storage);
    span.insert({ 11, 1 });
    BOOST_TEST_EQ(span[11], 1);
}

void api_operator_index_empty()
{
    map::pair<int, int> storage[4];
    map::span<int, int> span(storage);
    BOOST_TEST_EQ(span[11], 0);
}

void api_begin_end()
{
    map::pair<int, int> storage[4];
    map::span<int, int> span(storage);
    BOOST_TEST_EQ(span.begin(), span.end());
}

void api_begin_end_const()
{
    map::pair<int, int> storage[4];
    const map::span<int, int> span(storage);
    BOOST_TEST_EQ(span.begin(), span.end());
}

void api_cbegin_cend()
{
    map::pair<int, int> storage[4];
    map::span<int, int> span(storage);
    BOOST_TEST_EQ(span.cbegin(), span.cend());
}

void api_key_compare()
{
    map::span<int, int> span;
    BOOST_TEST(span.key_comp()(11, 22));
}

void run()
{
    api_ctor_default();
    api_ctor_move();
    api_ctor_move_assign();
    api_ctor_iterator();
    api_ctor_array();
    api_capacity();
    api_size();
    api_empty();
    api_full();
    api_clear();
    api_insert_value();
    api_insert_hint();
    api_erase_key();
    api_erase_iterator();
    api_contains();
    api_find();
    api_lower_bound();
    api_operator_index();
    api_operator_index_empty();
    api_begin_end();
    api_begin_end_const();
    api_cbegin_cend();
    api_key_compare();
}

} // namespace api_dynamic_suite

//-----------------------------------------------------------------------------

namespace api_fixed_suite
{

void api_ctor_default()
{
    map::span<int, int, 4> span;
    BOOST_TEST_EQ(span.capacity(), 4);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST(span.empty());
    BOOST_TEST(!span.full());
}

void api_ctor_move()
{
    map::span<int, int, 4> span;
    BOOST_TEST_EQ(span.capacity(), 4);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST(span.empty());
    BOOST_TEST(!span.full());
    map::span<int, int, 4> clone(std::move(span));
    BOOST_TEST_EQ(clone.capacity(), 4);
    BOOST_TEST_EQ(clone.size(), 0);
    BOOST_TEST(clone.empty());
    BOOST_TEST(!clone.full());
}

void api_ctor_move_assign()
{
    map::span<int, int, 4> span;
    BOOST_TEST_EQ(span.capacity(), 4);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST(span.empty());
    BOOST_TEST(!span.full());
    map::span<int, int, 4> clone;
    BOOST_TEST_EQ(span.capacity(), 4);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST(span.empty());
    BOOST_TEST(!span.full());
    clone = std::move(span);
    BOOST_TEST_EQ(clone.capacity(), 4);
    BOOST_TEST_EQ(clone.size(), 0);
    BOOST_TEST(clone.empty());
    BOOST_TEST(!clone.full());
}

void api_ctor_iterator()
{
    std::array<map::pair<int, int>, 4> storage = {};
    map::span<int, int, 4> span(storage.begin(), storage.end());
    BOOST_TEST_EQ(span.capacity(), 4);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST(span.empty());
    BOOST_TEST(!span.full());
}

void api_ctor_array()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    BOOST_TEST_EQ(span.capacity(), 4);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST(span.empty());
    BOOST_TEST(!span.full());
}

void api_capacity()
{
    map::span<int, int, 4> span;
    BOOST_TEST_EQ(span.capacity(), 4);
}

void api_size()
{
    map::span<int, int, 4> span;
    BOOST_TEST_EQ(span.size(), 0);
}

void api_empty()
{
    map::span<int, int, 4> span;
    BOOST_TEST(span.empty());
}

void api_full()
{
    map::span<int, int, 4> span;
    BOOST_TEST(!span.full());
}

void api_insert_value()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.insert({ 11, 1 }), span.begin());
    BOOST_TEST_EQ(span.size(), 1);
}

void api_insert_hint()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.insert(span.begin(), { 11, 1 }), span.begin());
    BOOST_TEST_EQ(span.size(), 1);
}

void api_erase_key()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    span.insert({ 11, 1 });
    BOOST_TEST_EQ(span.size(), 1);
    BOOST_TEST_EQ(span.erase(11), 1);
    BOOST_TEST_EQ(span.size(), 0);
}

void api_erase_iterator()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    span.insert({ 11, 1 });
    BOOST_TEST_EQ(span.size(), 1);
    span.erase(span.begin());
    BOOST_TEST_EQ(span.size(), 0);
}

void api_contains()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    span.insert({ 11, 1 });
    BOOST_TEST(!span.contains(10));
    BOOST_TEST(span.contains(11));
    BOOST_TEST(!span.contains(12));
}

void api_find()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    span.insert({ 11, 1 });
    BOOST_TEST_EQ(span.find(10), span.end());
    BOOST_TEST_EQ(span.find(11), span.begin());
    BOOST_TEST_EQ(span.find(12), span.end());
}

void api_lower_bound()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    span.insert({ 11, 1 });
    BOOST_TEST_EQ(span.lower_bound(10), span.begin());
    BOOST_TEST_EQ(span.lower_bound(11), span.begin());
    BOOST_TEST_EQ(span.lower_bound(12), span.end());
}

void api_operator_index()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    span.insert({ 11, 1 });
    BOOST_TEST_EQ(span[11], 1);
}

void api_operator_index_empty()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    BOOST_TEST_EQ(span[11], 0);
}

void api_begin_end()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    BOOST_TEST_EQ(span.begin(), span.end());
}

void api_begin_end_const()
{
    map::pair<int, int> storage[4];
    const map::span<int, int, 4> span(storage);
    BOOST_TEST_EQ(span.begin(), span.end());
}

void api_cbegin_cend()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    BOOST_TEST_EQ(span.cbegin(), span.cend());
}

void api_key_compare()
{
    map::span<int, int, 4> span;
    BOOST_TEST(span.key_comp()(11, 22));
}

void run()
{
    api_ctor_default();
    api_ctor_move();
    api_ctor_move_assign();
    api_ctor_iterator();
    api_ctor_array();
    api_capacity();
    api_size();
    api_empty();
    api_full();
    api_insert_value();
    api_insert_hint();
    api_erase_key();
    api_erase_iterator();
    api_contains();
    api_find();
    api_lower_bound();
    api_operator_index();
    api_operator_index_empty();
    api_begin_end();
    api_begin_end_const();
    api_cbegin_cend();
    api_key_compare();
}

} // namespace api_fixed_suite

//-----------------------------------------------------------------------------

namespace insert_suite
{

void insert_increasing()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    span.insert({ 11, 1 });
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    span.insert({ 22, 2 });
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 }, { 22, 2 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    span.insert({ 33, 3 });
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 }, { 22, 2 }, { 33, 3 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    span.insert({ 44, 4 });
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 }, { 22, 2 }, { 33, 3 }, { 44, 4 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    // Insertion into full map has no effect
    BOOST_TEST(span.full());
    BOOST_TEST_EQ(span.insert({ 55, 5 }), span.end());
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 }, { 22, 2 }, { 33, 3 }, { 44, 4 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
}

void insert_decreasing()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    span.insert({ 44, 4 });
    {
        std::vector<map::pair<int, int>> expect = { { 44, 4 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    span.insert({ 33, 3 });
    {
        std::vector<map::pair<int, int>> expect = { { 33, 3 }, { 44, 4 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    span.insert({ 22, 2 });
    {
        std::vector<map::pair<int, int>> expect = { { 22, 2 }, { 33, 3 }, { 44, 4 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    span.insert({ 11, 1 });
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 }, { 22, 2 }, { 33, 3 }, { 44, 4 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
}

void insert_alternating()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    span.insert({ 11, 1 });
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    span.insert({ 44, 4 });
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 }, { 44, 4 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    span.insert({ 22, 2 });
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 }, { 22, 2 }, { 44, 4 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    span.insert({ 33, 3 });
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 }, { 22, 2 }, { 33, 3 }, { 44, 4 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
}

void run()
{
    insert_increasing();
    insert_decreasing();
    insert_alternating();
}

} // namespace insert_suite

//-----------------------------------------------------------------------------

namespace erase_suite
{

void erase_beginning()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    span.insert({ 11, 1 });
    span.insert({ 22, 2 });
    span.insert({ 33, 3 });
    span.insert({ 44, 4 });
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 }, { 22, 2 }, { 33, 3 }, { 44, 4 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }

    span.erase(span.begin());
    {
        std::vector<map::pair<int, int>> expect = { { 22, 2 }, { 33, 3 }, { 44, 4 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    span.erase(span.begin());
    {
        std::vector<map::pair<int, int>> expect = { { 33, 3 }, { 44, 4 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    span.erase(span.begin());
    {
        std::vector<map::pair<int, int>> expect = { { 44, 4 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    span.erase(span.begin());
    {
        std::vector<map::pair<int, int>> expect = {};
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
}

void erase_ending()
{
    map::pair<int, int> storage[4];
    map::span<int, int, 4> span(storage);
    span.insert({ 11, 1 });
    span.insert({ 22, 2 });
    span.insert({ 33, 3 });
    span.insert({ 44, 4 });
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 }, { 22, 2 }, { 33, 3 }, { 44, 4 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }

    span.erase(std::prev(span.end()));
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 }, { 22, 2 }, { 33, 3 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    span.erase(std::prev(span.end()));
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 }, { 22, 2 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    span.erase(std::prev(span.end()));
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    span.erase(std::prev(span.end()));
    {
        std::vector<map::pair<int, int>> expect = {};
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
}

void run()
{
    erase_beginning();
    erase_ending();
}

} // namespace erase_suite

//-----------------------------------------------------------------------------

namespace string_suite
{

void string_clear()
{
    map::pair<std::string, std::string> storage[4];
    map::span<std::string, std::string> span(storage);
    span.insert({ "alpha", "hydrogen" });
    {
        std::vector<map::pair<std::string, std::string>> expect = { { "alpha", "hydrogen" } };
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
    span.clear();
    {
        std::vector<map::pair<std::string, std::string>> expect = {};
        BOOST_TEST_ALL_EQ(storage, storage + span.size(),
                          expect.begin(), expect.end());
    }
}

void run()
{
    string_clear();
}

} // namespace string_suite

//-----------------------------------------------------------------------------

int main()
{
    api_dynamic_suite::run();
    api_fixed_suite::run();
    insert_suite::run();
    erase_suite::run();
    string_suite::run();
 
    return boost::report_errors();
}
