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
_LIBCPP_WARNING("mirror cannot be used with this compiler")
#else
#warning mirror cannot be used with this compiler
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
/// @see no_metaobject
template <__metaobject_id M>
struct metaobject {};

template <typename>
struct unwrap_metaobject;

template <__metaobject_id M>
struct unwrap_metaobject<metaobject<M>> {
    static constexpr __metaobject_id value = M;
};

template <typename M>
static constexpr const auto unwrap = unwrap_metaobject<M>::value;

/// @brief Special instance of metaobject that does not reflect anything.
/// @ingroup metaobjects
/// @see metaobject
constinit const metaobject<__reflexpr_id()> no_metaobject{};

/// @brief Indicates if a metaobject reflects any base-level entity.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_object(metaobject<M>) -> bool {
    return __metaobject_is_meta_object(M);
}

/// @brief Indicates if the argument is a sequence of metaobjects.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_object_sequence(metaobject<M>) -> bool {
    return __metaobject_is_meta_object_sequence(M);
}

/// @brief Indicates if a metaobject reflects a named base-level entity.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_named(metaobject<M>) -> bool {
    return __metaobject_is_meta_named(M);
}

/// @brief Indicates if a metaobject reflects a base-level alias.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_alias(metaobject<M>) -> bool {
    return __metaobject_is_meta_alias(M);
}

/// @brief Indicates if a metaobject reflects a base-level scope.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_scope(metaobject<M>) -> bool {
    return __metaobject_is_meta_scope(M);
}

/// @brief Indicates if a metaobject reflects a base-level entity with a type.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_typed(metaobject<M>) -> bool {
    return __metaobject_is_meta_typed(M);
}

/// @brief Indicates if a metaobject reflects a base-level scope member.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_scope_member(metaobject<M>) -> bool {
    return __metaobject_is_meta_scope_member(M);
}

/// @brief Indicates if a metaobject reflects a base-level global scope member.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_global_scope_member(metaobject<M>) -> bool {
    if constexpr(__metaobject_is_meta_scope_member(M)) {
        return __metaobject_is_meta_global_scope(__metaobject_get_scope(M));
    } else {
        return false;
    }
}

/// @brief Indicates if a metaobject reflects an enumerator.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_enumerator(metaobject<M>) -> bool {
    return __metaobject_is_meta_enumerator(M);
}

/// @brief Indicates if a metaobject reflects a record member.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_record_member(metaobject<M>) -> bool {
    return __metaobject_is_meta_record_member(M);
}

/// @brief Indicates if a metaobject reflects a base class specifier.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_base(metaobject<M>) -> bool {
    return __metaobject_is_meta_base(M);
}

/// @brief Indicates if a metaobject reflects a namespace.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_namespace(metaobject<M>) -> bool {
    return __metaobject_is_meta_namespace(M);
}

/// @brief Indicates if a metaobject reflects an inline namespace.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_inline_namespace(metaobject<M>) -> bool {
    if constexpr(__metaobject_is_meta_namespace(M)) {
        return __metaobject_is_inline(M);
    } else {
        return false;
    }
}

/// @brief Indicates if a metaobject reflects the global scope.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_global_scope(metaobject<M>) -> bool {
    return __metaobject_is_meta_global_scope(M);
}

/// @brief Indicates if a metaobject reflects a type.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_type(metaobject<M>) -> bool {
    return __metaobject_is_meta_type(M);
}

/// @brief Indicates if a metaobject reflects an enumeration type.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_enum(metaobject<M>) -> bool {
    return __metaobject_is_meta_enum(M);
}

/// @brief Indicates if a metaobject reflects a record types (union or class).
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_record(metaobject<M>) -> bool {
    return __metaobject_is_meta_record(M);
}

/// @brief Indicates if a metaobject reflects a class.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_class(metaobject<M>) -> bool {
    return __metaobject_is_meta_class(M);
}

/// @brief Indicates if a metaobject reflects a lambda closure type.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_lambda(metaobject<M>) -> bool {
    return __metaobject_is_meta_lambda(M);
}

/// @brief Indicates if a metaobject reflects a constant.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_constant(metaobject<M>) -> bool {
    return __metaobject_is_meta_constant(M);
}

