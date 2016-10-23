/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[refltool_example_member_hash_1
#include <refltool/data_member_cmp.hpp>
#include <refltool/hash_data_members.hpp>
#include <unordered_set>
#include <iostream>
//]
//[refltool_example_member_hash_2
struct Point
{
	int x, y, z;
};

bool operator == (const Point& a, const Point& b)
{ return refltool::__data_members_equal(a, b); }

namespace std {

template <>
struct hash<Point>
{
	std::size_t operator()(const Point& p) const
	{ return refltool::__hash_data_members(p); }
};

} // namespace std
//]
//[refltool_example_member_hash_3
struct Triangle
{
	Point a, b, c;
};

bool operator == (const Triangle& a, const Triangle& b)
{ return refltool::__data_members_equal(a, b); }

namespace std {

template <>
struct hash<Triangle>
{
	std::size_t operator()(const Triangle& t) const
	{ return refltool::__hash_data_members(t); }
};

} // namespace std
//]
//[refltool_example_member_hash_4
int main(void)
{
	Point i{1,0,0}, j{0,1,0}, k{0,0,1}, l{1,1,1};

	std::unordered_set<Triangle> s;
	s.insert(Triangle{i,j,k}); /*<
	We insert 14 different instances of [^Triangle] which (should) have
	14 different hashes.
	>*/
	s.insert(Triangle{i,k,j});
	s.insert(Triangle{i,l,k});
	s.insert(Triangle{j,k,l});
	s.insert(Triangle{j,i,k});
	s.insert(Triangle{j,l,k});
	s.insert(Triangle{j,k,i});
	s.insert(Triangle{k,l,j});
	s.insert(Triangle{k,j,i});
	s.insert(Triangle{k,i,j});
	s.insert(Triangle{l,k,i});
	s.insert(Triangle{l,j,i});
	s.insert(Triangle{l,j,k});
	s.insert(Triangle{l,i,j});

	std::cout << s.size() << std::endl;

	return 0;
}
//]
//[refltool_example_member_hash_output
14
//]
