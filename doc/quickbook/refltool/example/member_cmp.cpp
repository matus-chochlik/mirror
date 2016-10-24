/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[refltool_example_member_cmp_1
#include <refltool/data_member_cmp.hpp>
#include <iostream>
#include <iomanip>
//]
//[refltool_example_member_cmp_2
struct Point
{
	int x, y, z;
};

struct Triangle
{
	Point a, b, c;
};
//]
//[refltool_example_member_cmp_3
// Point
bool operator == (const Point& a, const Point& b)
{ return refltool::__data_members_equal(a, b); }

bool operator <  (const Point& a, const Point& b)
{ return refltool::__data_members_less(a, b); }

// Triangle
bool operator == (const Triangle& a, const Triangle& b)
{ return refltool::data_members_equal(a, b); }

bool operator <  (const Triangle& a, const Triangle& b)
{ return refltool::data_members_less(a, b); }
//]
//[refltool_example_member_cmp_4
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
//]
//[refltool_example_member_cmp_output
// TODO
//]
