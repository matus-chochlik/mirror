/**
 * @file refltool/enum_to_string.hpp
 * @brief Implementation of enum-to-string conversions
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef REFLTOOL_ENUM_TO_STRING_1105240825_HPP
#define REFLTOOL_ENUM_TO_STRING_1105240825_HPP

#include <puddle/reflection.hpp>
#include <puddle/sequence_ops.hpp>
#include <puddle/meta_constant_ops.hpp>
#include <puddle/meta_enum_ops.hpp>
#include <puddle/meta_named_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <string>
#include <map>

namespace refltool {

template <typename T>
using enum_to_string_map_t = std::map<T, const std::string>;

template <typename T>
static constexpr inline
auto make_enum_to_string_map(void)
{
	using namespace puddle;

	return apply_on(
		get_enumerators(PUDDLED(T)),
		[](auto ... mec)
		{
			enum_to_string_map_t<T>  res;

			(void)(... && res.emplace(
				value(get_constant(mec)),
				c_str(get_base_name(mec))
			).second);

			return res;
		}
	);
}

template <typename T>
static inline
const auto& enum_to_string(T v)
{
	static const auto m = make_enum_to_string_map<T>();
	return m.find(v)->second;
}

} // namespace refltool

#endif //include guard

