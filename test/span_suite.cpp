///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <array>
#include <boost/detail/lightweight_test.hpp>
#include <vista/span.hpp>

//-----------------------------------------------------------------------------

namespace api_dynamic_suite
{

void dynamic_ctor_default()
{
    static_assert(std::is_default_constructible<vista::span<int>>::value, "span<int> must be default-constructible");
    static_assert(std::is_nothrow_default_constructible<vista::span<int>>::value, "span<int> must be nothrow default-constructible");

    vista::span<int> span;
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 0);
}

void dynamic_ctor_copy()
{
    static_assert(std::is_copy_constructible<vista::span<int>>::value, "span<int> must be copy-constructible");
    static_assert(std::is_nothrow_copy_constructible<vista::span<int>>::value, "span<int> must be nothrow copy-constructible");

    vista::span<int> span;
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 0);
    vista::span<int> clone(span);
    BOOST_TEST_EQ(clone.size(), 0);
    BOOST_TEST_EQ(clone.capacity(), 0);
}

void dynamic_ctor_copy_convertible()
{
    vista::span<int> span;
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 0);
    vista::span<const int> clone(span);
    BOOST_TEST_EQ(clone.size(), 0);
    BOOST_TEST_EQ(clone.capacity(), 0);
}

void dynamic_ctor_copy_assign()
{
    static_assert(std::is_copy_assignable<vista::span<int>>::value, "span<int> must be copy-assignable");
    static_assert(std::is_nothrow_copy_assignable<vista::span<int>>::value, "span<int> must be nothrow copy-assignable");

    vista::span<int> span;
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 0);
    vista::span<int> clone;
    BOOST_TEST_EQ(clone.size(), 0);
    BOOST_TEST_EQ(clone.capacity(), 0);
    clone = span;
    BOOST_TEST_EQ(clone.size(), 0);
    BOOST_TEST_EQ(clone.capacity(), 0);
}

void dynamic_ctor_move()
{
    static_assert(std::is_move_constructible<vista::span<int>>::value, "span<int> must be move-constructible");
    static_assert(std::is_nothrow_move_constructible<vista::span<int>>::value, "span<int> must be nothrow move-constructible");

    vista::span<int> span;
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 0);
    vista::span<int> clone(std::move(span));
    BOOST_TEST_EQ(clone.size(), 0);
    BOOST_TEST_EQ(clone.capacity(), 0);
}

void dynamic_ctor_pointers()
{
    int array[4] = {};
    vista::span<int> span(&array[0], &array[4]);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void dynamic_ctor_pointer_size()
{
    int array[4] = {};
    vista::span<int> span(&array[0], 4);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void dynamic_ctor_array()
{
    int array[4] = {};
    vista::span<int> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void dynamic_ctor_const_array()
{
    int array[4] = {};
    vista::span<const int> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void dynamic_empty()
{
    {
        vista::span<int> span;
        BOOST_TEST_EQ(span.empty(), true);
    }
    {
        int array[4] = { 11, 22, 33, 44 };
        vista::span<int> span(array);
        BOOST_TEST_EQ(span.empty(), false);
    }
}

void dynamic_size()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int> span(array);
    BOOST_TEST_EQ(span.size(), 4);
}

void dynamic_capacity()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int> span(array);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void dynamic_data()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int> span(array);
    BOOST_TEST_EQ(span.data(), array);
}

void dynamic_data_const()
{
    int array[4] = { 11, 22, 33, 44 };
    const vista::span<int> span(array);
    BOOST_TEST_EQ(span.data(), array);
}

void dynamic_front()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int> span(array);
    BOOST_TEST_EQ(span.front(), 11);
}

void dynamic_front_const()
{
    int array[4] = { 11, 22, 33, 44 };
    const vista::span<int> span(array);
    BOOST_TEST_EQ(span.front(), 11);
}

void dynamic_back()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int> span(array);
    BOOST_TEST_EQ(span.back(), 44);
}

