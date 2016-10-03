/**
 * @file mirror/string.hpp
 * @brief Declaration of compile-time basic_string and string
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_STRING_1105240825_HPP
#define MIRROR_STRING_1105240825_HPP

#include "int_const.hpp"

namespace mirror {

template <typename Char, Char ... C>
struct basic_string
{
	using type = basic_string<Char, C...>;
};

template <char ... C>
using string = basic_string<char, C...>;

using empty_string = string<>;

} // namespace mirror

#endif //include guard