/// @brief Indicates if a metaobject reflects a variable.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_variable(metaobject<M>) -> bool {
    return __metaobject_is_meta_variable(M);
}

/// @brief Indicates if a metaobject reflects a lambda capture.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_lambda_capture(metaobject<M>) -> bool {
    return __metaobject_is_meta_lambda_capture(M);
}

/// @brief Indicates if a metaobject reflects a function parameter.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_function_parameter(metaobject<M>) -> bool {
    return __metaobject_is_meta_function_parameter(M);
}

/// @brief Indicates if a metaobject reflects a callable base-level entity.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_callable(metaobject<M>) -> bool {
    return __metaobject_is_meta_callable(M);
}

/// @brief Indicates if a metaobject reflects a function.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_function(metaobject<M>) -> bool {
    return __metaobject_is_meta_function(M);
}

/// @brief Indicates if a metaobject reflects a record member function.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_member_function(metaobject<M>) -> bool {
    return __metaobject_is_meta_member_function(M);
}

/// @brief Indicates if a metaobject reflects a special member function.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_special_member_function(metaobject<M>) -> bool {
    return __metaobject_is_meta_special_member_function(M);
}

/// @brief Indicates if a metaobject reflects a constructor.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_constructor(metaobject<M>) -> bool {
    return __metaobject_is_meta_constructor(M);
}

/// @brief Indicates if a metaobject reflects a destructor.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_destructor(metaobject<M>) -> bool {
    return __metaobject_is_meta_destructor(M);
}

/// @brief Indicates if a metaobject reflects an operator.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_operator(metaobject<M>) -> bool {
    return __metaobject_is_meta_operator(M);
}

/// @brief Indicates if a metaobject reflects a conversion operator.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_conversion_operator(metaobject<M>) -> bool {
    return __metaobject_is_meta_conversion_operator(M);
}

/// @brief Indicates if a metaobject reflects an expression.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_expression(metaobject<M>) -> bool {
    return __metaobject_is_meta_expression(M);
}

/// @brief Indicates if a metaobject reflects a specifier.
/// @ingroup classification
template <__metaobject_id M>
consteval auto reflects_specifier(metaobject<M>) -> bool {
    return __metaobject_is_meta_specifier(M);
}

// unary operations
// boolean
template <__metaobject_id M>
consteval auto is_constexpr(metaobject<M>) -> bool requires(
  __metaobject_is_meta_variable(M) || __metaobject_is_meta_callable(M)) {
    return __metaobject_is_constexpr(M);
}

template <__metaobject_id M>
consteval auto is_noexcept(metaobject<M>)
  -> bool requires(__metaobject_is_meta_callable(M)) {
    return __metaobject_is_noexcept(M);
}

template <__metaobject_id M>
consteval auto is_explicit(metaobject<M>) -> bool requires(
  __metaobject_is_meta_constructor(M) ||
  __metaobject_is_meta_conversion_operator(M)) {
    return __metaobject_is_explicit(M);
}

template <__metaobject_id M>
consteval auto is_inline(metaobject<M>) -> bool requires(
  __metaobject_is_meta_namespace(M) || __metaobject_is_meta_callable(M)) {
    return __metaobject_is_inline(M);
}

template <__metaobject_id M>
consteval auto is_thread_local(metaobject<M>)
  -> bool requires(__metaobject_is_meta_variable(M)) {
    return __metaobject_is_thread_local(M);
}

template <__metaobject_id M>
consteval auto is_static(metaobject<M>) -> bool requires(
  __metaobject_is_meta_variable(M) || __metaobject_is_meta_member_function(M)) {
    return __metaobject_is_static(M);
}

template <__metaobject_id M>
consteval auto is_virtual(metaobject<M>) -> bool requires(
  __metaobject_is_meta_base(M) || __metaobject_is_meta_destructor(M) ||
  __metaobject_is_meta_member_function(M)) {
    return __metaobject_is_virtual(M);
}

template <__metaobject_id M>
consteval auto is_pure_virtual(metaobject<M>) -> bool requires(
  __metaobject_is_meta_destructor(M) ||
  __metaobject_is_meta_member_function(M)) {
    return __metaobject_is_pure_virtual(M);
}

