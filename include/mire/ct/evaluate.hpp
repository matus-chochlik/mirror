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
#include <mire/ct/nil_type.hpp>
#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {

template <typename X>
struct evaluate;

template <typename X>
struct can_evaluate
{
	template <typename Y>
	static false_type _can_hlp(Y*, Y*);

	template <typename Y, typename Z>
	static true_type _can_hlp(Y*, Z*);

	template <typename Y>
	static auto _can(Y* a, typename Y::type* b = nullptr) ->
	decltype(_can_hlp(a, b));

	static false_type _can(...);

	static X* _ptr(void);

	typedef decltype(_can(_ptr())) type;
};

template <typename X, typename CanEvaluate>
struct do_evaluate;

template <typename X>
struct do_evaluate<X, true_type>
 : evaluate<typename X::type>
{ };

template <typename X>
struct do_evaluate<X, false_type>
{
	typedef nil_t type;
};

/// Meta-function evaluates a compile-time string expression
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

template <>
struct evaluate<nil_t>
 : nil_t
{ };

} // namespace ct
} // namespace mire

#endif //include guard

