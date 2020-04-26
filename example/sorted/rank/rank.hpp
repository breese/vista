#ifndef VISTA_SORTED_EXAMPLE_RANK_HPP
#define VISTA_SORTED_EXAMPLE_RANK_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vista/sorted/span.hpp>

namespace vista
{
namespace sorted
{
namespace example
{

template <typename T, std::size_t N>
class rank
{
public:
    using value_type = T;
    using size_type = std::size_t;

    constexpr rank() noexcept
        : span(storage)
    {
    }

    // Insert new value
    void push(value_type value) noexcept
    {
        span.push(std::move(value));
    }

    template <typename Ratio>
    value_type value() const noexcept
    {
        const size_type index = Ratio::num * (span.size() - 1) / Ratio::den;
	return span[index];
    }

private:
    T storage[N] = {};
    sorted::span<T, N> span;
};

} // namespace example
} // namespace sorted
} // namespace vista

#endif // VISTA_SORTED_EXAMPLE_RANK_HPP
