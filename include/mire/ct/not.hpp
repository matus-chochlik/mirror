/**
 * @file mire/ct/not.hpp
 * @brief The not metafunction for boolean constant type
 *
 *  Copyright 2008-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_NOT_1011291729_HPP
#define MIRE_CT_NOT_1011291729_HPP

#include <mire/ct/evaluate.hpp>
#include <mire/ct/int_const.hpp>

namespace mire {
namespace ct {

template <class Bool>
struct not_
 : boolean_constant<!evaluate<Bool>::value>
{ };

#ifdef MIRROR_DOCUMENTATION_ONLY
/// Returns logical NOT of the BooleanConstant type passed as argument
/**
 *  @tparam BooleanConstant the boolean constant to be negated-ed
 *
 *  @ingroup ct_utils
 */
template <typename BooleanConstant>
struct not_ : public BooleanConstant
{ };
#endif

} // namespace ct
} // namespace mire

#endif //include guard

