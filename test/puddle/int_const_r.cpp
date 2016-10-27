/**
 *  .file test/puddle/int_const.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_int_const
#include <boost/test/unit_test.hpp>

#include <puddle/int_const.hpp>
#include <type_traits>
#include <sstream>

BOOST_AUTO_TEST_SUITE(puddle_int_const)

BOOST_AUTO_TEST_CASE(puddle_int_const_types)
{
	using namespace puddle;

	BOOST_CHECK(( std::is_same<
		decltype(bool_<0>)::value_type,
		bool
	>::value));
	BOOST_CHECK(( std::is_same<
		decltype(char_<0>)::value_type,
		char
	>::value));
	BOOST_CHECK(( std::is_same<
		decltype(int_<0>)::value_type,
		int
	>::value));
	BOOST_CHECK(( std::is_same<
		decltype(unsigned_<0>)::value_type,
		unsigned
	>::value));
}


BOOST_AUTO_TEST_CASE(puddle_int_const_bool_eq)
{
	using namespace puddle;

	BOOST_CHECK( value(bool_<true> == true_));
	BOOST_CHECK( value(bool_<false> == false_));
	BOOST_CHECK(!value(bool_<true> == false_));
	BOOST_CHECK(!value(bool_<false> == true_));
}

BOOST_AUTO_TEST_CASE(puddle_int_const_bool_ne)
{
	using namespace puddle;

	BOOST_CHECK(!value(bool_<true> != true_));
	BOOST_CHECK(!value(bool_<false> != false_));
	BOOST_CHECK( value(bool_<true> != false_));
	BOOST_CHECK( value(bool_<false> != true_));
}

BOOST_AUTO_TEST_CASE(puddle_int_const_char_eq)
{
	using namespace puddle;

	BOOST_CHECK( value(char_<'x'> == char_<'x'>));
	BOOST_CHECK( value(char_<'y'> == char_<'y'>));
	BOOST_CHECK(!value(char_<'x'> == char_<'y'>));
	BOOST_CHECK(!value(char_<'y'> == char_<'x'>));
}

BOOST_AUTO_TEST_CASE(puddle_int_const_char_ne)
{
	using namespace puddle;

	BOOST_CHECK(!value(char_<'x'> != char_<'x'>));
	BOOST_CHECK(!value(char_<'y'> != char_<'y'>));
	BOOST_CHECK( value(char_<'x'> != char_<'y'>));
	BOOST_CHECK( value(char_<'y'> != char_<'x'>));
}

BOOST_AUTO_TEST_CASE(puddle_int_const_int_eq1)
{
	using namespace puddle;

	BOOST_CHECK( value(int_<-1> == int_<-1>));
	BOOST_CHECK( value(int_<-23> == int_<-23>));
	BOOST_CHECK( value(int_<-456> == int_<-456>));
	BOOST_CHECK( value(int_<-7890> == int_<-7890>));

	BOOST_CHECK( value(int_<0> == int_<0>));
	BOOST_CHECK( value(int_<1> == int_<1>));
	BOOST_CHECK( value(int_<2> == int_<2>));
	BOOST_CHECK( value(int_<3> == int_<3>));
	BOOST_CHECK( value(int_<4> == int_<4>));
	BOOST_CHECK( value(int_<5> == int_<5>));
	BOOST_CHECK( value(int_<6> == int_<6>));
	BOOST_CHECK( value(int_<7> == int_<7>));
	BOOST_CHECK( value(int_<8> == int_<8>));
	BOOST_CHECK( value(int_<9> == int_<9>));

	BOOST_CHECK( value(int_<12> == int_<12>));
	BOOST_CHECK( value(int_<123> == int_<123>));
	BOOST_CHECK( value(int_<1234> == int_<1234>));
	BOOST_CHECK( value(int_<12345> == int_<12345>));
	BOOST_CHECK( value(int_<123456> == int_<123456>));
}

BOOST_AUTO_TEST_CASE(puddle_int_const_int_eq2)
{
	using namespace puddle;

	BOOST_CHECK(!value(int_<-1> == int_<1>));
	BOOST_CHECK(!value(int_<1> == int_<-1>));
	BOOST_CHECK(!value(int_<-23> == int_<23>));
	BOOST_CHECK(!value(int_<23> == int_<-23>));
	BOOST_CHECK(!value(int_<-456> == int_<456>));
	BOOST_CHECK(!value(int_<456> == int_<-456>));

	BOOST_CHECK(!value(int_<0> == int_<1>));
	BOOST_CHECK(!value(int_<1> == int_<0>));

	BOOST_CHECK(!value(int_<120> == int_<12>));
	BOOST_CHECK(!value(int_<23> == int_<123>));
}

BOOST_AUTO_TEST_CASE(puddle_int_const_int_ne1)
{
	using namespace puddle;

	BOOST_CHECK(!value(int_<-1> != int_<-1>));
	BOOST_CHECK(!value(int_<-23> != int_<-23>));
	BOOST_CHECK(!value(int_<-456> != int_<-456>));
	BOOST_CHECK(!value(int_<-7890> != int_<-7890>));

	BOOST_CHECK(!value(int_<0> != int_<0>));
	BOOST_CHECK(!value(int_<1> != int_<1>));
	BOOST_CHECK(!value(int_<2> != int_<2>));
	BOOST_CHECK(!value(int_<3> != int_<3>));
	BOOST_CHECK(!value(int_<4> != int_<4>));
	BOOST_CHECK(!value(int_<5> != int_<5>));
	BOOST_CHECK(!value(int_<6> != int_<6>));
	BOOST_CHECK(!value(int_<7> != int_<7>));
	BOOST_CHECK(!value(int_<8> != int_<8>));
	BOOST_CHECK(!value(int_<9> != int_<9>));

	BOOST_CHECK(!value(int_<12> != int_<12>));
	BOOST_CHECK(!value(int_<123> != int_<123>));
	BOOST_CHECK(!value(int_<1234> != int_<1234>));
	BOOST_CHECK(!value(int_<12345> != int_<12345>));
	BOOST_CHECK(!value(int_<123456> != int_<123456>));
}

BOOST_AUTO_TEST_CASE(puddle_int_const_int_ne2)
{
	using namespace puddle;

	BOOST_CHECK( value(int_<-1> != int_<1>));
	BOOST_CHECK( value(int_<1> != int_<-1>));
	BOOST_CHECK( value(int_<-23> != int_<23>));
	BOOST_CHECK( value(int_<23> != int_<-23>));
	BOOST_CHECK( value(int_<-456> != int_<456>));
	BOOST_CHECK( value(int_<456> != int_<-456>));

	BOOST_CHECK( value(int_<0> != int_<1>));
	BOOST_CHECK( value(int_<1> != int_<0>));

	BOOST_CHECK( value(int_<120> != int_<12>));
	BOOST_CHECK( value(int_<23> != int_<123>));
}

BOOST_AUTO_TEST_CASE(puddle_int_const_ostream)
{
	using namespace puddle;
	{
		std::stringstream ss;
		ss << int_<0>;
		BOOST_CHECK_EQUAL(ss.str(), "0");
	}
	{
		std::stringstream ss;
		ss << int_<123>;
		BOOST_CHECK_EQUAL(ss.str(), "123");
	}
	{
		std::stringstream ss;
		ss << int_<4567890>;
		BOOST_CHECK_EQUAL(ss.str(), "4567890");
	}
	{
		std::stringstream ss;
		ss << int_<-1234567890>;
		BOOST_CHECK_EQUAL(ss.str(), "-1234567890");
	}
}

BOOST_AUTO_TEST_SUITE_END()

