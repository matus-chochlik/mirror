/**
 *  .file test/mire/mirror/full_name.cpp
 *  .brief Test case for compile-time full_name meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_MIRROR_full_name
#include <boost/test/unit_test.hpp>

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/full_name.hpp>
#include <mire/ct/c_str.hpp>
#include <mire/reg/native.hpp>
#include <mire/reg/std/pair.hpp>
#include <mire/reg/std/basic_string.hpp>

#include <cctype>

BOOST_AUTO_TEST_SUITE(mire_mirror_full_name)

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

BOOST_AUTO_TEST_CASE(mire_mirror_full_name_test1)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<char>>>::value,
		"char"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<char*>>>::value,
		"char*"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int&>>>::value,
		"int&"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<float&&>>>::value,
		"float&&"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<char const>>>::value,
		"char const"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<char const*>>>::value,
		"char const *"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int volatile>>>::value,
		"int volatile"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<long const volatile>>>::value,
		"long int const volatile"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<unsigned volatile const>>>::value,
		"unsigned int const volatile"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int**>>>::value,
		"int**"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<long long const * const>>>::value,
		"long long int const * const"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<long long volatile * const *>>>::value,
		"long long int volatile * const *"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<long double const * volatile * &>>>::value,
		"long double const * volatile * &"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<long volatile * volatile * &&>>>::value,
		"long int volatile * volatile * &&"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int const * const * const>>>::value,
		"int const * const * const "
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int const * const * const *>>>::value,
		"int const * const * const *"
	));
}

BOOST_AUTO_TEST_CASE(mire_mirror_full_name_test2)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int*>>>::value,
		"int*"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int**>>>::value,
		"int**"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int***>>>::value,
		"int***"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int****>>>::value,
		"int****"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int*****>>>::value,
		"int*****"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int******>>>::value,
		"int******"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int*******>>>::value,
		"int*******"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int********>>>::value,
		"int********"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int*********>>>::value,
		"int*********"
	));
}

BOOST_AUTO_TEST_CASE(mire_mirror_full_name_test3)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int[]>>>::value,
		"int[]"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int[9]>>>::value,
		"int[9]"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int[][9]>>>::value,
		"int[][9]"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int[9][8]>>>::value,
		"int[9][8]"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int[9][8][7]>>>::value,
		"int[9][8][7]"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int[9][8][7][6]>>>::value,
		"int[9][8][7][6]"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int[9][8][7][6][5]>>>::value,
		"int[9][8][7][6][5]"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int[9][8][7][6][5][4]>>>::value,
		"int[9][8][7][6][5][4]"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int[9][8][7][6][5][4][3]>>>::value,
		"int[9][8][7][6][5][4][3]"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int[9][8][7][6][5][4][3][2]>>>::value,
		"int[9][8][7][6][5][4][3][2]"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int[9][8][7][6][5][4][3][2][1]>>>::value,
		"int[9][8][7][6][5][4][3][2][1]"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int[][9][8][7][6][5][4][3][2][1]>>>::value,
		"int[][9][8][7][6][5][4][3][2][1]"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int const *[]>>>::value,
		"int const * []"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<char const * [12345]>>>::value,
		"char const * [12345]"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<volatile int * [][100]>>>::value,
		"int volatile * [][100]"
	));
}

BOOST_AUTO_TEST_CASE(mire_mirror_full_name_test4)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<void(void)>>>::value,
		"void(void)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<int(void)>>>::value,
		"int(void)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<const char*(void)>>>::value,
		"char const*(void)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<volatile unsigned long &(void)>>>::value,
		"unsigned long int volatile&(void)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<double&(void)>>>::value,
		"double&(void)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<void(int)>>>::value,
		"void(int)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<bool(int)>>>::value,
		"bool(int)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<double&(bool, double&, double&)>>>::value,
		"double&(bool, double&, double&)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<wchar_t*(*)(void)>>>::value,
		"wchar_t* (*)(void)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<const char* (**)(bool, const float&, short*)>>>::value,
		"char const * (**)(bool, float const&, short int*)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<const char** (*)(bool, const float&, short*)>>>::value,
		"char const ** (*)(bool, float const&, short int*)"
	));
}

BOOST_AUTO_TEST_CASE(mire_mirror_full_name_test5)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
		float(long)
		>>>::value,
		"float(long int)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
		float(*)(long int)
		>>>::value,
		"float(*)(long int)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
		float(*(*)(unsigned int))(long int)
		>>>::value,
		"float(*(*)(unsigned int))(long int)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
		float(*(*(*)(int))(unsigned int))(long int)
		>>>::value,
		"float(*(*(*)(int))(unsigned int))(long int)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
		float(*(*(*(*)(short int))(int))(unsigned int))(long int)
		>>>::value,
		"float(*(*(*(*)(short int))(int))(unsigned int))(long int)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
		float(*(*(*(*(*)(wchar_t))(short int))(int))(unsigned int))(long int)
		>>>::value,
		"float(*(*(*(*(*)(wchar_t))(short int))(int))(unsigned int))(long int)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
		float(*(*(*(*(*(*)(char))(wchar_t))(short int))(int))(unsigned int))(long int)
		>>>::value,
		"float(*(*(*(*(*(*)(char))(wchar_t))(short int))(int))(unsigned int))(long int)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
		float(*(*(*(*(*(*(*)(bool))(char))(wchar_t))(short int))(int))(unsigned int))(long int)
		>>>::value,
		"float(*(*(*(*(*(*(*)(bool))(char))(wchar_t))(short int))(int))(unsigned int))(long int)"
	));
}

BOOST_AUTO_TEST_CASE(mire_mirror_full_name_test6)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
		float(*(*)(void))(void)
		>>>::value,
		"float(*(*)(void))(void)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
		float(*(*)(int, bool, float))(void)
		>>>::value,
		"float(*(*)(int, bool, float))(void)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
		float(*(*)(int, bool, float))(int)
		>>>::value,
		"float(*(*)(int, bool, float))(int)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
		float(*(*)(float))(double, char, int, bool)
		>>>::value,
		"float(*(*)(float))(double, char, int, bool)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
		float(*(*)(void))(double, char, int, bool)
		>>>::value,
		"float(*(*)(void))(double, char, int, bool)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
		float(*(*)(int, float))(double, char, int)
		>>>::value,
		"float(*(*)(int, float))(double, char, int)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
		float(*(*)(int, bool, float))(double, char, int)
		>>>::value,
		"float(*(*)(int, bool, float))(double, char, int)"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
		std::string(*(*)(std::pair<long,std::string>))(std::pair<char, int>)
		>>>::value,
		"std::basic_string<char, std::char_traits<char>, std::allocator<char>>"
		"(*(*)(std::pair<long int,std::basic_string<char, std::char_traits<char>, std::allocator<char>>>))"
		"(std::pair<char, int>)"
	));
}

BOOST_AUTO_TEST_CASE(mire_mirror_full_name_test7)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
			std::string
		>>>::value,
		"std::basic_string<char, std::char_traits<char>, std::allocator<char>>"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
			std::string*
		>>>::value,
		"std::basic_string<char, std::char_traits<char>, std::allocator<char>>*"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
			std::wstring
		>>>::value,
		"std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
			std::pair<std::string, std::wstring>
		>>>::value,
		"std::pair<"
		"  std::basic_string<char, std::char_traits<char>, std::allocator<char>>,"
		"  std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>"
		">"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
			std::pair<std::string * const, std::string const *>
		>>>::value,
		"std::pair<"
		"  std::basic_string<char, std::char_traits<char>, std::allocator<char>> * const,"
		"  std::basic_string<char, std::char_traits<char>, std::allocator<char>> const * "
		">"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
			const std::pair<std::string * const *, std::string const * *> * [10][9]
		>>>::value,
		"std::pair<"
		"  std::basic_string<char, std::char_traits<char>, std::allocator<char>> * const *,"
		"  std::basic_string<char, std::char_traits<char>, std::allocator<char>> const * *"
		"> const * [10][9]"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
			const std::pair<
				std::pair<long volatile, std::string * const *>,
				std::pair<std::string, long double const * volatile *>
			> & (std::pair<std::string, std::wstring> &&)
		>>>::value,
		"std::pair<"
		"  std::pair<"
		"    long int volatile,"
		"    std::basic_string<char, std::char_traits<char>, std::allocator<char>> * const *"
		"  >,"
		"  std::pair<"
		"    std::basic_string<char, std::char_traits<char>, std::allocator<char>>,"
		"    long double const * volatile *"
		"  >"
		"> const & (std::pair<"
		"    std::basic_string<char, std::char_traits<char>, std::allocator<char>>,"
		"    std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>"
		">&&)"
	));
}

BOOST_AUTO_TEST_SUITE_END()

