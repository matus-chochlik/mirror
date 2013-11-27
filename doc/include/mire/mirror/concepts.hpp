/**
 *  @file mire/mirror/doc.hpp
 *  @brief Documentation of Mirror's concepts
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef MIRE_MIRROR_CONCEPTS_1107121519_HPP
#define MIRE_MIRROR_CONCEPTS_1107121519_HPP

namespace mire {
namespace mirror {

/** @defgroup mirror_concepts Mirror metaobject concepts
 *
 */

/// Stateless anonymous type reflecting certain program features.
/**
 *  @ingroup mirror_concepts
 */
struct Metaobject
{
	/// This trait template returns true_type for Metaobject.
	friend struct is_metaobject<Metaobject>;
};

} // namespace ct
} // namespace mire

#endif // include guard
