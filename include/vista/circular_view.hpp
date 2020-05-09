#ifndef VISTA_CIRCULAR_VIEW_HPP
#define VISTA_CIRCULAR_VIEW_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <vista/span.hpp>
#include <vista/detail/config.hpp>
#include <vista/detail/type_traits.hpp>

namespace vista
{

//! @brief Circular view.
//!
//! A view that turns contiguous memory into a circular double-ended queue.
//! Inserting new elements will overwrite old elements when the queue is full.
//!
//! The memory is not owned by the view. The owner must ensure that the view is
//! destroyed before the memory is released.
//!
//! Size is the current number of elements in the view.
//!
//! Capacity is the maximum number of elements that can be inserted without
//! overwriting old elements. Capacity cannot be changed.
//!
//! Violation of any precondition results in undefined behavior.

template <typename T, std::size_t Extent = dynamic_extent>
class circular_view
{
    static_assert(Extent == dynamic_extent || Extent < std::numeric_limits<std::size_t>::max() / 2,
                  "Extent is too large");

public:
    using element_type = T;
    using value_type = typename std::remove_cv<element_type>::type;
    using size_type = std::size_t;
    using pointer = typename std::add_pointer<element_type>::type;
    using reference = typename std::add_lvalue_reference<element_type>::type;
    using const_reference = typename std::add_lvalue_reference<typename std::add_const<element_type>::type>::type;

private:
    template <typename, std::size_t>
    friend class circular_view;

    template <typename U>
    struct basic_iterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using element_type = U;
        using value_type = typename std::remove_cv<element_type>::type;
        using difference_type = std::ptrdiff_t;
        using pointer = typename std::add_pointer<element_type>::type;
        using reference = typename std::add_lvalue_reference<element_type>::type;
        using const_reference = typename std::add_lvalue_reference<typename std::add_const<element_type>::type>::type;
        using iterator_type = basic_iterator<U>;

        constexpr basic_iterator() noexcept = default;
        constexpr basic_iterator(const basic_iterator&) noexcept = default;
        constexpr basic_iterator(basic_iterator&&) noexcept = default;
        VISTA_CXX14_CONSTEXPR
        basic_iterator& operator=(const basic_iterator&) noexcept = default;
        VISTA_CXX14_CONSTEXPR
        basic_iterator& operator=(basic_iterator&&) noexcept = default;

        // iterator is convertible to const_iterator
        template <typename ConstU = U,
                  typename std::enable_if<std::is_const<ConstU>::value, int>::type = 0>
        constexpr basic_iterator(const basic_iterator<typename std::remove_const<ConstU>::type>& other) noexcept
            : parent(other.parent),
              current(other.current)
        {}

        VISTA_CXX14_CONSTEXPR
        iterator_type& operator++() noexcept;
        VISTA_CXX14_CONSTEXPR
        iterator_type operator++(int) noexcept;
        VISTA_CXX14_CONSTEXPR
        iterator_type& operator--() noexcept;
        VISTA_CXX14_CONSTEXPR
        iterator_type operator--(int) noexcept;

        VISTA_CXX14_CONSTEXPR
        iterator_type& operator+=(difference_type) noexcept;

        constexpr iterator_type operator+(difference_type) const noexcept;

        friend constexpr iterator_type operator+(difference_type amount,
                                                 const iterator_type& other) noexcept
        {
            return other + amount;
        }

        VISTA_CXX14_CONSTEXPR
        iterator_type& operator-=(difference_type) noexcept;

        constexpr iterator_type operator-(difference_type) const noexcept;

        constexpr difference_type operator-(const iterator_type&) const noexcept;

        VISTA_CXX14_CONSTEXPR
        reference operator[](difference_type) noexcept;

        VISTA_CXX14_CONSTEXPR
        pointer operator->() noexcept;
        VISTA_CXX14_CONSTEXPR
        reference operator*() noexcept;
        constexpr const_reference operator*() const noexcept;

        constexpr bool operator==(const iterator_type&) const noexcept;
        constexpr bool operator!=(const iterator_type&) const noexcept;
        constexpr bool operator<(const iterator_type&) const noexcept;
        constexpr bool operator<=(const iterator_type&) const noexcept;
        constexpr bool operator>(const iterator_type&) const noexcept;
        constexpr bool operator>=(const iterator_type&) const noexcept;

    private:
        friend class circular_view<T, Extent>;

        using view_pointer = typename std::conditional<std::is_const<U>::value,
                                                       typename std::add_pointer<typename std::add_const<circular_view<T, Extent>>::type>::type,
                                                       typename std::add_pointer<circular_view<T, Extent>>::type>::type;

