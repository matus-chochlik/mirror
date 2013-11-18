/**
 * @file mire/ct/exp10.hpp
 * @brief Base-10 exponential for compile-time integral constants
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_EXP10_1105240825_HPP
#define MIRE_CT_EXP10_1105240825_HPP

#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {
namespace aux {

template <typename Int, Int Boundary, Int Base, Int Value, Int Exp, bool Found>
struct exp_base;

template <typename Int, Int Boundary, Int Base, Int Value, Int Exp>
struct exp_base<Int, Boundary, Base, Value, Exp, true>
 : integral_constant<Int, Exp>
{ };

template <typename Int, Int Boundary, Int Base, Int Value, Int Exp>
struct exp_base<Int, Boundary, Base, Value, Exp, false>
 : exp_base<Int, Boundary + 1, Base, Value, Exp * Base, Boundary == Value>
{ };

template <typename Int, Int Boundary, Int Base, Int Value, Int Exp>
struct calc_exp_base
 : exp_base<Int, Boundary + 1, Base, Value, Exp, Boundary == Value>
{ };

} // namespace aux

/// Calculates the compile-time integral exponential of the specified value
/**
 *  @ingroup ct_utils
 */
template <typename IntegralConstant>
struct exp10
#ifndef MIRROR_DOCUMENTATION_ONLY
 : aux::calc_exp_base<
	typename std::remove_cv<decltype(IntegralConstant::value)>::type,
	0,
	10,
	IntegralConstant::value,
	1
>
#else
 : IntegralConstant
#endif
{ };

} // namespace ct
} // namespace mire

#endif //include guard

