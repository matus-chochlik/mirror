/**
 *  .file test/mire/mirror/named_mem_var.cpp
 *  .brief Test case for compile-time named_mem_var meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_MIRROR_named_mem_var
#include <boost/test/unit_test.hpp>

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/named_mem_var.hpp>
#include <mire/reg/std/string.hpp>
#include <mire/reg/native.hpp>

BOOST_AUTO_TEST_SUITE(mire_mirror_named_mem_var)

BOOST_AUTO_TEST_CASE(mire_mirror_named_mem_var_test1)
{
	using namespace mire;
	using namespace mire::mirror;

	named_mem_var<mirrored_t<int>, int>::type t1(123);
	BOOST_CHECK((std::is_same<decltype(t1.int_), int>::value));
	BOOST_CHECK(t1.int_ == 123);

	named_mem_var<mirrored_t<unsigned>, unsigned>::type t2(2345u);
	BOOST_CHECK((std::is_same<decltype(t2.unsigned_int_), unsigned>::value));
	BOOST_CHECK(t2.unsigned_int_ == 2345u);

	named_mem_var<mirrored_t<double>, double>::type t3(456.789);
	BOOST_CHECK((std::is_same<decltype(t3.double_), double>::value));
	BOOST_CHECK(t3.double_ == 456.789);
}

BOOST_AUTO_TEST_CASE(mire_mirror_named_mem_var_test2)
{
	using namespace mire;
	using namespace mire::mirror;

	named_mem_var<mirrored_t<std::string>, std::string>::type t1("test");
	BOOST_CHECK((std::is_same<decltype(t1.string), std::string>::value));
	BOOST_CHECK(t1.string == "test");

	named_mem_var<mirrored_t<std::string>, std::string>::type t2(10, 'x');
	BOOST_CHECK((std::is_same<decltype(t2.string), std::string>::value));
	BOOST_CHECK(t2.string == "xxxxxxxxxx");

	named_mem_var<mirrored_t<std::string>, std::string>::type t3(
		t1.string.begin(),
		t1.string.end()
	);
	BOOST_CHECK((std::is_same<decltype(t3.string), std::string>::value));
	t3.string.append(t2.string.begin(), t2.string.end());
	BOOST_CHECK(t3.string == "testxxxxxxxxxx");
}


BOOST_AUTO_TEST_CASE(mire_mirror_named_mem_var_test3)
{
	using namespace mire;
	using namespace mire::mirror;

	struct test
	 : named_mem_var<mirrored_t<bool>, bool>::type
	 , named_mem_var<mirrored_t<char>, char>::type
	 , named_mem_var<mirrored_t<short>, short>::type
	 , named_mem_var<mirrored_t<long>, long>::type
	 , named_mem_var<mirrored_t<double>, double>::type
	 , named_mem_var<mirrored_t<std::string>, std::string>::type
	{
		test(bool b, char c, short s, long l, double d, const std::string& t)
		 : named_mem_var<mirrored_t<bool>, bool>::type(b)
		 , named_mem_var<mirrored_t<char>, char>::type(c)
		 , named_mem_var<mirrored_t<short>, short>::type(s)
		 , named_mem_var<mirrored_t<long>, long>::type(l)
		 , named_mem_var<mirrored_t<double>, double>::type(d)
		 , named_mem_var<mirrored_t<std::string>, std::string>::type(t.begin(), t.end())
		{ };
	};

	test t(false, '1', 23, 456, 78.9, "string");

	BOOST_CHECK(t.bool_ == false);
	BOOST_CHECK(t.char_ == '1');
	BOOST_CHECK(t.short_int_ == 23);
	BOOST_CHECK(t.long_int_ == 456);
	BOOST_CHECK(t.double_ == 78.9);
	BOOST_CHECK(t.string == "string");
}

BOOST_AUTO_TEST_SUITE_END()

