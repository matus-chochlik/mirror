/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_BASE_TYPE_HPP
#define MIRROR_BASE_TYPE_HPP

#include "primitives.hpp"

namespace mirror {

template <typename T>
static constexpr auto _mirror_base_type(std::type_identity<T>) {
    return remove_all_aliases(mirror(T));
}

template <typename T>
static constexpr auto _mirror_base_type(std::type_identity<const T>) {
    return _mirror_base_type(std::type_identity<T>{});
}

template <typename T>
static constexpr auto _mirror_base_type(std::type_identity<volatile T>) {
    return _mirror_base_type(std::type_identity<T>{});
}

template <typename T>
static constexpr auto _mirror_base_type(std::type_identity<const volatile T>) {
    return _mirror_base_type(std::type_identity<T>{});
}

template <typename T>
static constexpr auto _mirror_base_type(std::type_identity<T*>) {
    return _mirror_base_type(std::type_identity<T>{});
}

template <typename T>
static constexpr auto _mirror_base_type(std::type_identity<T&>) {
    return _mirror_base_type(std::type_identity<T>{});
}

template <typename T>
static constexpr auto _mirror_base_type(std::type_identity<T&&>) {
    return _mirror_base_type(std::type_identity<T>{});
}

static constexpr auto
get_base_type(metaobject auto mo) requires(reflects_type(mo)) {
    return _mirror_base_type(get_reflected_type(mo));
}

} // namespace mirror

#endif // MIRROR_BASE_TYPE_HPP

