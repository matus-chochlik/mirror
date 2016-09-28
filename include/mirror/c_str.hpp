/**
 * @file mirror/c_str.hpp
 * @brief Implementation of the `c_str` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_C_STR_1105240825_HPP
#define MIRROR_C_STR_1105240825_HPP

#include "string.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_c_str;

template <typename Char, Char ... C>
struct op_c_str<basic_string<Char, C...>>
{
	using type = op_c_str;
	static constexpr const Char value[sizeof...(C)+1] = {C...,Char(0)};
};

/*TODO #if std < c++1z
template <typename Char, Char ... C>
const Char op_c_str<basic_string<Char, C...>>::value[sizeof...(C)+1];
*/

} // namespace _aux

template <typename X>
constexpr auto c_str = _aux::op_c_str<X>::value;

} // namespace mirror

#endif //include guard

