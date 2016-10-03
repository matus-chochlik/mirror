/**
 *  .file test/mire/ct/instead.cpp
 *  .brief Test case for compile-time instead meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_instead
#include <boost/test/unit_test.hpp>

#include <mire/ct/instead.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_instead)

BOOST_AUTO_TEST_CASE(mire_ct_instead_range)
{
	using namespace mire::ct;

	BOOST_CHECK((equal_types<instead<bool, void>, void>::value == true));
	BOOST_CHECK((equal_types<instead<char, void>, void>::value == true));
	BOOST_CHECK((equal_types<instead<void, char>, char>::value == true));
	BOOST_CHECK((equal_types<instead<void, long>, long>::value == true));
	BOOST_CHECK((equal_types<instead<float, float>, float>::value == true));
	BOOST_CHECK((equal_types<instead<double, float>, short>::value != true));
	BOOST_CHECK((equal_types<instead<unsigned, int>, wchar_t>::value != true));
}

BOOST_AUTO_TEST_CASE(mire_ct_instead_string)
{
	using namespace mire::ct;

	BOOST_CHECK((instead_c<char, 'A', 'X'>::value == 'X'));
	BOOST_CHECK((instead_c<char, 'B', 'X'>::value == 'X'));
	BOOST_CHECK((instead_c<char, 'C', 'X'>::value == 'X'));
	BOOST_CHECK((instead_c<char, 'X', 'A'>::value == 'A'));
	BOOST_CHECK((instead_c<char, 'X', 'B'>::value == 'B'));
	BOOST_CHECK((instead_c<char, 'X', 'C'>::value == 'C'));
	BOOST_CHECK((instead_c<char, 'A', 'A'>::value == 'A'));
	BOOST_CHECK((instead_c<char, 'B', 'B'>::value == 'B'));
	BOOST_CHECK((instead_c<char, 'C', 'C'>::value == 'C'));
	BOOST_CHECK((instead_c<char, 'A', 'B'>::value != 'C'));
	BOOST_CHECK((instead_c<char, 'C', 'D'>::value != 'C'));
}

BOOST_AUTO_TEST_SUITE_END()

