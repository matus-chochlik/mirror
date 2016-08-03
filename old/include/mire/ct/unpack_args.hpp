/**
 * @file mire/ct/unpack_args.hpp
 * @brief Implementation of the unpack_args function
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_UNPACK_ARGS_1105240825_HPP
#define MIRE_CT_UNPACK_ARGS_1105240825_HPP

#include <mire/ct/default.hpp>

namespace mire {
namespace ct {
namespace aux {

template <typename MF ,typename R>
struct unpack_args_apply;

template <typename MF, typename ... P>
struct unpack_args_apply<MF, range<P...>>
 : apply<MF, P...>
{ };

template <typename MF ,typename S>
struct unpack_args_apply_c;

template <typename MF, typename Char, Char ... C>
struct unpack_args_apply_c<MF, basic_string<Char, C...>>
 : apply_c<MF, Char, C...>
{ };

} // namespace aux

/// Turns an N-ary LambdaExpression into a unary MetafunctionClass
/** Creates a MetafunctionClass that accepts a single Range parameter.
 *  Its result is equal to the result of the LambdaExpression called
 *  with the types in the Range.
 *
 *  @ingroup ct_utils
 */
template <typename LambdaExpression>
struct unpack_args
{
	template <typename Range>
	struct apply
	 : aux::unpack_args_apply<
		LambdaExpression,
		typename evaluate<Range>::type
	>
	{ };
};

template <typename LambdaExpression>
struct unpack_args_c
{
	template <typename String>
	struct apply_c
	 : aux::unpack_args_apply_c<
		LambdaExpression,
		typename evaluate<String>::type
	>
	{ };
};

} // namespace ct
} // namespace mire

#endif //include guard

