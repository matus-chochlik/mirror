/**
 * @file mire/ct/protect.hpp
 * @brief The protect metafunction.
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_PROTECT_1011291729_HPP
#define MIRE_CT_PROTECT_1011291729_HPP

namespace mire {
namespace ct {

/// Protects the @a PlaceholderExpression from being expanded
/** This meta-function can be used to protect nested placeholder
 *  expressions from immediate expansion.
 *
 *  @ingroup ct_utils
 */
template <typename PlaceholderExpression>
struct protect
{
	/// The protected expression
	typedef PlaceholderExpression type;
};

} // namespace ct
} // namespace mire

#endif //include guard

