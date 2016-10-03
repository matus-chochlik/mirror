/**
 *  .file test/mire/ct/accumulate.cpp
 *  .brief Test case for compile-time accumulate function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_accumulate
#include <boost/test/unit_test.hpp>

#include <mire/ct/accumulate.hpp>
#include <functional>
#include <sstream>
#include <vector>

BOOST_AUTO_TEST_SUITE(mire_ct_accumulate)

struct mire_ct_accumulate_test1_func
{
	template <typename IterInfo>
	std::size_t operator()(std::size_t status, IterInfo) const
	{
		return status + sizeof(typename IterInfo::type);
	}
};

BOOST_AUTO_TEST_CASE(mire_ct_accumulate_test1)
{
	using namespace mire::ct;

	typedef mire_ct_accumulate_test1_func func;

	BOOST_CHECK((accumulate<range<>>(func(), 0) == 0));
	BOOST_CHECK((
		accumulate<range<char, long, bool,short, float>>(func(), 0) ==
		sizeof(char)+sizeof(long)+sizeof(bool)+sizeof(short)+sizeof(float)
	));
	BOOST_CHECK((
		accumulate<range<long, int, short, double>>(func(), 2) ==
		sizeof(long)+sizeof(int)+sizeof(short)+sizeof(double)+2
	));
	BOOST_CHECK((
		accumulate<range<long, int, short, double, wchar_t>>(func(), 7) ==
		sizeof(long)+sizeof(int)+sizeof(short)+sizeof(double)+sizeof(wchar_t)+7
	));
}

struct mire_ct_accumulate_test2_func
{
	template <typename IterInfo>
	static void print(std::ostream& out, IterInfo ii)
	{
		if(ii.first())
		{
			out << "(";
		}
		else
		{
			out << "|";
		}
		out << ii.pos();
		out << "=";
		out << sizeof(typename IterInfo::type);
		if(ii.last())
		{
			out << ")";
		}
	}

	template <typename Status, typename IterInfo>
	Status operator()(Status outr , IterInfo ii) const
	{
		print(outr.get(), ii);
		return outr;
	}
};

BOOST_AUTO_TEST_CASE(mire_ct_accumulate_test2)
{
	using namespace mire::ct;

	typedef mire_ct_accumulate_test2_func func;

	{
		std::stringstream ss;
		BOOST_CHECK((accumulate<range<>>(func(), std::ref(ss)).get().str() == ""));
	}

	{
		std::stringstream ss1, ss2;
		accumulate<range<long, int, short, double, wchar_t>>(func(), std::ref(ss1));
		ss2 << "(0=" << sizeof(long);
		ss2 << "|1=" << sizeof(int);
		ss2 << "|2=" << sizeof(short);
		ss2 << "|3=" << sizeof(double);
		ss2 << "|4=" << sizeof(wchar_t);
		ss2 << ")";

		BOOST_CHECK(ss1.str() == ss2.str());
	}
}

struct mire_ct_accumulate_test3_func
{
	template <typename IterInfo>
	static void push(std::vector<std::size_t>& vec, IterInfo ii)
	{
		vec.push_back(sizeof(typename IterInfo::type));
	}

	template <typename Status, typename IterInfo>
	Status operator()(Status vecr, IterInfo ii) const
	{
		push(vecr.get(), ii);
		return vecr;
	}
};

BOOST_AUTO_TEST_CASE(mire_ct_accumulate_test3)
{
	using namespace mire::ct;

	typedef mire_ct_accumulate_test3_func func;

	{
		std::vector<std::size_t> vec;
		BOOST_CHECK((accumulate<range<>>(func(), std::ref(vec)).get().empty()));
	}

	{
		std::vector<std::size_t> v1, v2;
		accumulate<range<long, int, unsigned, short, double, wchar_t>>(func(),std::ref(v1));
		v2.push_back(sizeof(long));
		v2.push_back(sizeof(int));
		v2.push_back(sizeof(unsigned));
		v2.push_back(sizeof(short));
		v2.push_back(sizeof(double));
		v2.push_back(sizeof(wchar_t));

		BOOST_CHECK(v1 == v2);
	}
}

BOOST_AUTO_TEST_SUITE_END()

