/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[puddle_op_has_source_info
template <typename X>
static constexpr inline
__mirror_has_source_info<X> has_source_info(X)
noexcept;
//]
//[puddle_op_get_source_file
template <typename X>
static constexpr inline
__mirror_get_source_file<X> get_source_file(X)
noexcept;
//]
//[puddle_op_get_source_line
template <typename X>
static constexpr inline
__mirror_get_source_line<X> get_source_line(X)
noexcept;
//]
//[puddle_op_get_source_column
template <typename X>
static constexpr inline
__mirror_get_source_column<X> get_source_column(X)
noexcept;
//]

