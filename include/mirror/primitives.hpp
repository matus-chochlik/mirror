/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_PRIMITIVES_HPP
#define MIRROR_PRIMITIVES_HPP

#include <experimental/__config>
#include <string_view>
#include <type_traits>
#include <__debug>

#ifdef _LIBCPP_HAS_NO_REFLECTION
#if defined(_LIBCPP_WARNING)
_LIBCPP_WARNING(
  "mirror cannot be used with this compiler without -freflection-ts")
#else
#warning mirror cannot be used with this compiler without -freflection-ts
#endif
#else
#ifdef _LIBCPP_HAS_NO_REFLECTION_EXT
#if defined(_LIBCPP_WARNING)
_LIBCPP_WARNING("mirror cannot be used without -freflection-ext ")
#else
#warning <experimental/mirror> cannot be used without -freflection-ext
#endif
#endif
#endif

#if defined(MIRROR_YCM) || defined(MIRROR_DOXYGEN) || \
  (!defined(_LIBCPP_HAS_NO_REFLECTION) &&             \
   !defined(_LIBCPP_HAS_NO_REFLECTION_EXT))

#if defined(MIRROR_DOXYGEN)
using __unspecified = unsigned;

/// @brief Internal type, values of which represent metaobjects in the compiler.
/// @ingroup metaobjects
/// @see wrapped_metaobject
using __metaobject_id = __unspecified;
#else
#if defined(MIRROR_YCM)
using __metaobject_id = unsigned;
#endif
#endif

