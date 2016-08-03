/**
 *  .file test/mire/mirror/scope.cpp
 *  .brief Test case for compile-time scope meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_MIRROR_scope
#include <boost/test/unit_test.hpp>

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/scope.hpp>
#include <mire/mirror/compare.hpp>
#include <mire/reg/std/string.hpp>
#include <mire/reg/native.hpp>

BOOST_AUTO_TEST_SUITE(mire_mirror_scope)


BOOST_AUTO_TEST_CASE(mire_mirror_scope_test1)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK((equal<
		MIRRORED_GLOBAL_SCOPE(),
		MIRRORED_GLOBAL_SCOPE()
	>::value));

	BOOST_CHECK((equal<
		MIRRORED_GLOBAL_SCOPE(),
		scope<MIRRORED_GLOBAL_SCOPE()>
	>::value));

	BOOST_CHECK((equal<
		MIRRORED_GLOBAL_SCOPE(),
		scope<scope<MIRRORED_GLOBAL_SCOPE()>>
	>::value));

	BOOST_CHECK((equal<
		scope<mirrored_t<void>>,
		MIRRORED_GLOBAL_SCOPE()
	>::value));

	BOOST_CHECK((equal<
		scope<mirrored_t<void>>,
		scope<mirrored_t<long>>
	>::value));

	BOOST_CHECK((equal<
		scope<scope<mirrored_t<long>>>,
		scope<mirrored_t<long double>>
	>::value));

	BOOST_CHECK((equal<
		scope<MIRRORED(std)>,
		MIRRORED_GLOBAL_SCOPE()
	>::value));

	BOOST_CHECK((equal<
		scope<mirrored_t<std::string>>,
		MIRRORED(std)
	>::value));

	BOOST_CHECK((equal<
		scope<scope<mirrored_t<std::string>>>,
		MIRRORED_GLOBAL_SCOPE()
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

