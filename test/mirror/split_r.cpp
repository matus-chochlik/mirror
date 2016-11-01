/**
 *  .file test/mirror/split_r.cpp
 *  .brief Test case for compile-time split operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_split
#include <boost/test/unit_test.hpp>

#include <mirror/split.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_split)

BOOST_AUTO_TEST_CASE(mirror_split_head_range_1)
{
	using namespace mirror;

	using r1 = range<void, bool, char, short, int, long, float, double>;

	BOOST_CHECK((value<equal<
		get_split_head<r1, empty_range>,
		empty_range
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<void>>,
		empty_range
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<bool>>,
		range<void>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<char>>,
		range<void, bool>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<short>>,
		range<void, bool, char>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<int>>,
		range<void, bool, char, short>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<long>>,
		range<void, bool, char, short, int>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<float>>,
		range<void, bool, char, short, int, long>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<double>>,
		range<void, bool, char, short, int, long, float>
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_split_head_range_2)
{
	using namespace mirror;

	using r1 = range<void, bool, char, short, int, long, float, double>;

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<void, bool>>,
		empty_range
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<void, bool, char>>,
		empty_range
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<void, bool, char, short>>,
		empty_range
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<void, bool, char, short, int>>,
		empty_range
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<void, bool, char, short, int, long>>,
		empty_range
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, r1>,
		empty_range
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_split_head_range_3)
{
	using namespace mirror;

	using r1 = range<void, bool, char, short, int, long, float, double>;

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<void, bool, void>>,
		r1
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<void, bool, char, void>>,
		r1
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<void, bool, char, short, void>>,
		r1
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<void, bool, char, short, int, void>>,
		r1
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<void, bool, char, short, void, int>>,
		r1
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<void, bool, void, char, short, int>>,
		r1
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<unsigned, wchar_t>>,
		r1
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_split_head_range_4)
{
	using namespace mirror;

	using r1 = range<void, bool, char, short, int, long, float, double>;

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<bool, char, short>>,
		range<void>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<char, short>>,
		range<void, bool>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<short, int, long, float>>,
		range<void, bool, char>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<int, long, float, double>>,
		range<void, bool, char, short>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<long, float, double>>,
		range<void, bool, char, short, int>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<r1, range<float, double>>,
		range<void, bool, char, short, int, long>
	>>));

}

BOOST_AUTO_TEST_CASE(mirror_split_tail_range_1)
{
	using namespace mirror;

	using r1 = range<void, bool, char, short, int, long, float, double>;

	BOOST_CHECK((value<equal<
		get_split_tail<r1, empty_range>,
		r1
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<void>>,
		r1
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<bool>>,
		range<bool, char, short, int, long, float, double>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<char>>,
		range<char, short, int, long, float, double>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<short>>,
		range<short, int, long, float, double>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<int>>,
		range<int, long, float, double>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<long>>,
		range<long, float, double>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<float>>,
		range<float, double>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<double>>,
		range<double>
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_split_tail_range_2)
{
	using namespace mirror;

	using r1 = range<void, bool, char, short, int, long, float, double>;

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<void, bool>>,
		r1
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<void, bool, char>>,
		r1
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<void, bool, char, short>>,
		r1
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<void, bool, char, short, int>>,
		r1
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<void, bool, char, short, int, long>>,
		r1
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, r1>,
		r1
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_split_tail_range_3)
{
	using namespace mirror;

	using r1 = range<void, bool, char, short, int, long, float, double>;

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<void, bool, void>>,
		empty_range
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<void, bool, char, void>>,
		empty_range
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<void, bool, char, short, void>>,
		empty_range
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<void, bool, char, short, int, void>>,
		empty_range
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<void, bool, char, short, void, int>>,
		empty_range
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<void, bool, void, char, short, int>>,
		empty_range
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<unsigned, wchar_t>>,
		empty_range
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_split_tail_range_4)
{
	using namespace mirror;

	using r1 = range<void, bool, char, short, int, long, float, double>;

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<bool, char, short>>,
		range<bool, char, short, int, long, float, double>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<char, short>>,
		range<char, short, int, long, float, double>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<short, int, long, float>>,
		range<short, int, long, float, double>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<int, long, float, double>>,
		range<int, long, float, double>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<long, float, double>>,
		range<long, float, double>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<r1, range<float, double>>,
		range<float, double>
	>>));

}

BOOST_AUTO_TEST_CASE(mirror_split_head_string_1)
{
	using namespace mirror;

	using s1 = string<'a','b','c','d','e','f','g','h'>;

	BOOST_CHECK((value<equal<
		get_split_head<s1, empty_string>,
		empty_string
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'a'>>,
		empty_string
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'b'>>,
		string<'a'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'c'>>,
		string<'a','b'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'d'>>,
		string<'a','b','c'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'e'>>,
		string<'a','b','c','d'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'f'>>,
		string<'a','b','c','d','e'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'g'>>,
		string<'a','b','c','d','e','f'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'h'>>,
		string<'a','b','c','d','e','f','g'>
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_split_head_string_2)
{
	using namespace mirror;

	using s1 = string<'a','b','c','d','e','f','g','h'>;

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'a','b'>>,
		empty_string
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'a','b','c'>>,
		empty_string
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'a','b','c','d'>>,
		empty_string
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'a','b','c','d','e'>>,
		empty_string
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'a','b','c','d','e','f'>>,
		empty_string
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'a','b','c','d','e','f','g'>>,
		empty_string
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'a','b','c','d','e','f','g','h'>>,
		empty_string
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_split_head_string_3)
{
	using namespace mirror;

	using s1 = string<'a','b','c','d','e','f','g','h'>;

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'b','x'>>,
		s1
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'b','c','x'>>,
		s1
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'c','d','e','x'>>,
		s1
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'d','e','f','g','h','x'>>,
		s1
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'e','f','x'>>,
		s1
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'f','g','h','x'>>,
		s1
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'h','x'>>,
		s1
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_split_head_string_4)
{
	using namespace mirror;

	using s1 = string<'a','b','c','d','e','f','g','h'>;

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'b','c'>>,
		string<'a'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'c','d','e','f','g'>>,
		string<'a','b'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'d','e','f','g','h'>>,
		string<'a','b','c'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'e'>>,
		string<'a','b','c','d'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'g','h'>>,
		string<'a','b','c','d','e','f'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_head<s1, string<'h'>>,
		string<'a','b','c','d','e','f','g'>
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_split_tail_string_1)
{
	using namespace mirror;

	using s1 = string<'a','b','c','d','e','f','g','h'>;

	BOOST_CHECK((value<equal<
		get_split_tail<s1, empty_string>,
		s1
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'a'>>,
		s1
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'b'>>,
		string<'b','c','d','e','f','g','h'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'c'>>,
		string<'c','d','e','f','g','h'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'d'>>,
		string<'d','e','f','g','h'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'e'>>,
		string<'e','f','g','h'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'f'>>,
		string<'f','g','h'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'g'>>,
		string<'g','h'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'h'>>,
		string<'h'>
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_split_tail_string_2)
{
	using namespace mirror;

	using s1 = string<'a','b','c','d','e','f','g','h'>;

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'a','b'>>,
		s1
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'a','b','c'>>,
		s1
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'a','b','c','d'>>,
		s1
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'a','b','c','d','e'>>,
		s1
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'a','b','c','d','e','f'>>,
		s1
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'a','b','c','d','e','f','g'>>,
		s1
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'a','b','c','d','e','f','g','h'>>,
		s1
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_split_tail_string_3)
{
	using namespace mirror;

	using s1 = string<'a','b','c','d','e','f','g','h'>;

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'b','x'>>,
		empty_string
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'b','c','x'>>,
		empty_string
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'c','d','e','x'>>,
		empty_string
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'d','e','f','g','h','x'>>,
		empty_string
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'e','f','x'>>,
		empty_string
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'f','g','h','x'>>,
		empty_string
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'h','x'>>,
		empty_string
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_split_tail_string_4)
{
	using namespace mirror;

	using s1 = string<'a','b','c','d','e','f','g','h'>;

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'b','c'>>,
		string<'b','c','d','e','f','g','h'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'c','d','e','f','g'>>,
		string<'c','d','e','f','g','h'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'d','e','f','g','h'>>,
		string<'d','e','f','g','h'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'e'>>,
		string<'e','f','g','h'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'g','h'>>,
		string<'g','h'>
	>>));

	BOOST_CHECK((value<equal<
		get_split_tail<s1, string<'h'>>,
		string<'h'>
	>>));
}

BOOST_AUTO_TEST_SUITE_END()

