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
 *  The types and classes listed in this group are defined only
 *  for documentation purposes and cannot be used in application code.
 *  They are models of the various concepts defined by Mirror and document
 *  the interface of real types modeling the same concepts.
 */

/// Compile-time tag specifying the category of a metaobject.
/** Types conforming to this concept can be used to distinguish between various
 *  Metaobject (s) provided by Mirror.
 *  Each Metaobject has a @em main category, the most specific, but some
 *  Metaobjects also fall into more general categories. For example a MetaClass
 *  is also a MetaType or the MetaGlobalScope is also a MetaNamespace.
 *
 *  The @c category template metafunction can be used to get the main
 *  MetaobjectCategory of a Metaobject. The @c is_a metafunction can be used
 *  to check if a @c Metaobject falls into a specified @c MetaobjectCategory.
 *
 *  @ingroup mirror_concepts
 *
 *  @see category
 *  @see is_a
 *
 *  @see mire::tags::meta_global_scope_tag
 *  @see mire::tags::meta_namespace_tag
 *  @see mire::tags::meta_type_tag
 *  @see mire::tags::meta_typedef_tag
 *  @see mire::tags::meta_class_tag
 *  @see mire::tags::meta_function_tag
 *  @see mire::tags::meta_constructor_tag
 *  @see mire::tags::meta_operator_tag
 *  @see mire::tags::meta_overloaded_function_tag
 *  @see mire::tags::meta_enum_tag
 *  @see mire::tags::meta_inheritance_tag
 *  @see mire::tags::meta_constant_tag
 *  @see mire::tags::meta_variable_tag
 *  @see mire::tags::meta_parameter_tag
 *
 */
struct MetaobjectCategory { };

/// Stateless anonymous type reflecting certain program features.
/**
 *  @ingroup mirror_concepts
 */
struct Metaobject
{
	/// The Metaobject itself.
	typedef Metaobject type;

	/// Tests if the parameter is a Metaobject
	friend struct is_metaobject<Metaobject>;

	/// Returns the main MetaobjectCategory of Metaobject.
	friend struct category<Metaobject>;

	/// Tests if a Metaobject falls into a MetaobjectCategory.
	friend struct is_a<Metaobject, MetaobjectCategory>;

	/// Tests if a Metaobject conforms to the MetaNamed concept.
	friend struct has_name<Metaobject>;

	/// Tests if a Metaobject conforms to the MetaScoped concept.
	friend struct has_scope<Metaobject>;

	/// Tests if a Metaobject conforms to the MetaScope concept.
	friend struct is_scope<Metaobject>;

	/// Tests if a Metaobject conforms to the MetaClassMember concept.
	friend struct is_class_member<Metaobject>;

	/// Tests if a Metaobject conforms to the MetaTemplate concept.
	friend struct is_template<Metaobject>;

	/// Tests if a Metaobject conforms to the MetaInstantiation concept.
	friend struct has_template<Metaobject>;
};

/// Metaobject reflecting program constructs having a human-readable name
/**
 *  @ingroup mirror_concepts
 */
struct MetaNamed
 : virtual Metaobject
{
	/// Returns the base name as a compile-time String.
	friend struct base_name<MetaNamed>;

	/// Returns true_type for MetaNamed metaobjects.
	friend struct has_name<MetaNamed>;
};

/// Metaobject reflecting program constructs defined inside of a named scope.
/**
 *  @ingroup mirror_concepts
 */
struct MetaScoped
 : virtual Metaobject
{
	/// Returns the MetaScope reflecting the scope.
	friend struct scope<MetaScoped>;

	/// Returns true_type for MetaScoped metaobjects.
	friend struct has_scope<MetaScoped>;
};

/// Metaobject reflecting named program constructs defined inside of a named scope.
/**
 *  @ingroup mirror_concepts
 */
struct MetaNamedScoped
 : virtual MetaNamed
 , virtual MetaScoped
{
	/// Returns the fully qualified name as a compile-time String.
	friend struct full_name<MetaNamedScoped>;

	/// Returns a type having a member typedef with type X named [NAME]
	friend struct named_typedef<MetaNamedScoped, X>;

	/// Returns a type having a member variable with type X named [NAME]
	friend struct named_mem_var<MetaNamedScoped, X>;
};

/// Metaobject reflecting a named scope
/**
 *  @ingroup mirror_concepts
 */
struct MetaScope
 : MetaNamedScoped
{
	/// Returns true_type for MetaScope metaobjects.
	friend struct is_scope<Metaobject>;
};

/// Metaobject reflecting a named namespace.
/**
 *  @ingroup mirror_concepts
 */
struct MetaNamespace
 : MetaScope
{
	/// Returns meta_namespace_tag
	friend struct category<Metaobject>;
};

/// Metaobject reflecting the global-scope namespace.
/**
 *  @ingroup mirror_concepts
 */
struct MetaGlobalScope
 : MetaNamespace
{
	/// Returns meta_global_scope_tag
	friend struct category<Metaobject>;
};


} // namespace ct
} // namespace mire

#endif // include guard
