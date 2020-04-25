///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vista/span.hpp>

//-----------------------------------------------------------------------------

namespace data
{

constexpr int increasing[] = { 11, 22, 33, 44 };

} // namespace data

//-----------------------------------------------------------------------------

namespace api_dynamic_suite
{

VISTA_CXX14_CONSTEXPR
void dynamic_ctor_default()
{
    constexpr vista::span<int> span;
    static_assert(span.capacity() == 0, "");
    static_assert(span.size() == 0, "");
    static_assert(span.data() == nullptr, "");
}

VISTA_CXX14_CONSTEXPR
void dynamic_ctor_copy()
{
    constexpr vista::span<const int> span(data::increasing);
    static_assert(span.capacity() == 4, "");
    static_assert(span.size() == 4, "");
    static_assert(span.data() == data::increasing, "");
    constexpr vista::span<const int> clone(span);
    static_assert(clone.capacity() == 4, "");
    static_assert(clone.size() == 4, "");
    static_assert(clone.data() == data::increasing, "");
}

VISTA_CXX14_CONSTEXPR
void dynamic_ctor_array()
{
    constexpr vista::span<const int> span(data::increasing);
    static_assert(span.capacity() == 4, "");
    static_assert(!span.empty(), "");
    static_assert(span.size() == 4, "");
    static_assert(span.data() == data::increasing, "");
}

VISTA_CXX14_CONSTEXPR
void dynamic_data()
{
    constexpr vista::span<const int> span(data::increasing);
    static_assert(span.size() == 4, "");
    static_assert(span.data() == data::increasing, "");
}

VISTA_CXX14_CONSTEXPR
void dynamic_front()
{
    constexpr vista::span<const int> span(data::increasing);
    static_assert(span.size() == 4, "");
    static_assert(span.front() == 11, "");
}

VISTA_CXX14_CONSTEXPR
void dynamic_back()
{
    constexpr vista::span<const int> span(data::increasing);
    static_assert(span.size() == 4, "");
    static_assert(span.back() == 44, "");
}

VISTA_CXX14_CONSTEXPR
void dynamic_operator_index()
{
    constexpr vista::span<const int> span(data::increasing);
    static_assert(span.size() == 4, "");
    static_assert(span[0] == 11, "");
    static_assert(span[1] == 22, "");
    static_assert(span[2] == 33, "");
    static_assert(span[3] == 44, "");
}

VISTA_CXX14_CONSTEXPR
void dynamic_subspan()
{
    constexpr vista::span<const int> span(data::increasing);
    static_assert(span.size() == 4, "");
    static_assert(span.front() == 11, "");
    constexpr auto subspan = span.subspan<2>();
    static_assert(subspan.size() == 2, "");
    static_assert(subspan.front() == 33, "");
}

VISTA_CXX14_CONSTEXPR
void run()
{
    dynamic_ctor_default();
    dynamic_ctor_copy();
    dynamic_ctor_array();
    dynamic_data();
    dynamic_front();
    dynamic_back();
    dynamic_operator_index();
    dynamic_subspan();
}

} // namespace api_dynamic_suite

//-----------------------------------------------------------------------------

namespace api_fixed_suite
{

VISTA_CXX14_CONSTEXPR
void fixed_ctor_default()
{
    constexpr vista::span<int, 0> span;
    static_assert(span.capacity() == 0, "");
    static_assert(span.size() == 0, "");
    static_assert(span.data() == nullptr, "");
}

VISTA_CXX14_CONSTEXPR
void fixed_ctor_copy()
{
    constexpr vista::span<const int, 4> span(data::increasing);
    static_assert(span.capacity() == 4, "");
    static_assert(span.size() == 4, "");
    static_assert(span.data() == data::increasing, "");
    constexpr vista::span<const int, 4> clone(span);
    static_assert(clone.capacity() == 4, "");
    static_assert(clone.size() == 4, "");
    static_assert(clone.data() == data::increasing, "");
}

VISTA_CXX14_CONSTEXPR
void fixed_ctor_array()
{
    constexpr vista::span<const int, 4> span(data::increasing);
    static_assert(span.capacity() == 4, "");
    static_assert(!span.empty(), "");
    static_assert(span.size() == 4, "");
    static_assert(span.data() == data::increasing, "");
}

VISTA_CXX14_CONSTEXPR
void fixed_data()
{
    constexpr vista::span<const int, 4> span(data::increasing);
    static_assert(span.size() == 4, "");
    static_assert(span.data() == data::increasing, "");
}

VISTA_CXX14_CONSTEXPR
void fixed_front()
{
    constexpr vista::span<const int, 4> span(data::increasing);
    static_assert(span.size() == 4, "");
    static_assert(span.front() == 11, "");
}

VISTA_CXX14_CONSTEXPR
void fixed_back()
{
    constexpr vista::span<const int, 4> span(data::increasing);
    static_assert(span.size() == 4, "");
    static_assert(span.back() == 44, "");
}

VISTA_CXX14_CONSTEXPR
void fixed_operator_index()
{
    constexpr vista::span<const int, 4> span(data::increasing);
    static_assert(span.size() == 4, "");
    static_assert(span[0] == 11, "");
    static_assert(span[1] == 22, "");
    static_assert(span[2] == 33, "");
    static_assert(span[3] == 44, "");
}

VISTA_CXX14_CONSTEXPR
void fixed_subspan()
{
    constexpr vista::span<const int, 4> span(data::increasing);
    static_assert(span.size() == 4, "");
    static_assert(span.front() == 11, "");
    constexpr auto subspan = span.subspan<2, 2>();
    static_assert(subspan.size() == 2, "");
    static_assert(subspan.front() == 33, "");
}

VISTA_CXX14_CONSTEXPR
void run()
{
    fixed_ctor_default();
    fixed_ctor_copy();
    fixed_ctor_array();
    fixed_data();
    fixed_front();
    fixed_back();
    fixed_operator_index();
    fixed_subspan();
}

} // namespace api_fixed_suite

//-----------------------------------------------------------------------------

int main()
{
    api_dynamic_suite::run();
    api_fixed_suite::run();

    return 0;
}
