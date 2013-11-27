/**
 *  .file test/mire/mirror/original_type.cpp
 *  .brief Test case for compile-time original_type meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_MIRROR_original_type
#include <boost/test/unit_test.hpp>

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/original_type.hpp>
#include <mire/reg/native.hpp>

#include <type_traits>

BOOST_AUTO_TEST_SUITE(mire_mirror_original_type)


BOOST_AUTO_TEST_CASE(mire_mirror_original_type_test1)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK((std::is_same<
		original_type<mirrored_t<void>>::type,
		void
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<mirrored_t<char>>::type,
		char
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<mirrored_t<char*>>::type,
		char*
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<mirrored_t<long&>>::type,
		long&
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<mirrored_t<long const * &>>::type,
		long const * &
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<mirrored_t<long const * volatile &>>::type,
		long const * volatile &
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<mirrored_t<long[]>>::type,
		long[]
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<mirrored_t<long[9]>>::type,
		long[9]
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<mirrored_t<long[9][8][7][6][5][4][3][2][1]>>::type,
		long[9][8][7][6][5][4][3][2][1]
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<mirrored_t<long(void)>>::type,
		long(void)
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<mirrored_t<long(int, float, char)>>::type,
		long(int, float, char)
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<mirrored_t<long(*)(int, float, char)>>::type,
		long(*)(int, float, char)
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<mirrored_t<long(*(*)(double))(int, float, char)>>::type,
		long(*(*)(double))(int, float, char)
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

