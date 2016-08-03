/**
 * @file mire/ct/multiply.hpp
 * @brief The multiply metafunction for boolean constant type
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_MULTIPLY_1011291729_HPP
#define MIRE_CT_MULTIPLY_1011291729_HPP

#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {

template <class ... Integers>
struct multiply;

// Single-parameter multiply meta function specialization
template <class Integer>
struct multiply<Integer>
 : integral_constant<decltype(Integer::value), Integer::value>
{ };

// Multi-parameter multiply meta function specialization
template <class Integer, class ... Integers>
struct multiply<Integer, Integers...>
 : integral_constant<
	decltype(Integer::value * multiply<Integers...>::value),
	Integer::value * multiply<Integers...>::value
>{ };

#ifdef MIRROR_DOCUMENTATION_ONLY
/// Returns the sum of the IntegralConstant(s) passed as arguments
/**
 *  @tparam IntegralConstants the integer constants to be Add-ed
 *
 *  @ingroup ct_utils
 */
template <typename ... IntegralConstants>
struct multiply : public IntegralConstant
{ };
#endif

} // namespace ct
} // namespace mire

#endif //include guard

