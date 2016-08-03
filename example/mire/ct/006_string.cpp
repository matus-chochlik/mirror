/**
 *  @example mire/ct/006_string.cpp
 *  @brief Example of Mirror Reflection compile-time string basic usage.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @mire_example_output{006_string}
 */

#include <mire/ct/range.hpp>
#include <mire/ct/traits.hpp>
#include <mire/ct/to_string.hpp>
#include <mire/ct/compare.hpp>
#include <mire/ct/empty.hpp>
#include <mire/ct/size.hpp>
#include <mire/ct/c_str.hpp>
#include <mire/ct/front.hpp>
#include <mire/ct/at.hpp>
#include <mire/ct/head.hpp>
#include <mire/ct/tail.hpp>
#include <mire/ct/slice.hpp>
#include <mire/ct/find.hpp>
#include <mire/ct/before.hpp>
#include <mire/ct/contains.hpp>
#include <mire/ct/starts_with.hpp>
#include <mire/ct/ends_with.hpp>
#include <mire/ct/concat.hpp>
#include <mire/ct/append.hpp>
#include <mire/ct/prepend.hpp>
#include <mire/ct/repeat.hpp>
#include <iostream>
#include <iomanip>

struct string_literal_class
{
	static constexpr const char* c_str = "a string literal";
	static constexpr size_t size = 16;
};

