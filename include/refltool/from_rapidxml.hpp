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
#include <reflbase/tuple_apply_fix.hpp>

#include <puddle/meta_named_ops.hpp>
#include <puddle/meta_variable_ops.hpp>
#include <puddle/meta_record_ops.hpp>
#include <puddle/string.hpp>

#include <mirror/reflection.hpp>
#include <mirror/get_type.hpp>
#include <mirror/transform.hpp>
#include <mirror/repack.hpp>

#include "string_to_enum.hpp"

#include <cstring>
#include <cstddef>
#include <cstdlib>
#include <limits>
#include <array>
#include <vector>
#include <set>
#include <map>

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

	template <typename Char>
	static inline bool _name_equal_to(
		const rapidxml::xml_base<Char>& rxb,
		const std::string_view& str
	) noexcept {
		return _str_eq({rxb.name(), rxb.name_size()}, str);
	}

	template <typename Char, typename Num>
	static inline bool _valtonum(
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
	static inline bool _valtonum(
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
	static inline bool _valtonumc(
		const rapidxml::xml_base<Char>& rxb,
		Tmp (*strtox)(const Char*, Char**, int),
		Num& v
	) noexcept {
		Tmp tmp;
		if(_valtonum(rxb, strtox, tmp)) {
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
		bool& v,
		bool from_name
	) const {
		if(from_name) {
			if(_name_equal_to(rxb, {"true", 4})) {
				v = true;
			} else if(_name_equal_to(rxb, {"false", 5})) {
				v = false;
			} else { return false; } 
		} else {
			if(_value_equal_to(rxb, {"true", 4})) {
				v = true;
			} else if(_value_equal_to(rxb, {"false", 5})) {
				v = false;
			} else { return false; } 
		}

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
		char& v,
		bool from_name
	) const {
		if(from_name) {
			if((rxb.name_size() == 1) && (rxb.name())) {
				v = *rxb.name();
				return true;
			}
		} else {
			if((rxb.value_size() == 1) && (rxb.value())) {
				v = *rxb.value();
				return true;
			}
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
		short& v,
		bool from_name
	) const { return !from_name && _valtonumc(rxb, &std::strtol, v); }
};

template <>
struct rapidxml_loader<unsigned short>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		unsigned short& v,
		bool from_name
	) const { return !from_name && _valtonumc(rxb, &std::strtoul, v); }
};

template <>
struct rapidxml_loader<int>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		int& v,
		bool from_name
	) const { return !from_name && _valtonumc(rxb, &std::strtol, v); }
};

template <>
struct rapidxml_loader<unsigned>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		unsigned& v,
		bool from_name
	) const { return !from_name && _valtonumc(rxb, &std::strtoul, v); }
};

template <>
struct rapidxml_loader<long>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		long& v,
		bool from_name
	) const { return !from_name && _valtonum(rxb, &std::strtol, v); }
};

template <>
struct rapidxml_loader<unsigned long>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		unsigned long& v,
		bool from_name
	) const { return !from_name && _valtonum(rxb, &std::strtoul, v); }
};

template <>
struct rapidxml_loader<long long>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		long long& v,
		bool from_name
	) const { return !from_name && _valtonum(rxb, &std::strtoll, v); }
};

template <>
struct rapidxml_loader<unsigned long long>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		unsigned long long& v,
		bool from_name
	) const { return !from_name && _valtonum(rxb, &std::strtoull, v); }
};

template <>
struct rapidxml_loader<float>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		float& v,
		bool from_name
	) const { return !from_name && _valtonum(rxb, &std::strtof, v); }
};

template <>
struct rapidxml_loader<double>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		double& v,
		bool from_name
	) const { return !from_name && _valtonum(rxb, &std::strtod, v); }
};

template <>
struct rapidxml_loader<long double>
 : rapidxml_loader_utils
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		long double& v,
		bool from_name
	) const { return !from_name && _valtonum(rxb, &std::strtold, v); }
};

template <>
struct rapidxml_loader<std::string>
{
	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		std::string& v,
		bool from_name
	) const {
		if(from_name) {
			v.assign(rxb.name(), rxb.name_size());
		} else {
			v.assign(rxb.value(), rxb.value_size());
		}
		return true;
	}
};

// array
template <typename T, std::size_t N>
struct rapidxml_loader<std::array<T, N>>
{
private:
	rapidxml_loader<T> _loader;
public:
	template <typename Char>
	bool operator()(
		const rapidxml::xml_node<Char>& rxn,
		std::array<T, N>& r,
		bool from_name
	) const {
		if(from_name) return false;

		std::size_t i = 0;
		for(auto* n = rxn.first_node(); n; n = n->next_sibling()) {
			if(!_loader(*n, r[i], false)) {
				return false;
			}
			++i;
		}
		return i == N;
	}
};

// vector
template <typename T, typename A>
struct rapidxml_loader<std::vector<T, A>>
{
private:
	rapidxml_loader<T> _loader;
public:
	template <typename Char>
	bool operator()(
		const rapidxml::xml_node<Char>& rxn,
		std::vector<T, A>& r,
		bool from_name
	) const {
		if(from_name) return false;

		std::size_t i = 0;
		for(auto* n = rxn.first_node(); n; n = n->next_sibling()) {
			++i;
		} 
		r.resize(i);

		i = 0;
		for(auto* n = rxn.first_node(); n; n = n->next_sibling()) {
			if(i >= r.size()) {
				return false;
			}
			if(
				!_loader(*n, r[i], false) &&
				!_loader(*n, r[i], true)
			) { return false; }
			++i;
		}
		return true;
	}
};

