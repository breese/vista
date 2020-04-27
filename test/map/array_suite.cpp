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
#include <vista/map/array.hpp>

using namespace vista;

//-----------------------------------------------------------------------------

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

namespace api_suite
{

void api_ctor_default()
{
    map::array<int, int, 4> array;
    BOOST_TEST_EQ(array.size(), 0);
    BOOST_TEST_EQ(array.capacity(), 4);
}

void api_capacity()
{
    map::array<int, int, 4> array;
    BOOST_TEST_EQ(array.capacity(), 4);
}

void api_size()
{
    map::array<int, int, 4> array;
    BOOST_TEST_EQ(array.size(), 0);
}

void api_empty()
{
    map::array<int, int, 4> array;
    BOOST_TEST(array.empty());
}

void api_full()
{
    map::array<int, int, 4> array;
    BOOST_TEST(!array.full());
}

void api_clear()
{
    map::array<int, int, 4> array;
    array.insert({ 11, 1 });
    BOOST_TEST_EQ(array.size(), 1);
    array.clear();
    BOOST_TEST_EQ(array.size(), 0);
}

void api_insert_value()
{
    map::array<int, int, 4> array;
    BOOST_TEST_EQ(array.size(), 0);
    BOOST_TEST_EQ(array.insert({ 11, 1 }), array.begin());
    BOOST_TEST_EQ(array.size(), 1);
}

void api_insert_hint()
{
    map::array<int, int, 4> array;
    BOOST_TEST_EQ(array.size(), 0);
    BOOST_TEST_EQ(array.insert(array.begin(), { 11, 1 }), array.begin());
    BOOST_TEST_EQ(array.size(), 1);
}

void api_emplace_value()
{
    map::array<int, int, 4> array;
    BOOST_TEST_EQ(array.size(), 0);
    BOOST_TEST_EQ(array.emplace(11, 1), array.begin());
    BOOST_TEST_EQ(array.size(), 1);
}

void api_emplace_piecewise()
{
    map::array<int, int, 4> array;
    BOOST_TEST_EQ(array.size(), 0);
    BOOST_TEST_EQ(array.emplace(std::piecewise_construct,
                                std::forward_as_tuple(11),
                                std::forward_as_tuple(1)),
                  array.begin());
    BOOST_TEST_EQ(array.size(), 1);
}

void api_emplace_hint()
{
    map::array<int, int, 4> array;
    BOOST_TEST_EQ(array.size(), 0);
    BOOST_TEST_EQ(array.emplace_hint(array.begin(), 11, 1), array.begin());
    BOOST_TEST_EQ(array.size(), 1);
}

void api_erase_key()
{
    map::array<int, int, 4> array;
    array.insert({ 11, 1 });
    BOOST_TEST_EQ(array.size(), 1);
    BOOST_TEST_EQ(array.erase(11), 1);
    BOOST_TEST_EQ(array.size(), 0);
}

void api_contains()
{
    map::array<int, int, 4> array;
    array.insert({ 11, 1 });
    BOOST_TEST(!array.contains(10));
    BOOST_TEST(array.contains(11));
    BOOST_TEST(!array.contains(12));
}

void api_find()
{
    map::array<int, int, 4> array;
    array.insert({ 11, 1 });
    BOOST_TEST_EQ(array.find(10), array.end());
    BOOST_TEST_EQ(array.find(11), array.begin());
    BOOST_TEST_EQ(array.find(12), array.end());
}

void api_lower_bound()
{
    map::array<int, int, 4> array;
    array.insert({ 11, 1 });
    BOOST_TEST_EQ(array.lower_bound(10), array.begin());
    BOOST_TEST_EQ(array.lower_bound(11), array.begin());
    BOOST_TEST_EQ(array.lower_bound(12), array.end());
}

void api_index_operator()
{
    map::array<int, int, 4> array;
    array.insert({ 11, 1 });
    BOOST_TEST_EQ(array[11], 1);
    BOOST_TEST_EQ(array[12], 0); // Inserts {12, 0}
}

void api_begin_end()
{
    map::array<int, int, 4> array;
    BOOST_TEST_EQ(array.begin(), array.end());
}

void api_begin_end_const()
{
    const map::array<int, int, 4> array;
    BOOST_TEST_EQ(array.begin(), array.end());
}

void api_cbegin_cend()
{
    map::array<int, int, 4> array;
    BOOST_TEST_EQ(array.cbegin(), array.cend());
}

void api_key_comp()
{
    map::array<int, int, 4> array;
    BOOST_TEST(!array.key_comp()(11, 10));
    BOOST_TEST(!array.key_comp()(11, 11));
    BOOST_TEST(array.key_comp()(11, 12));
}

void run()
{
    api_ctor_default();
    api_capacity();
    api_size();
    api_empty();
    api_full();
    api_clear();
    api_insert_value();
    api_insert_hint();
    api_emplace_value();
    api_emplace_value();
    api_emplace_piecewise();
    api_emplace_hint();
    api_erase_key();
    api_contains();
    api_find();
    api_lower_bound();
    api_index_operator();
    api_begin_end();
    api_begin_end_const();
    api_cbegin_cend();
    api_key_comp();
}

} // namespace api_suite

//-----------------------------------------------------------------------------

namespace erase_suite
{

void erase_beginning()
{
    map::array<int, int, 4> array;
    array.insert({ 11, 1 });
    array.insert({ 22, 2 });
    array.insert({ 33, 3 });
    array.insert({ 44, 4 });
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 }, { 22, 2 }, { 33, 3 }, { 44, 4 } };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }

    array.erase(array.begin());
    {
        std::vector<map::pair<int, int>> expect = { { 22, 2 }, { 33, 3 }, { 44, 4 } };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    array.erase(array.begin());
    {
        std::vector<map::pair<int, int>> expect = { { 33, 3 }, { 44, 4 } };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    array.erase(array.begin());
    {
        std::vector<map::pair<int, int>> expect = { { 44, 4 } };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    array.erase(array.begin());
    {
        std::vector<map::pair<int, int>> expect = {};
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
}

void erase_ending()
{
    map::array<int, int, 4> array;
    array.insert({ 11, 1 });
    array.insert({ 22, 2 });
    array.insert({ 33, 3 });
    array.insert({ 44, 4 });
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 }, { 22, 2 }, { 33, 3 }, { 44, 4 } };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }

    array.erase(std::prev(array.end()));
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 }, { 22, 2 }, { 33, 3 } };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    array.erase(std::prev(array.end()));
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 }, { 22, 2 } };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    array.erase(std::prev(array.end()));
    {
        std::vector<map::pair<int, int>> expect = { { 11, 1 } };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    array.erase(std::prev(array.end()));
    {
        std::vector<map::pair<int, int>> expect = {};
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
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
    map::array<std::string, std::string, 4> array;
    array.insert({ "alpha", "hydrogen" });
    {
        std::vector<map::pair<std::string, std::string>> expect = { { "alpha", "hydrogen" } };
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
    array.clear();
    {
        std::vector<map::pair<std::string, std::string>> expect = {};
        BOOST_TEST_ALL_EQ(array.begin(), array.end(),
                          expect.begin(), expect.end());
    }
}

void run()
{
    string_clear();
}

} // namespace string_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    api_suite::run();
    erase_suite::run();
    string_suite::run();

    return boost::report_errors();
}
