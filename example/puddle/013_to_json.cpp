/**
 * @example puddle/013_to_json.cpp
 * @brief Example of serialization to JSON
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <puddle/metaobject_ops.hpp>
#include <puddle/sequence_ops.hpp>
#include <puddle/reflection.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <iostream>

template <typename T>
std::ostream& to_json(std::ostream& out, const T& v);

struct Point
{
	int x, y, z;
};

struct Triangle
{
	Point a, b, c;
};

struct Tetrahedron
 : Triangle
 , Point
{ };

int main(void)
{
	Tetrahedron a{{{0,0,0},{1,0,0},{0,1,0}},{0,0,1}};
	Tetrahedron b{{{1,2,3},{6,5,4},{9,7,8}},{1,1,1}};

	to_json(std::cout, a) << std::endl;
	to_json(std::cout, b) << std::endl;

	return 0;
}

namespace {

using namespace puddle;

template <typename T>
struct json_writer
{
	std::ostream& operator()(std::ostream& out, const T& v) const
	{
		auto mt = PUDDLED(T);

		out << '{';

		bool first = true;

		auto write = [&out,&v,&first](auto mo)
		{
			if(first) first = false;
			else out << ", ";

			out << '"';
			out << c_str(get_base_name(mo));
			out << '"';
			out << ": ";

			to_json(out, dereference(mo, v));
		};

		for_each(
			get_base_classes(mt),
			[&write,&first](auto mi)
			{
				first = true;
				for_each(
					get_data_members(get_base_class(mi)),
					write
				);
			}
		);

		first = true;
		for_each(get_data_members(mt), write);

		return out << '}';
	}
};

template <>
struct json_writer<int>
{
	std::ostream& operator()(std::ostream& out, int v) const
	{
		return out << v;
	}
};

} // namespace

template <typename T>
std::ostream& to_json(std::ostream& out, const T& v)
{
	json_writer<T> jw;
	jw(out, v);
	return out;
}
