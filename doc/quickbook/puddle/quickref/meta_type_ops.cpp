/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[puddle_op_get_reflected_type
template <typename X>
static constexpr inline
__mirror_identity<__mirror_get_reflected_type<X>> get_reflected_type(X)
noexcept;
//]

