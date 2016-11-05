/**
 * @file refltool/to_rapidjson.hpp
 * @brief Implementation to serialization to JSON using RapidJSON
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef REFLTOOL_TO_RAPIDJSON_1105240825_HPP
#define REFLTOOL_TO_RAPIDJSON_1105240825_HPP

#include <puddle/reflection.hpp>
#include <puddle/sequence_ops.hpp>
#include <puddle/meta_named_ops.hpp>
#include <puddle/meta_variable_ops.hpp>
#include <puddle/meta_constant_ops.hpp>
#include <puddle/meta_record_ops.hpp>
#include <puddle/meta_class_ops.hpp>
#include <puddle/meta_enum_ops.hpp>
#include <puddle/string.hpp>
#include <rapidjson/document.h>

namespace refltool {

template <typename T>
struct rapidjson_compositor;

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

template <>
struct rapidjson_compositor<std::string>
{
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator& alloc,
		const std::string& v
	) const { rjv.SetString(v.data(), v.length(), alloc); }
};

template <typename Encoding, typename Allocator, typename T>
static
rapidjson::GenericValue<Encoding, Allocator>& to_rapidjson(
	rapidjson::GenericValue<Encoding, Allocator>& rjv,
	Allocator& alloc,
	const T& v
);

template <typename T>
struct rapidjson_compositor
{
	template <typename Encoding, typename Allocator>
	void operator()(
		rapidjson::GenericValue<Encoding, Allocator>& rjv,
		Allocator& alloc,
		const T& v
	) const
	{
		using namespace puddle;

		rjv.SetObject();
		auto write = [&rjv,&alloc,&v](auto mo)
		{
			using namespace rapidjson;

			Value mem;
			to_rapidjson(mem, alloc, dereference(mo, v));

			auto name = StringRef(c_str(get_base_name(mo)));
			rjv.AddMember(name, mem, alloc);
		};

		auto mt = PUDDLED(T);
		for_each(get_data_members(mt), write);
	}
};

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