template <__metaobject_id M>
consteval auto is_final(metaobject<M>) -> bool requires(
  __metaobject_is_meta_class(M) || __metaobject_is_meta_member_function(M)) {
    return __metaobject_is_final(M);
}

template <__metaobject_id M>
consteval auto is_private(metaobject<M>) -> bool requires(
  __metaobject_is_meta_record_member(M) || __metaobject_is_meta_base(M)) {
    return __metaobject_is_private(M);
}

template <__metaobject_id M>
consteval auto is_protected(metaobject<M>) -> bool requires(
  __metaobject_is_meta_record_member(M) || __metaobject_is_meta_base(M)) {
    return __metaobject_is_protected(M);
}

template <__metaobject_id M>
consteval auto is_public(metaobject<M>) -> bool requires(
  __metaobject_is_meta_record_member(M) || __metaobject_is_meta_base(M)) {
    return __metaobject_is_public(M);
}

template <__metaobject_id M>
consteval auto is_unnamed(metaobject<M>)
  -> bool requires(__metaobject_is_meta_named(M)) {
    return __metaobject_is_unnamed(M);
}

template <__metaobject_id M>
consteval auto is_enum(metaobject<M>)
  -> bool requires(__metaobject_is_meta_type(M)) {
    return __metaobject_is_enum(M);
}

template <__metaobject_id M>
consteval auto is_scoped_enum(metaobject<M>)
  -> bool requires(__metaobject_is_meta_type(M)) {
    return __metaobject_is_scoped_enum(M);
}

template <__metaobject_id M>
consteval auto is_union(metaobject<M>)
  -> bool requires(__metaobject_is_meta_type(M)) {
    return __metaobject_is_union(M);
}

template <__metaobject_id M>
consteval auto uses_class_key(metaobject<M>)
  -> bool requires(__metaobject_is_meta_type(M)) {
    return __metaobject_uses_class_key(M);
}

template <__metaobject_id M>
consteval auto uses_struct_key(metaobject<M>)
  -> bool requires(__metaobject_is_meta_type(M)) {
    return __metaobject_uses_struct_key(M);
}

template <__metaobject_id M>
consteval auto uses_default_copy_capture(metaobject<M>)
  -> bool requires(__metaobject_is_meta_lambda(M)) {
    return __metaobject_uses_default_copy_capture(M);
}

template <__metaobject_id M>
consteval auto uses_default_reference_capture(metaobject<M>)
  -> bool requires(__metaobject_is_meta_lambda(M)) {
    return __metaobject_uses_default_reference_capture(M);
}

template <__metaobject_id M>
consteval auto is_call_operator_const(metaobject<M>)
  -> bool requires(__metaobject_is_meta_lambda(M)) {
    return __metaobject_is_call_operator_const(M);
}

template <__metaobject_id M>
consteval auto is_explicitly_captured(metaobject<M>)
  -> bool requires(__metaobject_is_meta_lambda_capture(M)) {
    return __metaobject_is_explicitly_captured(M);
}

template <__metaobject_id M>
consteval auto has_default_argument(metaobject<M>)
  -> bool requires(__metaobject_is_meta_function_parameter(M)) {
    return __metaobject_has_default_argument(M);
}

template <__metaobject_id M>
consteval auto is_const(metaobject<M>)
  -> bool requires(__metaobject_is_meta_member_function(M)) {
    return __metaobject_is_const(M);
}

template <__metaobject_id M>
consteval auto is_volatile(metaobject<M>)
  -> bool requires(__metaobject_is_meta_member_function(M)) {
    return __metaobject_is_volatile(M);
}

template <__metaobject_id M>
consteval auto has_lvalueref_qualifier(metaobject<M>)
  -> bool requires(__metaobject_is_meta_member_function(M)) {
    return __metaobject_has_lvalueref_qualifier(M);
}

template <__metaobject_id M>
consteval auto has_rvalueref_qualifier(metaobject<M>)
  -> bool requires(__metaobject_is_meta_member_function(M)) {
    return __metaobject_has_rvalueref_qualifier(M);
}

template <__metaobject_id M>
consteval auto is_implicitly_declared(metaobject<M>)
  -> bool requires(__metaobject_is_meta_special_member_function(M)) {
    return __metaobject_is_implicitly_declared(M);
}

