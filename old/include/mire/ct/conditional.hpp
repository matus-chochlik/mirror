/**
 * @file mire/ct/conditional.hpp
 * @brief The if-else metafunction for branching based on boolean constant type
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_CONDITIONAL_1011291729_HPP
#define MIRE_CT_CONDITIONAL_1011291729_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/int_const.hpp>
#include <mire/ct/identity.hpp>

namespace mire {
namespace ct {

template <class IfTrue, class IfFalse>
struct conditional<true_type, IfTrue, IfFalse>
 : identity<IfTrue>
{ };

template <class IfTrue, class IfFalse>
struct conditional<false_type, IfTrue, IfFalse>
 : identity<IfFalse>
{ };

template <bool Value, class IfTrue, class IfFalse>
struct conditional_c
 : conditional<boolean_constant<Value>, IfTrue, IfFalse>
{ };


} // namespace ct
} // namespace mire

#endif //include guard

