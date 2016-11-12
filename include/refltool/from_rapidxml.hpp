/**
 * @file refltool/from_rapidxml.hpp
 * @brief Implementation of deserialization from JSON using RapidJSON
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef REFLTOOL_FROM_RAPIDJSON_1105240825_HPP
#define REFLTOOL_FROM_RAPIDJSON_1105240825_HPP

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wsign-conversion"
#endif
#include <rapidxml.hpp>
#ifdef __clang__
#pragma clang diagnostic pop
#endif

#include <reflbase/string_view_fix.hpp>

#include <cstring>
#include <cstddef>

namespace refltool {

template <typename T>
struct rapidxml_loader;

struct rapidxml_loader_utils
{
protected:
	static inline
	bool _str_eq(
		const std::string_view& a,
		const std::string_view& b
	) noexcept {
		if(a.size() != b.size()) { return false; }
		return std::strncmp(a.data(), b.data(), a.size()) == 0;
	}

	template <typename Char>
	static inline bool _value_equal_to(
		const rapidxml::xml_base<Char>& rxb,
		const std::string_view& str
	) noexcept {
		return _str_eq({rxb.value(), rxb.value_size()}, str);
	}
};

template <>
struct rapidxml_loader<bool>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		bool& v
	) const {
		if(_value_equal_to(rxb, {"true", 4})) {
			v = true;
		} else if(_value_equal_to(rxb, {"false", 5})) {
			v = false;
		} else { return false; } 

		return true;
	}
};

template <>
struct rapidxml_loader<std::string>
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		std::string& v
	) const {
		v.assign(rxb.value(), rxb.value_size());
		return true;
	}
};

// from_rapidxml
template <typename Char, typename T>
static inline
bool from_rapidxml(
	const rapidxml::xml_node<Char>& rxn,
	T& v
) {
	rapidxml_loader<T> rxl;
	return rxl(rxn, v);
}

// from_rapidxml
template <typename Char, typename T>
static inline
bool from_rapidxml(
	const rapidxml::xml_attribute<Char>& rxa,
	T& v
) {
	rapidxml_loader<T> rxl;
	return rxl(rxa, v);
}

} // namespace refltool

#endif //include guard

