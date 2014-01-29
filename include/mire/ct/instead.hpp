/**
 * @file mire/ct/instead.hpp
 * @brief Template meta-function returning a new type instead of old type.
 *
 *  Copyright 2008-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_CT_INSTEAD_1401292224_HPP
#define MIRE_CT_INSTEAD_1401292224_HPP

namespace mire {
namespace ct {

/// Meta-function returning NewT type.
/**
 *  @ingroup ct_utils
 */
template <typename OldT, typename NewT>
struct instead
{
	/// The resulting type
	typedef NewT type;
};

} // namespace ct
} // namespace mire

#endif //include guard

