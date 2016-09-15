/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[puddle_traits_1
template <typename X>
static constexpr inline
__mirror_is_int_const<X> is_int_const(X)
noexcept;

template <typename X>
static constexpr inline
__mirror_is_string<X> is_string(X)
noexcept;

template <typename X>
static constexpr inline
__mirror_is_range<X> is_range(X)
noexcept;

template <typename X>
static constexpr inline
__mirror_is_none<X> is_none(X)
noexcept;

template <typename X>
static constexpr inline
__mirror_is_metaobject<X> is_metaobject(X)
noexcept;

template <typename X>
static constexpr inline
__mirror_is_metaobject_sequence<X> is_metaobject_sequence(X)
noexcept;
//]
//[puddle_traits_2
template <typename X>
static constexpr inline
__mirror_reflects_alias<X> reflects_alias(X)
noexcept;

template <typename X>
static constexpr inline
__mirror_reflects_global_scope<X> reflects_global_scope(X)
noexcept;

template <typename X>
static constexpr inline
__mirror_reflects_namespace<X> reflects_namespace(X)
noexcept;

template <typename X>
static constexpr inline
__mirror_reflects_type<X> reflects_type(X)
noexcept;

template <typename X>
static constexpr inline
__mirror_reflects_tag_type<X> reflects_tag_type(X)
noexcept;

template <typename X>
static constexpr inline
__mirror_reflects_enum_member<X> reflects_enum_member(X)
noexcept;

template <typename X>
static constexpr inline
__mirror_reflects_record_member<X> reflects_record_member(X)
noexcept;

template <typename X>
static constexpr inline
__mirror_reflects_variable<X> reflects_variable(X)
noexcept;

template <typename X>
static constexpr inline
__mirror_reflects_constant<X> reflects_constant(X)
noexcept;

template <typename X>
static constexpr inline
__mirror_reflects_specifier<X> reflects_specifier(X)
noexcept;

template <typename X>
static constexpr inline
__mirror_reflects_inheritance<X> reflects_inheritance(X)
noexcept;

//]
