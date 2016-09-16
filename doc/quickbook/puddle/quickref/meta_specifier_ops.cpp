/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[puddle_op_get_elaborated_type_specifier
template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
__mirror_get_elaborated_type_specifier<X> get_elaborated_type_specifier(X)
noexcept;
//]
//[puddle_op_get_access_specifier
template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
__mirror_get_access_specifier<X> get_access_specifier(X)
noexcept;
//]
//[puddle_op_is_public
template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
__mirror_is_public<X> is_public(X)
noexcept;
//]
//[puddle_op_is_protected
template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
__mirror_is_protected<X> is_protected(X)
noexcept;
//]
//[puddle_op_is_private
template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
__mirror_is_private<X> is_private(X)
noexcept;
//]
//[puddle_op_is_static
template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
__mirror_is_static<X> is_static(X)
noexcept;
//]
//[puddle_op_is_virtual
template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
__mirror_is_virtual<X> is_virtual(X)
noexcept;
//]

