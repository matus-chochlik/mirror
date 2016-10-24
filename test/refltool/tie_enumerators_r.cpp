/**
 *  .file test/refltool/tie_enumerators.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE REFLTOOL_tie_enumerators
#include <boost/test/unit_test.hpp>

#include <refltool/tie_enumerators.hpp>

BOOST_AUTO_TEST_SUITE(refltool_tie_enumerators)

enum E { a, b, c, d, e, f };
enum class F { x, y, z };

BOOST_AUTO_TEST_CASE(refltool_tie_enumerators_E)
{
	using namespace refltool;

	std::array<E, 6> te = tie_enumerators<E>();

	BOOST_CHECK(te[0] == a);
	BOOST_CHECK(te[1] == b);
	BOOST_CHECK(te[2] == c);
	BOOST_CHECK(te[3] == d);
	BOOST_CHECK(te[4] == e);
	BOOST_CHECK(te[5] == f);
}

BOOST_AUTO_TEST_CASE(refltool_tie_enumerators_F)
{
	using namespace refltool;

	std::array<F, 3> tf = tie_enumerators<F>();

	BOOST_CHECK(tf[0] == F::x);
	BOOST_CHECK(tf[1] == F::y);
	BOOST_CHECK(tf[2] == F::z);
}

// TODO

BOOST_AUTO_TEST_SUITE_END()

