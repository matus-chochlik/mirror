/**
 *  .file test/mire/mirror/elaborated_type.cpp
 *  .brief Test case for compile-time elaborated_type meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_MIRROR_elaborated_type
#include <boost/test/unit_test.hpp>

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/elaborated_type.hpp>
#include <mire/mirror/keyword.hpp>
#include <mire/mirror/compare.hpp>
#include <mire/ct/c_str.hpp>
#include <mire/reg/native.hpp>
#include <mire/reg/std/string.hpp>
#include <mire/reg/std/pair.hpp>

#include <cstring>

BOOST_AUTO_TEST_SUITE(mire_mirror_elaborated_type)

BOOST_AUTO_TEST_CASE(mire_mirror_elaborated_type_test1)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK((equal<
		elaborated_type<mirrored_t<double>>,
		MIRRORED_SPECIFIER(none)
	>::value));

	BOOST_CHECK((equal<
		elaborated_type<mirrored_t<std::string>>,
		MIRRORED_SPECIFIER(class)
	>::value));

	BOOST_CHECK((equal<
		elaborated_type<mirrored_t<std::pair<int, long>>>,
		MIRRORED_SPECIFIER(struct)
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_mirror_elaborated_type_test2)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<elaborated_type<mirrored_t<long>>>>::value,
		""
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<elaborated_type<mirrored_t<std::string>>>>::value,
		"class"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<elaborated_type<mirrored_t<std::pair<int, long>>>>>::value,
		"struct"
	) == 0));
}

BOOST_AUTO_TEST_SUITE_END()

