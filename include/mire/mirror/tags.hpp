/**
 *  @file mire/mirror/tags.hpp
 *  @brief Metaobject/specifier tags.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_TAGS_1310291537_HPP
#define MIRE_MIRROR_TAGS_1310291537_HPP

namespace mire {
namespace mirror {

/// Indicates that a Metaobject is a model of MetaGlobalScope
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaGlobalScope
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaGlobalScope
 */
struct meta_global_scope_tag
{
};

/// Indicates that a Metaobject is a model of MetaNamespace
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaNamespace
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaNamespace
 */
struct meta_namespace_tag
{
};

/// Indicates that a Metaobject is a model of MetaType
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaType
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaType
 */
struct meta_type_tag
{
};

/// Indicates that a Metaobject is a model of MetaTypedef
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaTypedef
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaTypedef
 */
struct meta_typedef_tag
{
};

/// Indicates that a Metaobject is a model of MetaClass
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaClass
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaClass
 */
struct meta_class_tag
{
};

/// Indicates that a Metaobject is a model of MetaFunction
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaFunction
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaFunction
 */
struct meta_function_tag
{
};

/// Indicates that a Metaobject is a model of MetaConstructor
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaConstructor
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaConstructor
 */
struct meta_constructor_tag
{
};

/// Indicates that a Metaobject is a model of MetaOperator
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaOperator
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaOperator
 */
struct meta_operator_tag
{
};

/// Indicates that a Metaobject is a model of MetaOverloadedFunction
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the
 *  MetaOverloadedFunction
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaFunction
 */
struct meta_overloaded_function_tag
{
};

/// Indicates that a Metaobject is a model of MetaEnum
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaEnum
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaEnum
 */
struct meta_enum_tag
{
};

/// Indicates that a Metaobject is a model of MetaInheritance
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaInheritance
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaInheritance
 */
struct meta_inheritance_tag
{
};

/// Indicates that a Metaobject is a model of MetaConstant
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaConstant
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaConstant
 */
struct meta_constant_tag
{
};

/// Indicates that a Metaobject is a model of MetaVariable
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaVariable
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaVariable
 */
struct meta_variable_tag
{
};

/// Indicates that a Metaobject is a model of MetaParameter
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaParameter
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaParameter
 */
struct meta_parameter_tag
{
};


// -- Specifiers --

struct spec_none_tag
{
};

struct spec_extern_tag
{
};

struct spec_static_tag
{
};

struct spec_mutable_tag
{
};

struct spec_register_tag
{
};

struct spec_thread_local_tag
{
};

struct spec_constexpr_tag
{
};

struct spec_const_tag
{
};

struct spec_volatile_tag
{
};

struct spec_virtual_tag
{
};

struct spec_override_tag
{
};

struct spec_private_tag
{
};

struct spec_protected_tag
{
};

struct spec_public_tag
{
};

struct spec_class_tag
{
};

struct spec_struct_tag
{
};

struct spec_union_tag
{
};

struct spec_enum_tag
{
};

struct spec_enum_class_tag
{
};

struct spec_typedef_tag
{
};

struct spec_noexcept_tag
{
};

} // namespace mirror
} // namespace mire

#endif // include guard