void dynamic_back_const()
{
    int array[4] = { 11, 22, 33, 44 };
    const vista::span<int> span(array);
    BOOST_TEST_EQ(span.back(), 44);
}

void dynamic_operator_index()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int> span(array);
    BOOST_TEST_EQ(span[0], 11);
    BOOST_TEST_EQ(span[1], 22);
    BOOST_TEST_EQ(span[2], 33);
    BOOST_TEST_EQ(span[3], 44);
}

void dynamic_operator_index_const()
{
    int array[4] = { 11, 22, 33, 44 };
    const vista::span<int> span(array);
    BOOST_TEST_EQ(span[0], 11);
    BOOST_TEST_EQ(span[1], 22);
    BOOST_TEST_EQ(span[2], 33);
    BOOST_TEST_EQ(span[3], 44);
}

void dynamic_subspan()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.front(), 11);
    auto subspan = span.subspan<2>();
    BOOST_TEST_EQ(subspan.capacity(), 2);
    BOOST_TEST_EQ(subspan.size(), 2);
    BOOST_TEST_EQ(subspan.front(), 33);
}

void dynamic_subspan_count()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.front(), 11);
    auto subspan = span.subspan<2, 2>();
    BOOST_TEST_EQ(subspan.capacity(), 2);
    BOOST_TEST_EQ(subspan.size(), 2);
    BOOST_TEST_EQ(subspan.front(), 33);
}

void dynamic_remove_front()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.front(), 11);
    span.remove_front();
    BOOST_TEST_EQ(span.size(), 3);
    BOOST_TEST_EQ(span.front(), 22);
}

void dynamic_remove_front_n()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.front(), 11);
    span.remove_front(2);
    BOOST_TEST_EQ(span.size(), 2);
    BOOST_TEST_EQ(span.front(), 33);
}

void dynamic_remove_back()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.back(), 44);
    span.remove_back();
    BOOST_TEST_EQ(span.size(), 3);
    BOOST_TEST_EQ(span.back(), 33);
}

void dynamic_remove_back_n()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.back(), 44);
    span.remove_back(2);
    BOOST_TEST_EQ(span.size(), 2);
    BOOST_TEST_EQ(span.back(), 22);
}

void dynamic_begin()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int> span(array);
    BOOST_TEST_EQ(*span.begin(), 11);
}

void dynamic_begin_const()
{
    int array[4] = { 11, 22, 33, 44 };
    const vista::span<int> span(array);
    BOOST_TEST_EQ(*span.begin(), 11);
}

void dynamic_cbegin()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int> span(array);
    BOOST_TEST_EQ(*span.cbegin(), 11);
}

void dynamic_end()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int> span(array);
    BOOST_TEST_EQ(span.end()[-1], 44);
}

void dynamic_end_const()
{
    int array[4] = { 11, 22, 33, 44 };
    const vista::span<int> span(array);
    BOOST_TEST_EQ(span.end()[-1], 44);
}

void dynamic_cend()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int> span(array);
    BOOST_TEST_EQ(span.cend()[-1], 44);
}

void run()
{
    dynamic_ctor_default();
    dynamic_ctor_copy();
    dynamic_ctor_copy_convertible();
    dynamic_ctor_copy_assign();
    dynamic_ctor_move();
    dynamic_ctor_pointers();
    dynamic_ctor_pointer_size();
    dynamic_ctor_array();
    dynamic_ctor_const_array();
    dynamic_empty();
    dynamic_size();
    dynamic_capacity();
    dynamic_data();
    dynamic_data_const();
    dynamic_front();
    dynamic_front_const();
    dynamic_back();
    dynamic_back_const();
    dynamic_operator_index();
    dynamic_operator_index_const();
    dynamic_subspan();
    dynamic_subspan_count();
    dynamic_remove_front();
    dynamic_remove_front_n();
    dynamic_remove_back();
    dynamic_remove_back_n();
    dynamic_begin();
    dynamic_begin_const();
    dynamic_cbegin();
    dynamic_end();
    dynamic_end_const();
    dynamic_cend();
}

} // namespace api_dynamic_suite

