/**
 *  .file test/mire/mirror/keyword.cpp
 *  .brief Test case for compile-time keyword meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_MIRROR_keyword
#include <boost/test/unit_test.hpp>

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/keyword.hpp>
#include <mire/ct/c_str.hpp>

#include <cstring>

BOOST_AUTO_TEST_SUITE(mire_mirror_keyword)

BOOST_AUTO_TEST_CASE(mire_mirror_keyword_test1)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(none)>>::value,
		""
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(extern)>>::value,
		"extern"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(static)>>::value,
		"static"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(mutable)>>::value,
		"mutable"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(register)>>::value,
		"register"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(thread_local)>>::value,
		"thread_local"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(constexpr)>>::value,
		"constexpr"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(const)>>::value,
		"const"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(virtual)>>::value,
		"virtual"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(override)>>::value,
		"override"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(private)>>::value,
		"private"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(protected)>>::value,
		"protected"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(public)>>::value,
		"public"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(class)>>::value,
		"class"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(struct)>>::value,
		"struct"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(union)>>::value,
		"union"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(enum)>>::value,
		"enum"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(enum_class)>>::value,
		"enum class"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(typedef)>>::value,
		"typedef"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(noexcept)>>::value,
		"noexcept"
	) == 0));

	BOOST_CHECK((std::strcmp(
		ct::c_str<keyword<MIRRORED_SPECIFIER(constexpr)>>::value,
		"constexpr"
	) == 0));
}

BOOST_AUTO_TEST_SUITE_END()

