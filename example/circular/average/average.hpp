#ifndef VISTA_CIRCULAR_EXAMPLE_AVERAGE_HPP
#define VISTA_CIRCULAR_EXAMPLE_AVERAGE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <type_traits>
#include <vista/circular_array.hpp>

namespace vista
{
namespace circular
{
namespace example
{

template <typename T, std::size_t N>
class average
    : protected circular_array<T, N>
{
    static_assert(N > 0, "N must be greater than zero");

    using window = circular_array<T, N>;

public:
    using value_type = typename window::value_type;
    using size_type = typename window::size_type;

    average() noexcept = default;

    //! @brief Appends data point.

    void push(value_type input) noexcept(std::is_nothrow_move_assignable<value_type>::value)
    {
        // Update the running sum
        if (window::full())
        {
            // Undo the effect of the entry leaving the window
            sum += input - window::front();
        }
        else
        {
            sum += input;
        }
        // Remember the input value for later use
        window::push_back(input);
    }

    using window::empty;
    using window::size;

    //! @brief Returns biased mean.
    //!
    //! @pre window.size() > 0

    value_type mean() const noexcept(std::is_nothrow_move_constructible<value_type>::value)
    {
        assert(!empty());

        return sum / size();
    }

private:
    value_type sum = {};
};

} // namespace example
} // namespace circular
} // namespace vista

#endif // VISTE_CIRCULAR_EXAMPLE_AVERAGE_HPP
