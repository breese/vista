///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

namespace vista
{

template <typename T, std::size_t E>
template <bool Constraint,
          typename std::enable_if<Constraint, int>::type>
constexpr span<T, E>::span() noexcept
    : span(nullptr, nullptr)
{
}

template <typename T, std::size_t E>
template <typename OtherT,
          std::size_t OtherExtent,
          typename std::enable_if<(E == OtherExtent || E == dynamic_extent) && std::is_convertible<OtherT (*)[], T (*)[]>::value, int>::type>
constexpr span<T, E>::span(const span<OtherT, OtherExtent>& other) noexcept
    : span(other.begin(), other.end())
{
}

template <typename T, std::size_t E>
constexpr span<T, E>::span(pointer data, size_type size) noexcept
    : span(data, data + size)
{
}

template <typename T, std::size_t E>
constexpr span<T, E>::span(pointer first, pointer last) noexcept
    : member{ first, last }
{
}

template <typename T, std::size_t E>
template <std::size_t M,
          typename std::enable_if<(E == M || E == dynamic_extent), int>::type>
constexpr span<T, E>::span(element_type (&array)[M]) noexcept
    : span(array, array + M)
{
}

template <typename T, std::size_t E>
constexpr bool span<T, E>::empty() const noexcept
{
    return size() == 0;
}

template <typename T, std::size_t E>
constexpr auto span<T, E>::size() const noexcept -> size_type
{
    return member.tail - member.head;
}

template <typename T, std::size_t E>
constexpr auto span<T, E>::capacity() const noexcept -> size_type
{
    return member.capacity();
}

template <typename T, std::size_t E>
VISTA_CXX14_CONSTEXPR
auto span<T, E>::data() noexcept -> pointer
{
    return member.head;
}

template <typename T, std::size_t E>
constexpr auto span<T, E>::data() const noexcept -> const_pointer
{
    return member.head;
}

template <typename T, std::size_t E>
constexpr auto span<T, E>::front() const noexcept ->  const_reference
{
    return *member.head;
}

template <typename T, std::size_t E>
VISTA_CXX14_CONSTEXPR
auto span<T, E>::front() noexcept -> reference
{
    return *member.head;
}

template <typename T, std::size_t E>
VISTA_CXX14_CONSTEXPR
auto span<T, E>::back() noexcept -> reference
{
    return operator[](size() - 1);
}

template <typename T, std::size_t E>
constexpr auto span<T, E>::back() const noexcept -> const_reference
{
    return operator[](size() - 1);
}

template <typename T, std::size_t E>
VISTA_CXX14_CONSTEXPR
auto span<T, E>::operator[](difference_type position) noexcept -> reference
{
    return member.head[position];
}

template <typename T, std::size_t E>
constexpr auto span<T, E>::operator[](difference_type position) const noexcept -> const_reference
{
    return member.head[position];
}

template <typename T, std::size_t E>
template <std::size_t Offset, std::size_t Count>
constexpr auto span<T, E>::subspan() const noexcept -> span<element_type, Count>
{
    VISTA_CXX14(assert(Offset <= capacity()));
    VISTA_CXX14(assert(Count == dynamic_extent || Count <= capacity() - Offset));

    return span<element_type, Count>(member.head + Offset,
                                     (Count == dynamic_extent) ? (capacity() - Offset) : Count);
}

template <typename T, std::size_t E>
VISTA_CXX14_CONSTEXPR
void span<T, E>::remove_front(size_type amount) noexcept
{
    member.head += amount;
}

template <typename T, std::size_t E>
VISTA_CXX14_CONSTEXPR
void span<T, E>::remove_back(size_type amount) noexcept
{
    member.tail -= amount;
}

template <typename T, std::size_t E>
VISTA_CXX14_CONSTEXPR
auto span<T, E>::begin() noexcept -> iterator
{
    return member.head;
}

template <typename T, std::size_t E>
constexpr auto span<T, E>::begin() const noexcept -> const_iterator
{
    return member.head;
}

template <typename T, std::size_t E>
constexpr auto span<T, E>::cbegin() const noexcept -> const_iterator
{
    return member.head;
}

template <typename T, std::size_t E>
VISTA_CXX14_CONSTEXPR
auto span<T, E>::end() noexcept -> iterator
{
    return member.tail;
}

template <typename T, std::size_t E>
constexpr auto span<T, E>::end() const noexcept -> const_iterator
{
    return member.tail;
}

template <typename T, std::size_t E>
constexpr auto span<T, E>::cend() const noexcept -> const_iterator
{
    return member.tail;
}

} // namespace vista
