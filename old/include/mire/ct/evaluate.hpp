/**
 * @file mire/ct/evaluate.hpp
 * @brief Implementation of the evaluate meta-function
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_EVALUATE_1105240825_HPP
#define MIRE_CT_EVALUATE_1105240825_HPP

#include <mire/ct/range.hpp>
#include <mire/ct/string.hpp>
#include <mire/ct/optional.hpp>
#include <mire/ct/identity.hpp>
#include <mire/ct/nil_type.hpp>
#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {

template <typename X>
struct evaluate;

#ifndef MIRROR_DOCUMENTATION_ONLY
template <typename X>
struct can_evaluate
{
	static integral_constant<int, 0> _can(...);

	template <typename Y>
	static integral_constant<int, 1> _can_hlp(Y*, Y*);

	template <typename Y, typename Z>
	static integral_constant<int, 2> _can_hlp(Y*, Z*);

	template <typename Y>
	static auto _can(Y* a, typename Y::type* b = nullptr) ->
	decltype(_can_hlp(a, b));

	static X* _ptr(void);

	typedef decltype(_can(_ptr())) type;
};

template <typename X, typename CanEvaluate>
struct do_evaluate;

template <typename X>
struct do_evaluate<X, integral_constant<int, 2>>
 : evaluate<typename X::type>
{ };

template <typename X>
struct do_evaluate<X, integral_constant<int, 1>>
 : X
{ };

template <typename X>
struct do_evaluate<X, integral_constant<int, 0>>
{
	typedef X type;
};
#endif

/// Meta-function evaluates a compile-time expression
/**
 *  @see basic_string
 *  @see range
 *
 *  @ingroup ct_utils
 */
template <typename X>
struct evaluate
#ifndef MIRROR_DOCUMENTATION_ONLY
 : do_evaluate<X, typename can_evaluate<X>::type>
#endif
{ };

#ifndef MIRROR_DOCUMENTATION_ONLY
template <typename Char, Char ... C>
struct evaluate<basic_string<Char, C...>>
 : basic_string<Char, C...>
{ };

template <typename ... P>
struct evaluate<range<P...>>
 : range<P...>
{ };

template <typename T>
struct evaluate<optional<T>>
 : optional<T>
{ };

template <typename T, T C>
struct evaluate<integral_constant<T, C>>
 : integral_constant<T, C>
{ };

template <typename T>
struct evaluate<identity<T>>
 : identity<T>
{ };

template <>
struct evaluate<nil_t>
 : nil_t
{ };
#endif

} // namespace ct
} // namespace mire

#endif //include guard

