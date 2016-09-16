/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[puddle_op_is_class
template <typename X>
static constexpr inline
__mirror_is_class<X> is_class(X)
noexcept;
//]
//[puddle_op_is_struct
template <typename X>
static constexpr inline
__mirror_is_struct<X> is_struct(X)
noexcept;
//]
//[puddle_op_is_union
template <typename X>
static constexpr inline
__mirror_is_union<X> is_union(X)
noexcept;
//]
//[puddle_op_get_base_classes
template <typename X>
static constexpr inline
__mirror_get_base_classes<X> get_base_classes(X)
noexcept;
//]
//[puddle_op_get_member_types
template <typename X>
static constexpr inline
__mirror_get_member_types<X> get_member_types(X)
noexcept;
//]
//[puddle_op_get_data_members
template <typename X>
static constexpr inline
__mirror_get_data_members<X> get_data_members(X)
noexcept;
//]

