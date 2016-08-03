/**
 * @file mire/ct/fold.hpp
 * @brief Definition of the fold template.
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_FOLD_1011291729_HPP
#define MIRE_CT_FOLD_1011291729_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/lambda.hpp>
#include <mire/ct/identity.hpp>

namespace mire {
namespace ct {

// range
template <typename Status, typename ForwardOp>
struct fold<range<>, Status, ForwardOp>
 : identity<Status>
{ };

template <
	typename T,
	typename Status,
	typename ForwardOp
> struct fold<range<T>, Status, ForwardOp>
 : apply<ForwardOp, Status, T>
{ };

template <
	typename T,
	typename ... P,
	typename Status,
	typename ForwardOp
> struct fold<range<T, P...>, Status, ForwardOp>
 : fold<
	range<P...>,
	typename apply<
		ForwardOp,
		Status,
		T
	>::type,
	ForwardOp
>
{ };

// string
template <typename Status, typename Char, typename ForwardOp>
struct fold<basic_string<Char>, Status, ForwardOp>
 : identity<Status>
{ };

template <
	typename Char,
	Char C,
	typename Status,
	typename ForwardOp
> struct fold<basic_string<Char, C>, Status, ForwardOp>
 : apply<ForwardOp, Status, integral_constant<Char, C>>
{ };

template <
	typename Char,
	Char C,
	Char ... P,
	typename Status,
	typename ForwardOp
> struct fold<basic_string<Char, C, P...>, Status, ForwardOp>
 : fold<
	basic_string<Char, P...>,
	typename apply<
		ForwardOp,
		Status,
		integral_constant<Char, C>
	>::type,
	ForwardOp
>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

