/**
 * @example mirror/025_to_rapidjson.cpp
 * @brief Example of serialization to JSON using RapidJSON
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <mirror/for_each.hpp>
#include <mirror/dereference.hpp>
#include <mirror/get_base_name.hpp>
#include <mirror/get_data_members.hpp>
#include <mirror/c_str.hpp>
#include <mirror/value.hpp>
#include <mirror/reflection.hpp>
#include <mirror/range.hpp>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>

struct Point
{
	int x, y, z;
};

struct Triangle
{
	Point a, b, c;
};

struct Tetrahedron
{
	Triangle base;
	Point apex;
};

template <typename T>
rapidjson::Value& to_json(
	rapidjson::Document& doc,
	rapidjson::Value& rjv,
	const T& v
);

template <typename T>
void add_to_array(
	rapidjson::Document& doc,
	rapidjson::Value& ary,
	const T& val
) {
	rapidjson::Value rjv;
	ary.PushBack(to_json(doc, rjv, val), doc.GetAllocator());
}

int main(void)
{
	// create JSON document and an array
	rapidjson::Document doc(rapidjson::kObjectType);
	rapidjson::Value ary(rapidjson::kArrayType);

	// add various values to the array
	add_to_array(doc, ary, Point{1,2,3});
	add_to_array(doc, ary, 123.456f);
	add_to_array(doc, ary, Triangle{{0,0,0},{1,0,0},{0,1,0}});
	add_to_array(doc, ary, true);
	add_to_array(doc, ary, Tetrahedron{{{1,2,3},{6,5,4},{9,7,8}},{1,1,1}});
	add_to_array(doc, ary, false);
	add_to_array(doc, ary, std::string("blah"));


	doc.AddMember("values", ary, doc.GetAllocator());
	// write to stdout
	rapidjson::OStreamWrapper osw(std::cout);
	rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
	doc.Accept(writer);

	std::cout << std::endl;

	return 0;
}

namespace {

using namespace mirror;

template <typename T>
struct json_writer
{
private:
	struct _writer {
		rapidjson::Document& doc;
		rapidjson::Value& rjv;
		const T& v;

		template <typename MO>
		void operator()(MO)
		{
			using namespace rapidjson;
			auto name = StringRef(c_str<get_base_name<MO>>);
			Value mem;

			to_json(doc, mem, dereference<MO>::apply(v));
			rjv.AddMember(name, mem, doc.GetAllocator());
		}
	};
public:
	rapidjson::Value& operator()(
		rapidjson::Document& doc,
		rapidjson::Value& rjv,
		const T& v
	) const
	{
		rjv.SetObject();
		_writer write{doc, rjv, v};

		using MT = MIRRORED(T);

		for_each<get_data_members<MT>>::apply(write);

		return rjv;
	}
};

template <>
struct json_writer<bool>
{
	rapidjson::Value& operator()(
		rapidjson::Document&,
		rapidjson::Value& rjv,
		bool v
	) const
	{
		return rjv.SetBool(v);
	}
};

template <>
struct json_writer<int>
{
	rapidjson::Value& operator()(
		rapidjson::Document&,
		rapidjson::Value& rjv,
		int v
	) const
	{
		return rjv.SetInt(v);
	}
};

template <>
struct json_writer<float>
{
	rapidjson::Value& operator()(
		rapidjson::Document&,
		rapidjson::Value& rjv,
		float v
	) const
	{
		return rjv.SetFloat(v);
	}
};

template <>
struct json_writer<std::string>
{
	rapidjson::Value& operator()(
		rapidjson::Document&,
		rapidjson::Value& rjv,
		const std::string& v
	) const
	{
		using namespace rapidjson;
		return rjv.SetString(StringRef(v.data(), v.size()));
	}
};

} // namespace

template <typename T>
rapidjson::Value& to_json(
	rapidjson::Document& doc,
	rapidjson::Value& rjv,
	const T& v
)
{
	json_writer<T> jw;
	return jw(doc, rjv, v);
}
