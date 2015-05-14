/**
 *  .file test/mire/mirror/base_name.cpp
 *  .brief Test case for compile-time base_name meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_MIRROR_base_name
#include <boost/test/unit_test.hpp>

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/base_name.hpp>
#include <mire/ct/c_str.hpp>
#include <mire/reg/native.hpp>

#include <cctype>

BOOST_AUTO_TEST_SUITE(mire_mirror_base_name)

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

BOOST_AUTO_TEST_CASE(mire_mirror_base_name_test1)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<char>>>::value,
		"char"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<char*>>>::value,
		"char"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int&>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<float&&>>>::value,
		"float"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<char const>>>::value,
		"char"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<char const*>>>::value,
		"char"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int volatile>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<long const volatile>>>::value,
		"long int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<unsigned volatile const>>>::value,
		"unsigned int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int**>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<long long const * const>>>::value,
		"long long int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<long long volatile * const *>>>::value,
		"long long int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<long double const * volatile * &>>>::value,
		"long double"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<long volatile * volatile * &&>>>::value,
		"long int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int const * const * const>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int const * const * const *>>>::value,
		"int"
	));
}

BOOST_AUTO_TEST_CASE(mire_mirror_base_name_test2)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int*>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int**>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int***>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int****>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int*****>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int******>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int*******>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int********>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int*********>>>::value,
		"int"
	));
}

BOOST_AUTO_TEST_CASE(mire_mirror_base_name_test3)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int[]>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int[9]>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int[][9]>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int[9][8]>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int[9][8][7]>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int[9][8][7][6]>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int[9][8][7][6][5]>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int[9][8][7][6][5][4]>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int[9][8][7][6][5][4][3]>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int[9][8][7][6][5][4][3][2]>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int[9][8][7][6][5][4][3][2][1]>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int[][9][8][7][6][5][4][3][2][1]>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int const *[]>>>::value,
		"int"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<char const * [12345]>>>::value,
		"char"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<volatile int * [][100]>>>::value,
		"int"
	));
}

BOOST_AUTO_TEST_CASE(mire_mirror_base_name_test4)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<void(void)>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<int(void)>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<const char*(void)>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<volatile unsigned long &(void)>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<double&(void)>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<void(int)>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<bool(int)>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<double&(bool, double&, double&)>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<wchar_t*(*)(void)>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<const char* (**)(bool, const float&, short*)>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<const char** (*)(bool, const float&, short*)>>>::value,
		""
	));
}

BOOST_AUTO_TEST_CASE(mire_mirror_base_name_test5)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<
		float(long)
		>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<
		float(*)(long int)
		>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<
		float(*(*)(unsigned int))(long int)
		>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<
		float(*(*(*)(int))(unsigned int))(long int)
		>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<
		float(*(*(*(*)(short int))(int))(unsigned int))(long int)
		>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<
		float(*(*(*(*(*)(wchar_t))(short int))(int))(unsigned int))(long int)
		>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<
		float(*(*(*(*(*(*)(char))(wchar_t))(short int))(int))(unsigned int))(long int)
		>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<
		float(*(*(*(*(*(*(*)(bool))(char))(wchar_t))(short int))(int))(unsigned int))(long int)
		>>>::value,
		""
	));
}

BOOST_AUTO_TEST_CASE(mire_mirror_base_name_test6)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<
		float(*(*)(void))(void)
		>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<
		float(*(*)(int, bool, float))(void)
		>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<
		float(*(*)(int, bool, float))(int)
		>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<
		float(*(*)(float))(double, char, int, bool)
		>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<
		float(*(*)(void))(double, char, int, bool)
		>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<
		float(*(*)(int, float))(double, char, int)
		>>>::value,
		""
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<
		float(*(*)(int, bool, float))(double, char, int)
		>>>::value,
		""
	));
}

BOOST_AUTO_TEST_SUITE_END()

