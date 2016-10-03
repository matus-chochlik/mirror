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
 *  @see meta_global_scope_tag
 *  @see meta_namespace_tag
 *  @see meta_type_tag
 *  @see meta_typedef_tag
 *  @see meta_class_tag
 *  @see meta_function_tag
 *  @see meta_constructor_tag
 *  @see meta_operator_tag
 *  @see meta_overloaded_function_tag
 *  @see meta_enum_tag
 *  @see meta_inheritance_tag
 *  @see meta_constant_tag
 *  @see meta_variable_tag
 *  @see meta_parameter_tag
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

	/// Tests if the parameter is a MetaSpecifier
	friend struct is_specifier<Metaobject>;

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

/// Metaobject reflecting a C++ specifier.
/**
 *  @ingroup mirror_concepts
 */
struct MetaSpecifier
 : virtual Metaobject
{
	/// Returns true_type for MetaSpecifier metaobjects.
	friend struct is_specifier<MetaSpecifier>;

	/// Returns the specifier keyword as a compile-time String.
	friend struct keyword<MetaSpecifier>;
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

/// Metaobject reflecting a named scope.
/**
 *  @ingroup mirror_concepts
 */
struct MetaScope
 : MetaNamedScoped
{
	/// Returns true_type for MetaScope metaobjects.
	friend struct is_scope<MetaScope>;
};

/// Metaobject reflecting a named namespace.
/**
 *  @ingroup mirror_concepts
 */
struct MetaNamespace
 : MetaScope
{
	/// Returns meta_namespace_tag
	friend struct category<MetaNamespace>;
};

/// Metaobject reflecting the global-scope namespace.
/**
 *  @ingroup mirror_concepts
 */
struct MetaGlobalScope
 : MetaNamespace
{
	/// Returns meta_global_scope_tag.
	friend struct category<MetaGlobalScope>;
};

/// Metaobject reflecting a type.
/**
 *  @ingroup mirror_concepts
 */
struct MetaType
 : MetaNamedScoped
{
	/// Returns meta_type_tag.
	friend struct category<MetaType>;

	/// Returns the original (base-level) type reflected by the MetaType.
	friend struct original_type<MetaType>;
};

/// Metaobject reflecting a typedef.
/**
 *  @ingroup mirror_concepts
 */
struct MetaTypedef
 : MetaType
{
	/// Returns meta_typedef_tag.
	friend struct category<MetaTypedef>;

	/// Returns a MetaType reflecting the typedef type of the typedef.
	friend struct typedef_type<MetaTypedef>;
};

/// Metaobject reflecting a class.
/**
 *  @ingroup mirror_concepts
 */
struct MetaClass
 : virtual MetaType
 , virtual MetaScope
{
	/// Returns meta_class_tag.
	friend struct category<MetaClass>;

	/// Returns the elaborated type specifier used to declare the class.
	friend struct elaborated_type<MetaClass>;

	/// Returns the a range of MetaInheritance reflecting the base classes.
	friend struct base_classes<MetaClass>;
};

/// Metaobject reflecting a function.
/**
 *  @ingroup mirror_concepts
 */
struct MetaFunction
 : virtual MetaScope
{
	/// Returns meta_function_tag.
	friend struct category<MetaFunction>;

	/// Returns the linkage specifier of the function.
	friend struct linkage<MetaClass>;

	/// Returns true if the function was declared as constexpr.
	friend struct constexpr_<MetaClass>;

	/// Returns a MetaType reflecting the result type of the function.
	friend struct result_type<MetaClass>;
};

/// Metaobject reflecting a class member.
/**
 *  @ingroup mirror_concepts
 */
struct MetaClassMember
 : MetaNamedScoped
{
	/// Returns true for MetaClassMember metaobjects.
	friend struct is_class_member<MetaClassMember>;

	/// Returns the access-type specifier of the class member.
	friend struct linkage<MetaClass>;
};

/// Metaobject reflecting an initializer (constructor of native type)
/**
 *  @ingroup mirror_concepts
 */
struct MetaInitializer
 : MetaFunction
{
	/// Returns meta_constructor_tag.
	friend struct category<MetaInitializer>;
};

/// Metaobject reflecting a constructor
/**
 *  @ingroup mirror_concepts
 */
struct MetaConstructor
 : MetaFunction
 , MetaClassMember
{
	/// Returns meta_constructor_tag.
	friend struct category<MetaConstructor>;
};

/// Metaobject reflecting an operator
/**
 *  @ingroup mirror_concepts
 */
struct MetaOperator
 : MetaFunction
 , virtual MetaClassMember
{
	/// Returns meta_constructor_tag.
	friend struct category<MetaOperator>;
};

/// Metaobject reflecting an overloaded function
/**
 *  @ingroup mirror_concepts
 */
struct MetaOverloadedFunction
 : MetaNamedScoped
 , virtual MetaClassMember
{
	/// Returns meta_overloaded_function_tag.
	friend struct category<MetaOverloadedFunction>;

	/// Returns a range of MetaFunction listing the overloads.
	friend struct overloads<MetaOverloadedFunction>;
};

/// Metaobject reflecting template function or class
/**
 *  @ingroup mirror_concepts
 */
struct MetaTemplate
 : virtual MetaFunction
 , virtual MetaClass
 , virtual MetaClassMember
{
	/// Returns true_type for MetaTemplate metaobjects.
	friend struct is_template<MetaTemplate>;
};

/// Metaobject reflecting template type or constant parameter
/**
 *  @ingroup mirror_concepts
 */
struct MetaTemplateParameter
 : virtual MetaTypedef
 , virtual MetaConstant
{
	/// Returns true_type for MetaTemplateParameter metaobjects.
	friend struct is_template<MetaTemplateParameter>;

	/// Returns true_type if the parameter is a parameter pack
	friend struct pack<MetaTemplateParameter>;

	/// Returns the position of the template parameter
	friend struct position<MetaTemplateParameter>;
};

/// Metaobject reflecting template function or class instantiation
/**
 *  @ingroup mirror_concepts
 */
struct MetaInstantiation
 : virtual MetaFunction
 , virtual MetaClass
 , virtual MetaClassMember
{
	/// Returns true_type for MetaInstantiation metaobjects.
	friend struct has_template<MetaInstantiation>;

	/// Returns a MetaTemplate reflecting the template of the instantiation
	friend struct template_<MetaInstantiation>;
};

/// Metaobject reflecting an enum or enum class
/**
 *  @ingroup mirror_concepts
 */
struct MetaEnum
 : virtual MetaScope
 , virtual MetaType
{
	/// Returns meta_enum_tag for MetaEnum metaobjects.
	friend struct category<MetaEnum>;

	/// Returns the elaborated type specifier used to declare the enum.
	friend struct elaborated_type<MetaClass>;
};

/// Metaobject reflecting a class inheritance
/**
 *  @ingroup mirror_concepts
 */
struct MetaInheritance
 : virtual Metaobject
{
	/// Returns meta_inheritance_tag for MetaInheritance metaobjects.
	friend struct category<MetaInheritance>;

	/// Returns the access type specifier used in the inheritance
	friend struct access_type<MetaInheritance>;

	/// Returns the inheritance type specifier used in the inheritance
	friend struct inheritance_type<MetaInheritance>;

	/// Returns a MetaClass reflecting the base class in the inheritance
	friend struct base_class<MetaInheritance>;

	/// Returns a MetaClass reflecting the derived class in the inheritance
	friend struct derived_class<MetaInheritance>;
};

/// Metaobject reflecting a variable
/**
 *  @ingroup mirror_concepts
 */
struct MetaVariable
 : MetaNamedScoped
 , virtual MetaClassMember
{
	/// Returns meta_variable_tag for MetaVariable metaobjects.
	friend struct category<MetaVariable>;

	/// Returns the storage class specifier of the reflected variable.
	friend struct storage_class<MetaVariable>;

	/// Returns a MetaType reflecting the type of the variable
	friend struct data_type<MetaVariable>;
};

/// Metaobject reflecting a function parameter
/**
 *  @ingroup mirror_concepts
 */
struct MetaParameter
 : MetaVariable
{
	/// Returns meta_parameter_tag for MetaParameter metaobjects.
	friend struct category<MetaParameter>;

	/// Returns true_type if the parameter is a parameter pack
	friend struct pack<MetaTemplateParameter>;

	/// Returns the position of the function parameter
	friend struct position<MetaTemplateParameter>;
};

/// Metaobject reflecting a named compile-time constant.
/**
 *  @ingroup mirror_concepts
 */
struct MetaConstant
 : MetaNamedScoped
 , virtual MetaClassMember
{
	/// Returns meta_constant_tag for MetaConstant metaobjects.
	friend struct category<MetaConstant>;

	/// Returns the value of the constant.
	friend struct value<MetaConstant>;
};

//TODO

} // namespace ct
} // namespace mire

#endif // include guard