template <__metaobject_id M>
consteval auto is_defaulted(metaobject<M>)
  -> bool requires(__metaobject_is_meta_special_member_function(M)) {
    return __metaobject_is_defaulted(M);
}

template <__metaobject_id M>
consteval auto is_deleted(metaobject<M>)
  -> bool requires(__metaobject_is_meta_callable(M)) {
    return __metaobject_is_deleted(M);
}

template <__metaobject_id M>
consteval auto is_copy_constructor(metaobject<M>)
  -> bool requires(__metaobject_is_meta_constructor(M)) {
    return __metaobject_is_copy_constructor(M);
}

template <__metaobject_id M>
consteval auto is_move_constructor(metaobject<M>)
  -> bool requires(__metaobject_is_meta_constructor(M)) {
    return __metaobject_is_move_constructor(M);
}

template <__metaobject_id M>
consteval auto is_copy_assignment_operator(metaobject<M>) -> bool requires(
  __metaobject_is_meta_operator(M) &&
  __metaobject_is_meta_special_member_function(M)) {
    return __metaobject_is_copy_assignment_operator(M);
}

template <__metaobject_id M>
consteval auto is_move_assignment_operator(metaobject<M>) -> bool requires(
  __metaobject_is_meta_operator(M) &&
  __metaobject_is_meta_special_member_function(M)) {
    return __metaobject_is_move_assignment_operator(M);
}

template <__metaobject_id M>
consteval auto is_empty(metaobject<M>)
  -> bool requires(__metaobject_is_meta_object_sequence(M)) {
    return __metaobject_is_empty(M);
}

template <__metaobject_id Ml, __metaobject_id Mr>
consteval auto reflects_same(metaobject<Ml>, metaobject<Mr>) -> bool {
    return __metaobject_reflects_same(Ml, Mr);
}

// integer
template <__metaobject_id M>
consteval auto get_id(metaobject<M>) -> size_t {
    return __metaobject_get_id_value(M);
}

template <__metaobject_id M>
consteval auto get_source_line(metaobject<M>) -> size_t {
    return __metaobject_get_source_line(M);
}

template <__metaobject_id M>
consteval auto get_source_column(metaobject<M>) -> size_t {
    return __metaobject_get_source_column(M);
}

template <__metaobject_id M>
consteval auto get_size(metaobject<M>) -> size_t
  requires(__metaobject_is_meta_object_sequence(M)) {
    return __metaobject_get_size(M);
}

template <__metaobject_id M>
struct _get_pointer
  : integral_constant<
      __unrefltype(__metaobject_get_pointer(M)),
      __metaobject_get_pointer(M)> {};

template <__metaobject_id M>
consteval auto get_pointer(metaobject<M>) requires(
  __metaobject_is_meta_variable(M) || __metaobject_is_meta_function(M)) {
    return _get_pointer<M>::value;
}

template <__metaobject_id M>
constexpr const auto&
get_value(metaobject<M>) requires(__metaobject_is_meta_variable(M)) {
    return *_get_pointer<M>::value;
}

template <__metaobject_id M, class C>
constexpr const auto& get_value(metaobject<M>, const C& obj) requires(
  __metaobject_is_meta_record_member(M) && __metaobject_is_meta_variable(M)) {
    return obj.*_get_pointer<M>::value;
}

template <__metaobject_id M>
constexpr auto&
get_reference(metaobject<M>) requires(__metaobject_is_meta_variable(M)) {
    return *_get_pointer<M>::value;
}

template <__metaobject_id M, class C>
constexpr auto& get_reference(metaobject<M>, C& obj) requires(
  __metaobject_is_meta_record_member(M) && __metaobject_is_meta_variable(M)) {
    return obj.*_get_pointer<M>::value;
}

template <__metaobject_id M>
struct _get_constant
  : integral_constant<
      __unrefltype(__metaobject_get_constant(M)),
      __metaobject_get_constant(M)> {};

template <__metaobject_id M>
constexpr auto
get_constant(metaobject<M>) requires(__metaobject_is_meta_constant(M)) {
    return _get_constant<M>::value;
}

