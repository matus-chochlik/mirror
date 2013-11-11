/**
 * @file mire/ct/lambda.hpp
 * @brief Lambda expressions
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_LAMBDA_1011291729_HPP
#define MIRE_CT_LAMBDA_1011291729_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/at.hpp>
#include <mire/ct/stddef.hpp>

namespace mire {
namespace ct {

/// Meta-function class returning the @a Number -th of its arguments
/** This template is used in two different ways. First it wraps a meta-function
 *  returning the N-th of its arguments. Second it is used as a placeholder
 *  for the N-th argument in placeholder lambda expressions.
 *
 *  @ingroup ct_utils
 */
template <size_t Number>
struct arg
{
	template <typename ... Params>
	struct apply
	 : at_c<range<Params...>, Number>
	{ };
};

/// Returns the N-th Param or the @a Expr expression
/** This template returns either one of the @a Params if the @a Expr
 *  type is an instantiation of the arg<N> template or the @a Expr
 *  type itself otherwise.
 *
 *  In the First case the N-th of the @a Params is returned where
 *  @a N is the argument to the @a arg placeholder.
 *
 *  @ingroup ct_utils
 */
template <typename Expr, typename ... Params>
struct use_arg
#ifndef MIRROR_DOCUMENTATION_ONLY
{
	typedef Expr type;
};
#else
{
	/// Either the N-th argument or the Expr itself
	typedef unspecified type;
};
#endif

/// Protects the @a PlaceholderExpression from being expanded
/** This meta-function can be used to protect nested placeholder
 *  expressions from immediate expansion.
 *
 *  @ingroup ct_utils
 */
template <typename PlaceholderExpression>
struct protect
{
	/// The protected expression
	typedef PlaceholderExpression type;
};

template <size_t Number, typename ... Params>
struct use_arg<arg<Number>, Params...>
 : at_c<range<Params...>, Number>
{ };

template <
	template <class> class Expr,
	size_t Number,
	typename ... Params
>
struct use_arg<Expr<arg<Number> >, Params...>
 : Expr<typename at_c<range<Params...>, Number>::type>
{ };

template <typename Expr, typename ... Params>
struct use_arg<protect<Expr>, Params...>
{
	typedef Expr type;
};

template <
	template <class...> class Expr,
	typename ... SubExprs,
	typename ... Params
>
struct use_arg<Expr<SubExprs...>, Params...>
 : Expr<typename use_arg<SubExprs, Params...>::type...>
{ };

template <
	template <typename ...> class Expr,
	typename ... ExprArgs,
	typename ... Params
>
struct apply<Expr<ExprArgs...>, Params...>
 : Expr<typename use_arg<ExprArgs, Params...>::type...>
{ };

template <size_t Number, typename ... Params>
struct apply<arg<Number>, Params...>
 : arg<Number>::template apply<Params...>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

