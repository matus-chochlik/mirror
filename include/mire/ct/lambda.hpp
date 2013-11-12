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

template <size_t Number>
struct arg_c
{
	template <typename Char, Char ... Params>
	struct apply_c
	 : at_c<basic_string<Char, Params...>, Number>
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

template <typename Expr, typename Char, Char ... Params>
struct use_arg_c
{
	typedef Expr type;
};

template <typename Char, Char C, Char ... Params>
struct use_arg_c<integral_constant<Char, C>, Char, Params...>
 : integral_constant<Char, C>
{ };

/// Binds the arguments of a MetafunctionClass
/**
 *  @ingroup ct_utils
 */
template <typename MetafunctionClass, typename ... Params>
struct bind
{
	template <typename ... Params2>
	struct apply
	 : MetafunctionClass::template apply<use_arg<Params, Params2...>...>
	{ };
};

template <typename MetafunctionClass, typename ... Params>
struct bind_c
{
	template <typename Char, Char ... Params2>
	struct apply_c
	 : MetafunctionClass::template apply_c<
		Char,
		use_arg_c<Params, Char, Params2...>::value...
	>
	{ };
};

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

template <size_t Number, typename Char, Char ... Params>
struct use_arg_c<arg<Number>, Char, Params...>
 : at_c<basic_string<Char, Params...>, Number>
{ };

//
template <
	template <class> class Expr,
	size_t Number,
	typename ... Params
>
struct use_arg<Expr<arg<Number> >, Params...>
 : Expr<typename at_c<range<Params...>, Number>::type>
{ };

template <
	template <class> class Expr,
	size_t Number,
	typename Char,
	Char ... Params
>
struct use_arg_c<Expr<arg<Number> >, Char, Params...>
 : Expr<typename at_c<basic_string<Char, Params...>, Number>::type>
{ };

//
template <typename Expr, typename ... Params>
struct use_arg<protect<Expr>, Params...>
{
	typedef Expr type;
};

//
template <
	template <class...> class Expr,
	typename ... SubExprs,
	typename ... Params
>
struct use_arg<Expr<SubExprs...>, Params...>
 : Expr<typename use_arg<SubExprs, Params...>::type...>
{ };

template <
	template <class...> class Expr,
	typename ... SubExprs,
	typename Char,
	Char ... Params
>
struct use_arg_c<Expr<SubExprs...>, Char, Params...>
 : Expr<typename use_arg_c<SubExprs, Char, Params...>::type...>
{ };

//
template <typename MetafunctionClass, typename ... Params, typename ... Params2>
struct use_arg<bind<MetafunctionClass, Params...>, Params2...>
 : bind<MetafunctionClass, Params...>::template apply<Params2...>
{ };

template <
	typename MetafunctionClass,
	typename Char,
	typename ... Params,
	Char ... Params2
>
struct use_arg_c<bind_c<MetafunctionClass, Params...>, Char, Params2...>
 : bind_c<MetafunctionClass, Params...>::template apply_c<Char, Params2...>
{ };

//
template <
	template <typename ...> class Expr,
	typename ... ExprArgs,
	typename ... Params
>
struct apply<Expr<ExprArgs...>, Params...>
 : Expr<typename use_arg<ExprArgs, Params...>::type...>
{ };

template <
	template <typename ...> class Expr,
	typename ... ExprArgs,
	typename Char,
	Char ... Params
>
struct apply_c<Expr<ExprArgs...>, Char, Params...>
 : Expr<typename use_arg_c<ExprArgs, Char, Params...>::type...>
{ };

//
template <size_t Number, typename ... Params>
struct apply<arg<Number>, Params...>
 : arg<Number>::template apply<Params...>
{ };

template <size_t Number, typename Char, Char ... Params>
struct apply_c<arg<Number>, Char, Params...>
 : arg_c<Number>::template apply_c<Char, Params...>
{ };

//
template <typename MetafunctionClass, typename ... Params, typename ... Params2>
struct apply<bind<MetafunctionClass, Params...>, Params2...>
 : bind<MetafunctionClass, Params...>::template apply<Params2...>
{ };

template <
	typename MetafunctionClass,
	typename Char,
	typename ... Params,
	Char ... Params2>
struct apply_c<bind_c<MetafunctionClass, Params...>, Char, Params2...>
 : bind_c<MetafunctionClass, Params...>::template apply_c<Char, Params2...>
{ };

} // namespace ct
} // namespace mire

#endif //include guard