//-----------------------------------------------------------------------------

namespace api_fixed_suite
{

void fixed_ctor_default()
{
    static_assert(std::is_default_constructible<vista::span<int, 0>>::value, "span<int, 0> must be default-constructible");
    static_assert(std::is_nothrow_default_constructible<vista::span<int, 0>>::value, "span<int, 0> must be nothrow default-constructible");
    static_assert(!std::is_default_constructible<vista::span<int, 4>>::value, "span<int, N> must not be default-constructible");

    vista::span<int, 0> span;
    BOOST_TEST_EQ(span.size(), 0);
    BOOST_TEST_EQ(span.capacity(), 0);
}

void fixed_ctor_copy()
{
    static_assert(std::is_copy_constructible<vista::span<int, 4>>::value, "span<int, N> must be copy-constructible");
    static_assert(std::is_nothrow_copy_constructible<vista::span<int, 4>>::value, "span<int, N> must be nothrow copy-constructible");

    int array[4] = {};
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.capacity(), 4);
    vista::span<int, 4> clone(span);
    BOOST_TEST_EQ(clone.size(), 4);
    BOOST_TEST_EQ(clone.capacity(), 4);
}

void fixed_ctor_copy_convertible()
{
    int array[4] = {};
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.capacity(), 4);
    vista::span<const int, 4> clone(span);
    BOOST_TEST_EQ(clone.size(), 4);
    BOOST_TEST_EQ(clone.capacity(), 4);
}

void fixed_ctor_copy_assign()
{
    static_assert(std::is_copy_assignable<vista::span<int, 4>>::value, "span<int, N> must be copy-assignable");
    static_assert(std::is_nothrow_copy_assignable<vista::span<int, 4>>::value, "span<int, N> must be nothrow copy-assignable");

    int array[4] = {};
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.capacity(), 4);
    vista::span<int, 4> clone(array);
    BOOST_TEST_EQ(clone.size(), 4);
    BOOST_TEST_EQ(clone.capacity(), 4);
    clone = span;
    BOOST_TEST_EQ(clone.size(), 4);
    BOOST_TEST_EQ(clone.capacity(), 4);
}

void fixed_ctor_move()
{
    static_assert(std::is_move_constructible<vista::span<int, 4>>::value, "span<int, N> must be move-constructible");
    static_assert(std::is_nothrow_move_constructible<vista::span<int, 4>>::value, "span<int, N> must be nothrow move-constructible");

    int array[4] = {};
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.capacity(), 4);
    vista::span<int, 4> clone(std::move(span));
    BOOST_TEST_EQ(clone.size(), 4);
    BOOST_TEST_EQ(clone.capacity(), 4);
}

void fixed_ctor_pointers()
{
    int array[4] = {};
    vista::span<int, 4> span(&array[0], &array[4]);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void fixed_ctor_pointer_size()
{
    int array[4] = {};
    vista::span<int, 4> span(&array[0], 4);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void fixed_ctor_array()
{
    int array[4] = {};
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void fixed_ctor_const_array()
{
    int array[4] = {};
    vista::span<const int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void fixed_empty()
{
    {
        vista::span<int, 0> span;
        BOOST_TEST_EQ(span.empty(), true);
    }
    {
        int array[4] = { 11, 22, 33, 44 };
        vista::span<int, 4> span(array);
        BOOST_TEST_EQ(span.empty(), false);
    }
}

void fixed_size()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 4);
}

void fixed_capacity()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.capacity(), 4);
}

void fixed_data()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.data(), array);
}

void fixed_data_const()
{
    int array[4] = { 11, 22, 33, 44 };
    const vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.data(), array);
}

void fixed_front()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.front(), 11);
}

void fixed_front_const()
{
    int array[4] = { 11, 22, 33, 44 };
    const vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.front(), 11);
}