// set
template <typename T, typename C, typename A>
struct rapidxml_loader<std::set<T, C, A>>
{
private:
	rapidxml_loader<T> _loader;
public:
	template <typename Char>
	bool operator()(
		const rapidxml::xml_node<Char>& rxn,
		std::set<T, C, A>& c,
		bool from_name
	) const {
		if(from_name) return false;

		c.clear();

		for(auto* n = rxn.first_node(); n; n = n->next_sibling()) {
			T tmpval;
			if(
				!_loader(*n, tmpval, false) &&
				!_loader(*n, tmpval, true)
			) { return false; }

			c.emplace(std::move(tmpval));
		}
		return true;
	}
};

// map
template <typename K, typename V, typename C, typename A>
struct rapidxml_loader<std::map<K, V, C, A>>
{
private:
	rapidxml_loader<K> _keyldr;
	rapidxml_loader<V> _valldr;
public:
	template <typename Char>
	bool operator()(
		const rapidxml::xml_node<Char>& rxn,
		std::map<K, V, C, A>& c,
		bool from_name
	) const {
		if(from_name) return false;

		c.clear();

		for(
			auto* a = rxn.first_attribute();
			a; a = a->next_attribute()
		) {
			K tmpkey;
			if(!_keyldr(*a, tmpkey, true)) {
				return false;
			}
			V tmpval;
			if(!_valldr(*a, tmpval, false)) {
				return false;
			}
			c.emplace(std::move(tmpkey), std::move(tmpval));
		}

		for(
			auto* n = rxn.first_node();
			n; n = n->next_sibling()
		) {
			K tmpkey;
			if(!_keyldr(*n, tmpkey, true)) {
				return false;
			}
			V tmpval;
			if(!_valldr(*n, tmpval, false)) {
				return false;
			}
			c.emplace(std::move(tmpkey), std::move(tmpval));
		}
		return true;
	}
};

template <typename T>
struct rapidxml_loader_enum
{
private:
	string_to_enum_map_t<T> _map;
public:
	rapidxml_loader_enum(void)
	 : _map(make_string_to_enum_map<T>())
	{ }

	template <typename Char>
	bool operator()(
		const rapidxml::xml_base<Char>& rxb,
		T& v,
		bool from_name
	) const {
		std::string tmp;
		if(from_name) {
			tmp.assign(rxb.name(), rxb.name_size());
		} else {
			tmp.assign(rxb.value(), rxb.value_size());
		}
		auto p = _map.find(tmp);
		if(p == _map.end()) {
			return false;
		}
		v = p->second;
		return true;
	}
};

template <typename T>
struct rapidxml_loader_class
{
private:
	template <typename MA>
	struct _attrldr_t
	{
	private:
		using AT = mirror::get_reflected_type<mirror::get_type<MA>>;
		rapidxml_loader<AT> _ldr;
	public:
		template <typename Char>
		bool operator()(
			const rapidxml::xml_node<Char>& rxn,
			T& v,
			bool from_name
		) const {
			using namespace puddle;

			MA ma;
			auto n = rxn.first_node(c_str(get_base_name(ma)));
			if(n != nullptr) {
				if(_ldr(*n, dereference(ma, v), from_name)) {
					return true;
				}
			}
			auto a = rxn.first_attribute(c_str(get_base_name(ma)));
			if(a != nullptr) {
				if(_ldr(*a, dereference(ma, v), from_name)) {
					return true;
				}
			}
			return false;
		}
	};

	mirror::repack<
		mirror::transform<
			mirror::get_data_members<MIRRORED(T)>,
			_attrldr_t
		>, std::tuple
	> _attrldrs;
public:
	template <typename Char>
	bool operator()(
		const rapidxml::xml_node<Char>& rxb,
		T& v,
		bool from_name
	) const {
		return std::apply(
			[&rxb,&v,from_name](auto ... fn) {
				return (... && fn(rxb, v, from_name));
			}, _attrldrs
		);
	}
};

template <typename T>
struct rapidxml_loader
 : std::conditional_t<
	std::is_enum<T>::value,
	rapidxml_loader_enum<T>,
	rapidxml_loader_class<T>
> { };

// from_rapidxml (node)
template <typename Char, typename T>
static inline
bool from_rapidxml(
	const rapidxml::xml_node<Char>& rxn,
	T& v
) {
	rapidxml_loader<T> rxl;
	return rxl(rxn, v, false) || rxl(rxn, v, true);
}

template <typename Char, typename T>
static inline
bool from_rapidxml(
	const rapidxml::xml_node<Char>& rxn,
	T& v,
	bool from_name
) {
	rapidxml_loader<T> rxl;
	return rxl(rxn, v, from_name);
}

// from_rapidxml (attribute)
template <typename Char, typename T>
static inline
bool from_rapidxml(
	const rapidxml::xml_attribute<Char>& rxa,
	T& v,
	bool from_name
) {
	rapidxml_loader<T> rxl;
	return rxl(rxa, v, from_name);
}

} // namespace refltool

#endif //include guard

