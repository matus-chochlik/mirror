/**
 * @file mire/ct/add.hpp
 * @brief The add metafunction for boolean constant type
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_ADD_1011291729_HPP
#define MIRE_CT_ADD_1011291729_HPP

#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {

template <class ... Integers>
struct add;

// Single-parameter add meta function specialization
template <class Integer>
struct add<Integer>
 : integral_constant<decltype(Integer::value), Integer::value>
{ };

// Multi-parameter add meta function specialization
template <class Integer, class ... Integers>
struct add<Integer, Integers...>
 : integral_constant<
	decltype(Integer::value + add<Integers...>::value),
	Integer::value + add<Integers...>::value
>{ };

#ifdef MIRROR_DOCUMENTATION_ONLY
/// Returns the sum of the IntegralConstant(s) passed as arguments
/**
 *  @tparam IntegralConstants the integer constants to be Add-ed
 *
 *  @ingroup ct_utils
 */
template <typename ... IntegralConstants>
struct add : public IntegralConstant
{ };
#endif

} // namespace ct
} // namespace mire

#endif //include guard

