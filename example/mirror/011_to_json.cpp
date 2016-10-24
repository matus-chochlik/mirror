/**
 * @example mirror/011_to_json.cpp
 * @brief Example of simple serialization to JSON
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
{
	Triangle base;
	Point apex;
};

int main(void)
{
	Tetrahedron a{{{0,0,0},{1,0,0},{0,1,0}},{0,0,1}};
	Tetrahedron b{{{1,2,3},{6,5,4},{9,7,8}},{1,1,1}};

	to_json(std::cout, a) << std::endl;
	to_json(std::cout, b) << std::endl;

	return 0;
}

namespace {

using namespace mirror;

template <typename T>
struct json_writer
{
private:
	struct _writer {
		std::ostream& out;
		const T& v;
		bool first;

		template <typename MO>
		void operator()(MO)
		{
			if(first) first = false;
			else out << ", ";

			out << '"';
			out << c_str<get_base_name<MO>>;
			out << '"';
			out << ": ";

			to_json(out, dereference<MO>::apply(v));
		}
	};
public:
	std::ostream& operator()(std::ostream& out, const T& v) const
	{
		_writer write{out, v, true};

		using MT = MIRRORED(T);

		out << '{';

		for_each<get_data_members<MT>>::apply(write);

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
