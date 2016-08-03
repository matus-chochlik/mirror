/**
 *  .file test/mire/ct/for_each.cpp
 *  .brief Test case for compile-time for_each function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_for_each
#include <boost/test/unit_test.hpp>

#include <mire/ct/for_each.hpp>
#include <sstream>

BOOST_AUTO_TEST_SUITE(mire_ct_for_each)

struct mire_ct_for_each_test1_func
{
	size_t size;

	mire_ct_for_each_test1_func(void)
	 : size(0)
	{ }

	template <typename I>
	void operator()(I)
	{
		size += sizeof(typename I::type);
	}
};

BOOST_AUTO_TEST_CASE(mire_ct_for_each_test1)
{
	using namespace mire::ct;

	typedef mire_ct_for_each_test1_func func;

	BOOST_CHECK((for_each<range<>>(func()).size == 0));
	BOOST_CHECK((
		for_each<range<short, int, long>>(func()).size ==
		sizeof(short)+sizeof(int)+sizeof(long)
	));
	BOOST_CHECK((
		for_each<range<char, short, unsigned, int, long>>(func()).size ==
		sizeof(char)+sizeof(short)+sizeof(unsigned)+sizeof(int)+sizeof(long)
	));
}

struct mire_ct_for_each_test2_func
{
	std::ostream& out;

	template <typename I>
	void operator()(I) const
	{
		if(typename I::is_first())
		{
			out << "(";
		}
		out << typename I::position();
		out << '=';
		out << sizeof(typename I::type);
		if(typename I::is_last())
		{
			out << ")";
		}
		else
		{
			out << "|";
		}
	}
};

BOOST_AUTO_TEST_CASE(mire_ct_for_each_test2)
{
	using namespace mire::ct;

	std::stringstream ss1, ss2;
	mire_ct_for_each_test2_func func = {ss1};

	for_each<range<char, short, int, long, float, double>>(func);

	ss2	<< "(0=" << sizeof(char)
		<< "|1=" << sizeof(short)
		<< "|2=" << sizeof(int)
		<< "|3=" << sizeof(long)
		<< "|4=" << sizeof(float)
		<< "|5=" << sizeof(double)
		<< ")";

	BOOST_CHECK(ss1.str() == ss2.str());
}

struct mire_ct_for_each_test3_func
{
	std::ostream& out;

	template <typename I>
	void operator()(I i) const
	{
		if(i.first())
		{
			out << "[";
		}
		else
		{
			out << "|";
		}
		out << i.pos();
		out << '=';
		out << sizeof(typename I::type);
		if(i.last())
		{
			out << "]";
		}
	}
};

BOOST_AUTO_TEST_CASE(mire_ct_for_each_test3)
{
	using namespace mire::ct;

	std::stringstream ss1, ss2;
	mire_ct_for_each_test3_func func = {ss1};

	for_each<range<wchar_t, short, unsigned, long, long double>>(func);

	ss2	<< "[0=" << sizeof(wchar_t)
		<< "|1=" << sizeof(short)
		<< "|2=" << sizeof(unsigned)
		<< "|3=" << sizeof(long)
		<< "|4=" << sizeof(long double)
		<< "]";

	BOOST_CHECK(ss1.str() == ss2.str());
}

BOOST_AUTO_TEST_SUITE_END()

