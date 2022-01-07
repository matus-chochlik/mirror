/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_ELEMENT_TYPE_HPP
#define MIRROR_ELEMENT_TYPE_HPP

#include "primitives.hpp"
#include <array>
#include <set>
#include <span>
#include <vector>

namespace mirror {

template <typename T>
static constexpr auto _mirror_element_type(std::type_identity<T>) {
    return no_metaobject;
}

template <typename E>
static constexpr auto _mirror_element_type(std::type_identity<E[]>) {
    return remove_all_aliases(mirror(E));
}

template <typename E, size_t N>
static constexpr auto _mirror_element_type(std::type_identity<E[N]>) {
    return remove_all_aliases(mirror(E));
}

template <typename E, size_t N>
static constexpr auto
_mirror_element_type(std::type_identity<std::array<E, N>>) {
    return remove_all_aliases(mirror(E));
}

template <typename E, size_t X>
static constexpr auto _mirror_element_type(std::type_identity<std::span<E, X>>) {
    return remove_all_aliases(mirror(E));
}

template <typename E, typename A>
static constexpr auto
_mirror_element_type(std::type_identity<std::vector<E, A>>) {
    return remove_all_aliases(mirror(E));
}

template <typename E, typename C, typename A>
static constexpr auto
_mirror_element_type(std::type_identity<std::set<E, C, A>>) {
    return remove_all_aliases(mirror(E));
}

static constexpr auto
get_element_type(metaobject auto mo) requires(reflects_type(mo)) {
    return _mirror_element_type(get_reflected_type(mo));
}

} // namespace mirror

#endif // MIRROR_ELEMENT_TYPE_HPP