        constexpr basic_iterator(view_pointer parent, const size_type index) noexcept;

    private:
        view_pointer parent;
        size_type current;
    };

public:
    //! @brief Random access iterator.
    //!
    //! Type that models the RandomAccessIterator requirements.

    using iterator = basic_iterator<element_type>;
    using const_iterator = basic_iterator<typename std::add_const<element_type>::type>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    //! @brief Contiguous segment.
    //!
    //! Unspecified type that models the ContiguousRange and SizedRange requirements.

    using segment = span<value_type>;
    using const_segment = span<const value_type>;

    //! @brief Creates empty circular view.
    //!
    //! No elements can be inserted into a zero capacity view. The view must
    //! therefore be recreated before use.
    //!
    //! @post capacity() == 0
    //! @post size() == 0

    constexpr circular_view() noexcept;

    //! @brief Creates circular view by copying.

    constexpr circular_view(const circular_view&) noexcept = default;

    //! @brief Creates circular view by copying.
    //!
    //! Enables copying mutable view to immutable view.
    //!
    //! @pre Extent == N or Extent == dynamic_extent

    template <typename OtherT,
              std::size_t OtherExtent,
              typename std::enable_if<(Extent == OtherExtent || Extent == dynamic_extent) && std::is_convertible<OtherT (*)[], T (*)[]>::value, int>::type = 0>
    explicit constexpr circular_view(const circular_view<OtherT, OtherExtent>& other) noexcept;

    //! @brief Creates circular view by moving.
    //!
    //! State of moved-from view is valid but unspecified.

    constexpr circular_view(circular_view&&) noexcept = default;

    //! @brief Recreates circular view by copying.

    VISTA_CXX14_CONSTEXPR
    circular_view& operator=(const circular_view&) noexcept = default;

    //! @brief Recreates circular view by moving.
    //!
    //! State of moved-from view is valid but unspecified.

    VISTA_CXX14_CONSTEXPR
    circular_view& operator=(circular_view&&) noexcept = default;

    //! @brief Replaces circular view with elements from initializer list.
    //!
    //! @post size() == input.size()

    VISTA_CXX14_CONSTEXPR
    circular_view& operator=(std::initializer_list<value_type> input) noexcept(std::is_nothrow_move_assignable<value_type>::value);

    //! @brief Creates circular view from iterators.
    //!
    //! The view covers the range from @c begin to @c end.
    //!
    //! @pre Extent == std::distance(begin, end) or Extent == dynamic_extent
    //! @post capacity() == std::distance(begin, end)
    //! @post size() == 0

    template <typename ContiguousIterator>
    constexpr circular_view(ContiguousIterator begin,
                            ContiguousIterator end) noexcept;

    //! @brief Creates circular view from iterators.
    //!
    //! The view covers the range from @c begin to @c end.
    //!
    //! The view is initialized as if the pre-existing @c length values from
    //! @c first had already been pushed onto the view.
    //!
    //! @pre length <= std::distance(first, end)
    //! @pre Extent == std::distance(begin, end) or Extent == dynamic_extent
    //! @post capacity() == std::distance(begin, end)
    //! @post size() == length

    template <typename ContiguousIterator>
    constexpr circular_view(ContiguousIterator begin,
                            ContiguousIterator end,
                            ContiguousIterator first,
                            size_type length) noexcept;

    //! @brief Creates circular view from array.
    //!
    //! @post capacity() == N
    //! @post size() == 0

    template <std::size_t N,
              typename std::enable_if<(Extent == N || Extent == dynamic_extent), int>::type = 0>
    explicit constexpr circular_view(value_type (&array)[N]) noexcept;

    //! @brief Checks if view is empty.

    constexpr bool empty() const noexcept;

    //! @brief Checks if view is full.

    constexpr bool full() const noexcept;

    //! @brief Returns the maximum possible number of elements in view.

    constexpr size_type capacity() const noexcept;

    //! @brief Returns the number of elements in view.

    constexpr size_type size() const noexcept;

    //! @brief Returns reference to first element in view.
    //!
    //! @pre !empty()

    VISTA_CXX14_CONSTEXPR
    reference front() noexcept;

    //! @brief Returns reference to first element in view.
    //!
    //! @pre !empty()

    constexpr const_reference front() const noexcept;

    //! @brief Returns reference to last element in view.
    //!
    //! @pre !empty()

    VISTA_CXX14_CONSTEXPR
    reference back() noexcept;

