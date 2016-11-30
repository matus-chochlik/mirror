/**
 * @example dazzle/013_to_json.cpp
 * @brief Example of serialization to JSON
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <dazzle/metaobject.hpp>
#include <dazzle/reflection.hpp>
#include <dazzle/int_const.hpp>
#include <dazzle/string.hpp>
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

using namespace dazzle;

template <typename T>
struct json_writer
{
	std::ostream& operator()(std::ostream& out, const T& v) const
	{
		auto mt = DAZZLED(T);

		out << '{';

		auto write = [&out,&v](auto mo)
		{
			out << '"';
			out << mo.get_base_name();
			out << '"';
			out << ": ";

			to_json(out, mo.dereference(v));
		};

		auto separate = [&out](void) { out << ", "; };

		mt.get_base_classes().for_each(
			[&write,&separate](auto mi)
			{
				mi.get_base_class().get_data_members().for_each(
					write, separate
				);
			}, separate
		);

		mt.get_data_members().for_each(write, separate);

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
