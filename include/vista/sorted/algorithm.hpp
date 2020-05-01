#ifndef VISTA_SORTED_ALGORITHM_HPP
#define VISTA_SORTED_ALGORITHM_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vista/detail/config.hpp>
#include <vista/detail/type_traits.hpp>

namespace vista
{
namespace sorted
{

//! @brief Returns position where element is or would have been.
//!
//! Optimized version for sorted random-access range.
//!
//! Logarithmic time complexity.
//!
//! @pre is_sorted(first, last)

template <typename RandomAccessIterator,
          typename T>
VISTA_CXX14_CONSTEXPR
RandomAccessIterator lower_bound(RandomAccessIterator first,
                                 RandomAccessIterator last,
                                 const T& needle) noexcept;

//! @brief Returns position where element is or would have been.
//!
//! Optimized version for sorted random-access range.
//!
//! Logarithmic time complexity.
//!
//! @pre is_sorted(first, last)

template <typename RandomAccessIterator,
          typename T,
          typename Compare>
VISTA_CXX14_CONSTEXPR
RandomAccessIterator lower_bound(RandomAccessIterator first,
                                 RandomAccessIterator last,
                                 const T& needle,
                                 Compare compare) noexcept;

//! @brief Inserts trailing element into sorted range.
//!
//! Assumes that all elements in the range are sorted except for the trailing
//! element at position last - 1.
//!
//! Shuffles elements such that all elements in the range are sorted.
//!
//! Linear time complexity.
//!
//! @pre is_sorted(first, last - 1)
//! @post is_sorted(first, last)

template <typename RandomAccessIterator>
VISTA_CXX14_CONSTEXPR
RandomAccessIterator push(RandomAccessIterator first,
                          RandomAccessIterator last) noexcept(detail::is_nothrow_swappable<decltype(*first)>::value);

//! @brief Inserts trailing element into sorted range.
//!
//! Assumes that all elements in the range are sorted except for the trailing
//! element at position last - 1.
//!
//! Shuffles elements such that all elements in the range are sorted.
//!
//! Linear time complexity.
//!
//! @pre is_sorted(first, last - 1)
//! @posst is_sorted(first, last)

template <typename RandomAccessIterator,
          typename Compare = std::less<decltype(*std::declval<RandomAccessIterator>())>>
VISTA_CXX14_CONSTEXPR
RandomAccessIterator push(RandomAccessIterator first,
                          RandomAccessIterator last,
                          Compare compare) noexcept(detail::is_nothrow_swappable<decltype(*first)>::value);

//! @brief Removes first element from sorted range.
//!
//! Assumes that all elements in the range are sorted.
//!
//! Shuffles elements such that the first element is in trailing position and
//! the remaining elements are sorted.
//!
//! Linear time complexity.
//!
//! @pre is_sorted(first, last)
//! @poss is_sorted(first, last - 1)

template <typename RandomAccessIterator>
VISTA_CXX14_CONSTEXPR
RandomAccessIterator pop(RandomAccessIterator first,
                         RandomAccessIterator last) noexcept(detail::is_nothrow_swappable<decltype(*first)>::value);

} // namespace sorted
} // namespace vista

#include <vista/sorted/detail/algorithm.ipp>

#endif // VISTA_SORTED_ALGORITHM_HPP