int main(void)
{
	using namespace mire::ct;

	typedef string<'c'> one_char;
	typedef basic_string<wchar_t, L'w'> one_wchar;
	typedef string<'b','l','a','h'> blah;
	typedef string<'a',' ','s','t','r','i','n','g'> a_string;
	typedef basic_string<wchar_t, L'a',L' ',L'w',L's',L't',L'r',L'i',L'n',L'g'> a_wstring;
	typedef to_string<string_literal_class> a_string_literal;

	std::cout	<<"is_string<void> = " << std::boolalpha
			<< is_string<void>() << std::endl;
	std::cout	<<"is_string<std::string> = " << std::boolalpha
			<< is_string<std::string>() << std::endl;
	std::cout	<<"is_string<one_char> = " << std::boolalpha
			<< is_string<one_char>() << std::endl;
	std::cout	<<"is_string<one_char> = " << std::boolalpha
			<< is_string<one_char>() << std::endl;
	std::cout	<<"is_string<one_wchar> = " << std::boolalpha
			<< is_string<one_wchar>() << std::endl;
	std::cout	<<"is_string<a_string> = " << std::boolalpha
			<< is_string<a_string>() << std::endl;
	std::cout	<<"is_string<a_wstring> = " << std::boolalpha
			<< is_string<a_wstring>() << std::endl;
	std::cout	<<"is_string<a_string_literal> = " << std::boolalpha
			<< is_string<a_string_literal>() << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"empty<empty_string> = " << std::boolalpha
			<< empty<empty_string>() << std::endl;
	std::cout	<<"empty<basic_string<wchar_t>> = " << std::boolalpha
			<< empty<basic_string<wchar_t>>() << std::endl;
	std::cout	<<"empty<one_char> = " << std::boolalpha
			<< empty<one_char>() << std::endl;
	std::cout	<<"empty<one_wchar> = " << std::boolalpha
			<< empty<one_wchar>() << std::endl;
	std::cout	<<"empty<a_string> = " << std::boolalpha
			<< empty<a_string>() << std::endl;
	std::cout	<<"empty<a_string_literal> = " << std::boolalpha
			<< empty<a_string_literal>() << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"size<empty_string> = "
			<< size<empty_string>() << std::endl;
	std::cout	<<"size<one_wchar> = "
			<< size<one_wchar>() << std::endl;
	std::cout	<<"size<blah> = "
			<< size<blah>() << std::endl;
	std::cout	<<"size<a_string> = "
			<< size<a_string>() << std::endl;
	std::cout	<<"size<a_string_literal> = "
			<< size<a_string_literal>() << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"size<concat<a_string, string<' ','a','n','d',' '>, a_string_literal>> = "
			<< size<concat<a_string, string<' ','a','n','d',' '>, a_string_literal>>()
			<< std::endl;

	std::cout	<< std::endl;

	std::cout	<<"c_str<empty_string> = \""
			<< c_str<empty_string>()
			<<"\"" << std::endl;
	std::cout	<<"c_str<one_char> = \""
			<< c_str<one_char>()
			<<"\"" << std::endl;
	std::cout	<<"c_str<a_string> = \""
			<< c_str<a_string>()
			<<"\"" << std::endl;
	std::cout	<<"c_str<a_string_literal> = \""
			<< c_str<a_string_literal>()
			<<"\"" << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"c_str<concat<a_string, string<' ','a','n','d',' '>, a_string_literal>> ="
			<< std::endl << "\t\""
			<< c_str<concat<a_string, string<' ','a','n','d',' '>, a_string_literal>>()
			<<"\"" << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"c_str<append_c<one_char, char, 'h','a','r'>> = \""
			<< c_str<append_c<one_char, char, 'h','a','r'>>()
			<<"\"" << std::endl;
	std::cout	<<"size<prepend_c<one_wchar, wchar_t, L'C',L'o'>> = "
			<< size<prepend_c<one_wchar, wchar_t, L'C',L'o'>>() << std::endl;
	std::cout	<<"c_str<prepend_c<append_c<one_char, char, 'd','e'>, char, 'a','b'>> = \""
			<< c_str<prepend_c<append_c<one_char, char, 'd','e'>, char, 'a','b'>>()
			<<"\"" << std::endl;
	std::cout	<<"c_str<concat<append_c<blah, char,',',' '>, blah, repeat_char_c<3,char,'.'>>> ="
			<< std::endl << "\t\""
			<< c_str<concat<append_c<blah, char,',',' '>, blah, repeat_char_c<3,char,'.'>>>()
			<<"\"" << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"front<one_char> = '"
			<< front<one_char>() <<"'" << std::endl;
	std::cout	<<"front<a_string> = '"
			<< front<a_string>() <<"'" << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"at_c<a_string, 0> = '"
			<< at_c<a_string, 0>() <<"'" << std::endl;
	std::cout	<<"at_c<a_string, 2> = '"
			<< at_c<a_string, 2>() <<"'" << std::endl;
	std::cout	<<"at_c<a_string, 3> = '"
			<< at_c<a_string, 3>() <<"'" << std::endl;
	std::cout	<<"at_c<a_string, 4> = '"
			<< at_c<a_string, 4>() <<"'" << std::endl;
	std::cout	<<"at_c<a_string, 6> = '"
			<< at_c<a_string, 6>() <<"'" << std::endl;
	std::cout	<<"at_c<a_string, 7> = '"
			<< at_c<a_string, 7>() <<"'" << std::endl;

	std::cout	<< std::endl;

	std::cout	<<"c_str<head_c<blah, 2>> = \""
			<< c_str<head_c<blah, 2>>()
			<<"\"" << std::endl;
	std::cout	<<"c_str<head_c<one_char, 3>> = \""
			<< c_str<head_c<one_char, 5>>()
			<<"\"" << std::endl;
	std::cout	<<"c_str<head_c<a_string, 5>> = \""
			<< c_str<head_c<a_string, 5>>()
			<<"\"" << std::endl;
	std::cout	<<"c_str<tail_c<blah, 2>> = \""
			<< c_str<tail_c<blah, 2>>()
			<<"\"" << std::endl;
	std::cout	<<"c_str<tail_c<a_string, 6>> = \""
			<< c_str<tail_c<a_string, 6>>()
			<<"\"" << std::endl;
	std::cout	<<"c_str<tail_c<head_c<blah, 3>, 2>> = \""
			<< c_str<tail_c<head_c<blah, 3>, 2>>()
			<<"\"" << std::endl;
	std::cout	<<"c_str<slice_c<a_string, 3, 3>> = \""
			<< c_str<slice_c<a_string, 3, 3>>()
			<<"\"" << std::endl;
	std::cout	<<"equal<tail_c<a_string, 6>, slice_c<a_string_literal, 2, 6>> = "
			<< std::boolalpha
			<< equal<tail_c<a_string, 6>, slice_c<a_string_literal, 2, 6>>()
			<< std::endl;

	std::cout	<< std::endl;

	std::cout	<<"starts_with<one_char, one_char> = " << std::boolalpha
			<< starts_with<one_char, one_char>()
			<< std::endl;
	std::cout	<<"starts_with<a_string_literal, a_string> = " << std::boolalpha
			<< starts_with<a_string_literal, a_string>()
			<< std::endl;
	std::cout	<<"starts_with<a_string, blah> = " << std::boolalpha
			<< starts_with<a_string, blah>()
			<< std::endl;
	std::cout	<<"ends_with<a_string, a_string> = " << std::boolalpha
			<< ends_with<a_string, a_string>()
			<< std::endl;
	std::cout	<<"ends_with<a_string_literal, string<'l','i','t','e','r','a','l'>> = "
			<< std::boolalpha
			<< ends_with<a_string_literal, string<'l','i','t','e','r','a','l'>>()
			<< std::endl;
	std::cout	<<"ends_with<a_string, blah> = " << std::boolalpha
			<< ends_with<a_string, blah>()
			<< std::endl;

	std::cout	<< std::endl;

	std::cout	<<"contains<blah, blah> = " << std::boolalpha
			<< contains<blah, blah>()
			<< std::endl;
	std::cout	<<"contains<a_string_literal, blah> = " << std::boolalpha
			<< contains<a_string_literal, blah>()
			<< std::endl;
	std::cout	<<"contains<a_string_literal, string<'a'>> = "
			<< std::boolalpha
			<< contains<a_string_literal, string<'s','t','r','i','n','g'>>()
			<< std::endl;
	std::cout	<<"contains<a_string_literal, string<'s','t','r','i','n','g'>> = "
			<< std::boolalpha
			<< contains<a_string_literal, string<'s','t','r','i','n','g'>>()
			<< std::endl;

	std::cout	<< std::endl;

	std::cout	<<"c_str<find<a_string_literal, string<'l','i','t','e','r','a','l'>>> = \""
			<< c_str<find<a_string_literal, string<'l','i','t','e','r','a','l'>>>()
			<<"\"" << std::endl;
	std::cout	<<"c_str<before<a_string_literal, string<' ','l'>>> = \""
			<< c_str<before<a_string_literal, string<' ','l'>>>()
			<<"\"" << std::endl;

	std::cout	<< std::endl;

	return 0;
}
