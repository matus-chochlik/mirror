/**
 *  @file mire/tags/metaobject.hpp
 *  @brief Metaobject tag types
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_TAGS_METAOBJECT_1310291537_HPP
#define MIRE_TAGS_METAOBJECT_1310291537_HPP

namespace mire {
namespace tags {

/// Indicates that a Metaobject is a model of MetaGlobalScope
/** Tag indicating that the tagged @ref mire::mirror::Metaobject "Metaobject"
 *  satisfies requirements of the @ref mire::mirror::MetaGlobalScope "MetaGlobalScope"
 *  concept.
 *
 *  @see mire::mirror::MetaobjectCategory
 *  @see mire::mirror::MetaGlobalScope
 */
struct meta_global_scope_tag
{
};

/// Indicates that a Metaobject is a model of MetaNamespace
/** Tag indicating that the tagged @ref mire::mirror::Metaobject "Metaobject"
 *  satisfies requirements of the @ref mire::mirror::MetaNamespace "MetaNamespace"
 *  concept.
 *
 *  @see mire::mirror::MetaobjectCategory
 *  @see mire::mirror::MetaNamespace
 */
struct meta_namespace_tag
{
};

/// Indicates that a Metaobject is a model of MetaType
/** Tag indicating that the tagged @ref mire::mirror::Metaobject "Metaobject"
 *  satisfies requirements of the @ref mire::mirror::MetaType "MetaType"
 *  concept.
 *
 *  @see mire::mirror::MetaobjectCategory
 *  @see mire::mirror::MetaType
 */
struct meta_type_tag
{
};

/// Indicates that a Metaobject is a model of MetaTypedef
/** Tag indicating that the tagged @ref mire::mirror::Metaobject "Metaobject"
 *  satisfies requirements of the @ref mire::mirror::MetaTypedef "MetaTypedef"
 *  concept.
 *
 *  @see mire::mirror::MetaobjectCategory
 *  @see mire::mirror::MetaTypedef
 */
struct meta_typedef_tag
{
};

/// Indicates that a Metaobject is a model of MetaClass
/** Tag indicating that the tagged @ref mire::mirror::Metaobject "Metaobject"
 *  satisfies requirements of the @ref mire::mirror::MetaClass "MetaClass"
 *  concept.
 *
 *  @see mire::mirror::MetaobjectCategory
 *  @see mire::mirror::MetaClass
 */
struct meta_class_tag
{
};

/// Indicates that a Metaobject is a model of MetaFunction
/** Tag indicating that the tagged @ref mire::mirror::Metaobject "Metaobject"
 *  satisfies requirements of the @ref mire::mirror::MetaFunction "MetaFunction"
 *  concept.
 *
 *  @see mire::mirror::MetaobjectCategory
 *  @see mire::mirror::MetaFunction
 */
struct meta_function_tag
{
};

/// Indicates that a Metaobject is a model of MetaConstructor
/** Tag indicating that the tagged @ref mire::mirror::Metaobject "Metaobject"
 *  satisfies requirements of the @ref mire::mirror::MetaConstructor "MetaConstructor"
 *  concept.
 *
 *  @see mire::mirror::MetaobjectCategory
 *  @see mire::mirror::MetaConstructor
 */
struct meta_constructor_tag
{
};

/// Indicates that a Metaobject is a model of MetaOperator
/** Tag indicating that the tagged @ref mire::mirror::Metaobject "Metaobject"
 *  satisfies requirements of the @ref mire::mirror::MetaOperator "MetaOperator"
 *  concept.
 *
 *  @see mire::mirror::MetaobjectCategory
 *  @see mire::mirror::MetaOperator
 */
struct meta_operator_tag
{
};

/// Indicates that a Metaobject is a model of MetaOverloadedFunction
/** Tag indicating that the tagged @ref mire::mirror::Metaobject "Metaobject"
 *  satisfies requirements of the
 *  @ref mire::mirror::MetaOverloadedFunction "MetaOverloadedFunction"
 *  concept.
 *
 *  @see mire::mirror::MetaobjectCategory
 *  @see mire::mirror::MetaFunction
 */
struct meta_overloaded_function_tag
{
};

/// Indicates that a Metaobject is a model of MetaEnum
/** Tag indicating that the tagged @ref mire::mirror::Metaobject "Metaobject"
 *  satisfies requirements of the @ref mire::mirror::MetaEnum "MetaEnum"
 *  concept.
 *
 *  @see mire::mirror::MetaobjectCategory
 *  @see mire::mirror::MetaEnum
 */
struct meta_enum_tag
{
};

/// Indicates that a Metaobject is a model of MetaInheritance
/** Tag indicating that the tagged @ref mire::mirror::Metaobject "Metaobject"
 *  satisfies requirements of the @ref mire::mirror::MetaInheritance "MetaInheritance"
 *  concept.
 *
 *  @see mire::mirror::MetaobjectCategory
 *  @see mire::mirror::MetaInheritance
 */
struct meta_inheritance_tag
{
};

/// Indicates that a Metaobject is a model of MetaConstant
/** Tag indicating that the tagged @ref mire::mirror::Metaobject "Metaobject"
 *  satisfies requirements of the @ref mire::mirror::MetaConstant "MetaConstant"
 *  concept.
 *
 *  @see mire::mirror::MetaobjectCategory
 *  @see mire::mirror::MetaConstant
 */
struct meta_constant_tag
{
};

/// Indicates that a Metaobject is a model of MetaVariable
/** Tag indicating that the tagged @ref mire::mirror::Metaobject "Metaobject"
 *  satisfies requirements of the @ref mire::mirror::MetaVariable "MetaVariable"
 *  concept.
 *
 *  @see mire::mirror::MetaobjectCategory
 *  @see mire::mirror::MetaVariable
 */
struct meta_variable_tag
{
};

/// Indicates that a Metaobject is a model of MetaParameter
/** Tag indicating that the tagged @ref mire::mirror::Metaobject "Metaobject"
 *  satisfies requirements of the @ref mire::mirror::MetaParameter "MetaParameter"
 *  concept.
 *
 *  @see mire::mirror::MetaobjectCategory
 *  @see mire::mirror::MetaParameter
 */
struct meta_parameter_tag
{
};

} // namespace tags
} // namespace mire

#endif // include guard