namespace mirror {

using std::integral_constant;
using std::string_view;
using std::type_identity;

/// @brief Represents a list of types. Unlike tuple does not store values.
/// @ingroup utilities
template <typename... T>
struct type_list {};

/// @brief Internal representation of metaobjects.
/// @ingroup metaobjects
/// @warning Do not use directly. Use the metaobject concept instead.
template <__metaobject_id M>
struct wrapped_metaobject {
    consteval operator __metaobject_id() const noexcept {
        return M;
    }
};

template <__metaobject_id M>
consteval auto is_object(wrapped_metaobject<M>) noexcept -> bool {
    return true;
}

/// @brief Indicates if the argument is a metaobject.
/// @ingroup classification
/// @see reflects_object
template <typename X>
consteval auto is_object(const X&) noexcept -> bool {
    return false;
}

/// @brief Concept for metaobject types.
/// @ingroup classification
/// @see reflects_object
/// @see is_object
/// @see no_metaobject
template <typename X>
concept metaobject = is_object(X{});

template <__metaobject_id M>
consteval auto unwrap(wrapped_metaobject<M>) noexcept -> __metaobject_id {
    return M;
}

#if defined(MIRROR_DOXYGEN)
/// @brief Special instance of metaobject that does not reflect anything.
/// @ingroup metaobjects
/// @see metaobject
constinit const __unspecified no_metaobject{};
#else
constinit const wrapped_metaobject<__reflexpr_id()> no_metaobject{};
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects any base-level entity.
/// @ingroup classification
/// @see find_if
/// @see meta_trait
/// @see has_trait
consteval auto reflects_object(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_object(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_object(mo);
}
#endif

consteval auto has_value(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_object(mo);
}

template <__metaobject_id M>
constexpr auto extract(wrapped_metaobject<M> mo) noexcept {
    return mo;
}

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the argument reflects a sequence of metaobjects.
/// @ingroup classification
/// @see is_object_sequence
/// @see is_empty
/// @see get_size
/// @see get_element
/// @see meta_trait
/// @see has_trait
consteval auto reflects_object_sequence(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_object_sequence(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_object_sequence(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a named base-level entity.
/// @ingroup classification
/// @see reflects_alias
/// @see get_name
/// @see has_name
/// @see get_display_name
/// @see get_full_name
/// @see meta_trait
/// @see has_trait
consteval auto reflects_named(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_named(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_named(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a base-level alias.
/// @ingroup classification
/// @see reflects_named
/// @see get_aliased
/// @see remove_all_aliases
/// @see meta_trait
/// @see has_trait
consteval auto reflects_alias(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_alias(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_alias(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a base-level entity with a type.
/// @ingroup classification
/// @see get_type
/// @see has_type
/// @see has_type_trait
/// @see meta_trait
/// @see has_trait
consteval auto reflects_typed(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_typed(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_typed(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a base-level scope.
/// @ingroup classification
/// @see reflects_namespace
/// @see reflects_global_scope
/// @see reflects_record
/// @see reflects_scope_member
/// @see get_scope
/// @see meta_trait
/// @see has_trait
consteval auto reflects_scope(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_scope(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_scope(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a base-level scope member.
/// @ingroup classification
/// @see reflects_scope
/// @see get_scope
/// @see meta_trait
/// @see has_trait
consteval auto reflects_scope_member(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_scope_member(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_scope_member(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a base-level global scope member.
/// @ingroup classification
/// @see reflects_global_scope
/// @see get_scope
consteval auto reflects_global_scope_member(metaobject auto) noexcept -> bool;
#else
template <__metaobject_id M>
consteval auto reflects_global_scope_member(wrapped_metaobject<M>) noexcept
  -> bool {
    if constexpr(__metaobject_is_meta_scope_member(M)) {
        return __metaobject_is_meta_global_scope(__metaobject_get_scope(M));
    } else {
        return false;
    }
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects an enumerator.
/// @ingroup classification
/// @see reflects_constant
/// @see reflects_enum
/// @see get_enumerators
/// @see get_underlying_type
/// @see meta_trait
/// @see has_trait
consteval auto reflects_enumerator(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_enumerator(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_enumerator(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a record member.
/// @ingroup classification
/// @see reflects_scope_member
/// @see reflects_record
/// @see get_data_members
/// @see get_member_types
/// @see get_member_functions
/// @see meta_trait
/// @see has_trait
consteval auto reflects_record_member(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_record_member(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_record_member(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a base class specifier.
/// @ingroup classification
/// @see get_base_classes
/// @see get_class
/// @see is_private
/// @see is_protected
/// @see is_public
/// @see is_virtual
/// @see meta_trait
/// @see has_trait
consteval auto reflects_base(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_base(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_base(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a namespace.
/// @ingroup classification
/// @see reflects_inline_namespace
/// @see reflects_global_scope
/// @see get_scope
/// @see meta_trait
/// @see has_trait
consteval auto reflects_namespace(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_namespace(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_namespace(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects an inline namespace.
/// @ingroup classification
/// @see reflects_namespace
/// @see meta_trait
/// @see has_trait
consteval auto reflects_inline_namespace(metaobject auto) noexcept -> bool;
#else
template <__metaobject_id M>
consteval auto reflects_inline_namespace(wrapped_metaobject<M>) noexcept
  -> bool {
    if constexpr(__metaobject_is_meta_namespace(M)) {
        return __metaobject_is_inline(M);
    } else {
        return false;
    }
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects the global scope.
/// @ingroup classification
/// @see reflects_namespace
/// @see meta_trait
/// @see has_trait
consteval auto reflects_global_scope(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_global_scope(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_global_scope(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a type.
/// @ingroup classification
/// @see get_type
/// @see get_reflected_type
/// @see meta_trait
/// @see has_trait
consteval auto reflects_type(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_type(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_type(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects an enumeration type.
/// @ingroup classification
/// @see reflects_enumerator
/// @see reflects_type
/// @see get_enumerators
/// @see get_underlying_type
/// @see meta_trait
/// @see has_trait
consteval auto reflects_enum(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_enum(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_enum(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a record types (union or class).
/// @ingroup classification
/// @see reflects_type
/// @see reflects_class
/// @see get_data_members
/// @see get_member_types
/// @see get_member_functions
/// @see get_constructors
/// @see get_destructors
/// @see get_operators
/// @see meta_trait
/// @see has_trait
consteval auto reflects_record(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_record(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_record(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a class.
/// @ingroup classification
/// @see reflects_type
/// @see reflects_record
/// @see reflects_lambda
/// @see get_data_members
/// @see get_member_types
/// @see get_member_functions
/// @see get_constructors
/// @see get_destructors
/// @see get_operators
/// @see get_base_classes
/// @see meta_trait
/// @see has_trait
consteval auto reflects_class(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_class(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_class(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a lambda closure type.
/// @ingroup classification
/// @see reflects_record
/// @see reflects_class
/// @see get_captures
/// @see meta_trait
/// @see has_trait
consteval auto reflects_lambda(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_lambda(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_lambda(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a constant.
/// @ingroup classification
/// @see reflects_enumerator
/// @see get_constant
/// @see get_value
/// @see meta_trait
/// @see has_trait
consteval auto reflects_constant(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_constant(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_constant(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a variable.
/// @ingroup classification
/// @see reflects_function_parameter
/// @see get_data_members
/// @see get_pointer
/// @see get_reference
/// @see get_value
/// @see meta_trait
/// @see has_trait
consteval auto reflects_variable(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_variable(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_variable(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a lambda capture.
/// @ingroup classification
/// @see reflects_lambda
/// @see get_captures
/// @see is_explicitly_captured
/// @see meta_trait
/// @see has_trait
consteval auto reflects_lambda_capture(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_lambda_capture(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_lambda_capture(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a function parameter.
/// @ingroup classification
/// @see reflects_callable
/// @see reflects_variable
/// @see get_parameters
/// @see meta_trait
/// @see has_trait
consteval auto reflects_function_parameter(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_function_parameter(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_is_meta_function_parameter(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a callable base-level entity.
/// @ingroup classification
/// @see reflects_function
/// @see reflects_function_parameter
/// @see get_parameters
/// @see meta_trait
/// @see has_trait
consteval auto reflects_callable(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_callable(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_callable(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a function.
/// @ingroup classification
/// @see reflects_callable
/// @see reflects_member_function
/// @see reflects_function_parameter
/// @see get_type
/// @see get_parameters
/// @see is_deleted
/// @see meta_trait
/// @see has_trait
consteval auto reflects_function(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_function(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_function(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a record member function.
/// @ingroup classification
/// @see reflects_callable
/// @see reflects_function
/// @see reflects_special_member_function
/// @see reflects_function_parameter
/// @see get_member_functions
/// @see get_scope
/// @see get_type
/// @see get_parameters
/// @see meta_trait
/// @see has_trait
consteval auto reflects_member_function(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_member_function(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_member_function(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a special member function.
/// @ingroup classification
/// @see reflects_callable
/// @see reflects_function
/// @see reflects_member_function
/// @see reflects_function_parameter
/// @see get_operators
/// @see get_scope
/// @see get_type
/// @see get_parameters
/// @see is_defaulted
/// @see is_deleted
/// @see meta_trait
/// @see has_trait
consteval auto reflects_special_member_function(metaobject auto) noexcept
  -> bool;
#else
consteval auto reflects_special_member_function(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_is_meta_special_member_function(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a constructor.
/// @ingroup classification
/// @see reflects_callable
/// @see reflects_operator
/// @see reflects_destructor
/// @see reflects_function_parameter
/// @see get_constructors
/// @see get_scope
/// @see get_parameters
/// @see is_defaulted
/// @see is_deleted
/// @see meta_trait
/// @see has_trait
consteval auto reflects_constructor(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_constructor(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_constructor(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a destructor.
/// @ingroup classification
/// @see reflects_callable
/// @see reflects_constructor
/// @see reflects_function_parameter
/// @see get_destructors
/// @see get_scope
/// @see get_parameters
/// @see is_defaulted
/// @see is_deleted
/// @see meta_trait
/// @see has_trait
consteval auto reflects_destructor(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_destructor(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_destructor(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects an operator.
/// @ingroup classification
/// @see reflects_function
/// @see reflects_conversion_operator
/// @see reflects_function_parameter
/// @see get_operators
/// @see get_scope
/// @see get_parameters
/// @see is_deleted
/// @see meta_trait
/// @see has_trait
consteval auto reflects_operator(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_operator(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_operator(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a conversion operator.
/// @ingroup classification
/// @see reflects_function
/// @see reflects_operator
/// @see reflects_function_parameter
/// @see get_operators
/// @see get_scope
/// @see get_parameters
/// @see meta_trait
/// @see has_trait
consteval auto reflects_conversion_operator(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_conversion_operator(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_is_meta_conversion_operator(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects an expression.
/// @ingroup classification
/// @see reflects_parenthesized_expression
/// @see reflects_construction_expression
/// @see reflects_function_call_expression
/// @see meta_trait
/// @see has_trait
consteval auto reflects_expression(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_expression(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_expression(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a parenthesized expression.
/// @ingroup classification
/// @see reflects_expression
/// @see reflects_construction_expression
/// @see reflects_function_call_expression
/// @see meta_trait
/// @see has_trait
consteval auto reflects_parenthesized_expression(metaobject auto) noexcept
  -> bool;
#else
consteval auto reflects_parenthesized_expression(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_is_meta_parenthesized_expression(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a constructor call expression.
/// @ingroup classification
/// @see reflects_expression
/// @see reflects_parenthesized_expression
/// @see reflects_function_call_expression
/// @see meta_trait
/// @see has_trait
consteval auto reflects_construction_expression(metaobject auto) noexcept
  -> bool;
#else
consteval auto reflects_construction_expression(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_is_meta_construction_expression(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a function call expression.
/// @ingroup classification
/// @see reflects_expression
/// @see reflects_parenthesized_expression
/// @see reflects_construction_expression
/// @see meta_trait
/// @see has_trait
consteval auto reflects_function_call_expression(metaobject auto) noexcept
  -> bool;
#else
consteval auto reflects_function_call_expression(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_is_meta_function_call_expression(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject reflects a specifier.
/// @ingroup classification
/// @see meta_trait
/// @see has_trait
consteval auto reflects_specifier(metaobject auto) noexcept -> bool;
#else
consteval auto reflects_specifier(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_specifier(mo);
}
#endif

// unary operations
// boolean

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected base-level entity is @c constexpr.
/// @ingroup operations
/// @see reflects_variable
/// @see reflects_callable
/// @see metaobject_operation
consteval auto is_constexpr(metaobject auto mo) noexcept
  -> bool requires(reflects_variable(mo) || reflects_callable(mo));
#else
consteval auto is_constexpr(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_constexpr(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected base-level entity is @c noexcept.
/// @ingroup operations
/// @see reflects_callable
/// @see metaobject_operation
consteval auto is_noexcept(metaobject auto mo) noexcept
  -> bool requires(reflects_callable(mo));
#else
consteval auto is_noexcept(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_noexcept(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected base-level entity is @c explicit.
/// @ingroup operations
/// @see reflects_constructor
/// @see reflects_conversion_operator
/// @see metaobject_operation
consteval auto is_explicit(metaobject auto mo) noexcept
  -> bool requires(reflects_constructor(mo) || reflects_conversion_operator(mo));
#else
consteval auto is_explicit(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_explicit(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected base-level entity is @c inline.
/// @ingroup operations
/// @see reflects_namespace
/// @see reflects_variable
/// @see reflects_callable
/// @see metaobject_operation
consteval auto is_inline(metaobject auto mo) noexcept -> bool requires(
  reflects_namespace(mo) || reflects_variable(mo) || reflects_callable(mo));
#else
consteval auto is_inline(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_inline(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected base-level entity is @c thread_local.
/// @ingroup operations
/// @see reflects_variable
/// @see metaobject_operation
consteval auto is_thread_local(metaobject auto mo) noexcept
  -> bool requires(reflects_variable(mo));
#else
consteval auto is_thread_local(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_thread_local(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected base-level entity is @c static.
/// @ingroup operations
/// @see reflects_variable
/// @see reflects_member_function
/// @see metaobject_operation
consteval auto is_static(metaobject auto mo) noexcept
  -> bool requires(reflects_variable(mo) || reflects_member_function(mo));
#else
consteval auto is_static(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_static(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected base-level entity is @c virtual.
/// @ingroup operations
/// @see reflects_base
/// @see reflects_destructor
/// @see reflects_member_function
/// @see metaobject_operation
consteval auto is_virtual(metaobject auto mo) noexcept -> bool requires(
  reflects_base(mo) || reflects_destructor(mo) || reflects_member_function(mo));
#else
consteval auto is_virtual(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_virtual(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected base-level entity is pure @c virtual.
/// @ingroup operations
/// @see reflects_destructor
/// @see reflects_member_function
/// @see metaobject_operation
consteval auto is_pure_virtual(metaobject auto mo) noexcept
  -> bool requires(reflects_destructor(mo) || reflects_member_function(mo));
#else
consteval auto is_pure_virtual(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_pure_virtual(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected base-level entity is @c final.
/// @ingroup operations
/// @see reflects_class
/// @see reflects_member_function
/// @see metaobject_operation
consteval auto is_final(metaobject auto mo) noexcept
  -> bool requires(reflects_class(mo) || reflects_member_function(mo));
#else
consteval auto is_final(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_final(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected base-level entity is @c private.
/// @ingroup operations
/// @see reflects_base
/// @see reflects_record_member
/// @see metaobject_operation
consteval auto is_private(metaobject auto mo) noexcept
  -> bool requires(reflects_record_member(mo) || reflects_base(mo));
#else
consteval auto is_private(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_private(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected base-level entity is @c protected.
/// @ingroup operations
/// @see reflects_base
/// @see reflects_record_member
/// @see metaobject_operation
consteval auto is_protected(metaobject auto mo) noexcept
  -> bool requires(reflects_record_member(mo) || reflects_base(mo));
#else
consteval auto is_protected(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_protected(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected base-level entity is @c public.
/// @ingroup operations
/// @see reflects_base
/// @see reflects_record_member
/// @see metaobject_operation
consteval auto is_public(metaobject auto mo) noexcept
  -> bool requires(reflects_record_member(mo) || reflects_base(mo));
#else
consteval auto is_public(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_public(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected base-level entity is unnamed.
/// @ingroup operations
/// @see reflects_named
/// @see get_name
/// @see get_display_name
/// @see metaobject_operation
consteval auto is_unnamed(metaobject auto mo) noexcept
  -> bool requires(reflects_named(mo));
#else
consteval auto is_unnamed(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_unnamed(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected base-level entity is an @c enum.
/// @ingroup operations
/// @see reflects_type
/// @see reflects_enum
/// @see is_scoped_enum
/// @see metaobject_operation
consteval auto is_enum(metaobject auto mo) noexcept
  -> bool requires(reflects_type(mo));
#else
consteval auto is_enum(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_enum(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected base-level entity is a scoped @c enum.
/// @ingroup operations
/// @see reflects_type
/// @see reflects_enum
/// @see is_enum
/// @see metaobject_operation
consteval auto is_scoped_enum(metaobject auto mo) noexcept
  -> bool requires(reflects_type(mo));
#else
consteval auto is_scoped_enum(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_scoped_enum(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected base-level entity is an @c union.
/// @ingroup operations
/// @see reflects_type
/// @see is_union
/// @see uses_class_key
/// @see uses_struct_key
/// @see metaobject_operation
consteval auto is_union(metaobject auto mo) noexcept
  -> bool requires(reflects_type(mo));
#else
consteval auto is_union(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_union(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected record type uses a @c class specifier.
/// @ingroup operations
/// @see reflects_type
/// @see is_union
/// @see uses_struct_key
/// @see metaobject_operation
consteval auto uses_class_key(metaobject auto mo) noexcept
  -> bool requires(reflects_type(mo));
#else
consteval auto uses_class_key(__metaobject_id mo) noexcept -> bool {
    return __metaobject_uses_class_key(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected record type uses a @c struct specifier.
/// @ingroup operations
/// @see reflects_type
/// @see is_union
/// @see uses_class_key
/// @see metaobject_operation
consteval auto uses_struct_key(metaobject auto mo) noexcept
  -> bool requires(reflects_type(mo));
#else
consteval auto uses_struct_key(__metaobject_id mo) noexcept -> bool {
    return __metaobject_uses_struct_key(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected lambda closure uses default capture by copy.
/// @ingroup operations
/// @see reflects_lambda
/// @see uses_default_reference_capture
/// @see get_captures
/// @see metaobject_operation
consteval auto uses_default_copy_capture(metaobject auto mo) noexcept
  -> bool requires(reflects_lambda(mo));
#else
consteval auto uses_default_copy_capture(__metaobject_id mo) noexcept -> bool {
    return __metaobject_uses_default_copy_capture(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected lambda closure uses default capture by reference.
/// @ingroup operations
/// @see reflects_lambda
/// @see uses_default_copy_capture
/// @see get_captures
/// @see metaobject_operation
consteval auto uses_default_reference_capture(metaobject auto mo) noexcept
  -> bool requires(reflects_lambda(mo));
#else
consteval auto uses_default_reference_capture(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_uses_default_reference_capture(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected lambda closure's call operator is @c const.
/// @ingroup operations
/// @see reflects_lambda
/// @see get_captures
/// @see metaobject_operation
consteval auto is_call_operator_const(metaobject auto mo) noexcept
  -> bool requires(reflects_lambda(mo));
#else
consteval auto is_call_operator_const(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_call_operator_const(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected lambda capture is explicitly captured.
/// @ingroup operations
/// @see reflects_lambda_capture
/// @see get_captures
/// @see metaobject_operation
consteval auto is_explicitly_captured(metaobject auto mo) noexcept
  -> bool requires(reflects_lambda_capture(mo));
#else
consteval auto is_explicitly_captured(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_explicitly_captured(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected function parameter has default argument.
/// @ingroup operations
/// @see reflects_function_parameter
/// @see get_parameters
/// @see metaobject_operation
consteval auto has_default_argument(metaobject auto mo) noexcept
  -> bool requires(reflects_function_parameter(mo));
#else
consteval auto has_default_argument(__metaobject_id mo) noexcept -> bool {
    return __metaobject_has_default_argument(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected member function is @c const.
/// @ingroup operations
/// @see reflects_member_function
/// @see is_volatile
/// @see has_lvalueref_qualifier
/// @see has_rvalueref_qualifier
/// @see metaobject_operation
consteval auto is_const(metaobject auto mo) noexcept
  -> bool requires(reflects_member_function(mo));
#else
consteval auto is_const(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_const(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected member function is @c volatile.
/// @ingroup operations
/// @see reflects_member_function
/// @see is_const
/// @see has_lvalueref_qualifier
/// @see has_rvalueref_qualifier
/// @see metaobject_operation
consteval auto is_volatile(metaobject auto mo) noexcept
  -> bool requires(reflects_member_function(mo));
#else
consteval auto is_volatile(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_volatile(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected member function has lvalue-ref qualifier.
/// @ingroup operations
/// @see reflects_member_function
/// @see is_const
/// @see is_volatile
/// @see has_rvalueref_qualifier
/// @see metaobject_operation
consteval auto has_lvalueref_qualifier(metaobject auto mo) noexcept
  -> bool requires(reflects_member_function(mo));
#else
consteval auto has_lvalueref_qualifier(__metaobject_id mo) noexcept -> bool {
    return __metaobject_has_lvalueref_qualifier(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected member function has rvalue-ref qualifier.
/// @ingroup operations
/// @see reflects_member_function
/// @see is_const
/// @see is_volatile
/// @see has_rvalueref_qualifier
/// @see metaobject_operation
consteval auto has_rvalueref_qualifier(metaobject auto mo) noexcept
  -> bool requires(reflects_member_function(mo));
#else
consteval auto has_rvalueref_qualifier(__metaobject_id mo) noexcept -> bool {
    return __metaobject_has_rvalueref_qualifier(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected special member function is implicitly declared.
/// @ingroup operations
/// @see reflects_member_function
/// @see reflects_special_member_function
/// @see is_defaulted
/// @see is_deleted
/// @see metaobject_operation
consteval auto is_implicitly_declared(metaobject auto mo) noexcept
  -> bool requires(reflects_special_member_function(mo));
#else
consteval auto is_implicitly_declared(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_implicitly_declared(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected special member function is defaulted.
/// @ingroup operations
/// @see reflects_member_function
/// @see reflects_special_member_function
/// @see is_implicitly_declared
/// @see is_deleted
/// @see metaobject_operation
consteval auto is_defaulted(metaobject auto mo) noexcept
  -> bool requires(reflects_special_member_function(mo));
#else
consteval auto is_defaulted(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_defaulted(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected function is deleted.
/// @ingroup operations
/// @see reflects_member_function
/// @see reflects_special_member_function
/// @see is_implicitly_declared
/// @see is_defaulted
/// @see metaobject_operation
consteval auto is_deleted(metaobject auto mo) noexcept
  -> bool requires(reflects_callable(mo));
#else
consteval auto is_deleted(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_deleted(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected constructor is copy constructor.
/// @ingroup operations
/// @see reflects_constructor
/// @see get_constructors
/// @see is_move_constructor
/// @see is_copy_assignment_operator
/// @see metaobject_operation
consteval auto is_copy_constructor(metaobject auto mo) noexcept
  -> bool requires(reflects_constructor(mo));
#else
consteval auto is_copy_constructor(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_copy_constructor(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected constructor is move constructor.
/// @ingroup operations
/// @see reflects_constructor
/// @see get_constructors
/// @see is_copy_constructor
/// @see is_move_assignment_operator
/// @see metaobject_operation
consteval auto is_move_constructor(metaobject auto mo) noexcept
  -> bool requires(reflects_constructor(mo));
#else
consteval auto is_move_constructor(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_move_constructor(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected operator is copy assignment operator.
/// @ingroup operations
/// @see reflects_operator
/// @see reflects_special_member_function
/// @see get_operators
/// @see is_copy_constructor
/// @see is_move_assignment_operator
/// @see metaobject_operation
consteval auto is_copy_assignment_operator(metaobject auto mo) noexcept
  -> bool requires(
    reflects_operator(mo) && reflects_special_member_function(mo));
#else
consteval auto is_copy_assignment_operator(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_is_copy_assignment_operator(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the reflected operator is move assignment operator.
/// @ingroup operations
/// @see reflects_operator
/// @see reflects_special_member_function
/// @see get_operators
/// @see is_move_constructor
/// @see is_copy_assignment_operator
/// @see metaobject_operation
consteval auto is_move_assignment_operator(metaobject auto mo) noexcept
  -> bool requires(
    reflects_operator(mo) && reflects_special_member_function(mo));
#else
consteval auto is_move_assignment_operator(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_is_move_assignment_operator(mo);
}
#endif

consteval auto is_empty(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_empty(mo);
}

consteval auto has_one_element(__metaobject_id mo) noexcept -> bool {
    return __metaobject_get_size(mo) == 1Z;
}

consteval auto has_multiple_elements(__metaobject_id mo) noexcept -> bool {
    return __metaobject_get_size(mo) > 1Z;
}

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the two metaobjects reflect the same base-level entity.
/// @ingroup operations
/// @see get_hash
consteval auto reflect_same(metaobject auto ml, metaobject auto mr) noexcept
  -> bool;
#else
template <__metaobject_id Ml, __metaobject_id Mr>
consteval auto
reflect_same(wrapped_metaobject<Ml>, wrapped_metaobject<Mr>) noexcept -> bool {
    return __metaobject_reflects_same(Ml, Mr);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if the base name of the reflected entity is equal to @p str.
/// @ingroup operations
/// @see reflects_named
/// @see get_name
/// @see get_display_name
consteval auto has_name(metaobject auto mo, string_view str) noexcept
  -> bool requires(reflects_named(mo));
#else
template <__metaobject_id M, size_t L>
consteval auto has_name(wrapped_metaobject<M>, const char (&str)[L]) noexcept
  -> bool requires(__metaobject_is_meta_named(M)) {
    return __builtin_strcmp(__metaobject_get_name(M), str) == 0;
}

template <__metaobject_id M>
constexpr auto has_name(wrapped_metaobject<M> mo, string_view str) noexcept
  -> bool requires(__metaobject_is_meta_named(M)) {
    return get_name(mo) == str;
}
#endif

// integer
#if defined(MIRROR_DOXYGEN)
/// @brief Returns a unique metaobject identifier value.
/// @ingroup operations
/// @see reflects_object
/// @see metaobject_operation
consteval auto get_id(metaobject auto mo) noexcept -> size_t;
#else
consteval auto get_id(__metaobject_id mo) noexcept -> size_t {
    return __metaobject_get_id_value(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns source file line of the reflected entity if available.
/// @ingroup operations
/// @see reflects_object
/// @see get_source_column
/// @see get_source_file_name
/// @see metaobject_operation
consteval auto get_source_line(metaobject auto mo) noexcept -> size_t;
#else
consteval auto get_source_line(__metaobject_id mo) noexcept -> size_t {
    return __metaobject_get_source_line(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns source file column of the reflected entity if available.
/// @ingroup operations
/// @see reflects_object
/// @see get_source_line
/// @see get_source_file_name
/// @see metaobject_operation
consteval auto get_source_column(metaobject auto mo) noexcept -> size_t;
#else
consteval auto get_source_column(__metaobject_id mo) noexcept -> size_t {
    return __metaobject_get_source_column(mo);
}
#endif

consteval auto get_size(__metaobject_id mo) noexcept -> size_t {
    return __metaobject_get_size(mo);
}

consteval auto get_size(std::string_view s) noexcept -> size_t {
    return s.size();
}

template <__metaobject_id M>
struct _get_pointer
  : integral_constant<
      __unrefltype(__metaobject_get_pointer(M)),
      __metaobject_get_pointer(M)> {};

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a pointer to the reflected base-level entity.
/// @ingroup operations
/// @see reflects_variable
/// @see reflects_function
/// @see get_value
/// @see get_reference
/// @see get_constant
/// @see metaobject_operation
consteval auto get_pointer(metaobject auto mo) noexcept
  requires(reflects_variable(mo) || reflects_function(mo));
#else
template <__metaobject_id M>
consteval auto get_pointer(wrapped_metaobject<M>) noexcept requires(
  __metaobject_is_meta_variable(M) || __metaobject_is_meta_function(M)) {
    return _get_pointer<M>::value;
}
#endif

template <__metaobject_id M>
struct _get_constant
  : integral_constant<
      __unrefltype(__metaobject_get_constant(M)),
      __metaobject_get_constant(M)> {};

#if defined(MIRROR_DOXYGEN)
/// @brief Returns the value of the reflected base-level constant.
/// @ingroup operations
/// @see reflects_constant
/// @see get_pointer
/// @see get_reference
/// @see get_value
/// @see metaobject_operation
constexpr auto get_constant(metaobject auto mo) noexcept
  requires(reflects_constant(mo));
#else
template <__metaobject_id M>
constexpr auto get_constant(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_constant(M)) {
    return _get_constant<M>::value;
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns the value of the reflected base-level constant.
/// @ingroup operations
/// @see reflects_constant
/// @see get_pointer
/// @see get_reference
/// @see get_constant
/// @see metaobject_operation
constexpr auto get_value(metaobject auto mo) noexcept
  requires(reflects_constant(mo));
#else
template <__metaobject_id M>
constexpr auto get_value(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_constant(M)) {
    return _get_constant<M>::value;
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns the value of the reflected base-level entity.
/// @ingroup operations
/// @see reflects_variable
/// @see get_pointer
/// @see get_reference
/// @see get_constant
constexpr const auto& get_value(metaobject auto mo) noexcept
  requires(reflects_variable(mo));
#else
template <__metaobject_id M>
constexpr const auto& get_value(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_variable(M)) {
    return *_get_pointer<M>::value;
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns the value of the reflected base-level data member in @p obj.
/// @ingroup operations
/// @see reflects_record_member
/// @see reflects_variable
/// @see get_pointer
/// @see get_reference
/// @see get_constant
template <class C>
constexpr const auto& get_value(metaobject auto mo, const C& obj) noexcept
  requires(reflects_record_member(mo) && reflects_variable(mo));
#else
template <__metaobject_id M, class C>
constexpr const auto& get_value(wrapped_metaobject<M>, const C& obj) noexcept
  requires(
    __metaobject_is_meta_record_member(M) && __metaobject_is_meta_variable(M)) {
    return obj.*_get_pointer<M>::value;
}
#endif

template <__metaobject_id M, typename T>
constexpr auto has_value(wrapped_metaobject<M> mo, const T value) noexcept
  -> bool {
    return get_value(mo) == value;
}

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a reference to the reflected base-level entity.
/// @ingroup operations
/// @see reflects_variable
/// @see get_value
/// @see get_pointer
/// @see get_constant
constexpr auto& get_reference(metaobject auto mo) noexcept
  requires(reflects_variable(mo));
#else
template <__metaobject_id M>
constexpr auto& get_reference(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_variable(M)) {
    return *_get_pointer<M>::value;
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a reference to the reflected base-level data member in @p obj.
/// @ingroup operations
/// @see reflects_record_member
/// @see reflects_variable
/// @see get_value
/// @see get_pointer
/// @see get_constant
template <class C>
constexpr auto& get_reference(metaobject auto mo, C& obj) noexcept
  requires(reflects_record_member(mo) && reflects_variable(mo));
#else
template <__metaobject_id M, class C>
constexpr auto& get_reference(wrapped_metaobject<M>, C& obj) noexcept requires(
  __metaobject_is_meta_record_member(M) && __metaobject_is_meta_variable(M)) {
    return obj.*_get_pointer<M>::value;
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Invokes the reflected member function on @p obj with specified @p args.
/// @ingroup operations
/// @see reflects_member_function
/// @see get_pointer
/// @see invoke
/// @see apply
constexpr auto invoke_on(metaobject auto mo auto& obj, auto&&... args) requires(
  reflects_member_function(mo));
#else
template <__metaobject_id M, typename C, typename... A>
constexpr auto invoke_on(
  wrapped_metaobject<M> mo,
  C& obj,
  A&&... args) requires(__metaobject_is_meta_member_function(M)) {
    if constexpr(is_static(mo)) {
        return (*_get_pointer<M>::value)(std::forward<A>(args)...);
    } else {
        return (obj.*_get_pointer<M>::value)(std::forward<A>(args)...);
    }
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Invokes the reflected function with the specified @p args.
/// @ingroup operations
/// @see reflects_function
/// @see reflects_member_function
/// @see is_static
/// @see get_pointer
/// @see invoke_on
/// @see apply_on
constexpr auto invoke(metaobject auto mo, auto&&... args) requires(
  reflects_function(mo) ||
  (reflects_member_function(mo) && __metaobject_is_static(M)));
#else
template <__metaobject_id M, typename... A>
constexpr auto invoke(wrapped_metaobject<M>, A&&... args) requires(
  __metaobject_is_meta_function(M) ||
  (__metaobject_is_meta_member_function(M) && __metaobject_is_static(M))) {
    return (*_get_pointer<M>::value)(std::forward<A>(args)...);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Invokes the reflected member function on @p obj with specified @p args.
/// @ingroup operations
/// @see reflects_member_function
/// @see is_static
/// @see get_pointer
/// @see get_reference
/// @see invoke_on
/// @see apply
constexpr auto invoke(metaobject auto mo, auto& obj, auto&&... args) requires(
  reflects_member_function(mo) && !is_static(mo));
#else
template <__metaobject_id M, typename C, typename... A>
constexpr auto invoke(wrapped_metaobject<M>, C& obj, A&&... args) requires(
  __metaobject_is_meta_member_function(M) && !__metaobject_is_static(M)) {
    return (obj.*_get_pointer<M>::value)(std::forward<A>(args)...);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Invokes the reflected constructor with the specified @p args.
/// @ingroup operations
/// @see reflects_constructor
/// @see get_pointer
/// @see invoke_on
/// @see apply
constexpr auto
invoke(metaobject auto mo, auto&&... args) requires(reflects_constructor(mo));
#else
template <__metaobject_id M, typename... A>
constexpr auto invoke(wrapped_metaobject<M>, A&&... args) -> __unrefltype(
  __metaobject_get_scope(M)) requires(__metaobject_is_meta_constructor(M)) {
    return __unrefltype(__metaobject_get_scope(M))(std::forward<A>(args)...);
}
#endif

// string
consteval auto get_debug_info(__metaobject_id mo) noexcept -> string_view {
    return {__metaobject_get_debug_info(mo)};
}

#if defined(MIRROR_DOXYGEN)
/// @brief Returns source file column of the reflected entity if available.
/// @ingroup operations
/// @see reflects_object
/// @see get_source_line
/// @see get_source_column
/// @see metaobject_operation
consteval auto get_source_file_name(metaobject auto mo) noexcept -> string_view;
#else
consteval auto get_source_file_name(__metaobject_id mo) noexcept
  -> string_view {
    return {
      __metaobject_get_source_file_name(mo),
      __metaobject_source_file_name_len(mo)};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns the unqualified "base name" of the reflected base-level entity.
/// @ingroup operations
/// @see reflects_named
/// @see get_full_name
/// @see get_display_name
/// @see has_name
/// @see metaobject_operation
consteval auto get_name(metaobject auto mo) noexcept -> string_view
  requires(reflects_named(mo));
#else
consteval auto get_name(__metaobject_id mo) noexcept -> string_view {
    return {__metaobject_get_name(mo), __metaobject_name_len(mo)};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns the user-friendly name of the reflected base-level entity.
/// @ingroup operations
/// @see reflects_named
/// @see get_name
/// @see get_display_name
/// @see metaobject_operation
consteval auto get_display_name(metaobject auto mo) noexcept -> string_view
  requires(reflects_named(mo));
#else
consteval auto get_display_name(__metaobject_id mo) noexcept -> string_view {
    return {
      __metaobject_get_display_name(mo), __metaobject_display_name_len(mo)};
}
#endif

// metaobject
#if defined(MIRROR_DOXYGEN)
/// @brief Returns a reflection of the scope of a reflected scope member.
/// @ingroup operations
/// @see reflects_scope_member
/// @see reflects_scope
/// @see metaobject_operation
constexpr auto get_scope(metaobject auto mo) noexcept
  requires(reflects_scope_member(mo));
#else
template <__metaobject_id M>
constexpr auto get_scope(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_scope_member(M)) {
    return wrapped_metaobject<__metaobject_get_scope(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a reflection of the type of a reflected typed entity.
/// @ingroup operations
/// @see reflects_typed
/// @see get_reflected_type
/// @see metaobject_operation
constexpr auto get_type(metaobject auto mo) noexcept
  requires(reflects_typed(mo));
#else
template <__metaobject_id M>
constexpr auto get_type(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_typed(M)) {
    return wrapped_metaobject<__metaobject_get_type(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a reflection of the underlying type of a reflected enum,
/// @ingroup operations
/// @see get_constant
/// @see reflects_enum
/// @see metaobject_operation
constexpr auto get_underlying_type(metaobject auto mo) noexcept
  requires(reflects_enum(mo));
#else
template <__metaobject_id M>
constexpr auto get_underlying_type(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_enum(M)) {
    return wrapped_metaobject<__metaobject_get_underlying_type(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a reflection of the aliased entity reflected by a reflected alias.
/// @ingroup operations
/// @see reflects_named
/// @see reflects_alias
/// @see remove_all_aliases
/// @see metaobject_operation
constexpr auto get_aliased(metaobject auto mo) noexcept
  requires(reflects_alias(mo));
#else
template <__metaobject_id M>
constexpr auto get_aliased(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_alias(M)) {
    return wrapped_metaobject<__metaobject_get_aliased(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Removes all aliases from a potentially aliased reflected entity.
/// @ingroup operations
/// @see reflects_alias
/// @see get_aliased
/// @see metaobject_operation
constexpr auto remove_all_aliases(metaobject auto mo) noexcept;
#else
template <__metaobject_id M>
constexpr auto remove_all_aliases(wrapped_metaobject<M> mo) noexcept {
    if constexpr(__metaobject_is_meta_alias(M)) {
        return remove_all_aliases(
          wrapped_metaobject<__metaobject_get_aliased(M)>{});
    } else {
        return mo;
    }
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns the reflection of the class in a reflected base class specifier.
/// @ingroup operations
/// @see get_base_classes
/// @see reflects_base
/// @see is_private
/// @see is_protected
/// @see is_public
/// @see is_virtual
/// @see metaobject_operation
constexpr auto get_class(metaobject auto mo) noexcept
  requires(reflects_base(mo));
#else
template <__metaobject_id M>
constexpr auto get_class(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_base(M)) {
    return wrapped_metaobject<__metaobject_get_class(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns the reflection of the sub-expression of a parenthesized expression.
/// @ingroup operations
/// @see reflects_parenthesized_expression
/// @see reflects_function_call_expression
/// @see reflects_construction_expression
/// @see get_callable
/// @see metaobject_operation
constexpr auto get_subexpression(metaobject auto mo) noexcept
  requires(reflects_parenthesized_expression(mo));
#else
template <__metaobject_id M>
constexpr auto get_subexpression(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_parenthesized_expression(M)) {
    return wrapped_metaobject<__metaobject_get_subexpression(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns the reflection of the sub-expression of a parenthesized expression.
/// @ingroup operations
/// @see reflects_parenthesized_expression
/// @see reflects_construction_expression
/// @see reflects_function_call_expression
/// @see get_subexpression
/// @see metaobject_operation
constexpr auto get_callable(metaobject auto mo) noexcept requires(
  reflects_construction_expression(mo) ||
  reflects_function_call_expression(mo));
#else
template <__metaobject_id M>
constexpr auto get_callable(wrapped_metaobject<M>) noexcept requires(
  __metaobject_is_meta_construction_expression(M) ||
  __metaobject_is_meta_function_call_expression(M)) {
    return wrapped_metaobject<__metaobject_get_callable(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a sequence of base class specifier reflections of a reflected class.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_base
/// @see is_empty
/// @see get_size
/// @see get_class
/// @see metaobject_operation
constexpr auto get_base_classes(metaobject auto mo) noexcept
  requires(reflects_class(mo));
#else
template <__metaobject_id M>
constexpr auto get_base_classes(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_class(M)) {
    return wrapped_metaobject<__metaobject_get_base_classes(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a sequence of member type reflections of a reflected class.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_type
/// @see is_empty
/// @see get_size
/// @see get_type
/// @see metaobject_operation
constexpr auto get_member_types(metaobject auto mo) noexcept
  requires(reflects_record(mo));
#else
template <__metaobject_id M>
constexpr auto get_member_types(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_member_types(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a sequence of member type reflections of a reflected class.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_variable
/// @see is_empty
/// @see get_size
/// @see get_pointer
/// @see get_reference
/// @see get_value
/// @see metaobject_operation
constexpr auto get_data_members(metaobject auto mo) noexcept
  requires(reflects_record(mo));
#else
template <__metaobject_id M>
constexpr auto get_data_members(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_data_members(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a sequence of member function reflections of a reflected class.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_function
/// @see is_empty
/// @see get_size
/// @see get_pointer
/// @see invoke_on
/// @see invoke
/// @see apply
/// @see apply_on
/// @see metaobject_operation
constexpr auto get_member_functions(metaobject auto mo) noexcept
  requires(reflects_record(mo));
#else
template <__metaobject_id M>
constexpr auto get_member_functions(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_member_functions(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a sequence of constructor reflections of a reflected class.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_constructor
/// @see is_empty
/// @see get_size
/// @see invoke_on
/// @see invoke
/// @see metaobject_operation
constexpr auto get_constructors(metaobject auto mo) noexcept
  requires(reflects_record(mo));
#else
template <__metaobject_id M>
constexpr auto get_constructors(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_constructors(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a sequence of destructors reflections of a reflected class.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_constructor
/// @see is_empty
/// @see get_size
/// @see metaobject_operation
constexpr auto get_destructors(metaobject auto mo) noexcept
  requires(reflects_record(mo));
#else
template <__metaobject_id M>
constexpr auto get_destructors(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_destructors(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a sequence of operator reflections of a reflected class.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_operator
/// @see is_empty
/// @see get_size
/// @see invoke_on
/// @see invoke
/// @see metaobject_operation
constexpr auto get_operators(metaobject auto mo) noexcept
  requires(reflects_record(mo));
#else
template <__metaobject_id M>
constexpr auto get_operators(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_operators(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a sequence of enumerator reflections of a reflected enum type.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_enumerator
/// @see is_empty
/// @see get_size
/// @see get_constant
/// @see metaobject_operation
constexpr auto get_enumerators(metaobject auto mo) noexcept
  requires(reflects_enum(mo));
#else
template <__metaobject_id M>
constexpr auto get_enumerators(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_enum(M)) {
    return wrapped_metaobject<__metaobject_get_enumerators(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a sequence of parameter reflections of a reflected callable.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_function_parameter
/// @see is_empty
/// @see get_size
/// @see has_default_argument
/// @see metaobject_operation
constexpr auto get_parameters(metaobject auto mo) noexcept
  requires(reflects_callable(mo));
#else
template <__metaobject_id M>
constexpr auto get_parameters(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_callable(M)) {
    return wrapped_metaobject<__metaobject_get_parameters(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a sequence of capture reflections of a reflected closure.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_lambda_capture
/// @see is_empty
/// @see get_size
/// @see is_explicitly_captured
/// @see metaobject_operation
constexpr auto get_captures(metaobject auto mo) noexcept
  requires(reflects_lambda(mo));
#else
template <__metaobject_id M>
constexpr auto get_captures(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_lambda(M)) {
    return wrapped_metaobject<__metaobject_get_captures(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a sequence with private elements filtered out.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see hide_protected
/// @see metaobject_operation
constexpr auto hide_private(metaobject auto mo) noexcept
  requires(reflects_object_sequence(mo));
#else
template <__metaobject_id M>
constexpr auto hide_private(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return wrapped_metaobject<__metaobject_hide_private(M)>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns a sequence with private and protected elements filtered out.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see hide_private
/// @see metaobject_operation
constexpr auto hide_protected(metaobject auto mo) noexcept
  requires(reflects_object_sequence(mo));
#else
template <__metaobject_id M>
constexpr auto hide_protected(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return wrapped_metaobject<__metaobject_hide_protected(M)>{};
}
#endif

template <size_t I, __metaobject_id M>
constexpr auto get_element(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return wrapped_metaobject<__metaobject_get_element(M, I)>{};
}

template <__metaobject_id M>
constexpr auto get_front(wrapped_metaobject<M>) noexcept requires(
  __metaobject_is_meta_object_sequence(M) && !__metaobject_is_empty(M)) {
    return wrapped_metaobject<__metaobject_get_element(M, 0Z)>{};
}

// type unreflection
template <__metaobject_id M>
using _get_reflected_type = type_identity<__unrefltype(M)>;

#if defined(MIRROR_DOXYGEN)
/// @brief Returns the base-level type reflected by a type reflecting metaobject.
/// @ingroup operations
/// @see reflects_type
/// @see get_type
/// @see get_reflected_type
/// @see get_transformed_type_t
template <typename M>
using get_reflected_type_t = __unspecified;
#else
template <typename M>
using get_reflected_type_t = __unrefltype(unwrap(M{}));
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns type_identity of base-level type reflected by a metaobject.
/// @ingroup operations
/// @see reflects_type
/// @see get_reflected_type_of
/// @see get_type
/// @see get_reflected_type_t
consteval auto get_reflected_type(metaobject auto mo) noexcept
  requires(reflects_type(mo));
#else
template <__metaobject_id M>
consteval auto get_reflected_type(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_type(M)) {
    return _get_reflected_type<M>{};
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Returns type_identity of base-level type from a typed metaobject.
/// @ingroup operations
/// @see reflects_type
/// @see get_reflected_type
/// @see get_type
/// @see get_sizeof
/// @see get_reflected_type_t
consteval auto get_reflected_type_of(metaobject auto mo) noexcept
  requires(reflects_typed(mo));
#else
template <__metaobject_id M>
consteval auto get_reflected_type_of(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_typed(M)) {
    return _get_reflected_type<__metaobject_get_type(M)>{};
}
#endif

template <template <typename T> class Transform, __metaobject_id M>
using _get_transformed_type = Transform<__unrefltype(M)>;

template <template <typename T> class Transform, typename M>
using get_transformed_type_t = Transform<__unrefltype(unwrap(M{}))>;

template <template <typename T> class Transform, __metaobject_id M>
consteval auto get_transformed_type(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_type(M)) {
    return _get_transformed_type<Transform, M>{};
}

#if defined(MIRROR_DOXYGEN)
/// @brief Returns the size (in bytes) of the reflected type.
/// @ingroup operations
/// @see reflects_type
/// @see get_reflected_type
/// @see get_type
consteval auto get_sizeof(metaobject auto mo) noexcept
  requires(reflects_type(mo) || reflects_typed(mo));
#else
template <__metaobject_id M>
consteval auto get_sizeof(wrapped_metaobject<M> mo) noexcept
  requires(__metaobject_is_meta_type(M) || __metaobject_is_meta_typed(M)) {
    if constexpr(__metaobject_is_meta_typed(M)) {
        return get_sizeof(get_type(mo));
    } else {
        return sizeof(__unrefltype(M));
    }
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if type-reflecting metaobject reflects the specified type.
/// @ingroup operations
/// @see reflects_type
/// @see has_type
/// @see has_type_trait
/// @see has_type_with_trait
/// @see get_type
/// @see get_reflected_type
template <typename T>
consteval auto is_type(metaobject auto mo, type_identity<T> = {}) noexcept
  -> bool requires(reflects_type(mo));
#else
template <typename T, __metaobject_id M>
consteval auto is_type(wrapped_metaobject<M>, type_identity<T> = {}) noexcept
  -> bool requires(__metaobject_is_meta_type(M)) {
    return std::is_same_v<__unrefltype(M), T>;
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if type-reflecting metaobject reflects the specified type.
/// @ingroup operations
/// @see reflects_type
/// @see is_type
/// @see has_type
/// @see has_type_with_trait
/// @see get_type
/// @see get_reflected_type
consteval auto has_type_trait(metaobject auto mo) noexcept
  -> bool requires(reflects_type(mo));
#else
template <template <typename> class Trait, __metaobject_id M>
consteval auto has_type_trait(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_type(M)) {
    return Trait<__unrefltype(M)>::value;
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if typed metaobject has the specified type.
/// @ingroup operations
/// @see reflects_typed
/// @see is_type
/// @see has_type_trait
/// @see has_type_with_trait
/// @see get_type
/// @see get_reflected_type_of
template <typename T>
consteval auto has_type(metaobject auto mo, type_identity<T> = {}) noexcept
  -> bool;
#else
template <typename T, __metaobject_id M>
consteval auto has_type(wrapped_metaobject<M>, type_identity<T> = {}) noexcept
  -> bool {
    if constexpr(__metaobject_is_meta_typed(M)) {
        return std::is_same_v<__unrefltype(__metaobject_get_type(M)), T>;
    } else {
        return false;
    }
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if typed metaobject has type with specified trait.
/// @ingroup operations
/// @see reflects_type
/// @see is_type
/// @see has_type
/// @see has_type_with_trait
/// @see get_type
/// @see get_reflected_type
template <template <typename> class Trait>
consteval auto has_type_with_trait(metaobject auto mo) noexcept -> bool;
#else
template <template <typename> class Trait, __metaobject_id M>
consteval auto has_type_with_trait(wrapped_metaobject<M>) noexcept -> bool {
    if constexpr(__metaobject_is_meta_typed(M)) {
        return Trait<__unrefltype(__metaobject_get_type(M))>::value;
    } else {
        return false;
    }
}
#endif

// reflection "operator"
#if defined(MIRROR_YCM)
#define mirror(...) \
    ::mirror::wrapped_metaobject<0U> {}
#elif defined(MIRROR_DOXYGEN)
#define mirror(...) \
    ::mirror::wrapped_metaobject<__metaobject_id{}> {}
#else
#define mirror(...) \
    ::mirror::wrapped_metaobject<__reflexpr_id(__VA_ARGS__)> {}
#endif

} // namespace mirror

#endif // !_LIBCPP_HAS_NO_REFLECTION && !_LIBCPP_HAS_NO_REFLECTION_EXT

#endif // MIRROR_PRIMITIVES_HPP
