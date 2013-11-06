/**
 * @file mire/ct/or.hpp
 * @brief The or metafunction for boolean constant type
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_OR_1011291729_HPP
#define MIRE_CT_OR_1011291729_HPP

#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {

template <class ... Bools>
struct or_;

// Single-parameter or_ meta function specialization
template <class Bool>
struct or_<Bool>
 : integral_constant<bool, Bool::value>
{ };

// Multi-parameter or_ meta function specialization
template <class Bool, class ... Bools>
struct or_<Bool, Bools...>
 : integral_constant<
	bool,
	Bool::value || or_<Bools...>::value
>{ };

#ifdef MIRROR_DOCUMENTATION_ONLY
/// Returns logical OR of the BooleanConstants type passed as arguments
/**
 *  @tparam BooleanConstants the boolean constants to be AND-ed
 *
 *  @ingroup meta_programming
 */
template <typename ... BooleanConstants>
struct or_ : public BooleanConstant
{ };
#endif

} // namespace ct
} // namespace mire

#endif //include guard

