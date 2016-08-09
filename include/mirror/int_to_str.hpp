/**
 * @file mirror/int_to_str.hpp
 * @brief Compile-time conversion from integers to strings
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_INT_TO_STR_1105240825_HPP
#define MIRROR_INT_TO_STR_1105240825_HPP

#include "int_const.hpp"
#include "identity.hpp"
#include "conditional.hpp"
#include "concat.hpp"

namespace mirror {
namespace _aux {

template <unsigned I>
struct op_uint_to_dec_str;

template <> struct op_uint_to_dec_str<0u> : string<'0'> { };
template <> struct op_uint_to_dec_str<1u> : string<'1'> { };
template <> struct op_uint_to_dec_str<2u> : string<'2'> { };
template <> struct op_uint_to_dec_str<3u> : string<'3'> { };
template <> struct op_uint_to_dec_str<4u> : string<'4'> { };
template <> struct op_uint_to_dec_str<5u> : string<'5'> { };
template <> struct op_uint_to_dec_str<6u> : string<'6'> { };
template <> struct op_uint_to_dec_str<7u> : string<'7'> { };
template <> struct op_uint_to_dec_str<8u> : string<'8'> { };
template <> struct op_uint_to_dec_str<9u> : string<'9'> { };

template <unsigned I>
struct op_uint_to_dec_str
 : concat<eval<op_uint_to_dec_str<I/10>>, eval<op_uint_to_dec_str<I%10>>>
{ };

template <int I>
struct op_int_to_dec_str
 : conditional<
	bool_<(I < 0)>,
	concat<string<'-'>, eval<op_uint_to_dec_str<unsigned(-I)>>>,
	op_uint_to_dec_str<unsigned(I)>
> { };

} // namespace _aux

template <unsigned I>
using uint_to_dec_str = eval<_aux::op_uint_to_dec_str<I>>;

template <int I>
using int_to_dec_str = eval<_aux::op_int_to_dec_str<I>>;

} // namespace mirror

#endif //include guard

