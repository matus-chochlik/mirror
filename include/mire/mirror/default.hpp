/**
 *  @file mire/mirror/default.hpp
 *  @brief Default implementations of the intrinsic metafunctions.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_DEFAULT_1310291537_HPP
#define MIRE_MIRROR_DEFAULT_1310291537_HPP

#include <mire/mirror/fwd.hpp>
#include <mire/mirror/evaluate.hpp>

namespace mire {
namespace mirror {

template <typename Metaobject>
struct category
#ifndef MIRROR_DOCUMENTATION_ONLY
 : category<typename evaluate<Metaobject>::type>
#else
#endif
{ };

template <typename Metaobject>
struct keyword
#ifndef MIRROR_DOCUMENTATION_ONLY
 : keyword<typename evaluate<Metaobject>::type>
#else
#endif
{ };

/// Returns the base name of the base-level object reflected by a Metaobject
/**
 *  @tparam Metaobject the meta-object the base name of which should be returned.
 */
template <typename Metaobject>
struct base_name
#ifndef MIRROR_DOCUMENTATION_ONLY
 : base_name<typename evaluate<Metaobject>::type>
#else
 : ct::String
#endif
{ };

/// Returns the full name of the base-level object reflected by a Metaobject
/**
 *  @tparam Metaobject the meta-object the full name of which should be returned.
 */
template <typename Metaobject>
struct full_name
#ifndef MIRROR_DOCUMENTATION_ONLY
 : full_name<typename evaluate<Metaobject>::type>
#else
 : ct::String
#endif
{ };

template <typename Metaobject>
struct original_type
#ifndef MIRROR_DOCUMENTATION_ONLY
 : original_type<typename evaluate<Metaobject>::type>
#else
#endif
{ };

template <typename Metaobject>
struct scope
#ifndef MIRROR_DOCUMENTATION_ONLY
 : scope<typename evaluate<Metaobject>::type>
#else
#endif
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
