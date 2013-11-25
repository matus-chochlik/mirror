/**
 *  .file test/mire/mirror/traits.cpp
 *  .brief Test case for mirror compile-time metaobject traits
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_MIRROR_traits
#include <boost/test/unit_test.hpp>

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/traits.hpp>
#include <mire/reg/native.hpp>

BOOST_AUTO_TEST_SUITE(mire_mirror_traits)

BOOST_AUTO_TEST_CASE(mire_mirror_traits_is_metaobject)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK((!is_metaobject<int>::value));
	BOOST_CHECK(( is_metaobject<mirrored_t<int>>::value));
}

BOOST_AUTO_TEST_CASE(mire_mirror_traits_has_name)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK((!has_name<int>::value));
	BOOST_CHECK(( has_name<mirrored_t<int>>::value));
}

BOOST_AUTO_TEST_CASE(mire_mirror_traits_has_scope)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK((!has_scope<int>::value));
	BOOST_CHECK(( has_scope<mirrored_t<int>>::value));
}

BOOST_AUTO_TEST_CASE(mire_mirror_traits_is_scope)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK((!is_scope<int>::value));
	BOOST_CHECK((!is_scope<mirrored_t<int>>::value));
	BOOST_CHECK(( is_scope<MIRRORED_GLOBAL_SCOPE()>::value));
}

//TODO

BOOST_AUTO_TEST_SUITE_END()

