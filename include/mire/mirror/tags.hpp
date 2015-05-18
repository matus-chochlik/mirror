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
struct global_scope_tag { };

/// Indicates that a Metaobject is a model of MetaNamespace
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaNamespace
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaNamespace
 */
struct namespace_tag { };

/// Indicates that a Metaobject is a model of MetaType
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaType
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaType
 */
struct type_tag { };

/// Indicates that a Metaobject is a model of MetaTypedef
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaTypedef
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaTypedef
 */
struct typedef_tag { };

/// Indicates that a Metaobject is a model of MetaClass
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaClass
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaClass
 */
struct class_tag { };

/// Indicates that a Metaobject is a model of MetaFunction
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaFunction
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaFunction
 */
struct function_tag { };

/// Indicates that a Metaobject is a model of MetaConstructor
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaConstructor
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaConstructor
 */
struct constructor_tag { };

/// Indicates that a Metaobject is a model of MetaOperator
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaOperator
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaOperator
 */
struct operator_tag { };

/// Indicates that a Metaobject is a model of MetaOverloadedFunction
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the
 *  MetaOverloadedFunction
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaFunction
 */
struct overloaded_function_tag { };

/// Indicates that a Metaobject is a model of MetaEnum
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaEnum
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaEnum
 */
struct enum_tag { };

/// Indicates that a Metaobject is a model of MetaEnumClass
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaEnumClass
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaEnumClass
 */
struct enum_class_tag { };

/// Indicates that a Metaobject is a model of MetaInheritance
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaInheritance
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaInheritance
 */
struct inheritance_tag { };

/// Indicates that a Metaobject is a model of MetaConstant
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaConstant
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaConstant
 */
struct constant_tag { };

/// Indicates that a Metaobject is a model of MetaVariable
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaVariable
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaVariable
 */
struct variable_tag { };

/// Indicates that a Metaobject is a model of MetaParameter
/** Tag indicating that the tagged Metaobject
 *  satisfies requirements of the MetaParameter
 *  concept.
 *
 *  @see MetaobjectCategory
 *  @see MetaParameter
 */
struct parameter_tag { };


// -- Specifiers --

struct none_tag { };

struct extern_tag { };

struct static_tag { };

struct mutable_tag { };

struct register_tag { };

struct thread_local_tag { };

struct constexpr_tag { };

struct const_tag { };

struct volatile_tag { };

struct virtual_tag { };

struct override_tag { };

struct private_tag { };

struct protected_tag { };

struct public_tag { };

struct class_tag /*{ }*/;

struct struct_tag { };

struct union_tag { };

struct enum_tag /*{ }*/;

struct enum_class_tag /*{ }*/;

struct typedef_tag /*{ }*/;

struct noexcept_tag { };

} // namespace mirror
} // namespace mire

#endif // include guard