template <__metaobject_id M, typename C, typename... A>
constexpr auto invoke_on(metaobject<M> mo, C& obj, A&&... args) requires(
  __metaobject_is_meta_member_function(M)) {
    if constexpr(is_static(mo)) {
        return (*_get_pointer<M>::value)(std::forward<A>(args)...);
    } else {
        return (obj.*_get_pointer<M>::value)(std::forward<A>(args)...);
    }
}

template <__metaobject_id M, typename... A>
constexpr auto invoke(metaobject<M>, A&&... args) requires(
  __metaobject_is_meta_function(M) ||
  (__metaobject_is_meta_member_function(M) && __metaobject_is_static(M))) {
    return (*_get_pointer<M>::value)(std::forward<A>(args)...);
}

template <__metaobject_id M, typename C, typename... A>
constexpr auto invoke(metaobject<M>, C& obj, A&&... args) requires(
  __metaobject_is_meta_member_function(M) && !__metaobject_is_static(M)) {
    return (obj.*_get_pointer<M>::value)(std::forward<A>(args)...);
}

template <__metaobject_id M, typename... A>
constexpr auto invoke(metaobject<M>, A&&... args) -> __unrefltype(
  __metaobject_get_scope(M)) requires(__metaobject_is_meta_constructor(M)) {
    return __unrefltype(__metaobject_get_scope(M))(std::forward<A>(args)...);
}

// string
consteval auto get_source_file_name_view(__metaobject_id mo) -> string_view {
    return {
      __metaobject_get_source_file_name(mo),
      __metaobject_source_file_name_len(mo)};
}

template <__metaobject_id M>
consteval auto get_source_file_name(metaobject<M>) -> string_view {
    return get_source_file_name_view(M);
}

consteval auto get_name_view(__metaobject_id mo) -> string_view {
    return {__metaobject_get_name(mo), __metaobject_name_len(mo)};
}

template <__metaobject_id M>
consteval auto get_name(metaobject<M>) -> string_view
  requires(__metaobject_is_meta_named(M)) {
    return get_name_view(M);
}

template <__metaobject_id M, size_t L>
consteval auto has_name(metaobject<M>, const char (&str)[L])
  -> bool requires(__metaobject_is_meta_named(M)) {
    return __builtin_strcmp(__metaobject_get_name(M), str) == 0;
}

consteval auto get_display_name_view(__metaobject_id mo) -> string_view {
    return {
      __metaobject_get_display_name(mo), __metaobject_display_name_len(mo)};
}

template <__metaobject_id M>
consteval auto get_display_name(metaobject<M>) -> string_view
  requires(__metaobject_is_meta_named(M)) {
    return get_display_name_view(M);
}

// metaobject
template <__metaobject_id M>
constexpr auto
get_scope(metaobject<M>) requires(__metaobject_is_meta_scope_member(M)) {
    return metaobject<__metaobject_get_scope(M)>{};
}

template <__metaobject_id M>
constexpr auto get_type(metaobject<M>) requires(__metaobject_is_meta_typed(M)) {
    return metaobject<__metaobject_get_type(M)>{};
}

template <__metaobject_id M>
constexpr auto
get_underlying_type(metaobject<M>) requires(__metaobject_is_meta_enum(M)) {
    return metaobject<__metaobject_get_underlying_type(M)>{};
}

template <__metaobject_id M>
constexpr auto
get_aliased(metaobject<M>) requires(__metaobject_is_meta_alias(M)) {
    return metaobject<__metaobject_get_aliased(M)>{};
}

template <__metaobject_id M>
constexpr auto remove_all_aliases(metaobject<M> mo) {
    if constexpr(__metaobject_is_meta_alias(M)) {
        return remove_all_aliases(metaobject<__metaobject_get_aliased(M)>{});
    } else {
        return mo;
    }
}

template <__metaobject_id M>
constexpr auto get_class(metaobject<M>) requires(__metaobject_is_meta_base(M)) {
    return metaobject<__metaobject_get_class(M)>{};
}

template <__metaobject_id M>
constexpr auto
get_base_classes(metaobject<M>) requires(__metaobject_is_meta_class(M)) {
    return metaobject<__metaobject_get_base_classes(M)>{};
}

template <__metaobject_id M>
constexpr auto
get_member_types(metaobject<M>) requires(__metaobject_is_meta_record(M)) {
    return metaobject<__metaobject_get_member_types(M)>{};
}

