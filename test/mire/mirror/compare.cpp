/**
 *  .file test/mire/mirror/compare.cpp
 *  .brief Test case for compile-time compare meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_MIRROR_compare
#include <boost/test/unit_test.hpp>

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/compare.hpp>
#include <mire/reg/std/string.hpp>
#include <mire/reg/native.hpp>

BOOST_AUTO_TEST_SUITE(mire_mirror_compare)


BOOST_AUTO_TEST_CASE(mire_mirror_compare_test1)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK((equal<
		MIRRORED_GLOBAL_SCOPE(),
		MIRRORED_GLOBAL_SCOPE()
	>::value));

	BOOST_CHECK((equal<
		mirrored_t<void>,
		mirrored_t<void>
	>::value));

	BOOST_CHECK((!equal<
		mirrored_t<void>,
		mirrored_t<long>
	>::value));

	BOOST_CHECK((nonequal<
		mirrored_t<void>,
		mirrored_t<long>
	>::value));

	BOOST_CHECK((!nonequal<
		mirrored_t<long>,
		mirrored_t<long>
	>::value));

	BOOST_CHECK((equal<
		MIRRORED(std),
		MIRRORED(std)
	>()));

	BOOST_CHECK((!nonequal<
		MIRRORED(std),
		MIRRORED(std)
	>()));

	BOOST_CHECK((equal<
		mirrored_t<std::string>,
		mirrored_t<std::string>
	>()));

	BOOST_CHECK((nonequal<
		mirrored_t<std::string>,
		mirrored_t<std::wstring>
	>()));

	BOOST_CHECK((!nonequal<
		mirrored_t<std::string>,
		mirrored_t<std::string>
	>()));

	BOOST_CHECK((!equal<
		mirrored_t<std::string>,
		mirrored_t<std::wstring>
	>()));
}

BOOST_AUTO_TEST_SUITE_END()

