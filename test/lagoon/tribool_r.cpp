/**
 *  .file test/lagoon/tribool_r.cpp
 *  .brief Test case for compile-time tribool operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE LAGOON_tribool
#include <boost/test/unit_test.hpp>

#include <lagoon/tribool.hpp>

BOOST_AUTO_TEST_SUITE(lagoon_tribool)

BOOST_AUTO_TEST_CASE(lagoon_tribool_1)
{
	using namespace lagoon;

	tribool f = false;
	tribool t = true;
	tribool n = none;
	tribool x;

	BOOST_CHECK( (f == f));
	BOOST_CHECK(!(f != f));
	BOOST_CHECK(!(f <  f));
	BOOST_CHECK(!is_none(f));

	BOOST_CHECK( (t == t));
	BOOST_CHECK(!(t != t));
	BOOST_CHECK(!(t <  t));
	BOOST_CHECK(!is_none(f));

	BOOST_CHECK(!(n == n));
	BOOST_CHECK(!(n != n));
	BOOST_CHECK(!(n <  n));
	BOOST_CHECK( is_none(n));

	BOOST_CHECK(!(x == x));
	BOOST_CHECK(!(x != x));
	BOOST_CHECK(!(x <  x));
	BOOST_CHECK( is_none(x));
}

BOOST_AUTO_TEST_CASE(lagoon_tribool_w1)
{
	using namespace lagoon;

	tribool tf = false;
	tribool tt = true;
	tribool tn = none;

	weak_bool f = ~tf;
	weak_bool t = ~tt;
	weak_bool n = ~tn;

	BOOST_CHECK( (f == f));
	BOOST_CHECK(!(f != f));
	BOOST_CHECK(!(f <  f));
	BOOST_CHECK(!is_none(f));

	BOOST_CHECK( (t == t));
	BOOST_CHECK(!(t != t));
	BOOST_CHECK(!(t <  t));
	BOOST_CHECK(!is_none(f));

	BOOST_CHECK( (n == n));
	BOOST_CHECK(!(n != n));
	BOOST_CHECK(!(n <  n));
	BOOST_CHECK( is_none(n));
}

BOOST_AUTO_TEST_CASE(lagoon_tribool_2)
{
	using namespace lagoon;

	tribool f = false;
	tribool t = true;
	tribool n = none;

	BOOST_CHECK(!(f == t));
	BOOST_CHECK(!(t == f));
	BOOST_CHECK( (f != t));
	BOOST_CHECK( (t != f));
	BOOST_CHECK((f < t) || (t < f));

	BOOST_CHECK(!(f == n));
	BOOST_CHECK(!(n == f));
	BOOST_CHECK(!(f != n));
	BOOST_CHECK(!(n != f));
	BOOST_CHECK((f < n) || (n < f));

	BOOST_CHECK(!(t == n));
	BOOST_CHECK(!(n == t));
	BOOST_CHECK(!(t != n));
	BOOST_CHECK(!(n != t));
	BOOST_CHECK((t < n) || (n < t));
}

BOOST_AUTO_TEST_CASE(lagoon_tribool_w2)
{
	using namespace lagoon;

	tribool tf = false;
	tribool tt = true;
	tribool tn = none;

	weak_bool f = ~tf;
	weak_bool t = ~tt;
	weak_bool n = ~tn;

	BOOST_CHECK(!(f == t));
	BOOST_CHECK(!(t == f));
	BOOST_CHECK( (f != t));
	BOOST_CHECK( (t != f));
	BOOST_CHECK((f < t) || (t < f));

	BOOST_CHECK(!(f == n));
	BOOST_CHECK(!(n == f));
	BOOST_CHECK( (f != n));
	BOOST_CHECK( (n != f));
	BOOST_CHECK((f < n) || (n < f));

	BOOST_CHECK(!(t == n));
	BOOST_CHECK(!(n == t));
	BOOST_CHECK( (t != n));
	BOOST_CHECK( (n != t));
	BOOST_CHECK((t < n) || (n < t));
}

BOOST_AUTO_TEST_CASE(lagoon_tribool_and)
{
	using namespace lagoon;

	tribool f = false;
	tribool t = true;
	tribool n = none;

	BOOST_CHECK(!(f && f));
	BOOST_CHECK(!(f && t));
	BOOST_CHECK(!(t && f));
	BOOST_CHECK( (t && t));

	BOOST_CHECK(is_none(n && n));
	BOOST_CHECK(is_none(t && n));
	BOOST_CHECK(is_none(n && t));
	BOOST_CHECK(!(f && n));
	BOOST_CHECK(!(n && f));
}

BOOST_AUTO_TEST_CASE(lagoon_tribool_and_w)
{
	using namespace lagoon;

	tribool tf = false;
	tribool tt = true;
	tribool tn = none;

	weak_bool f = ~tf;
	weak_bool t = ~tt;
	weak_bool n = ~tn;

	BOOST_CHECK(!(f && f));
	BOOST_CHECK(!(tf&& f));
	BOOST_CHECK(!(f && t));
	BOOST_CHECK(!(tf&& t));
	BOOST_CHECK(!(t && f));
	BOOST_CHECK(!(tt&& f));
	BOOST_CHECK( (t && t));
	BOOST_CHECK( (tt&& t));

	BOOST_CHECK(is_none(n && n));
	BOOST_CHECK(is_none(t && n));
	BOOST_CHECK(is_none(n && t));
	BOOST_CHECK(!(f && n));
	BOOST_CHECK(!(n && f));
}

BOOST_AUTO_TEST_CASE(lagoon_tribool_or)
{
	using namespace lagoon;

	tribool f = false;
	tribool t = true;
	tribool n = none;

	BOOST_CHECK(!(f || f));
	BOOST_CHECK( (f || t));
	BOOST_CHECK( (t || f));
	BOOST_CHECK( (t || t));

	BOOST_CHECK(is_none(n || n));
	BOOST_CHECK(is_none(f || n));
	BOOST_CHECK(is_none(n || f));
	BOOST_CHECK( (t || n));
	BOOST_CHECK( (n || t));
}

BOOST_AUTO_TEST_CASE(lagoon_tribool_or_w)
{
	using namespace lagoon;

	tribool tf = false;
	tribool tt = true;
	tribool tn = none;

	weak_bool f = ~tf;
	weak_bool t = ~tt;
	weak_bool n = ~tn;

	BOOST_CHECK(!(f || f));
	BOOST_CHECK(!(tf|| f));
	BOOST_CHECK( (f || t));
	BOOST_CHECK( (tf|| t));
	BOOST_CHECK( (t || f));
	BOOST_CHECK( (tt|| f));
	BOOST_CHECK( (t || t));
	BOOST_CHECK( (tt|| t));

	BOOST_CHECK(is_none(n || n));
	BOOST_CHECK(is_none(f || n));
	BOOST_CHECK(is_none(n || f));
	BOOST_CHECK( (t || n));
	BOOST_CHECK( (n || t));
}

BOOST_AUTO_TEST_SUITE_END()