    //! @brief Returns reference to last element in view.
    //!
    //! @pre !empty()

    constexpr const_reference back() const noexcept;

    //! @brief Returns reference to element at position.
    //!
    //! @pre size() > position

    VISTA_CXX14_CONSTEXPR
    reference operator[](size_type position) noexcept;

    //! @brief Returns reference to element at position.
    //!
    //! @pre size() > position

    constexpr const_reference operator[](size_type position) const noexcept;

    //! @brief Clears the view.
    //!
    //! The content of the underlying storage is not modified.
    //!
    //! @post size() == 0

    VISTA_CXX14_CONSTEXPR
    void clear() noexcept;

    //! @brief Replaces circular view with elements from range.
    //!
    //! @post size() == std::min(std::distance(first, last), capacity())

    template <typename InputIterator>
    VISTA_CXX14_CONSTEXPR
    void assign(InputIterator first, InputIterator last) noexcept(std::is_nothrow_copy_assignable<value_type>::value);

    //! @brief Replaces circular view with elements from intializer list.
    //!
    //! @post size() == std::min(input.size(), capacity())

    VISTA_CXX14_CONSTEXPR
    void assign(std::initializer_list<value_type> input) noexcept(std::is_nothrow_move_assignable<value_type>::value);

    //! @brief Inserts element at beginning of view.
    //!
    //! If view is full, then the element at the end of the view is silently erased
    //! to make room for the @c input value.
    //!
    //! @pre capacity() > 0

    VISTA_CXX14_CONSTEXPR
    void push_front(value_type input) noexcept(std::is_nothrow_move_assignable<value_type>::value);

    //! @brief Inserts element at beginning of view.
    //!
    //! @pre capacity() > 0

    template <typename InputIterator>
    VISTA_CXX14_CONSTEXPR
    void push_front(InputIterator first, InputIterator last) noexcept(std::is_nothrow_copy_assignable<value_type>::value);

    //! @brief Inserts element at end of view.
    //!
    //! If view is full, then the element at the end of the view is silently erased
    //! to make room for the @c input value.
    //!
    //! @pre capacity() > 0

    VISTA_CXX14_CONSTEXPR
    void push_back(value_type input) noexcept(std::is_nothrow_move_assignable<value_type>::value);

    //! @brief Inserts elements at end of view.
    //!
    //! @pre capacity() > 0

    template <typename InputIterator>
    VISTA_CXX14_CONSTEXPR
    void push_back(InputIterator first, InputIterator last) noexcept(std::is_nothrow_copy_assignable<value_type>::value);

    //! @brief Removes and returns element from beginning of view.
    //!
    //! @pre !empty()

    VISTA_CXX14_CONSTEXPR
    value_type pop_front() noexcept(std::is_nothrow_move_constructible<value_type>::value);

    //! @brief Removes and returns element from end of view.
    //!
    //! @pre !empty()

    VISTA_CXX14_CONSTEXPR
    value_type pop_back() noexcept(std::is_nothrow_move_constructible<value_type>::value);

    //! @brief Inserts unspecified elements at the beginning of the view.
    //!
    //! Make room for @c count elements at the front. No elements are constructed
    //! in the underlying storage. The elements are in an unspecified but valid
    //! state that may be default-initialized, previously properly initialized,
    //! or in a moved-from state. The elements must be overwritten with properly
    //! initialized values.
    //!
    //! If the view is full, then the elements at the front are taken from the
    //! back.
    //!
    //! @pre capacity() > 0
    //! @pre count <= capacity()

    VISTA_CXX14_CONSTEXPR
    void expand_front(size_type count = 1U) noexcept;

    //! @brief Inserts unspecified elements at the end of the view.
    //!
    //! @pre capacity() > 0
    //! @pre count <= capacity()
    //!
    //! @sa increment_front

    VISTA_CXX14_CONSTEXPR
    void expand_back(size_type count = 1U) noexcept;

    //! @brief Removes elements from beginning of view.
    //!
    //! The removed elements in the underlying storage are not destroyed.
    //!
    //! By default only one element is erased.
    //!
    //! @pre 0 < count <= size()

    VISTA_CXX14_CONSTEXPR
    void remove_front(size_type count = 1U) noexcept;

    //! @brief Removes elements from end of view.
    //!
    //! The removed elements in the underlying storage are not destroyed.
    //!
    //! By default only one element is erased.
    //!
    //! @pre 0 < count <= size()

    VISTA_CXX14_CONSTEXPR
    void remove_back(size_type count = 1U) noexcept;