template <__metaobject_id M>
constexpr auto
get_data_members(metaobject<M>) requires(__metaobject_is_meta_record(M)) {
    return metaobject<__metaobject_get_data_members(M)>{};
}

template <__metaobject_id M>
constexpr auto
get_member_functions(metaobject<M>) requires(__metaobject_is_meta_record(M)) {
    return metaobject<__metaobject_get_member_functions(M)>{};
}

template <__metaobject_id M>
constexpr auto
get_constructors(metaobject<M>) requires(__metaobject_is_meta_record(M)) {
    return metaobject<__metaobject_get_constructors(M)>{};
}

template <__metaobject_id M>
constexpr auto
get_destructors(metaobject<M>) requires(__metaobject_is_meta_record(M)) {
    return metaobject<__metaobject_get_destructors(M)>{};
}

template <__metaobject_id M>
constexpr auto
get_operators(metaobject<M>) requires(__metaobject_is_meta_record(M)) {
    return metaobject<__metaobject_get_operators(M)>{};
}

template <__metaobject_id M>
constexpr auto
get_enumerators(metaobject<M>) requires(__metaobject_is_meta_enum(M)) {
    return metaobject<__metaobject_get_enumerators(M)>{};
}

template <__metaobject_id M>
constexpr auto
get_parameters(metaobject<M>) requires(__metaobject_is_meta_callable(M)) {
    return metaobject<__metaobject_get_parameters(M)>{};
}

template <__metaobject_id M>
constexpr auto
get_captures(metaobject<M>) requires(__metaobject_is_meta_lambda(M)) {
    return metaobject<__metaobject_get_captures(M)>{};
}

template <__metaobject_id M>
constexpr auto
hide_private(metaobject<M>) requires(__metaobject_is_meta_object_sequence(M)) {
    return metaobject<__metaobject_hide_private(M)>{};
}

template <__metaobject_id M>
constexpr auto hide_protected(metaobject<M>) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return metaobject<__metaobject_hide_protected(M)>{};
}

template <size_t I, __metaobject_id M>
constexpr auto
get_element(metaobject<M>) requires(__metaobject_is_meta_object_sequence(M)) {
    return metaobject<__metaobject_get_element(M, I)>{};
}

// unpacking
template <__metaobject_id... M>
struct unpacked_metaobject_sequence {};

template <__metaobject_id M>
constexpr auto unpack(metaobject<M>) {
    return __unpack_metaobject_seq<unpacked_metaobject_sequence, M>{};
}

// unpacked range operations
// transform
template <__metaobject_id... M, typename F>
constexpr auto transform(unpacked_metaobject_sequence<M...>, F function) {
    return unpacked_metaobject_sequence<
      unwrap<decltype((function(metaobject<M>{})))>...>{};
}

template <__metaobject_id M, typename F>
constexpr auto transform(metaobject<M> mo, F function) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return transform(unpack(mo), function);
}

// transform types
template <
  template <typename...>
  class Container,
  template <typename>
  class Transform,
  __metaobject_id... M>
constexpr auto store_transformed_types(unpacked_metaobject_sequence<M...>) {
    return Container<typename Transform<__unrefltype(M)>::type...>{};
}

template <
  template <typename...>
  class Container,
  template <typename>
  class Transform,
  __metaobject_id M>
constexpr auto store_transformed_types(metaobject<M> mo) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return store_transformed_types(unpack(mo));
}

template <template <typename> class Transform, __metaobject_id... M>
constexpr auto transform_types(unpacked_metaobject_sequence<M...> ms) {
    return store_transformed_types<type_list, Transform>(ms);
}

template <template <typename> class Transform, __metaobject_id M>
constexpr auto transform_types(metaobject<M> mo) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return store_transformed_types<type_list, Transform>(unpack(mo));
}

// extract types
template <__metaobject_id... M>
constexpr auto extract_types(unpacked_metaobject_sequence<M...> ms) {
    return transform_types<std::type_identity>(ms);
}

template <__metaobject_id M>
constexpr auto extract_types(metaobject<M> mo) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return transform_types<std::type_identity>(unpack(mo));
}

