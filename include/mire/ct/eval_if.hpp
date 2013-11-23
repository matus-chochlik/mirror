/**
 * @file mire/ct/eval_if.hpp
 * @brief The eval_if metafunction for conditional evaluation of two expressions
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_EVAL_IF_1011291729_HPP
#define MIRE_CT_EVAL_IF_1011291729_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/int_const.hpp>
#include <mire/ct/evaluate.hpp>

namespace mire {
namespace ct {

template <class IfTrue, class IfFalse>
struct eval_if<true_type, IfTrue, IfFalse>
 : evaluate<IfTrue>
{ };

template <class IfTrue, class IfFalse>
struct eval_if<false_type, IfTrue, IfFalse>
 : evaluate<IfFalse>
{ };

template <bool Value, class IfTrue, class IfFalse>
struct eval_if_c
 : eval_if<integral_constant<bool, Value>, IfTrue, IfFalse>
{ };


} // namespace ct
} // namespace mire

#endif //include guard