    //! @brief Rotates elements so view starts at beginning of storage.
    //!
    //! For instance, a view consisting of the sequence A, B, C, may be stored
    //! in memory as:
    //!
    //!   +---+---+---+---+---+
    //!   | C |   |   | A | B |
    //!   +---+---+---+---+---+
    //!
    //! After rotation the elements are stored in memory as:
    //!
    //!   +---+---+---+---+---+
    //!   | A | B | C |   |   |
    //!   +---+---+---+---+---+
    //!
    //! Rotation invalidates pointers and references.
    //! Rotation does not invalidate iterators.
    //!
    //! Linear time complexity.

    VISTA_CXX14_CONSTEXPR
    void rotate_front() noexcept(vista::detail::is_nothrow_swappable<value_type>::value);

    //! @brief Returns iterator to the beginning of the view.

    VISTA_CXX14_CONSTEXPR
    iterator begin() noexcept;

    //! @brief Returns iterator to the beginning of the view.

    constexpr const_iterator begin() const noexcept;

    //! @brief Returns iterator to the ending of the view.

    VISTA_CXX14_CONSTEXPR
    iterator end() noexcept;

    //! @brief Returns iterator to the ending of the view.

    constexpr const_iterator end() const noexcept;

    //! @brief Returns iterator to the beginning of the view.

    constexpr const_iterator cbegin() const noexcept;

    //! @brief Returns iterator to the ending of the view.

    constexpr const_iterator cend() const noexcept;

    //! @brief Returns reverse iterator to the beginning of the view.

    VISTA_CXX14_CONSTEXPR
    reverse_iterator rbegin() noexcept;

    //! @brief Returns reverse iterator to the beginning of the view.

    constexpr const_reverse_iterator rbegin() const noexcept;

    //! @brief Returns reverse iterator to the end of the view.

    VISTA_CXX14_CONSTEXPR
    reverse_iterator rend() noexcept;

    //! @brief Returns reverse iterator to the end of the view.

    constexpr const_reverse_iterator rend() const noexcept;

    //! @brief Returns reverse iterator to the beginning of the view.

    constexpr const_reverse_iterator crbegin() const noexcept;

    //! @brief Returns reverse iterator to the end of the view.

    constexpr const_reverse_iterator crend() const noexcept;

    //! @brief Returns first contiguous segment of the view.
    //!
    //! The first segment covers the longest contiguous sequence of used
    //! elements in the underlying storage from the beginning of the view.
    //!
    //! @pre capacity() > 0
    //!
    //! @post std::distance(first_segment().begin(), first_segment().end()) > 0 unless empty()

    VISTA_CXX14_CONSTEXPR
    segment first_segment() noexcept;

    //! @brief Returns first contiguous segment of the view.
    //!
    //! The first segment covers the longest contiguous sequence of used
    //! elements in the underlying storage from the beginning of the view.
    //!
    //! @pre capacity() > 0
    //!
    //! @post std::distance(first_segment().begin(), first_segment().end()) > 0 unless empty()

    constexpr const_segment first_segment() const noexcept;

    //! @brief Returns last contiguous segment of the view.
    //!
    //! The last segment covers the remaining used elements not covered by the
    //! first segment.
    //!
    //! @pre capacity() > 0

    VISTA_CXX14_CONSTEXPR
    segment last_segment() noexcept;

    //! @brief Returns last contiguous segment of the view.
    //!
    //! The last segment covers the remaining used elements not covered by the
    //! first segment.
    //!
    //! @pre capacity() > 0

    constexpr const_segment last_segment() const noexcept;

    //! @brief Returns first contiguous unused segment of the view.
    //!
    //! The unused first segment covers the longest contiguous sequence of
    //! unused elements in the underlying storage from the end of the view.
    //!
    //! @pre capacity() > 0
    //! @post std::distance(unused_back_segment().begin(), unused_back_segment().end()) > 0 unless full()

    VISTA_CXX14_CONSTEXPR
    segment first_unused_segment() noexcept;
    constexpr const_segment first_unused_segment() const noexcept;

    //! @brief Returns last contiguous unused segment of the view.
    //!
    //! The unused last segment covers the remaining unused elements in the
    //! underlying storage not covered by the unused first segment.
    //!
    //! @pre capacity() > 0

    VISTA_CXX14_CONSTEXPR
    segment last_unused_segment() noexcept;
    constexpr const_segment last_unused_segment() const noexcept;

protected:
    //! @brief Creates circular view by copying.
    //!
    //! The pointer parameter overrides the pointer of the input view.

