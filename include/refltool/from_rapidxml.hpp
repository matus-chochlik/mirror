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
#include <cstdlib>
#include <limits>

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

	template <typename Char, typename Num>
	static inline bool _strtonum(
		const rapidxml::xml_base<Char>& rxb,
		Num (*strtox)(const Char*, Char**),
		Num& v
	) noexcept {
		const Char* b = rxb.value();
		const Char* e = b+rxb.value_size();
		if(b == e) { return false; }
		Char* p = nullptr; 
		v = strtox(b, &p);
		return (p == e);
	}

	template <typename Char, typename Num>
	static inline bool _strtonum(
		const rapidxml::xml_base<Char>& rxb,
		Num (*strtox)(const Char*, Char**, int),
		Num& v
	) noexcept {
		const Char* b = rxb.value();
		const Char* e = b+rxb.value_size();
		if(b == e) { return false; }
		Char* p = nullptr; 
		v = strtox(b, &p, 0);
		return (p == e);
	}

	template <typename Char, typename Tmp, typename Num>
	static inline bool _strtonumc(
		const rapidxml::xml_base<Char>& rxb,
		Tmp (*strtox)(const Char*, Char**, int),
		Num& v
	) noexcept {
		Tmp tmp;
		if(_strtonum(rxb, strtox, tmp)) {
			using nl = std::numeric_limits<Num>;
			if(tmp < Tmp(nl::lowest())) {
				return false;
			}
			if(tmp > Tmp(nl::max())) {
				return false;
			}
			v = Num(tmp);
			return true;
		}
		return false;
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
struct rapidxml_loader<char>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		char& v
	) const {
		if((rxb.value_size() == 1) && (rxb.value() != nullptr)) {
			v = *rxb.value();
			return true;
		}
		return false;
	}
};

template <>
struct rapidxml_loader<short>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		short& v
	) const { return _strtonumc(rxb, &std::strtol, v); }
};

template <>
struct rapidxml_loader<unsigned short>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		unsigned short& v
	) const { return _strtonumc(rxb, &std::strtoul, v); }
};

template <>
struct rapidxml_loader<int>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		int& v
	) const { return _strtonumc(rxb, &std::strtol, v); }
};

template <>
struct rapidxml_loader<unsigned>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		unsigned& v
	) const { return _strtonumc(rxb, &std::strtoul, v); }
};

template <>
struct rapidxml_loader<long>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		long& v
	) const { return _strtonum(rxb, &std::strtol, v); }
};

template <>
struct rapidxml_loader<unsigned long>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		unsigned long& v
	) const { return _strtonum(rxb, &std::strtoul, v); }
};

template <>
struct rapidxml_loader<long long>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		long long& v
	) const { return _strtonum(rxb, &std::strtoll, v); }
};

template <>
struct rapidxml_loader<unsigned long long>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		unsigned long long& v
	) const { return _strtonum(rxb, &std::strtoull, v); }
};

template <>
struct rapidxml_loader<float>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		float& v
	) const { return _strtonum(rxb, &std::strtof, v); }
};

template <>
struct rapidxml_loader<double>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		double& v
	) const { return _strtonum(rxb, &std::strtod, v); }
};

template <>
struct rapidxml_loader<long double>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		long double& v
	) const { return _strtonum(rxb, &std::strtold, v); }
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

