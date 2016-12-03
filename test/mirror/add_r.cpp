/**
 *  .file test/mirror/add_r.cpp
 *  .brief Test case for compile-time add operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_add
#include <boost/test/unit_test.hpp>

#include <mirror/add.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_add)

BOOST_AUTO_TEST_CASE(mirror_add_1)
{
	using namespace mirror;

	using i0 = int_const<int, 0>;
	using i1 = int_const<int, 1>;
	using i2 = int_const<int, 2>;
	using i3 = int_const<int, 3>;
	using i4 = int_const<int, 4>;
	using i5 = int_const<int, 5>;
	using i6 = int_const<int, 6>;
	using i7 = int_const<int, 7>;
	using i8 = int_const<int, 8>;
	using i9 = int_const<int, 9>;

	BOOST_CHECK_EQUAL((value<add<i0>>), 0);
	BOOST_CHECK_EQUAL((value<add<i5>>), 5);

	BOOST_CHECK_EQUAL((value<add<i1,i2>>), 3);
	BOOST_CHECK_EQUAL((value<add<i3,i4>>), 7);
	BOOST_CHECK_EQUAL((value<add<i6,i7>>), 13);

	BOOST_CHECK_EQUAL((value<add<i2,i3,i4>>), 9);
	BOOST_CHECK_EQUAL((value<add<i7,i8,i9>>), 24);

	BOOST_CHECK_EQUAL((value<add<i1,i3,i5,i7>>), 16);
	BOOST_CHECK_EQUAL((value<add<i2,i4,i6,i8>>), 20);

	BOOST_CHECK_EQUAL((value<add<i0,i2,i4,i6,i8>>), 20);
	BOOST_CHECK_EQUAL((value<add<i0,i1,i2,i3,i4,i5,i6,i7,i8,i9>>), 45);
}

BOOST_AUTO_TEST_CASE(mirror_add_2)
{
	using namespace mirror;

	using i0 = int_const<int, 0>;
	using i1 = int_const<int, 1>;
	using i2 = int_const<int, 2>;
	using i3 = int_const<int, 3>;
	using i4 = int_const<int, 4>;
	using i5 = int_const<int, 5>;
	using i6 = int_const<int, 6>;
	using i7 = int_const<int, 7>;
	using i8 = int_const<int, 8>;
	using i9 = int_const<int, 9>;

	BOOST_CHECK_EQUAL((value<
		add<add<i0,i1>,add<add<i2,i3>,add<i4,i5,i6>,i7,add<i8>>,i9>
	>), 45);

}

BOOST_AUTO_TEST_SUITE_END()

