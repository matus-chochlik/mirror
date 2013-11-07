/**
 *  .file test/mire/ct/basic.cpp
 *  .brief Test case for compile-time strings
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_string
#include <boost/test/unit_test.hpp>

#include <mire/ct/string.hpp>
#include <cstring>
#include <cwchar>

BOOST_AUTO_TEST_SUITE(mire_ct_string)

BOOST_AUTO_TEST_CASE(mire_ct_string_test1)
{
	using namespace mire;
	typedef ct::basic_string<wchar_t, L't',L'e',L's',L't',L'1'> wtest;
	typedef ct::basic_string<char, 't','e','s','t','2'> btest;
	typedef ct::string<'t','e','s','t','3'> test;
	typedef ct::empty_string es;

	BOOST_CHECK(std::wcscmp(wtest::c_str,L"test1") == 0);
	BOOST_CHECK(std::strcmp(btest::c_str, "test2") == 0);
	BOOST_CHECK(std::strcmp( test::c_str, "test3") == 0);
	BOOST_CHECK(std::strcmp(es::c_str, "") == 0);

	BOOST_CHECK(wtest::size == 5);
	BOOST_CHECK(btest::size == 5);
	BOOST_CHECK( test::size == 5);
	BOOST_CHECK(es::size == 0);
}

BOOST_AUTO_TEST_CASE(mire_ct_string_test2)
{
	using namespace mire::ct;

	BOOST_CHECK((string<>::size == 0));
	BOOST_CHECK((string<'A'>::size == 1));
	BOOST_CHECK((string<'A','B'>::size == 2));
	BOOST_CHECK((string<'A','B','C'>::size == 3));
	BOOST_CHECK((string<'A','B','C','D'>::size == 4));
	BOOST_CHECK((string<'A','B','C','D','E'>::size == 5));
	BOOST_CHECK((string<'A','B','C','D','E','F'>::size == 6));
	BOOST_CHECK((string<'A','B','C','D','E','F','G'>::size == 7));
	BOOST_CHECK((string<'A','B','C','D','E','F','G','H'>::size == 8));
	BOOST_CHECK((string<'A','B','C','D','E','F','G','H','I'>::size == 9));
}

BOOST_AUTO_TEST_CASE(mire_ct_string_test3)
{
	using namespace mire::ct;

	BOOST_CHECK(std::strcmp(string<>::c_str, "") == 0);
	BOOST_CHECK(std::strcmp(string<'A'>::c_str, "A") == 0);
	BOOST_CHECK(std::strcmp(string<'A','B'>::c_str, "AB") == 0);
	BOOST_CHECK(std::strcmp(string<'A','B','C'>::c_str, "ABC") == 0);
	BOOST_CHECK(std::strcmp(string<'A','B','C','D'>::c_str, "ABCD") == 0);
	BOOST_CHECK(std::strcmp(string<'A','B','C','D','E'>::c_str, "ABCDE") == 0);
	BOOST_CHECK(std::strcmp(string<'A','B','C','D','E','F'>::c_str, "ABCDEF") == 0);
}

BOOST_AUTO_TEST_SUITE_END()

