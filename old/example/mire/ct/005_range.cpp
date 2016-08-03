/**
 *  @example mire/ct/005_range.cpp
 *  @brief Example of Mirror Reflection compile-time range basic usage.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @mire_example_output{005_range}
 */

#include <mire/ct/range.hpp>
#include <mire/ct/traits.hpp>
#include <mire/ct/compare.hpp>
#include <mire/ct/empty.hpp>
#include <mire/ct/size.hpp>
#include <mire/ct/front.hpp>
#include <mire/ct/at.hpp>
#include <mire/ct/head.hpp>
#include <mire/ct/tail.hpp>
#include <mire/ct/slice.hpp>
#include <mire/ct/find.hpp>
#include <mire/ct/contains.hpp>
#include <mire/ct/starts_with.hpp>
#include <mire/ct/ends_with.hpp>
#include <mire/ct/concat.hpp>
#include <mire/ct/append.hpp>
#include <mire/ct/prepend.hpp>
#include <iostream>
#include <iomanip>

int main(void)
{
	using namespace mire::ct;

	typedef range<void> one_type;
	typedef range<bool, char, wchar_t, short, float, long double> some_types;
	typedef range<char, short, int, long, long long, float, double> other_types;

	std::cout	<<"is_range<void> = " << std::boolalpha
			<< is_range<void>() << std::endl;
	std::cout	<<"is_range<empty_range> = " << std::boolalpha
			<< is_range<empty_range>() << std::endl;
	std::cout	<<"is_range<one_type> = " << std::boolalpha
			<< is_range<one_type>() << std::endl;
	std::cout	<<"is_range<some_types> = " << std::boolalpha
			<< is_range<some_types>() << std::endl;
	std::cout	<<"is_range<decltype(std::cout)> = " << std::boolalpha
			<< is_range<decltype(std::cout)>() << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"empty<empty_range> = " << std::boolalpha
			<< empty<empty_range>() << std::endl;
	std::cout	<<"empty<one_type> = " << std::boolalpha
			<< empty<one_type>() << std::endl;
	std::cout	<<"empty<some_types> = " << std::boolalpha
			<< empty<some_types>() << std::endl;
	std::cout	<<"empty<other_types> = " << std::boolalpha
			<< empty<other_types>() << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"size<empty_range> = "
			<< size<empty_range>() << std::endl;
	std::cout	<<"size<one_type> = "
			<< size<one_type>() << std::endl;
	std::cout	<<"size<some_types> = "
			<< size<some_types>() << std::endl;
	std::cout	<<"size<other_types> = "
			<< size<other_types>() << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"size<concat<some_types, other_types>> = "
			<< size<concat<some_types, other_types>>() << std::endl;
	std::cout	<<"size<concat<some_types, other_types, one_type>> = "
			<< size<concat<some_types, other_types, one_type>>() << std::endl;
	std::cout	<<"size<concat<one_type, some_types, other_types, one_type>> = "
			<< size<concat<one_type, some_types, other_types, one_type>>() << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"size<append<some_types, void>> = "
			<< size<append<some_types, void>>() << std::endl;
	std::cout	<<"size<append<some_types, void, int, long>> = "
			<< size<append<some_types, void, int, long>>() << std::endl;
	std::cout	<<"size<append<append<some_types, void, int>, long>> = "
			<< size<append<append<some_types, void, int>, long>>() << std::endl;
	std::cout	<<"size<prepend<some_types, void, long>> = "
			<< size<prepend<some_types, void, long>>() << std::endl;
	std::cout	<<"size<prepend<prepend<some_types, void>, int, long>> = "
			<< size<prepend<prepend<some_types, void>, int, long>>() << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"equal_types<front<one_type>, void> = "
			<< equal_types<front<one_type>, void>() << std::endl;
	std::cout	<<"equal_types<front<some_types>, bool> = "
			<< equal_types<front<some_types>, bool>() << std::endl;
	std::cout	<<"equal_types<front<other_types>, long> = "
			<< equal_types<front<other_types>, long>() << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"equal_types<at_c<one_type, 0>, void> = "
			<< equal_types<at_c<one_type, 0>, void>() << std::endl;
	std::cout	<<"equal_types<at_c<some_types, 0>, long> = "
			<< equal_types<at_c<some_types, 0>, long>() << std::endl;
	std::cout	<<"equal_types<at_c<some_types, 1>, char> = "
			<< equal_types<at_c<some_types, 1>, char>() << std::endl;
	std::cout	<<"equal_types<at_c<some_types, 2>, wchar_t> = "
			<< equal_types<at_c<some_types, 2>, wchar_t>() << std::endl;
	std::cout	<<"equal_types<at_c<some_types, 3>, short> = "
			<< equal_types<at_c<some_types, 3>, short>() << std::endl;
	std::cout	<<"equal_types<at_c<some_types, 4>, float> = "
			<< equal_types<at_c<some_types, 4>, float>() << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"equal<head_c<some_types, 2>, range<bool, char>> = "
			<< equal<head_c<some_types, 2>, range<bool, char>>() << std::endl;
	std::cout	<<"equal<head_c<other_types, 3>, range<char, short, int>> = "
			<< equal<head_c<other_types, 3>, range<char, short, int>>() << std::endl;
	std::cout	<<"equal<tail_c<other_types, 2>, range<float, double>> = "
			<< equal<tail_c<other_types, 2>, range<float, double>>() << std::endl;
	std::cout	<<"equal<slice_c<some_types, 2, 3>, range<wchar_t, short, float>> = "
			<< equal<slice_c<some_types, 2, 3>, range<wchar_t, short, float>>() << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"starts_with<some_types, one_type> = "
			<< starts_with<some_types, one_type>() << std::endl;
	std::cout	<<"starts_with<some_types, range<bool, char, wchar_t>> = "
			<< starts_with<some_types, range<bool, char, wchar_t>>() << std::endl;
	std::cout	<<"ends_with<other_types, range<float, double>> = "
			<< ends_with<other_types, range<float, double>>() << std::endl;
	std::cout	<<"ends_with<one_type, one_type> = "
			<< ends_with<one_type, one_type>() << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"contains<some_types, one_type> = "
			<< contains<some_types, one_type>() << std::endl;
	std::cout	<<"contains<one_type, range<void>> = "
			<< contains<one_type, range<void>>() << std::endl;
	std::cout	<<"contains<some_types, range<void>> = "
			<< contains<some_types, range<void>>() << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"size<find<one_type, range<void>>> = "
			<< size<find<one_type, range<void>>>() << std::endl;
	std::cout	<<"size<find<one_type, range<bool>>> = "
			<< size<find<one_type, range<bool>>>() << std::endl;
	std::cout	<<"size<find<other_types, range<float>>>> = "
			<< size<find<other_types, range<float>>>() << std::endl;

	return 0;
}
