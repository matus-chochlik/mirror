/**
 *  @file mire/ct/unique.hpp
 *  @brief Meta-function returning a range which contains the elements
 *  of the passed ranges without duplicities.
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_UNIQUE_1011291729_HPP
#define MIRE_CT_UNIQUE_1011291729_HPP


#include <mire/ct/default.hpp>
#include <mire/ct/if.hpp>
#include <mire/ct/contains.hpp>

namespace mire {
namespace ct {
namespace aux {

template <class UniqueRange, class TailRange>
struct unique;

template <typename Char, Char ... UniqueP>
struct unique<basic_string<Char, UniqueP...>, basic_string<Char>>
 : basic_string<Char, UniqueP...>
{ };

template <typename ... UniqueP>
struct unique<range<UniqueP...>, range<>>
 : range<UniqueP...>
{ };

template <typename Char, Char ... UniqueP, Char T, Char ... P>
struct unique<basic_string<Char, UniqueP...>, basic_string<Char, T, P...>>
 : if_<
	contains<basic_string<Char, UniqueP...>, basic_string<Char, T>>,
	unique<
		basic_string<Char, UniqueP...>,
		basic_string<Char, P...>
	>,
	unique<
		basic_string<Char, UniqueP..., T>,
		basic_string<Char, P...>
	>
>
{ };

template <typename ... UniqueP, typename T, typename ... P>
struct unique<range<UniqueP...>, range<T, P...>>
 : if_<
	contains<range<UniqueP...>, range<T>>,
	unique<
		range<UniqueP...>,
		range<P...>
	>,
	unique<
		range<UniqueP..., T>,
		range<P...>
	>
>
{ };

} // namespace aux

template <typename Char, Char ... P>
struct unique<basic_string<Char, P...>>
 : aux::unique<basic_string<Char>, basic_string<Char, P...>>
{ };

template <typename ... P>
struct unique<range<P...>>
 : aux::unique<range<>, range<P...>>
{ };


} // namespace ct
} // namespace mire

#endif //include guard

