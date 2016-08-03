/**
 * @file mire/ct/log.hpp
 * @brief Logarithm for compile-time integral constants
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_LOG_1105240825_HPP
#define MIRE_CT_LOG_1105240825_HPP

#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {
namespace aux {

template <typename Int, Int Boundary, Int Base, Int Value, Int Log, bool Found>
struct log_base;

template <typename Int, Int Boundary, Int Base, Int Value, Int Log>
struct log_base<Int, Boundary, Base, Value, Log, true>
 : integral_constant<Int, Log>
{ };

template <typename Int, Int Boundary, Int Base, Int Value, Int Log>
struct log_base<Int, Boundary, Base, Value, Log, false>
 : log_base<Int, Boundary * Base, Base, Value, Log + 1, (Boundary > Value/Base)>
{ };

template <typename Int, Int Boundary, Int Base, Int Value, Int Log>
struct calc_log_base
 : log_base<Int, Boundary * Base, Base, Value, Log, (Boundary > Value/Base)>
{ };

} // namespace aux

/// Calculates the compile-time integral logarithm of the specified value
/**
 *  @ingroup ct_utils
 */
template <typename IntegralConstant>
struct log10
#ifndef MIRROR_DOCUMENTATION_ONLY
 : aux::calc_log_base<
	typename std::remove_cv<decltype(IntegralConstant::value)>::type,
	1,
	10,
	IntegralConstant::value,
	0
>
#else
 : IntegralConstant
#endif
{ };


} // namespace ct
} // namespace mire

#endif //include guard

