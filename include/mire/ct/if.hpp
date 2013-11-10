/**
 * @file mire/ct/if.hpp
 * @brief The if-else metafunction for branching based on boolean constant type
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_IF_1011291729_HPP
#define MIRE_CT_IF_1011291729_HPP

#include <mire/ct/default.hpp>
#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {

template <class IfTrue, class IfFalse>
struct if_<true_type, IfTrue, IfFalse>
{
	typedef IfTrue type;
};

template <class IfTrue, class IfFalse>
struct if_<false_type, IfTrue, IfFalse>
{
	typedef IfFalse type;
};

template <bool Value, class IfTrue, class IfFalse>
struct if_c
 : if_<integral_constant<bool, Value>, IfTrue, IfFalse>
{ };


} // namespace ct
} // namespace mire

#endif //include guard