void fixed_back()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.back(), 44);
}

void fixed_back_const()
{
    int array[4] = { 11, 22, 33, 44 };
    const vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.back(), 44);
}

void fixed_operator_index()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span[0], 11);
    BOOST_TEST_EQ(span[1], 22);
    BOOST_TEST_EQ(span[2], 33);
    BOOST_TEST_EQ(span[3], 44);
}

void fixed_operator_index_const()
{
    int array[4] = { 11, 22, 33, 44 };
    const vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span[0], 11);
    BOOST_TEST_EQ(span[1], 22);
    BOOST_TEST_EQ(span[2], 33);
    BOOST_TEST_EQ(span[3], 44);
}

void fixed_subspan()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.front(), 11);
    auto subspan = span.subspan<2>();
    BOOST_TEST_EQ(subspan.capacity(), 2);
    BOOST_TEST_EQ(subspan.size(), 2);
    BOOST_TEST_EQ(subspan.front(), 33);
}

void fixed_subspan_count()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.front(), 11);
    auto subspan = span.subspan<2, 2>();
    BOOST_TEST_EQ(subspan.capacity(), 2);
    BOOST_TEST_EQ(subspan.size(), 2);
    BOOST_TEST_EQ(subspan.front(), 33);
}

void fixed_remove_front()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.front(), 11);
    span.remove_front();
    BOOST_TEST_EQ(span.size(), 3);
    BOOST_TEST_EQ(span.front(), 22);
}

void fixed_remove_front_n()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.front(), 11);
    span.remove_front(2);
    BOOST_TEST_EQ(span.size(), 2);
    BOOST_TEST_EQ(span.front(), 33);
}

void fixed_remove_back()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.back(), 44);
    span.remove_back();
    BOOST_TEST_EQ(span.size(), 3);
    BOOST_TEST_EQ(span.back(), 33);
}

void fixed_remove_back_n()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.size(), 4);
    BOOST_TEST_EQ(span.back(), 44);
    span.remove_back(2);
    BOOST_TEST_EQ(span.size(), 2);
    BOOST_TEST_EQ(span.back(), 22);
}

void fixed_begin()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(*span.begin(), 11);
}

void fixed_begin_const()
{
    int array[4] = { 11, 22, 33, 44 };
    const vista::span<int, 4> span(array);
    BOOST_TEST_EQ(*span.begin(), 11);
}

void fixed_cbegin()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(*span.cbegin(), 11);
}

void fixed_end()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.end()[-1], 44);
}

void fixed_end_const()
{
    int array[4] = { 11, 22, 33, 44 };
    const vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.end()[-1], 44);
}

void fixed_cend()
{
    int array[4] = { 11, 22, 33, 44 };
    vista::span<int, 4> span(array);
    BOOST_TEST_EQ(span.cend()[-1], 44);
}

void run()
{
    fixed_ctor_default();
    fixed_ctor_copy();
    fixed_ctor_copy_convertible();
    fixed_ctor_copy_assign();
    fixed_ctor_move();
    fixed_ctor_pointers();
    fixed_ctor_pointer_size();
    fixed_ctor_array();
    fixed_ctor_const_array();
    fixed_empty();
    fixed_size();
    fixed_capacity();
    fixed_data();
    fixed_data_const();
    fixed_front();
    fixed_front_const();
    fixed_back();
    fixed_back_const();
    fixed_operator_index();
    fixed_operator_index_const();
    fixed_subspan();
    fixed_subspan_count();
    fixed_remove_front();
    fixed_remove_front_n();
    fixed_remove_back();
    fixed_remove_back_n();
    fixed_begin();
    fixed_begin_const();
    fixed_cbegin();
    fixed_end();
    fixed_end_const();
    fixed_cend();
}

} // namespace api_fixed_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    api_dynamic_suite::run();
    api_fixed_suite::run();
 
    return boost::report_errors();
}
