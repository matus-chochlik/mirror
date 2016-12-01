/**
 * @file refltool/to_rapidjson.hpp
 * @brief Implementation of serialization to JSON using RapidJSON
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef REFLTOOL_TO_RAPIDJSON_1105240825_HPP
#define REFLTOOL_TO_RAPIDJSON_1105240825_HPP

#include "enum_to_string.hpp"

#include <puddle/reflection.hpp>
#include <puddle/sequence_ops.hpp>
#include <puddle/meta_named_ops.hpp>
#include <puddle/meta_variable_ops.hpp>
#include <puddle/meta_constant_ops.hpp>
#include <puddle/meta_record_ops.hpp>
#include <puddle/meta_class_ops.hpp>
#include <puddle/meta_enum_ops.hpp>
#include <puddle/string.hpp>

#include <mirror/reflection.hpp>
#include <mirror/get_type.hpp>
#include <mirror/transform.hpp>
#include <mirror/repack.hpp>

#include <reflbase/type_traits_fixes.hpp>
#include <reflbase/int_sequence_fix.hpp>
#include <reflbase/tuple_apply_fix.hpp>

#include <rapidjson/document.h>
#include <map>
#include <set>
#include <tuple>
#include <array>
#include <vector>
#include <memory>
#include <cstddef>

namespace refltool {

template <typename T>
struct rapidjson_compositor;

template <typename T>
struct rapidjson_compositor<const T>
 : rapidjson_compositor<T>
{ };

template <typename T>
struct rapidjson_compositor<T*>
{
private:
	rapidjson_compositor<T> _comp;
public:
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator& alloc,
		T* v
	) const {
		if(bool(v)) {
			_comp(rjv, alloc, *v);
		} else {
			rjv.SetNull();
		}
	}
};

template <>
struct rapidjson_compositor<std::nullptr_t>
{
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator&,
		std::nullptr_t
	) const { rjv.SetNull(); }
};

template <>
struct rapidjson_compositor<bool>
{
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator&,
		bool v
	) const { rjv.SetBool(v); }
};

template <>
struct rapidjson_compositor<char>
{
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator& alloc,
		char v
	) const { rjv.SetString(&v, 1, alloc); }
};

template <>
struct rapidjson_compositor<short>
{
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator&,
		short v
	) const { rjv.SetInt(v); }
};

template <>
struct rapidjson_compositor<unsigned short>
{
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator&,
		unsigned short v
	) const { rjv.SetUint(v); }
};

template <>
struct rapidjson_compositor<int>
{
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator&,
		int v
	) const { rjv.SetInt(v); }
};

template <>
struct rapidjson_compositor<unsigned>
{
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator&,
		unsigned v
	) const { rjv.SetUint(v); }
};

template <>
struct rapidjson_compositor<int64_t>
{
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator&,
		int64_t v
	) const { rjv.SetInt64(v); }
};

template <>
struct rapidjson_compositor<uint64_t>
{
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator&,
		uint64_t v
	) const { rjv.SetUint64(v); }
};

template <>
struct rapidjson_compositor<float>
{
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator&,
		float v
	) const { rjv.SetFloat(v); }
};

template <>
struct rapidjson_compositor<double>
{
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator&,
		double v
	) const { rjv.SetDouble(v); }
};

// const char*
template <>
struct rapidjson_compositor<char*>
{
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator& alloc,
		const char* v
	) const { rjv.SetString(v, alloc); }
};

// const char[N]
template <std::size_t N>
struct rapidjson_compositor<char[N]>
{
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator& alloc,
		const char* v
	) const { rjv.SetString(v, (N>0 && v[N-1])?N:N-1, alloc); }
};

// unique_ptr
template <typename T, typename D>
struct rapidjson_compositor<std::unique_ptr<T, D>>
{
private:
	rapidjson_compositor<T> _comp;
public:
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator& alloc,
		const std::unique_ptr<T, D>& v
	) const {
		if(bool(v)) {
			_comp(rjv, alloc, *v);
		} else {
			rjv.SetNull();
		}
	}
};

// shared_ptr
template <typename T>
struct rapidjson_compositor<std::shared_ptr<T>>
{
private:
	rapidjson_compositor<T> _comp;
public:
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator& alloc,
		const std::shared_ptr<T>& v
	) const {
		if(bool(v)) {
			_comp(rjv, alloc, *v);
		} else {
			rjv.SetNull();
		}
	}
};

// map
template <typename K, typename V, typename C, typename A>
struct rapidjson_compositor<std::map<K, V, C, A>>
{
private:
	static_assert(
		std::is_same<K, char>::value ||
		std::is_same<K, std::string>::value ||
		std::is_enum<K>::value,
		"Map key must be a string on enum type"
	);

	rapidjson_compositor<K> _keycomp;
	rapidjson_compositor<V> _valcomp;
public:
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjo,
		Allocator& alloc,
		const std::map<K, V, C, A>& c
	) const {
		using namespace puddle;

		rjo.SetObject();
		for(const auto& p : c) {
			rapidjson::Value rjk;
			_keycomp(rjk, alloc, p.first);
			rapidjson::Value rjv;
			_valcomp(rjv, alloc, p.second);

			rjo.AddMember(rjk, rjv, alloc);
		}
	}
};

// arrays / ranges
template <typename T, typename Range>
struct rapidjson_compositor_range
{
private:
	rapidjson_compositor<T> _comp;
public:
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rja,
		Allocator& alloc,
		const Range& r
	) const {
		using namespace puddle;

		rja.SetArray();
		for(const auto& e : r) {
			rapidjson::Value rje;
			_comp(rje, alloc, e);
			rja.PushBack(rje, alloc);
		}
	}
};

// set
template <typename T, typename C, typename A>
struct rapidjson_compositor<std::set<T, C, A>>
 : rapidjson_compositor_range<T, std::set<T, C, A>>
{ };

// array
template <typename T, std::size_t N>
struct rapidjson_compositor<std::array<T, N>>
 : rapidjson_compositor_range<T, std::array<T, N>>
{ };

// vector
template <typename T, typename A>
struct rapidjson_compositor<std::vector<T, A>>
 : rapidjson_compositor_range<T, std::vector<T, A>>
{ };

// tuple
template <typename ... T>
struct rapidjson_compositor<std::tuple<T...>>
{
private:
	std::tuple<rapidjson_compositor<T>...> _comps;

	template <typename Enc, typename Alloc, typename E>
	bool _compose_element(
		rapidjson::GenericValue<Enc, Alloc>& rja,
		Alloc& alloc,
		const E& e,
		const rapidjson_compositor<E>& comp
	) const {
		rapidjson::Value rje;
		comp(rje, alloc, e);
		rja.PushBack(rje, alloc);
		return true;
	}

	template <typename Enc, typename Alloc, std::size_t ... I>
	bool _compose_tuple(
		rapidjson::GenericValue<Enc, Alloc>& rja,
		Alloc& alloc,
		const std::tuple<T...>& t,
		std::index_sequence<I...>
	) const {
		return (... && _compose_element(
			rja, alloc,
			std::get<I>(t),
			std::get<I>(_comps)
		));

	}
public:
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rja,
		Allocator& alloc,
		const std::tuple<T...>& tup
	) const {
		rja.SetArray();
		_compose_tuple(
			rja, alloc, tup,
			std::make_index_sequence<sizeof...(T)>{}
		);
	}
};


// string
template <>
struct rapidjson_compositor<std::string>
{
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator& alloc,
		const std::string& v
	) const {
		using namespace rapidjson;
		rjv.SetString(StringRef(v.data(), v.length()), alloc);
	}
};

template <typename T>
struct rapidjson_compositor_class
{
private:
	template <typename MA>
	struct _attrcomp_t
	{
	private:
		using AT = mirror::get_reflected_type<mirror::get_type<MA>>;
		rapidjson_compositor<AT> _comp;
	public:
		template <typename Encoding, typename Allocator>
		bool operator()(
			rapidjson::GenericValue<Encoding, Allocator>& rjv,
			Allocator& alloc,
			const T& v
		) const {
			using namespace puddle;
			using namespace rapidjson;

			MA ma;
			Value mem;
			_comp(mem, alloc, dereference(ma, v));

			auto name = StringRef(c_str(get_base_name(ma)));
			rjv.AddMember(name, mem, alloc);

			return true;
		}
	};

	mirror::repack<
		mirror::transform<
			_attrcomp_t,
			mirror::get_data_members<MIRRORED(T)>
		>, std::tuple
	> _attrcomps;
public:
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator& alloc,
		const T& v
	) const {
		rjv.SetObject();

		std::apply(
			[&rjv,&alloc,&v](auto ... fn) {
				return (... && fn(rjv, alloc, v));
			}, _attrcomps
		);
	}
};

template <typename T>
struct rapidjson_compositor_enum
{
private:
	const enum_to_string_map_t<T> _e2smap;
public:
	rapidjson_compositor_enum(void)
	 : _e2smap(make_enum_to_string_map<T>())
	{ }

	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator& alloc,
		const T& v
	) const {
		using namespace puddle;
		using namespace rapidjson;

		auto s = _e2smap.find(v)->second;
		rjv.SetString(StringRef(s.data(), s.length()), alloc);
	}
};

template <typename T>
struct rapidjson_compositor
 : std::conditional_t<
	std::is_enum<T>::value,
	rapidjson_compositor_enum<T>,
	rapidjson_compositor_class<T>
> { };

// to_rapidjson
template <typename Encoding, typename Allocator, typename T>
static inline
rapidjson::GenericValue<Encoding, Allocator>& to_rapidjson(
	rapidjson::GenericValue<Encoding, Allocator>& rjv,
	Allocator& alloc,
	const T& v
) {
	rapidjson_compositor<T> rjc;
	rjc(rjv, alloc, v);
	return rjv;
}

// to_rapidjson
template <typename Encoding, typename T>
static inline
rapidjson::GenericDocument<Encoding>& to_rapidjson(
	rapidjson::GenericDocument<Encoding>& doc,
	const T& val
) {
	to_rapidjson(doc, doc.GetAllocator(), val);
	return doc;
}

} // namespace refltool

#endif //include guard

