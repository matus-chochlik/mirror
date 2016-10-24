/**
 * @file puddle/traits.hpp
 * @brief Implementation of the metaobject trait wrappers
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_TRAITS_1105240825_HPP
#define PUDDLE_TRAITS_1105240825_HPP

#include <mirror/traits.hpp>

namespace puddle {

template <typename X>
static constexpr inline
auto is_none(X)
noexcept { return mirror::is_none<X>{}; }

template <typename X>
static constexpr inline
auto is_string(X)
noexcept { return mirror::is_string<X>{}; }

template <typename X>
static constexpr inline
auto is_metaobject(X)
noexcept { return mirror::is_metaobject<X>{}; }

template <typename X>
static constexpr inline
auto is_metaobject_sequence(X)
noexcept { return mirror::is_metaobject_sequence<X>{}; }

template <typename X>
static constexpr inline
auto reflects_specifier(X)
noexcept { return mirror::reflects_specifier<X>{}; }

template <typename X>
static constexpr inline
auto reflects_global_scope(X)
noexcept { return mirror::reflects_global_scope<X>{}; }

template <typename X>
static constexpr inline
auto reflects_namespace(X)
noexcept { return mirror::reflects_namespace<X>{}; }

template <typename X>
static constexpr inline
auto reflects_type(X)
noexcept { return mirror::reflects_type<X>{}; }

template <typename X>
static constexpr inline
auto reflects_tag_type(X)
noexcept { return mirror::reflects_tag_type<X>{}; }

template <typename X>
static constexpr inline
auto reflects_enum(X)
noexcept { return mirror::reflects_enum<X>{}; }

template <typename X>
static constexpr inline
auto reflects_record(X)
noexcept { return mirror::reflects_record<X>{}; }

template <typename X>
static constexpr inline
auto reflects_class(X)
noexcept { return mirror::reflects_class<X>{}; }

template <typename X>
static constexpr inline
auto reflects_alias(X)
noexcept { return mirror::reflects_alias<X>{}; }

template <typename X>
static constexpr inline
auto reflects_variable(X)
noexcept { return mirror::reflects_variable<X>{}; }

template <typename X>
static constexpr inline
auto reflects_constant(X)
noexcept { return mirror::reflects_constant<X>{}; }

template <typename X>
static constexpr inline
auto reflects_enum_member(X)
noexcept { return mirror::reflects_enum_member<X>{}; }

template <typename X>
static constexpr inline
auto reflects_record_member(X)
noexcept { return mirror::reflects_record_member<X>{}; }

template <typename X>
static constexpr inline
auto reflects_inheritance(X)
noexcept { return mirror::reflects_inheritance<X>{}; }

} // namespace puddle

#endif //include guard

