///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vista/algorithm.hpp>

namespace vista
{

template <typename K, typename T, std::size_t N, typename C>
constexpr constant_map<K, T, N, C>::constant_map(value_type (&&input)[N]) noexcept(vista::detail::is_nothrow_swappable<value_type>::value)
    : storage{ to_sorted(std::forward<decltype(input)>(input)) }
{
}

template <typename K, typename T, std::size_t N, typename C>
VISTA_CXX14_CONSTEXPR
bool constant_map<K, T, N, C>::contains(const key_type& key) const noexcept
{
    return find(key) != end();
}

template <typename K, typename T, std::size_t N, typename C>
VISTA_CXX14_CONSTEXPR
auto constant_map<K, T, N, C>::lower_bound(const key_type& key) const noexcept -> const_iterator
{
    return lower_bound_sorted(begin(),
                              end(),
                              key,
                              value_key_compare{});
}

template <typename K, typename T, std::size_t N, typename C>
VISTA_CXX14_CONSTEXPR
auto constant_map<K, T, N, C>::find(const key_type& key) const noexcept -> const_iterator
{
    auto where = lower_bound(key);
    if (where == end() || key_compare{}(key, where->first))
        return end();
    return where;
}

template <typename K, typename T, std::size_t N, typename C>
VISTA_CXX14_CONSTEXPR
auto constant_map<K, T, N, C>::operator[](const key_type& key) const noexcept -> const mapped_type&
{
    auto where = lower_bound(key);
    if (where == end() || key_compare{}(key, where->first))
        return error_key_not_found(where->second);
    return where->second;
}

template <typename K, typename T, std::size_t N, typename C>
constexpr auto constant_map<K, T, N, C>::key_comp() const noexcept -> key_compare
{
    return key_compare{};
}

template <typename K, typename T, std::size_t N, typename C>
constexpr auto constant_map<K, T, N, C>::value_comp() const noexcept -> value_compare
{
    return value_compare{};
}

template <typename K, typename T, std::size_t N, typename C>
constexpr auto constant_map<K, T, N, C>::to_sorted(value_type (&&input)[N]) noexcept(vista::detail::is_nothrow_swappable<value_type>::value) -> storage
{
    storage result {};
    vista::copy(input, input + N, result.begin());
    vista::insertion_sort<true>(result.begin(), result.end(), value_compare{});
    return result;
}

} // namespace vista
