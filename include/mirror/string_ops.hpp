/**
 * @file mirror/string_ops.hpp
 * @brief Implementation of constexpr operations on string
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_STRING_OPS_1105240825_HPP
#define MIRROR_STRING_OPS_1105240825_HPP

#include "string.hpp"
#include "int_const.hpp"
#include <iostream>
#include <string>

namespace mirror {

template <typename Char, Char ... CL, Char ... CR>
static constexpr inline
false_
operator == (basic_string<Char, CL...>, basic_string<Char, CR...>)
noexcept { return {}; }

template <typename Char, Char ... C>
static constexpr inline
true_
operator == (basic_string<Char, C...>, basic_string<Char, C...>)
noexcept { return {}; }

template <typename Char, Char ... CL, Char ... CR>
static constexpr inline
true_
operator != (basic_string<Char, CL...>, basic_string<Char, CR...>)
noexcept { return {}; }

template <typename Char, Char ... C>
static constexpr inline
false_
operator != (basic_string<Char, C...>, basic_string<Char, C...>)
noexcept { return {}; }

template <typename Char, Char ... CL, Char ... CR>
static constexpr inline
basic_string<Char, CL..., CR...>
operator + (basic_string<Char, CL...>, basic_string<Char, CR...>)
noexcept { return {}; }

template <typename Char, Char ... C>
static inline
std::ostream& operator << (std::ostream& out, basic_string<Char, C...>)
{
	const Char s[] = {C..., '\0'};
	return out.write(
		static_cast<const char*>(s),
		sizeof...(C)*sizeof(Char)
	);
}

template <typename Char, Char ... C>
static inline
std::string str(basic_string<Char, C...>)
{
	const Char s[] = {C..., '\0'};
	return std::string{s, sizeof...(C)};
}

} // namespace mirror

#endif //include guard

