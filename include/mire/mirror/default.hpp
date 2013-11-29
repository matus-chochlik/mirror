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

/// Returns the keyword of a specifier reflected by a MetaSpecifier
/**
 *  @tparam MetaSpecifer the metaobject reflecting the specifier for which
 *  the keyword should be returned.
 *
 *  @see is_specifier
 */
template <typename MetaSpecifier>
struct keyword
#ifndef MIRROR_DOCUMENTATION_ONLY
 : keyword<typename evaluate<MetaSpecifier>::type>
#else
 : String
#endif
{ };

/// Returns the base name of the base-level object reflected by a Metaobject
/**
 *  @tparam Metaobject the metaobject the base name of which should be returned.
 *
 *  @note This metafunction is applicable only to Metaobjects for which
 *  the has_name trait returns true i.e. for MetaNamed metaobjects.
 *
 *  @see has_name
 */
template <typename MetaNamed>
struct base_name
#ifndef MIRROR_DOCUMENTATION_ONLY
 : base_name<typename evaluate<MetaNamed>::type>
#else
 : String
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
 : String
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
 : MetaScope
#endif
{ };

/// Returns the typedef-type of a @c MetaTypedef
/**
 *  @tparam MetaTypedef the meta-object for which a @c MetaType reflecting
 *  the typedef-type should be returned.
 *
 *  @note This metafunction is applicable only to Metaobjects reflecting typedefs.
 */
template <typename MetaTypedef>
struct typedef_type
#ifndef MIRROR_DOCUMENTATION_ONLY
 : typedef_type<typename evaluate<MetaTypedef>::type>
#else
 : Metaobject
#endif
{ };

/// Creates a type having a member typedef with type X named [NAME].
/** This metafunction creates and returns a type that is equivalent
 *  to the following structure:
 *  @code
 *  struct type
 *  {
 *    typedef X NAME;
 *  };
 *  @endcode
 *
 *  Where @c NAME is replaced with the actual name of the named constructs
 *  reflected by the MetaNamedScoped metaobject.
 *  For multi-word names or names that are reserved keywords the name of the
 *  typedef is concatenated using a single underscore and suffixed with single
 *  underscore. For MetaType reflecting the @c unsigned @c long @c int type
 *  the struct above would be generated as follows:
 *  @code
 *  struct type
 *  {
 *    typedef X unsigned_long_int_;
 *  };
 *  @endcode
 *
 *  @tparam MetaNamedScoped the meta-object for which the type should be created.
 *  @tparam X the underlying type of the member typedef.
 *
 *  @note This metafunction is applicable only to Metaobjects for which
 *  the has_name and has_scope traits return true.
 */
template <typename MetaNamedScoped, typename X>
struct named_typedef
#ifndef MIRROR_DOCUMENTATION_ONLY
 : named_typedef<typename evaluate<MetaNamedScoped>::type, X>
{ };
#else
{
	/// The generated type.
	typedef Unspecified type;
};
#endif

/// Creates a type having a member variable with type X named [NAME].
/** This metafunction creates and returns a type that is equivalent
 *  to the following structure:
 *  @code
 *  struct type
 *  {
 *    X NAME;
 *
 *    template <typename ... P>
 *    type(P&& ... p)
 *     : NAME(p...)
 *    { };
 *  };
 *  @endcode
 *
 *  Where @c NAME is replaced with the actual name of the named constructs
 *  reflected by the MetaNamedScoped metaobject.
 *  For multi-word names or names that are reserved keywords the name of the
 *  typedef is concatenated using a single underscore and suffixed with single
 *  underscore. For MetaType reflecting the @c unsigned @c long @c int type
 *  the struct above would be generated as follows:
 *  @code
 *  struct type
 *  {
 *    X unsigned_long_int_;
 *
 *    template <typename ... P>
 *    type(P&& ... p)
 *     : unsigned_long_int_(p...)
 *    { };
 *  };
 *  @endcode
 *
 *  @tparam MetaNamedScoped the meta-object for which the type should be created.
 *  @tparam X the underlying type of the member variable.
 *
 *  @note This metafunction is applicable only to Metaobjects for which
 *  the has_name and has_scope traits return true.
 */
template <typename MetaNamedScoped, typename X>
struct named_mem_var
#ifndef MIRROR_DOCUMENTATION_ONLY
 : named_mem_var<typename evaluate<MetaNamedScoped>::type, X>
{ };
#else
{
	/// The generated type.
	typedef Unspecified type;
};
#endif

/// Returns the elaborated type specifier of a @c MetaClass or @c MetaEnum
/**
 *  @tparam Metaobject the meta-object for which the @c MetaSpecifier
 *  should be returned.
 *
 *  @note This metafunction is applicable only to Metaobjects reflecting typedefs.
 */
template <typename MetaType>
struct elaborated_type
#ifndef MIRROR_DOCUMENTATION_ONLY
 : elaborated_type<typename evaluate<MetaType>::type>
#else
 : MetaSpecifier
#endif
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
