#ifndef VISTA_ALGORITHM_HPP
#define VISTA_ALGORITHM_HPP

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

namespace vista
{

//! @brief Same as std::push_heap
//!
//! @pre is_heap(first, last - 1)
//! @post is_heap(first, last)

template <typename RandomAccessIterator>
VISTA_CXX14_CONSTEXPR
void push_heap(RandomAccessIterator first, RandomAccessIterator last);

//! @brief Same as std::push_heap
//!
//! @pre is_heap(first, last - 1)
//! @post is_heap(first, last)

template <typename RandomAccessIterator,
          typename Compare>
VISTA_CXX14_CONSTEXPR
void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

template <bool WithConstexpr,
          typename RandomAccessIterator,
          typename Compare>
VISTA_CXX14_CONSTEXPR
void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

//! @brief Same as std::pop_heap
//!
//! @pre is_heap(first, last)
//! @pre is_heap(first, last - 1)

template <typename RandomAccessIterator>
VISTA_CXX14_CONSTEXPR
void pop_heap(RandomAccessIterator first, RandomAccessIterator last);

//! @brief Same as std::pop_heap
//!
//! @pre is_heap(first, last)
//! @pre is_heap(first, last - 1)

template <typename RandomAccessIterator,
          typename Compare>
VISTA_CXX14_CONSTEXPR
void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

template <bool WithConstexpr,
          typename RandomAccessIterator,
          typename Compare>
VISTA_CXX14_CONSTEXPR
void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

} // namespace vista

#include <vista/detail/algorithm.ipp>

#endif // VISTA_ALGORITHM_HPP
