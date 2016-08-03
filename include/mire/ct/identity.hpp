/**
 * @file mire/ct/identity.hpp
 * @brief Identity template meta-function returning the type passed
 * as argument. Also used in tag dispatching.
 *
 *  Copyright 2008-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_IDENTITY_1011291729_HPP
#define MIRE_CT_IDENTITY_1011291729_HPP


namespace mire {
namespace ct {

/// Meta-function returning T unchanged
/** This meta-function is also useful in tag dispatching between
 *  different function overloads.
 *  @tparam T the type to be returned.
 *
 *  @ingroup ct_utils
 */
template <typename T>
struct identity
{
	/// The resulting type
	typedef T type;
};

} // namespace ct
} // namespace mire

#endif //include guard

