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
/// @brief Internal type, values of which represent metaobjects.
/// @ingroup metaobjects
using __metaobject_id = __unspecified;
#elif defined(MIRROR_YCM)
using __metaobject_id = unsigned;
#endif

namespace mirror {

using std::integral_constant;
using std::string_view;
using std::type_identity;

template <typename... T>
struct type_list {};

/// @brief Template implementing the metaobject type reflecting base-level entities.
/// @ingroup metaobjects
/// @see metaobject
/// @see reflects_metaobject
/// @see no_metaobject
/// @see unpacked_metaobject_sequence
template <__metaobject_id M>
struct wrapped_metaobject {};

/// @brief Indicates if the argument is a metaobject.
/// @ingroup classification
/// @see reflects_object
template <__metaobject_id M>
consteval auto is_object(wrapped_metaobject<M>) noexcept -> bool {
    return true;
}

template <typename X>
consteval auto is_object(const X&) noexcept -> bool {
    return false;
}

/// @brief Concept for metaobject types.
/// @ingroup classification
/// @see reflects_object
/// @see is_object
/// @see wrapped_metaobject
/// @see no_metaobject
template <typename X>
concept metaobject = is_object(X{});

template <__metaobject_id M>
consteval auto unwrap(wrapped_metaobject<M>) noexcept -> __metaobject_id {
    return M;
}

template <__metaobject_id... M>
using expanded_metaobject_sequence = type_list<wrapped_metaobject<M>...>;

/// @brief Special instance of metaobject that does not reflect anything.
/// @ingroup metaobjects
/// @see metaobject
constinit const wrapped_metaobject<__reflexpr_id()> no_metaobject{};

/// @brief Indicates if a metaobject reflects any base-level entity.
/// @ingroup classification
/// @see find_if
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_object(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_object(M);
}

template <__metaobject_id M>
consteval auto has_value(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_object(M);
}

template <__metaobject_id M>
constexpr auto extract(wrapped_metaobject<M> mo) noexcept {
    return mo;
}

/// @brief Indicates if the argument reflects a sequence of metaobjects.
/// @ingroup classification
/// @see is_object_sequence
/// @see is_empty
/// @see get_size
/// @see get_element
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_object_sequence(wrapped_metaobject<M>) noexcept
  -> bool {
    return __metaobject_is_meta_object_sequence(M);
}

/// @brief Indicates if a metaobject reflects a named base-level entity.
/// @ingroup classification
/// @see reflects_alias
/// @see get_name
/// @see has_name
/// @see get_display_name
/// @see get_full_name
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_named(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_named(M);
}

/// @brief Indicates if a metaobject reflects a base-level alias.
/// @ingroup classification
/// @see reflects_named
/// @see get_aliased
/// @see remove_all_aliases
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_alias(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_alias(M);
}

/// @brief Indicates if a metaobject reflects a base-level entity with a type.
/// @ingroup classification
/// @see get_type
/// @see has_type
/// @see has_type_trait
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_typed(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_typed(M);
}

/// @brief Indicates if a metaobject reflects a base-level scope.
/// @ingroup classification
/// @see reflects_namespace
/// @see reflects_global_scope
/// @see reflects_record
/// @see reflects_scope_member
/// @see get_scope
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_scope(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_scope(M);
}

/// @brief Indicates if a metaobject reflects a base-level scope member.
/// @ingroup classification
/// @see reflects_scope
/// @see get_scope
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_scope_member(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_scope_member(M);
}

/// @brief Indicates if a metaobject reflects a base-level global scope member.
/// @ingroup classification
/// @see reflects_global_scope
/// @see get_scope
template <__metaobject_id M>
consteval auto reflects_global_scope_member(wrapped_metaobject<M>) noexcept
  -> bool {
    if constexpr(__metaobject_is_meta_scope_member(M)) {
        return __metaobject_is_meta_global_scope(__metaobject_get_scope(M));
    } else {
        return false;
    }
}

/// @brief Indicates if a metaobject reflects an enumerator.
/// @ingroup classification
/// @see reflects_constant
/// @see reflects_enum
/// @see get_enumerators
/// @see get_underlying_type
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_enumerator(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_enumerator(M);
}

/// @brief Indicates if a metaobject reflects a record member.
/// @ingroup classification
/// @see reflects_scope_member
/// @see reflects_record
/// @see get_data_members
/// @see get_member_types
/// @see get_member_functions
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_record_member(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_record_member(M);
}

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
template <__metaobject_id M>
consteval auto reflects_base(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_base(M);
}

/// @brief Indicates if a metaobject reflects a namespace.
/// @ingroup classification
/// @see reflects_inline_namespace
/// @see reflects_global_scope
/// @see get_scope
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_namespace(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_namespace(M);
}

/// @brief Indicates if a metaobject reflects an inline namespace.
/// @ingroup classification
/// @see reflects_namespace
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_inline_namespace(wrapped_metaobject<M>) noexcept
  -> bool {
    if constexpr(__metaobject_is_meta_namespace(M)) {
        return __metaobject_is_inline(M);
    } else {
        return false;
    }
}

/// @brief Indicates if a metaobject reflects the global scope.
/// @ingroup classification
/// @see reflects_namespace
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_global_scope(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_global_scope(M);
}

/// @brief Indicates if a metaobject reflects a type.
/// @ingroup classification
/// @see get_type
/// @see get_reflected_type
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_type(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_type(M);
}

/// @brief Indicates if a metaobject reflects an enumeration type.
/// @ingroup classification
/// @see reflects_enumerator
/// @see reflects_type
/// @see get_enumerators
/// @see get_underlying_type
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_enum(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_enum(M);
}

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
template <__metaobject_id M>
consteval auto reflects_record(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_record(M);
}

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
template <__metaobject_id M>
consteval auto reflects_class(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_class(M);
}

/// @brief Indicates if a metaobject reflects a lambda closure type.
/// @ingroup classification
/// @see reflects_record
/// @see reflects_class
/// @see get_captures
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_lambda(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_lambda(M);
}

/// @brief Indicates if a metaobject reflects a constant.
/// @ingroup classification
/// @see reflects_enumerator
/// @see get_constant
/// @see get_value
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_constant(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_constant(M);
}

/// @brief Indicates if a metaobject reflects a variable.
/// @ingroup classification
/// @see reflects_function_parameter
/// @see get_data_members
/// @see get_pointer
/// @see get_reference
/// @see get_value
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_variable(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_variable(M);
}

/// @brief Indicates if a metaobject reflects a lambda capture.
/// @ingroup classification
/// @see reflects_lambda
/// @see get_captures
/// @see is_explicitly_captured
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_lambda_capture(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_lambda_capture(M);
}

/// @brief Indicates if a metaobject reflects a function parameter.
/// @ingroup classification
/// @see reflects_callable
/// @see reflects_variable
/// @see get_parameters
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_function_parameter(wrapped_metaobject<M>) noexcept
  -> bool {
    return __metaobject_is_meta_function_parameter(M);
}

/// @brief Indicates if a metaobject reflects a callable base-level entity.
/// @ingroup classification
/// @see reflects_function
/// @see reflects_function_parameter
/// @see get_parameters
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_callable(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_callable(M);
}

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
template <__metaobject_id M>
consteval auto reflects_function(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_function(M);
}

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
template <__metaobject_id M>
consteval auto reflects_member_function(wrapped_metaobject<M>) noexcept
  -> bool {
    return __metaobject_is_meta_member_function(M);
}

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
template <__metaobject_id M>
consteval auto reflects_special_member_function(wrapped_metaobject<M>) noexcept
  -> bool {
    return __metaobject_is_meta_special_member_function(M);
}

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
template <__metaobject_id M>
consteval auto reflects_constructor(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_constructor(M);
}

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
template <__metaobject_id M>
consteval auto reflects_destructor(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_destructor(M);
}

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
template <__metaobject_id M>
consteval auto reflects_operator(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_operator(M);
}

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
template <__metaobject_id M>
consteval auto reflects_conversion_operator(wrapped_metaobject<M>) noexcept
  -> bool {
    return __metaobject_is_meta_conversion_operator(M);
}

/// @brief Indicates if a metaobject reflects an expression.
/// @ingroup classification
/// @see reflects_parenthesized_expression
/// @see reflects_construction_expression
/// @see reflects_function_call_expression
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_expression(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_expression(M);
}

/// @brief Indicates if a metaobject reflects a parenthesized expression.
/// @ingroup classification
/// @see reflects_expression
/// @see reflects_construction_expression
/// @see reflects_function_call_expression
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_parenthesized_expression(wrapped_metaobject<M>) noexcept
  -> bool {
    return __metaobject_is_meta_parenthesized_expression(M);
}

/// @brief Indicates if a metaobject reflects a constructor call expression.
/// @ingroup classification
/// @see reflects_expression
/// @see reflects_parenthesized_expression
/// @see reflects_function_call_expression
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_construction_expression(wrapped_metaobject<M>) noexcept
  -> bool {
    return __metaobject_is_meta_construction_expression(M);
}

/// @brief Indicates if a metaobject reflects a function call expression.
/// @ingroup classification
/// @see reflects_expression
/// @see reflects_parenthesized_expression
/// @see reflects_construction_expression
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_function_call_expression(wrapped_metaobject<M>) noexcept
  -> bool {
    return __metaobject_is_meta_function_call_expression(M);
}

/// @brief Indicates if a metaobject reflects a specifier.
/// @ingroup classification
/// @see meta_trait
/// @see has_trait
template <__metaobject_id M>
consteval auto reflects_specifier(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_specifier(M);
}

// unary operations
// boolean
/// @brief Indicates if the reflected base-level entity is @c constexpr.
/// @ingroup operations
/// @see reflects_variable
/// @see reflects_callable
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_constexpr(wrapped_metaobject<M>) noexcept -> bool requires(
  __metaobject_is_meta_variable(M) || __metaobject_is_meta_callable(M)) {
    return __metaobject_is_constexpr(M);
}

/// @brief Indicates if the reflected base-level entity is @c noexcept.
/// @ingroup operations
/// @see reflects_callable
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_noexcept(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_callable(M)) {
    return __metaobject_is_noexcept(M);
}

/// @brief Indicates if the reflected base-level entity is @c explicit.
/// @ingroup operations
/// @see reflects_constructor
/// @see reflects_conversion_operator
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_explicit(wrapped_metaobject<M>) noexcept -> bool requires(
  __metaobject_is_meta_constructor(M) ||
  __metaobject_is_meta_conversion_operator(M)) {
    return __metaobject_is_explicit(M);
}

/// @brief Indicates if the reflected base-level entity is @c inline.
/// @ingroup operations
/// @see reflects_namespace
/// @see reflects_variable
/// @see reflects_callable
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_inline(wrapped_metaobject<M>) noexcept -> bool requires(
  __metaobject_is_meta_namespace(M) || __metaobject_is_meta_variable(M) ||
  __metaobject_is_meta_callable(M)) {
    return __metaobject_is_inline(M);
}

/// @brief Indicates if the reflected base-level entity is @c thread_local.
/// @ingroup operations
/// @see reflects_variable
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_thread_local(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_variable(M)) {
    return __metaobject_is_thread_local(M);
}

/// @brief Indicates if the reflected base-level entity is @c static.
/// @ingroup operations
/// @see reflects_variable
/// @see reflects_member_function
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_static(wrapped_metaobject<M>) noexcept -> bool requires(
  __metaobject_is_meta_variable(M) || __metaobject_is_meta_member_function(M)) {
    return __metaobject_is_static(M);
}

/// @brief Indicates if the reflected base-level entity is @c virtual.
/// @ingroup operations
/// @see reflects_base
/// @see reflects_destructor
/// @see reflects_member_function
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_virtual(wrapped_metaobject<M>) noexcept -> bool requires(
  __metaobject_is_meta_base(M) || __metaobject_is_meta_destructor(M) ||
  __metaobject_is_meta_member_function(M)) {
    return __metaobject_is_virtual(M);
}

/// @brief Indicates if the reflected base-level entity is pure @c virtual.
/// @ingroup operations
/// @see reflects_destructor
/// @see reflects_member_function
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_pure_virtual(wrapped_metaobject<M>) noexcept -> bool requires(
  __metaobject_is_meta_destructor(M) ||
  __metaobject_is_meta_member_function(M)) {
    return __metaobject_is_pure_virtual(M);
}

/// @brief Indicates if the reflected base-level entity is @c final.
/// @ingroup operations
/// @see reflects_class
/// @see reflects_member_function
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_final(wrapped_metaobject<M>) noexcept -> bool requires(
  __metaobject_is_meta_class(M) || __metaobject_is_meta_member_function(M)) {
    return __metaobject_is_final(M);
}

/// @brief Indicates if the reflected base-level entity is @c private.
/// @ingroup operations
/// @see reflects_base
/// @see reflects_record_member
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_private(wrapped_metaobject<M>) noexcept -> bool requires(
  __metaobject_is_meta_record_member(M) || __metaobject_is_meta_base(M)) {
    return __metaobject_is_private(M);
}

/// @brief Indicates if the reflected base-level entity is @c protected.
/// @ingroup operations
/// @see reflects_base
/// @see reflects_record_member
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_protected(wrapped_metaobject<M>) noexcept -> bool requires(
  __metaobject_is_meta_record_member(M) || __metaobject_is_meta_base(M)) {
    return __metaobject_is_protected(M);
}

/// @brief Indicates if the reflected base-level entity is @c public.
/// @ingroup operations
/// @see reflects_base
/// @see reflects_record_member
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_public(wrapped_metaobject<M>) noexcept -> bool requires(
  __metaobject_is_meta_record_member(M) || __metaobject_is_meta_base(M)) {
    return __metaobject_is_public(M);
}

/// @brief Indicates if the reflected base-level entity is unnamed.
/// @ingroup operations
/// @see reflects_named
/// @see get_name
/// @see get_display_name
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_unnamed(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_named(M)) {
    return __metaobject_is_unnamed(M);
}

/// @brief Indicates if the reflected base-level entity is an @c enum.
/// @ingroup operations
/// @see reflects_type
/// @see reflects_enum
/// @see is_scoped_enum
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_enum(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_type(M)) {
    return __metaobject_is_enum(M);
}

/// @brief Indicates if the reflected base-level entity is a scoped @c enum.
/// @ingroup operations
/// @see reflects_type
/// @see reflects_enum
/// @see is_enum
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_scoped_enum(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_type(M)) {
    return __metaobject_is_scoped_enum(M);
}

/// @brief Indicates if the reflected base-level entity is an @c union.
/// @ingroup operations
/// @see reflects_type
/// @see is_union
/// @see uses_class_key
/// @see uses_struct_key
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_union(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_type(M)) {
    return __metaobject_is_union(M);
}

/// @brief Indicates if the reflected record type uses a @c class specifier.
/// @ingroup operations
/// @see reflects_type
/// @see is_union
/// @see uses_struct_key
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto uses_class_key(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_type(M)) {
    return __metaobject_uses_class_key(M);
}

/// @brief Indicates if the reflected record type uses a @c struct specifier.
/// @ingroup operations
/// @see reflects_type
/// @see is_union
/// @see uses_class_key
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto uses_struct_key(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_type(M)) {
    return __metaobject_uses_struct_key(M);
}

/// @brief Indicates if the reflected lambda closure uses default capture by copy.
/// @ingroup operations
/// @see reflects_lambda
/// @see uses_default_reference_capture
/// @see get_captures
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto uses_default_copy_capture(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_lambda(M)) {
    return __metaobject_uses_default_copy_capture(M);
}

/// @brief Indicates if the reflected lambda closure uses default capture by reference.
/// @ingroup operations
/// @see reflects_lambda
/// @see uses_default_copy_capture
/// @see get_captures
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto uses_default_reference_capture(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_lambda(M)) {
    return __metaobject_uses_default_reference_capture(M);
}

/// @brief Indicates if the reflected lambda closure's call operator is @c const.
/// @ingroup operations
/// @see reflects_lambda
/// @see get_captures
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_call_operator_const(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_lambda(M)) {
    return __metaobject_is_call_operator_const(M);
}

/// @brief Indicates if the reflected lambda capture is explicitly captured.
/// @ingroup operations
/// @see reflects_lambda_capture
/// @see get_captures
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_explicitly_captured(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_lambda_capture(M)) {
    return __metaobject_is_explicitly_captured(M);
}

/// @brief Indicates if the reflected function parameter has default argument.
/// @ingroup operations
/// @see reflects_function_parameter
/// @see get_parameters
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto has_default_argument(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_function_parameter(M)) {
    return __metaobject_has_default_argument(M);
}

/// @brief Indicates if the reflected member function is @c const.
/// @ingroup operations
/// @see reflects_member_function
/// @see is_volatile
/// @see has_lvalueref_qualifier
/// @see has_rvalueref_qualifier
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_const(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_member_function(M)) {
    return __metaobject_is_const(M);
}

/// @brief Indicates if the reflected member function is @c volatile.
/// @ingroup operations
/// @see reflects_member_function
/// @see is_const
/// @see has_lvalueref_qualifier
/// @see has_rvalueref_qualifier
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_volatile(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_member_function(M)) {
    return __metaobject_is_volatile(M);
}

/// @brief Indicates if the reflected member function has lvalue-ref qualifier.
/// @ingroup operations
/// @see reflects_member_function
/// @see is_const
/// @see is_volatile
/// @see has_rvalueref_qualifier
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto has_lvalueref_qualifier(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_member_function(M)) {
    return __metaobject_has_lvalueref_qualifier(M);
}

/// @brief Indicates if the reflected member function has rvalue-ref qualifier.
/// @ingroup operations
/// @see reflects_member_function
/// @see is_const
/// @see is_volatile
/// @see has_rvalueref_qualifier
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto has_rvalueref_qualifier(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_member_function(M)) {
    return __metaobject_has_rvalueref_qualifier(M);
}

/// @brief Indicates if the reflected special member function is implicitly declared.
/// @ingroup operations
/// @see reflects_member_function
/// @see reflects_special_member_function
/// @see is_defaulted
/// @see is_deleted
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_implicitly_declared(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_special_member_function(M)) {
    return __metaobject_is_implicitly_declared(M);
}

/// @brief Indicates if the reflected special member function is defaulted.
/// @ingroup operations
/// @see reflects_member_function
/// @see reflects_special_member_function
/// @see is_implicitly_declared
/// @see is_deleted
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_defaulted(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_special_member_function(M)) {
    return __metaobject_is_defaulted(M);
}

/// @brief Indicates if the reflected function is deleted.
/// @ingroup operations
/// @see reflects_member_function
/// @see reflects_special_member_function
/// @see is_implicitly_declared
/// @see is_defaulted
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_deleted(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_callable(M)) {
    return __metaobject_is_deleted(M);
}

/// @brief Indicates if the reflected constructor is copy constructor.
/// @ingroup operations
/// @see reflects_constructor
/// @see get_constructors
/// @see is_move_constructor
/// @see is_copy_assignment_operator
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_copy_constructor(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_constructor(M)) {
    return __metaobject_is_copy_constructor(M);
}

/// @brief Indicates if the reflected constructor is move constructor.
/// @ingroup operations
/// @see reflects_constructor
/// @see get_constructors
/// @see is_copy_constructor
/// @see is_move_assignment_operator
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_move_constructor(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_constructor(M)) {
    return __metaobject_is_move_constructor(M);
}

/// @brief Indicates if the reflected operator is copy assignment operator.
/// @ingroup operations
/// @see reflects_operator
/// @see reflects_special_member_function
/// @see get_operators
/// @see is_copy_constructor
/// @see is_move_assignment_operator
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_copy_assignment_operator(wrapped_metaobject<M>) noexcept
  -> bool requires(
    __metaobject_is_meta_operator(M) &&
    __metaobject_is_meta_special_member_function(M)) {
    return __metaobject_is_copy_assignment_operator(M);
}

/// @brief Indicates if the reflected operator is move assignment operator.
/// @ingroup operations
/// @see reflects_operator
/// @see reflects_special_member_function
/// @see get_operators
/// @see is_move_constructor
/// @see is_copy_assignment_operator
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_move_assignment_operator(wrapped_metaobject<M>) noexcept
  -> bool requires(
    __metaobject_is_meta_operator(M) &&
    __metaobject_is_meta_special_member_function(M)) {
    return __metaobject_is_move_assignment_operator(M);
}

/// @brief Indicates if the metaobject sequence is empty.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see get_size
/// @see get_element
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto is_empty(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_object_sequence(M)) {
    return __metaobject_is_empty(M);
}

/// @brief Indicates if the two metaobjects reflect the same base-level entity.
/// @ingroup operations
template <__metaobject_id Ml, __metaobject_id Mr>
consteval auto
reflects_same(wrapped_metaobject<Ml>, wrapped_metaobject<Mr>) noexcept -> bool {
    return __metaobject_reflects_same(Ml, Mr);
}

/// @brief Indicates if the base name of the reflected entity is equal to @p str.
/// @ingroup operations
/// @see reflects_named
/// @see get_name
/// @see get_display_name
template <__metaobject_id M, size_t L>
consteval auto has_name(wrapped_metaobject<M>, const char (&str)[L]) noexcept
  -> bool requires(__metaobject_is_meta_named(M)) {
    return __builtin_strcmp(__metaobject_get_name(M), str) == 0;
}

// integer
/// @brief Returns a unique metaobject identifier value.
/// @ingroup operations
/// @see reflects_object
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto get_id(wrapped_metaobject<M>) noexcept -> size_t {
    return __metaobject_get_id_value(M);
}

/// @brief Returns source file line of the reflected entity if available.
/// @ingroup operations
/// @see reflects_object
/// @see get_source_column
/// @see get_source_file_name
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto get_source_line(wrapped_metaobject<M>) noexcept -> size_t {
    return __metaobject_get_source_line(M);
}

/// @brief Returns source file column of the reflected entity if available.
/// @ingroup operations
/// @see reflects_object
/// @see get_source_line
/// @see get_source_file_name
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto get_source_column(wrapped_metaobject<M>) noexcept -> size_t {
    return __metaobject_get_source_column(M);
}

/// @brief Returns the number of elements in a metaobject sequence.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see is_empty
/// @see get_element
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto get_size(wrapped_metaobject<M>) noexcept -> size_t
  requires(__metaobject_is_meta_object_sequence(M)) {
    return __metaobject_get_size(M);
}

template <__metaobject_id M>
struct _get_pointer
  : integral_constant<
      __unrefltype(__metaobject_get_pointer(M)),
      __metaobject_get_pointer(M)> {};

/// @brief Returns a pointer to the reflected base-level entity.
/// @ingroup operations
/// @see reflects_variable
/// @see reflects_function
/// @see get_value
/// @see get_reference
/// @see get_constant
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto get_pointer(wrapped_metaobject<M>) noexcept requires(
  __metaobject_is_meta_variable(M) || __metaobject_is_meta_function(M)) {
    return _get_pointer<M>::value;
}

/// @brief Returns the value of the reflected base-level entity.
/// @ingroup operations
/// @see reflects_variable
/// @see get_pointer
/// @see get_reference
/// @see get_constant
template <__metaobject_id M>
constexpr const auto& get_value(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_variable(M)) {
    return *_get_pointer<M>::value;
}

/// @brief Returns the value of the reflected base-level data member in @p obj.
/// @ingroup operations
/// @see reflects_record_member
/// @see reflects_variable
/// @see get_pointer
/// @see get_reference
/// @see get_constant
template <__metaobject_id M, class C>
constexpr const auto& get_value(wrapped_metaobject<M>, const C& obj) noexcept
  requires(
    __metaobject_is_meta_record_member(M) && __metaobject_is_meta_variable(M)) {
    return obj.*_get_pointer<M>::value;
}

/// @brief Returns a reference to the reflected base-level entity.
/// @ingroup operations
/// @see reflects_variable
/// @see get_value
/// @see get_pointer
/// @see get_constant
template <__metaobject_id M>
constexpr auto& get_reference(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_variable(M)) {
    return *_get_pointer<M>::value;
}

/// @brief Returns a reference to the reflected base-level data member in @p obj.
/// @ingroup operations
/// @see reflects_record_member
/// @see reflects_variable
/// @see get_value
/// @see get_pointer
/// @see get_constant
template <__metaobject_id M, class C>
constexpr auto& get_reference(wrapped_metaobject<M>, C& obj) noexcept requires(
  __metaobject_is_meta_record_member(M) && __metaobject_is_meta_variable(M)) {
    return obj.*_get_pointer<M>::value;
}

template <__metaobject_id M>
struct _get_constant
  : integral_constant<
      __unrefltype(__metaobject_get_constant(M)),
      __metaobject_get_constant(M)> {};

/// @brief Returns the value of the reflected base-level constant.
/// @ingroup operations
/// @see reflects_constant
/// @see get_pointer
/// @see get_reference
/// @see get_value
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_constant(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_constant(M)) {
    return _get_constant<M>::value;
}

/// @brief Invokes the reflected member function on @p obj with specified @p args.
/// @ingroup operations
/// @see reflects_member_function
/// @see get_pointer
/// @see invoke
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

/// @brief Invokes the reflected function with the specified @p args.
/// @ingroup operations
/// @see reflects_function
/// @see reflects_member_function
/// @see is_static
/// @see get_pointer
/// @see invoke_on
template <__metaobject_id M, typename... A>
constexpr auto invoke(wrapped_metaobject<M>, A&&... args) requires(
  __metaobject_is_meta_function(M) ||
  (__metaobject_is_meta_member_function(M) && __metaobject_is_static(M))) {
    return (*_get_pointer<M>::value)(std::forward<A>(args)...);
}

/// @brief Invokes the reflected member function on @p obj with specified @p args.
/// @ingroup operations
/// @see reflects_member_function
/// @see is_static
/// @see get_pointer
/// @see get_reference
/// @see invoke_on
template <__metaobject_id M, typename C, typename... A>
constexpr auto invoke(wrapped_metaobject<M>, C& obj, A&&... args) requires(
  __metaobject_is_meta_member_function(M) && !__metaobject_is_static(M)) {
    return (obj.*_get_pointer<M>::value)(std::forward<A>(args)...);
}

/// @brief Invokes the reflected constructor with the specified @p args.
/// @ingroup operations
/// @see reflects_constructor
/// @see get_pointer
/// @see invoke_on
template <__metaobject_id M, typename... A>
constexpr auto invoke(wrapped_metaobject<M>, A&&... args) -> __unrefltype(
  __metaobject_get_scope(M)) requires(__metaobject_is_meta_constructor(M)) {
    return __unrefltype(__metaobject_get_scope(M))(std::forward<A>(args)...);
}

// string
consteval auto get_source_file_name_view(__metaobject_id mo) noexcept
  -> string_view {
    return {
      __metaobject_get_source_file_name(mo),
      __metaobject_source_file_name_len(mo)};
}

/// @brief Returns source file column of the reflected entity if available.
/// @ingroup operations
/// @see reflects_object
/// @see get_source_line
/// @see get_source_column
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto get_source_file_name(wrapped_metaobject<M>) noexcept
  -> string_view {
    return get_source_file_name_view(M);
}

consteval auto get_name_view(__metaobject_id mo) noexcept -> string_view {
    return {__metaobject_get_name(mo), __metaobject_name_len(mo)};
}

/// @brief Returns the unqualified "base name" of the reflected base-level entity.
/// @ingroup operations
/// @see reflects_named
/// @see get_full_name
/// @see get_display_name
/// @see has_name
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto get_name(wrapped_metaobject<M>) noexcept -> string_view
  requires(__metaobject_is_meta_named(M)) {
    return get_name_view(M);
}

consteval auto get_display_name_view(__metaobject_id mo) noexcept
  -> string_view {
    return {
      __metaobject_get_display_name(mo), __metaobject_display_name_len(mo)};
}

/// @brief Returns the user-friendly name of the reflected base-level entity.
/// @ingroup operations
/// @see reflects_named
/// @see get_name
/// @see get_display_name
/// @see metaobject_operation
template <__metaobject_id M>
consteval auto get_display_name(wrapped_metaobject<M>) noexcept -> string_view
  requires(__metaobject_is_meta_named(M)) {
    return get_display_name_view(M);
}

// metaobject
/// @brief Returns a reflection of the scope of a reflected scope member.
/// @ingroup operations
/// @see reflects_scope_member
/// @see reflects_scope
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_scope(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_scope_member(M)) {
    return wrapped_metaobject<__metaobject_get_scope(M)>{};
}

/// @brief Returns a reflection of the type of a reflected typed entity.
/// @ingroup operations
/// @see reflects_typed
/// @see get_reflected_type
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_type(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_typed(M)) {
    return wrapped_metaobject<__metaobject_get_type(M)>{};
}

/// @brief Returns a reflection of the underlying type of a reflected enum,
/// @ingroup operations
/// @see get_constant
/// @see reflects_enum
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_underlying_type(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_enum(M)) {
    return wrapped_metaobject<__metaobject_get_underlying_type(M)>{};
}

/// @brief Returns a reflection of the aliased entity reflected by a reflected alias.
/// @ingroup operations
/// @see reflects_named
/// @see reflects_alias
/// @see remove_all_aliases
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_aliased(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_alias(M)) {
    return wrapped_metaobject<__metaobject_get_aliased(M)>{};
}

/// @brief Removes all aliases from a potentially aliased reflected entity.
/// @ingroup operations
/// @see reflects_alias
/// @see get_aliased
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto remove_all_aliases(wrapped_metaobject<M> mo) noexcept {
    if constexpr(__metaobject_is_meta_alias(M)) {
        return remove_all_aliases(
          wrapped_metaobject<__metaobject_get_aliased(M)>{});
    } else {
        return mo;
    }
}

/// @brief Returns the reflection of the class in a reflected base class specifier.
/// @ingroup operations
/// @see get_base_classes
/// @see reflects_base
/// @see is_private
/// @see is_protected
/// @see is_public
/// @see is_virtual
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_class(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_base(M)) {
    return wrapped_metaobject<__metaobject_get_class(M)>{};
}

/// @brief Returns the reflection of the sub-expression of a parenthesized expression.
/// @ingroup operations
/// @see reflects_parenthesized_expression
/// @see reflects_function_call_expression
/// @see reflects_construction_expression
/// @see get_callable
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_subexpression(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_parenthesized_expression(M)) {
    return wrapped_metaobject<__metaobject_get_subexpression(M)>{};
}

/// @brief Returns the reflection of the sub-expression of a parenthesized expression.
/// @ingroup operations
/// @see reflects_parenthesized_expression
/// @see reflects_construction_expression
/// @see reflects_function_call_expression
/// @see get_subexpression
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_callable(wrapped_metaobject<M>) noexcept requires(
  __metaobject_is_meta_construction_expression(M) ||
  __metaobject_is_meta_function_call_expression(M)) {
    return wrapped_metaobject<__metaobject_get_callable(M)>{};
}

/// @brief Returns a sequence of base class specifier reflections of a reflected class.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_base
/// @see is_empty
/// @see get_size
/// @see get_class
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_base_classes(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_class(M)) {
    return wrapped_metaobject<__metaobject_get_base_classes(M)>{};
}

/// @brief Returns a sequence of member type reflections of a reflected class.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_type
/// @see is_empty
/// @see get_size
/// @see get_type
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_member_types(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_member_types(M)>{};
}

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
template <__metaobject_id M>
constexpr auto get_data_members(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_data_members(M)>{};
}

/// @brief Returns a sequence of member function reflections of a reflected class.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_function
/// @see is_empty
/// @see get_size
/// @see get_pointer
/// @see invoke_on
/// @see invoke
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_member_functions(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_member_functions(M)>{};
}

/// @brief Returns a sequence of constructor reflections of a reflected class.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_constructor
/// @see is_empty
/// @see get_size
/// @see invoke_on
/// @see invoke
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_constructors(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_constructors(M)>{};
}

/// @brief Returns a sequence of destructors reflections of a reflected class.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_constructor
/// @see is_empty
/// @see get_size
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_destructors(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_destructors(M)>{};
}

/// @brief Returns a sequence of operator reflections of a reflected class.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_operator
/// @see is_empty
/// @see get_size
/// @see invoke_on
/// @see invoke
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_operators(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_operators(M)>{};
}

/// @brief Returns a sequence of enumerator reflections of a reflected enum type.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_enumerator
/// @see is_empty
/// @see get_size
/// @see get_constant
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_enumerators(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_enum(M)) {
    return wrapped_metaobject<__metaobject_get_enumerators(M)>{};
}

/// @brief Returns a sequence of parameter reflections of a reflected callable.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_function_parameter
/// @see is_empty
/// @see get_size
/// @see has_default_argument
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_parameters(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_callable(M)) {
    return wrapped_metaobject<__metaobject_get_parameters(M)>{};
}

/// @brief Returns a sequence of capture reflections of a reflected closure.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see reflects_lambda_capture
/// @see is_empty
/// @see get_size
/// @see is_explicitly_captured
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto get_captures(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_lambda(M)) {
    return wrapped_metaobject<__metaobject_get_captures(M)>{};
}

/// @brief Returns a sequence with private elements filtered out.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see hide_protected
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto hide_private(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return wrapped_metaobject<__metaobject_hide_private(M)>{};
}

/// @brief Returns a sequence with private and protected elements filtered out.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see hide_private
/// @see metaobject_operation
template <__metaobject_id M>
constexpr auto hide_protected(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return wrapped_metaobject<__metaobject_hide_protected(M)>{};
}

/// @brief Returns the I-th metaobject in a metaobject sequence.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see get_size
template <size_t I, __metaobject_id M>
constexpr auto get_element(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return wrapped_metaobject<__metaobject_get_element(M, I)>{};
}

/// @brief Unpacks a sequence metaobject into sequence of separate metaobjects.
/// @ingroup operations
/// @see reflects_object_sequence
/// @see unpack
template <__metaobject_id M>
constexpr auto expand(wrapped_metaobject<M>) noexcept
  -> __unpack_metaobject_seq<expanded_metaobject_sequence, M> requires(
    __metaobject_is_meta_object_sequence(M)) {
    return {};
}

// type unreflection
template <__metaobject_id M>
using _get_reflected_type = type_identity<__unrefltype(M)>;

/// @brief Returns the base-level type reflected by a type reflecting metaobject.
/// @ingroup operations
/// @see reflects_type
/// @see get_type
/// @see get_reflected_type
/// @see get_transformed_type_t
template <typename M>
using get_reflected_type_t = __unrefltype(unwrap(M{}));

/// @brief Returns type_identity of base-level type reflected by a metaobject.
/// @ingroup operations
/// @see reflects_type
/// @see get_reflected_type_of
/// @see get_type
/// @see get_reflected_type_t
template <__metaobject_id M>
consteval auto get_reflected_type(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_type(M)) {
    return _get_reflected_type<M>{};
}

/// @brief Returns type_identity of base-level type from a typed metaobject.
/// @ingroup operations
/// @see reflects_type
/// @see get_reflected_type
/// @see get_type
/// @see get_reflected_type_t
template <__metaobject_id M>
consteval auto get_reflected_type_of(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_typed(M)) {
    return _get_reflected_type<__metaobject_get_type(M)>{};
}

template <template <typename T> class Transform, __metaobject_id M>
using _get_transformed_type = Transform<__unrefltype(M)>;

template <template <typename T> class Transform, typename M>
using get_transformed_type_t = Transform<__unrefltype(unwrap(M{}))>;

template <template <typename T> class Transform, __metaobject_id M>
consteval auto get_transformed_type(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_type(M)) {
    return _get_transformed_type<Transform, M>{};
}

/// @brief Indicates if type-reflecting metaobject reflects the specified type.
/// @ingroup operations
/// @see reflects_type
/// @see has_type
/// @see has_type_trait
/// @see has_type_with_trait
/// @see get_type
/// @see get_reflected_type
template <typename T, __metaobject_id M>
consteval auto is_type(wrapped_metaobject<M>, type_identity<T> = {}) noexcept
  -> bool requires(__metaobject_is_meta_type(M)) {
    return std::is_same_v<__unrefltype(M), T>;
}

/// @brief Indicates if type-reflecting metaobject reflects the specified type.
/// @ingroup operations
/// @see reflects_type
/// @see is_type
/// @see has_type
/// @see has_type_with_trait
/// @see get_type
/// @see get_reflected_type
template <template <typename> class Trait, __metaobject_id M>
consteval auto has_type_trait(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_type(M)) {
    return Trait<__unrefltype(M)>::value;
}

/// @brief Indicates if typed metaobject has the specified type.
/// @ingroup operations
/// @see reflects_typed
/// @see is_type
/// @see has_type_trait
/// @see has_type_with_trait
/// @see get_type
/// @see get_reflected_type_of
template <typename T, __metaobject_id M>
consteval auto has_type(wrapped_metaobject<M>, type_identity<T> = {}) noexcept
  -> bool {
    if constexpr(__metaobject_is_meta_typed(M)) {
        return std::is_same_v<__unrefltype(__metaobject_get_type(M)), T>;
    } else {
        return false;
    }
}

/// @brief Indicates if typed metaobject has type with specified trait.
/// @ingroup operations
/// @see reflects_type
/// @see is_type
/// @see has_type
/// @see has_type_with_trait
/// @see get_type
/// @see get_reflected_type
template <template <typename> class Trait, __metaobject_id M>
consteval auto has_type_with_trait(wrapped_metaobject<M>) noexcept -> bool {
    if constexpr(__metaobject_is_meta_typed(M)) {
        return Trait<__unrefltype(__metaobject_get_type(M))>::value;
    } else {
        return false;
    }
}

// reflection "operator"
#if defined(MIRROR_YCM)
#define mirror(...) \
    ::mirror::wrapped_metaobject<0U> {}
#else
#define mirror(...) \
    ::mirror::wrapped_metaobject<__reflexpr_id(__VA_ARGS__)> {}
#endif

} // namespace mirror

#endif // !_LIBCPP_HAS_NO_REFLECTION && !_LIBCPP_HAS_NO_REFLECTION_EXT

#endif // MIRROR_PRIMITIVES_HPP