// for each
template <__metaobject_id... M, typename F>
constexpr void for_each(unpacked_metaobject_sequence<M...>, F function) {
    (void)(..., function(metaobject<M>{}));
}

template <__metaobject_id M, typename F>
constexpr void for_each(metaobject<M> mo, F function) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return for_each(unpack(mo), std::move(function));
}

// for each with iteration info
class for_each_iteration_info {
private:
    std::size_t _index;
    std::size_t _count;

public:
    constexpr for_each_iteration_info(
      std::size_t index,
      std::size_t count) noexcept
      : _index{index}
      , _count{count} {}

    constexpr auto is_first() const noexcept -> bool {
        return _index == 0Z;
    }

    constexpr auto is_last() const noexcept -> bool {
        return _index + 1Z >= _count;
    }

    constexpr auto index() const noexcept -> std::size_t {
        return _index;
    }

    constexpr auto count() const noexcept -> std::size_t {
        return _count;
    }
};

template <__metaobject_id M, typename F>
constexpr void for_each_info(metaobject<M> mo, F function) requires(
  __metaobject_is_meta_object_sequence(M)) {
    std::size_t index{0};
    const auto count{__metaobject_get_size(M)};
    return for_each(unpack(mo), [&](auto me) {
        function(me, for_each_iteration_info(index++, count));
    });
}

// find if
template <typename F>
constexpr auto find_if(unpacked_metaobject_sequence<>, F) {
    return no_metaobject;
}

template <__metaobject_id M1, __metaobject_id... M, typename F>
constexpr auto find_if(unpacked_metaobject_sequence<M1, M...>, F predicate) {
    if constexpr(predicate(metaobject<M1>{})) {
        return metaobject<M1>{};
    } else {
        return find_if(unpacked_metaobject_sequence<M...>{}, predicate);
    }
}

template <__metaobject_id M, typename F>
constexpr auto find_if(metaobject<M> mo, F predicate) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return find_if(unpack(mo), predicate);
}

// select
template <typename T, __metaobject_id... M, typename F, typename... P>
constexpr auto
select(unpacked_metaobject_sequence<M...>, F function, T fallback, P&&... param)
  -> T {
    (..., function(fallback, metaobject<M>{}, std::forward<P>(param)...));
    return fallback;
}

template <typename T, __metaobject_id M, typename F, typename... P>
constexpr auto select(metaobject<M> mo, F function, T fallback, P&&... param)
  -> T requires(__metaobject_is_meta_object_sequence(M)) {
    return select(
      unpack(mo),
      std::move(function),
      std::move(fallback),
      std::forward<P>(param)...);
}

// type unreflection
template <__metaobject_id M>
using _get_reflected_type = type_identity<__unrefltype(M)>;

template <__metaobject_id M>
consteval auto
get_reflected_type(metaobject<M>) requires(__metaobject_is_meta_type(M)) {
    return _get_reflected_type<M>{};
}

template <template <typename T> class transform, __metaobject_id M>
using _get_transformed_type = transform<__unrefltype(M)>;

template <template <typename T> class Transform, __metaobject_id M>
consteval auto
get_transformed_type(metaobject<M>) requires(__metaobject_is_meta_type(M)) {
    return _get_transformed_type<Transform, M>{};
}

template <typename T, __metaobject_id M>
consteval auto is_type(metaobject<M>, type_identity<T> = {})
  -> bool requires(__metaobject_is_meta_type(M)) {
    return std::is_same_v<__unrefltype(M), T>;
}

template <typename T, __metaobject_id M>
consteval auto has_type(metaobject<M>, type_identity<T> = {}) -> bool {
    if constexpr(__metaobject_is_meta_typed(M)) {
        return std::is_same_v<__unrefltype(__metaobject_get_type(M)), T>;
    } else {
        return false;
    }
}

// reflection "operator"
#if defined(MIRROR_YCM)
#define mirror(...) \
    ::mirror::metaobject<0U> {}
#else
#define mirror(...) \
    ::mirror::metaobject<__reflexpr_id(__VA_ARGS__)> {}
#endif

} // namespace mirror

#endif // !_LIBCPP_HAS_NO_REFLECTION && !_LIBCPP_HAS_NO_REFLECTION_EXT

#endif // MIRROR_PRIMITIVES_HPP
