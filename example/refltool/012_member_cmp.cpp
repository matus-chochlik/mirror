/**
 * @example refltool/012_member_cmp.cpp
 * @brief Shows per-data-member comparisons
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <refltool/data_member_cmp.hpp>
#include <iostream>
#include <iomanip>

struct Point
{
	int x, y, z;
};

bool operator == (const Point& a, const Point& b)
{ return refltool::data_members_equal(a, b); }

bool operator <  (const Point& a, const Point& b)
{ return refltool::data_members_less(a, b); }

struct Triangle
{
	Point a, b, c;
};

bool operator == (const Triangle& a, const Triangle& b)
{ return refltool::data_members_equal(a, b); }

bool operator <  (const Triangle& a, const Triangle& b)
{ return refltool::data_members_less(a, b); }

int main(void)
{
	Point i{1,0,0}, j{0,1,0}, k{0,0,1}, l{1,1,1};

	Triangle d{i,j,k};
	Triangle e{j,k,l};
	Triangle f = d;

	std::cout << "d == d : "  << std::boolalpha << (d == d) << std::endl;
	std::cout << "d == e : "  << std::boolalpha << (d == e) << std::endl;
	std::cout << "d == f : "  << std::boolalpha << (d == f) << std::endl;

	std::cout << "d <  d : "  << std::boolalpha << (d <  d) << std::endl;
	std::cout << "d <  e : "  << std::boolalpha << (d <  e) << std::endl;
	std::cout << "e <  f : "  << std::boolalpha << (e <  f) << std::endl;

	return 0;
}

