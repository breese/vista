#ifndef VISTA_CONSTEXPR_ARRAY_HPP
#define VISTA_CONSTEXPR_ARRAY_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if __cplusplus >= 201703L

#include <array>

namespace vista
{

template <typename T, std::size_t N>
using constexpr_array = std::array<T, N>;

} // namespace vista

#else

#include <vista/detail/config.hpp>

namespace vista
{

template <typename T, std::size_t N>
class constexpr_array
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = value_type*;
    using const_iterator = const value_type*;

    VISTA_CXX14_CONSTEXPR
    reference operator[](size_type position) noexcept { return storage[position]; }
    constexpr const_reference operator[](size_type position) const noexcept { return storage[position]; }

    VISTA_CXX14_CONSTEXPR
    reference front() noexcept { return storage[0]; }
    constexpr const_reference front() const noexcept { return storage[0]; }

    VISTA_CXX14_CONSTEXPR
    reference back() noexcept { return storage[N - 1]; }
    constexpr const_reference back() const noexcept { return storage[N - 1]; }

    VISTA_CXX14_CONSTEXPR
    pointer data() noexcept { return storage; }
    constexpr const_pointer data() const noexcept { return storage; }

    constexpr size_type size() const noexcept { return N; }
    constexpr size_type max_size() const noexcept { return N; }
    constexpr size_type empty() const noexcept { return false; }

    VISTA_CXX14_CONSTEXPR
    iterator begin() noexcept { return storage; }
    constexpr const_iterator begin() const noexcept { return storage; }
    constexpr const_iterator cbegin() const noexcept { return storage; }

    VISTA_CXX14_CONSTEXPR
    iterator end() noexcept { return storage + N; }
    constexpr const_iterator end() const noexcept { return storage + N; }
    constexpr const_iterator cend() const noexcept { return storage + N; }

private:
    value_type storage[N] {};
};

template <typename T>
class constexpr_array<T, 0>;

} // namespace vista

#endif

#endif // VISTA_CONSTEXPR_ARRAY_HPP
