/**
 * @file mire/ct/divide.hpp
 * @brief The divide metafunction for boolean constant type
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_DIVIDE_1011291729_HPP
#define MIRE_CT_DIVIDE_1011291729_HPP

#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {

template <class ... Integers>
struct divide;

// Single-parameter divide meta function specialization
template <class Integer>
struct divide<Integer>
 : integral_constant<decltype(Integer::value), Integer::value>
{ };

// Multi-parameter divide meta function specialization
template <class Integer1, class Integer2>
struct divide<Integer1, Integer2>
 : integral_constant<
	decltype(Integer1::value / Integer2::value),
	Integer1::value / Integer2::value
>{ };

#ifdef MIRROR_DOCUMENTATION_ONLY
/// Returns the division of the IntegralConstant(s) passed as arguments
/**
 *  @tparam IntegralConstants the integer constants to be Subtracted-ed
 *
 *  @ingroup ct_utils
 */
template <typename ... IntegralConstants>
struct divide : public IntegralConstant
{ };
#endif

} // namespace ct
} // namespace mire

#endif //include guard

