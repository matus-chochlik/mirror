/**
 *  .file test/mire/mirror/typedef_type.cpp
 *  .brief Test case for compile-time typedef_type meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_MIRROR_typedef_type
#include <boost/test/unit_test.hpp>

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/typedef_type.hpp>
#include <mire/mirror/full_name.hpp>
#include <mire/mirror/compare.hpp>
#include <mire/mirror/original_type.hpp>

#include <mire/ct/c_str.hpp>

#include <mire/reg/native.hpp>
#include <mire/reg/std/string.hpp>
#include <mire/reg/std/wstring.hpp>

#include <type_traits>
#include <cctype>

BOOST_AUTO_TEST_SUITE(mire_mirror_typedef_type)

bool mire_mirror_name_equal(const char* s1, const char* s2)
{
	assert(s1 && s2);
	while(true)
	{
		while(*s1 && std::isspace(*s1)) ++s1;
		while(*s2 && std::isspace(*s2)) ++s2;

		if(!*s1) break;
		if(!*s2) break;

		if(*s1++ != *s2++) return false;
	}
	return (!*s1) && (!*s2);
}

BOOST_AUTO_TEST_CASE(mire_mirror_typedef_type_test1)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK((!equal<
		typedef_type<mirrored_t<std::string>>,
		mirrored_t<std::string>
	>::value));

	BOOST_CHECK((nonequal<
		typedef_type<mirrored_t<std::wstring>>,
		mirrored_t<std::wstring>
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<typedef_type<mirrored_t<std::string>>>::type,
		original_type<mirrored_t<std::string>>::type
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<typedef_type<mirrored_t<std::wstring>>>::type,
		original_type<mirrored_t<std::wstring>>::type
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_mirror_typedef_type_test2)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<
			mirrored_t<std::string>
		>>::value,
		"std::string"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<typedef_type<
			mirrored_t<std::string>
		>>>::value,
		"std::basic_string<char, std::char_traits<char>, std::allocator<char>>"
	));
}

BOOST_AUTO_TEST_CASE(mire_mirror_typedef_type_test3)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<
			mirrored_t<std::wstring>
		>>::value,
		"std::wstring"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<typedef_type<
			mirrored_t<std::wstring>
		>>>::value,
		"std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>"
	));
}
// TODO

BOOST_AUTO_TEST_SUITE_END()

