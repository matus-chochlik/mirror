/**
 * @file mire/ct/c_str.hpp
 * @brief Implementation of the c_str function
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_C_STR_1105240825_HPP
#define MIRE_CT_C_STR_1105240825_HPP

#include <mire/ct/string.hpp>
#include <mire/ct/default.hpp>
#include <mire/ct/evaluate.hpp>

namespace mire {
namespace ct {

template <typename Char, Char ... C>
struct c_str<basic_string<Char, C...>>
{
	static constexpr const char* value = basic_string<Char, C...>::c_str;

	operator const char* (void) const
	{
		return value;
	}
};

} // namespace ct
} // namespace mire

#endif //include guard

