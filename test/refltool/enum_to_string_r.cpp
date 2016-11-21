/**
 *  .file test/refltool/enum_to_string.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE REFLTOOL_enum_to_string
#include <boost/test/unit_test.hpp>

#include <refltool/enum_to_string.hpp>

BOOST_AUTO_TEST_SUITE(refltool_enum_to_string)

enum E { a, b, c, d, e, f };
enum class F { x, y, z };

BOOST_AUTO_TEST_CASE(refltool_enum_to_string_map)
{
	using namespace refltool;

	enum_to_string_map_t<E> m = make_enum_to_string_map<E>();

	BOOST_CHECK_EQUAL(m[a], "a");
	BOOST_CHECK_EQUAL(m[b], "b");
	BOOST_CHECK_EQUAL(m[c], "c");
	BOOST_CHECK_EQUAL(m[d], "d");
	BOOST_CHECK_EQUAL(m[e], "e");
	BOOST_CHECK_EQUAL(m[f], "f");
}

BOOST_AUTO_TEST_CASE(refltool_enum_to_string_E)
{
	using namespace refltool;

	BOOST_CHECK_EQUAL(enum_to_string(a), "a");
	BOOST_CHECK_EQUAL(enum_to_string(b), "b");
	BOOST_CHECK_EQUAL(enum_to_string(c), "c");
	BOOST_CHECK_EQUAL(enum_to_string(d), "d");
	BOOST_CHECK_EQUAL(enum_to_string(e), "e");
	BOOST_CHECK_EQUAL(enum_to_string(f), "f");
}

BOOST_AUTO_TEST_CASE(refltool_enum_to_string_F)
{
	using namespace refltool;

	BOOST_CHECK_EQUAL(enum_to_string(F::x), "x");
	BOOST_CHECK_EQUAL(enum_to_string(F::y), "y");
	BOOST_CHECK_EQUAL(enum_to_string(F::z), "z");
}

BOOST_AUTO_TEST_SUITE_END()

