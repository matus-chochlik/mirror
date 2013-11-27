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

/// Equality comparison metafunction for compile-time Metaobjects
/** Returns true is @c Metaobject1 is equal to @c Metaobject2
 */
template <typename Metaobject1, typename Metaobject2>
struct equal
#ifndef MIRROR_DOCUMENTATION_ONLY
 : equal<
	typename evaluate<Metaobject1>::type,
	typename evaluate<Metaobject2>::type
>
#else
 : BooleanConstantType
#endif
{ };

/// Non-equality comparison metafunction for compile-time Metaobjects
/** Returns true is @c Metaobject1 is not equal to @c Metaobject2
 */
template <typename Metaobject1, typename Metaobject2>
struct nonequal
#ifndef MIRROR_DOCUMENTATION_ONLY
 : nonequal<
	typename evaluate<Metaobject1>::type,
	typename evaluate<Metaobject2>::type
>
#else
 : BooleanConstantType
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
 *
 *  @note This metafunction is applicable only to Metaobjects for which
 *  the has_name trait returns true.
 *
 *  @see has_name
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
 *
 *  @note This metafunction is applicable only to Metaobjects for which
 *  the has_name and has_scope traits both return true.
 *
 *  @see has_name
 *  @see has_scope
 */
template <typename Metaobject>
struct full_name
#ifndef MIRROR_DOCUMENTATION_ONLY
 : full_name<typename evaluate<Metaobject>::type>
#else
 : ct::String
#endif
{ };

/// Returns the original type reflected by the @c Metaobject
/**
 *  @note This metafunction is applicable only to Metaobjects reflecting types.
 *
 *  @see category
 *  @see is_a
 *  @see meta_type_tag
 *  @see meta_typedef_tag
 *  @see meta_class_tag
 */
template <typename Metaobject>
struct original_type
#ifndef MIRROR_DOCUMENTATION_ONLY
 : original_type<typename evaluate<Metaobject>::type>
#else
#endif
{ };

/// Returns the scope of a @c Metaobject
/**
 *  @tparam Metaobject the meta-object for which the scope should be returned.
 *
 *  @note This metafunction is applicable only to Metaobjects for which
 *  the has_scope trait returns true.
 */
template <typename Metaobject>
struct scope
#ifndef MIRROR_DOCUMENTATION_ONLY
 : scope<typename evaluate<Metaobject>::type>
#else
 : Metaobject
#endif
{ };

/// Returns the typedef-type of a @c Metaobject
/**
 *  @tparam Metaobject the meta-object for which the @
 *  should be returned.
 *
 *  @note This metafunction is applicable only to Metaobjects reflecting typedefs.
 */
template <typename Metaobject>
struct typedef_type
#ifndef MIRROR_DOCUMENTATION_ONLY
 : typedef_type<typename evaluate<Metaobject>::type>
#else
 : Metaobject
#endif
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
