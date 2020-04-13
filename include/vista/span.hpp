#ifndef VISTA_SPAN_HPP
#define VISTA_SPAN_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <type_traits>
#include <vista/detail/config.hpp>

namespace vista
{

template <typename T, std::size_t Extent = dynamic_extent>
class span
{
public:
    using element_type = T;
    using value_type = typename std::remove_cv<element_type>::type;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = typename std::add_pointer<element_type>::type;
    using const_pointer = typename std::add_pointer<typename std::add_const<element_type>::type>::type;
    using reference = typename std::add_lvalue_reference<element_type>::type;
    using const_reference = typename std::add_lvalue_reference<typename std::add_const<element_type>::type>::type;
    using iterator = pointer;
    using const_iterator = const_pointer;

    //! @brief Creates empty span.
    //!
    //! @pre Extent == 0 or Extent == dynamic_extent
    //!
    //! @post data() == nullptr
    //! @post size() == 0

    template <bool Constraint = (Extent == dynamic_extent || Extent == 0),
              typename std::enable_if<Constraint, int>::type = 0>
    constexpr span() noexcept;

    //! @brief Creates span by copying.
    //!
    //! @post data() == other.data()
    //! @post size() == other.size()

    constexpr span(const span& other) = default;

    //! @brief Creates span by copying.
    //!
    //! Enables copying mutable span to immutable span.
    //!
    //! @pre Extent == OtherExtent or Extent == dynamic_extent
    //!
    //! @post data() == other.data()
    //! @post size() == other.size()

    template <typename OtherT,
              std::size_t OtherExtent,
              typename std::enable_if<(Extent == OtherExtent || Extent == dynamic_extent) && std::is_convertible<OtherT (*)[], T (*)[]>::value, int>::type = 0>
    explicit constexpr span(const span<OtherT, OtherExtent>& other) noexcept;

    //! @brief Creates span by moving
    //!
    //! State of moved-from span is valid but unspecified.

    constexpr span(span&&) = default;

    //! @brief Creates span from pointer and size.
    //!
    //! The span covers the range from @c begin and @c size elements forwards.

    constexpr span(pointer data, size_type size) noexcept;

    //! @brief Creates span from pointers.
    //!
    //! The span covers the range from @c begin to @c end.

    constexpr span(pointer first, pointer last) noexcept;

    //! @brief Creates span from array.
    //!
    //! @pre Extent == M or Extent == dynamic_extent

    template <std::size_t M,
              typename std::enable_if<(Extent == M || Extent == dynamic_extent), int>::type = 0>
    explicit constexpr span(element_type (&array)[M]) noexcept;

    //! @brief Checks if span is empty.

    constexpr bool empty() const noexcept;

    //! @brief Returns the number of elements in span.

    constexpr size_type size() const noexcept;

    //! @brief Returns the maximum possible number of elements in span.

    constexpr size_type capacity() const noexcept;

    //! @brief Returns pointer to beginning of span.

    VISTA_CXX14_CONSTEXPR
    pointer data() noexcept;

    //! @brief Returns pointer to beginning of span.

    constexpr const_pointer data() const noexcept;

    //! @brief Returns reference to first element in span.
    //!
    //! @pre size() > 0

    VISTA_CXX14_CONSTEXPR
    reference front() noexcept;

    //! @brief Returns reference to first element in span.
    //!
    //! @pre size() > 0

    constexpr const_reference front() const noexcept;

    //! @brief Returns reference to last element in span.
    //!
    //! @pre size() > 0

    VISTA_CXX14_CONSTEXPR
    reference back() noexcept;

    //! @brief Returns reference to last element in span.
    //!
    //! @pre size() > 0

    constexpr const_reference back() const noexcept;

    //! @brief Returns reference to element at position.
    //!
    //! @pre size() > position

    VISTA_CXX14_CONSTEXPR
    reference operator[](difference_type position) noexcept;

    //! @brief Returns reference to element at position.
    //!
    //! @pre size() > position

    constexpr const_reference operator[](difference_type position) const noexcept;

    //! @brief Removes elements from beginning of span.
    //!
    //! The span is modified, but the elements in the underlying storage
    //! are not destroyed.
    //!
    //! By default only one element is removed.
    //!
    //! @pre 0 < count <= size()

    VISTA_CXX14_CONSTEXPR
    void remove_front(size_type count = 1) noexcept;

    //! @brief Removes elements from end of span.
    //!
    //! The span is modified, but the elements in the underlying storage
    //! are not destroyed.
    //!
    //! By default only one element is removed.
    //!
    //! @pre 0 < count <= size()

    VISTA_CXX14_CONSTEXPR
    void remove_back(size_type count = 1) noexcept;

    //! @brief Returns iterator to beginning of span.

    VISTA_CXX14_CONSTEXPR
    iterator begin() noexcept;

    //! @brief Returns iterator to beginning of span.

    constexpr const_iterator begin() const noexcept;

    //! @brief Returns iterator to beginning of span.

    constexpr const_iterator cbegin() const noexcept;

    //! @brief Returns iterator to end of span.

    VISTA_CXX14_CONSTEXPR
    iterator end() noexcept;

    //! @brief Returns iterator to end of span.

    constexpr const_iterator end() const noexcept;

    //! @brief Returns iterator to end of span.

    constexpr const_iterator cend() const noexcept;

private:
    template <typename, std::size_t E1>
    struct member_storage
    {
        constexpr size_type capacity() const noexcept
        {
            return E1;
        }

        pointer head;
        pointer tail;
    };

    template <typename T1>
    struct member_storage<T1, dynamic_extent>
    {
        constexpr size_type capacity() const noexcept
        {
            return tail - head;
        }

        pointer head;
        pointer tail;
    };

    struct member_storage<T, Extent> member;
};

} // namespace vista

#include <vista/detail/span.ipp>

#endif // VISTA_SPAN_HPP
