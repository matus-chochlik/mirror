/**
 *  .file test/refltool/string_to_enum.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE REFLTOOL_string_to_enum
#include <boost/test/unit_test.hpp>

#include <refltool/string_to_enum.hpp>

BOOST_AUTO_TEST_SUITE(refltool_string_to_enum)

enum E { a, b, c, d, e, f };
enum class F { x, y, z };

BOOST_AUTO_TEST_CASE(refltool_string_to_enum_map)
{
	using namespace refltool;

	string_to_enum_map_t<E> m = make_string_to_enum_map<E>();

	BOOST_CHECK(m["a"] == a);
	BOOST_CHECK(m["b"] == b);
	BOOST_CHECK(m["c"] == c);
	BOOST_CHECK(m["d"] == d);
	BOOST_CHECK(m["e"] == e);
	BOOST_CHECK(m["f"] == f);
}

BOOST_AUTO_TEST_CASE(refltool_string_to_enum_E)
{
	using namespace refltool;

	BOOST_CHECK(string_to_enum<E>("a") == a);
	BOOST_CHECK(string_to_enum<E>("b") == b);
	BOOST_CHECK(string_to_enum<E>("c") == c);
	BOOST_CHECK(string_to_enum<E>("d") == d);
	BOOST_CHECK(string_to_enum<E>("e") == e);
	BOOST_CHECK(string_to_enum<E>("f") == f);
}

BOOST_AUTO_TEST_CASE(refltool_string_to_enum_F)
{
	using namespace refltool;

	BOOST_CHECK(string_to_enum<F>("x") == F::x);
	BOOST_CHECK(string_to_enum<F>("y") == F::y);
	BOOST_CHECK(string_to_enum<F>("z") == F::z);
}

BOOST_AUTO_TEST_SUITE_END()

