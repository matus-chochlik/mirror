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
	typedef ct::string<'A','B','C','D','E','F','G','H','I'> abcdefghi;
	typedef ct::empty_string es;
	typedef ct::basic_string<int, 0,1,2,3,4,5,6,7,8,9> _0123456789;
}

BOOST_AUTO_TEST_SUITE_END()