    constexpr circular_view(const circular_view&, pointer) noexcept;

    //! @brief Recreates circular view by copying.
    //!
    //! The pointer parameter overrides the pointer of the input view.

    VISTA_CXX14_CONSTEXPR
    void assign(const circular_view&, pointer) noexcept;

private:
    constexpr size_type index(size_type) const noexcept;
    constexpr size_type vindex(size_type) const noexcept;

    constexpr size_type front_index() const noexcept;
    constexpr size_type back_index() const noexcept;

    VISTA_CXX14_CONSTEXPR
    reference at(size_type) noexcept;
    constexpr const_reference at(size_type) const noexcept;

    constexpr bool wraparound() const noexcept;
    constexpr bool unused_wraparound() const noexcept;

    VISTA_CXX14_CONSTEXPR
    void rotate_range(size_type lower_length, size_type upper_length) noexcept(vista::detail::is_nothrow_swappable<value_type>::value);

    VISTA_CXX14_CONSTEXPR
    void swap_range(size_type lhs, size_type rhs, size_type length) noexcept(vista::detail::is_nothrow_swappable<value_type>::value);

private:
    template <typename T1, std::size_t E1>
    struct member_storage
    {
        constexpr member_storage() noexcept;
        constexpr member_storage(const member_storage&) noexcept = default;
        constexpr member_storage(member_storage&&) noexcept = default;
        VISTA_CXX14_CONSTEXPR
        member_storage& operator=(const member_storage&) noexcept = default;
        VISTA_CXX14_CONSTEXPR
        member_storage& operator=(member_storage&&) noexcept = default;

        constexpr member_storage(pointer data, size_type size, size_type next) noexcept;

        constexpr member_storage(const member_storage&, pointer data) noexcept;

        template <typename OtherT, std::size_t OtherExtent>
        explicit constexpr member_storage(const circular_view<OtherT, OtherExtent>&) noexcept;

        template <typename ContiguousIterator>
        VISTA_CXX14_CONSTEXPR
        member_storage(ContiguousIterator, ContiguousIterator) noexcept;

        template <typename ContiguousIterator>
        VISTA_CXX14_CONSTEXPR
        member_storage(ContiguousIterator, ContiguousIterator, ContiguousIterator, size_type) noexcept;

        template <std::size_t N>
        explicit constexpr member_storage(value_type (&array)[N]) noexcept;

        constexpr size_type capacity() const noexcept;

        VISTA_CXX14_CONSTEXPR
        void capacity(size_type) noexcept;

        VISTA_CXX14_CONSTEXPR
        void assign(const member_storage&, pointer) noexcept;

        constexpr size_type modulo(size_type, size_type) const noexcept;

        pointer data;
        size_type size;
        size_type next;
    };

    template <typename T1>
    struct member_storage<T1, dynamic_extent>
    {
        constexpr member_storage() noexcept;
        constexpr member_storage(const member_storage&) noexcept = default;
        constexpr member_storage(member_storage&&) noexcept = default;
        VISTA_CXX14_CONSTEXPR
        member_storage& operator=(const member_storage&) noexcept = default;
        VISTA_CXX14_CONSTEXPR
        member_storage& operator=(member_storage&&) noexcept = default;

        constexpr member_storage(pointer data, size_type capacity, size_type size, size_type next) noexcept;

        constexpr member_storage(const member_storage&, pointer data) noexcept;

        template <typename OtherT, std::size_t OtherExtent>
        explicit constexpr member_storage(const circular_view<OtherT, OtherExtent>&) noexcept;

        template <typename ContiguousIterator>
        constexpr member_storage(ContiguousIterator, ContiguousIterator) noexcept;

        template <typename ContiguousIterator>
        constexpr member_storage(ContiguousIterator, ContiguousIterator, ContiguousIterator, size_type) noexcept;

        template <std::size_t N>
        explicit constexpr member_storage(value_type (&array)[N]) noexcept;

        constexpr size_type capacity() const noexcept;

        VISTA_CXX14_CONSTEXPR
        void capacity(size_type input) noexcept;

        VISTA_CXX14_CONSTEXPR
        void assign(const member_storage&, pointer) noexcept;

        constexpr size_type modulo(size_type, size_type) const noexcept;

        pointer data;
        size_type cap;
        size_type size;
        size_type next;
    };

    struct member_storage<T, Extent> member;
};

} // namespace vista

#include <vista/detail/circular_view.ipp>

#endif // VISTA_CIRCULAR_VIEW_HPP
