/**
 * @file mirror/string_view.hpp
 * @brief Implementation of the `string_view` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_STRING_VIEW_1105240825_HPP
#define MIRROR_STRING_VIEW_1105240825_HPP

#include "c_str.hpp"
#include <string_view>

namespace mirror {
namespace _aux {

template <typename X>
struct op_string_view;

template <typename Char, Char ... C>
struct op_string_view<basic_string<Char, C...>>
{
	typedef op_string_view type;
	static constexpr std::string_view value = {
		c_str<basic_string<Char, C...>>,
		sizeof ... (C)
	};
};

} // namespace _aux

template <typename X>
constexpr ::std::string_view string_view = _aux::op_string_view<X>::value;

} // namespace mirror

#endif //include guard

