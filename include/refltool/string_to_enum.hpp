/**
 * @file refltool/string_to_enum.hpp
 * @brief Implementation of enum-to-string conversions
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef REFLTOOL_STRING_TO_ENUM_1105240825_HPP
#define REFLTOOL_STRING_TO_ENUM_1105240825_HPP

#include <puddle/reflection.hpp>
#include <puddle/sequence_ops.hpp>
#include <puddle/meta_constant_ops.hpp>
#include <puddle/meta_enum_ops.hpp>
#include <puddle/meta_named_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <stdexcept>
#include <string>
#include <map>

namespace refltool {

template <typename T>
using string_to_enum_map_t = std::map<std::string, const T>;

template <typename T>
static constexpr inline
auto make_string_to_enum_map(void)
{
	using namespace puddle;

	return apply_on(
		get_enumerators(PUDDLED(T)),
		[](auto ... mec)
		{
			string_to_enum_map_t<T> res;

			(void)(... && res.emplace(
				c_str(get_base_name(mec)),
				value(get_constant(mec))
			).second);

			return res;
		}
	);
}

template <typename T>
static inline
T string_to_enum(const std::string& s)
{
	static const auto m = make_string_to_enum_map<T>();
	auto p = m.find(s);

	if(p == m.end()) {
		throw std::invalid_argument("Invalid enumerator name");
	}
	return p->second;
}

} // namespace refltool

#endif //include guard

