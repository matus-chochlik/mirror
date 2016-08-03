/**
 *  .file test/mire/mirror/named_typedef.cpp
 *  .brief Test case for compile-time named_typedef meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_MIRROR_named_typedef
#include <boost/test/unit_test.hpp>

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/named_typedef.hpp>
#include <mire/reg/std/string.hpp>
#include <mire/reg/native.hpp>

BOOST_AUTO_TEST_SUITE(mire_mirror_named_typedef)

struct mire_mirror_named_typedef_test1_type { };

BOOST_AUTO_TEST_CASE(mire_mirror_named_typedef_test1)
{
	using namespace mire;
	using namespace mire::mirror;

	typedef named_typedef<
		mirrored_t<int>,
		mire_mirror_named_typedef_test1_type
	>::type t1;

	BOOST_CHECK((std::is_same<
		t1::int_,
		mire_mirror_named_typedef_test1_type
	>::value));

	typedef named_typedef<
		mirrored_t<float>,
		mire_mirror_named_typedef_test1_type
	>::type t2;

	BOOST_CHECK((std::is_same<
		t2::float_,
		mire_mirror_named_typedef_test1_type
	>::value));

	typedef named_typedef<
		mirrored_t<decltype(1ull)>,
		mire_mirror_named_typedef_test1_type
	>::type t3;

	BOOST_CHECK((std::is_same<
		t3::unsigned_long_long_int_,
		mire_mirror_named_typedef_test1_type
	>::value));
}

struct mire_mirror_named_typedef_test2_type { };

BOOST_AUTO_TEST_CASE(mire_mirror_named_typedef_test2)
{
	using namespace mire;
	using namespace mire::mirror;

	typedef named_typedef<
		mirrored_t<std::string>,
		mire_mirror_named_typedef_test2_type
	>::type t1;

	BOOST_CHECK((std::is_same<
		t1::string,
		mire_mirror_named_typedef_test2_type
	>::value));

	typedef named_typedef<
		mirrored_t<std::wstring>,
		mire_mirror_named_typedef_test2_type
	>::type t2;

	BOOST_CHECK((std::is_same<
		t2::basic_string,
		mire_mirror_named_typedef_test2_type
	>::value));
}


BOOST_AUTO_TEST_CASE(mire_mirror_named_typedef_test3)
{
	using namespace mire;
	using namespace mire::mirror;

	struct test
	 : named_typedef<mirrored_t<void>, void>::type
	 , named_typedef<mirrored_t<bool>, bool>::type
	 , named_typedef<mirrored_t<char>, char>::type
	 , named_typedef<mirrored_t<short>, short>::type
	 , named_typedef<mirrored_t<int>, int>::type
	 , named_typedef<mirrored_t<long>, long>::type
	 , named_typedef<mirrored_t<double>, double>::type
	 , named_typedef<mirrored_t<std::string>, std::string>::type
	{ };

	BOOST_CHECK((std::is_same<test::void_, void>::value));
	BOOST_CHECK((std::is_same<test::bool_, bool>::value));
	BOOST_CHECK((std::is_same<test::char_, char>::value));
	BOOST_CHECK((std::is_same<test::short_int_, short>::value));
	BOOST_CHECK((std::is_same<test::int_, int>::value));
	BOOST_CHECK((std::is_same<test::long_int_, long>::value));
	BOOST_CHECK((std::is_same<test::double_, double>::value));
	BOOST_CHECK((std::is_same<test::string, std::string>::value));
}

BOOST_AUTO_TEST_SUITE_END()

