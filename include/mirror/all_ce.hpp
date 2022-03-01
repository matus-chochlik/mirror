// Automatically generated file (all edits will be lost)
// Copyright Matus Chochlik.
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#ifndef MIRROR_ALL_HPP
#define MIRROR_ALL_HPP


#ifndef MIRROR_ENUM_UTILS_HPP
#define MIRROR_ENUM_UTILS_HPP


#ifndef MIRROR_PLACEHOLDER_HPP
#define MIRROR_PLACEHOLDER_HPP


#ifndef MIRROR_OVERLOAD_HPP
#define MIRROR_OVERLOAD_HPP

#include <utility>

namespace mirror {

template <typename... Func>
struct overload;

template <typename Func>
struct overload<Func> : Func {
    overload(const Func& func)
      : Func{func} {}

    overload(Func&& func)
      : Func{std::move(func)} {}

    using Func::operator();
};

template <typename Func, typename... Funcs>
struct overload<Func, Funcs...>
  : Func
  , overload<Funcs...> {
    template <typename... F>
    overload(const Func& func, F&&... funcs)
      : Func{func}
      , overload<Funcs...>{std::forward<Funcs>(funcs)...} {}

    template <typename... F>
    overload(Func&& func, F&&... funcs)
      : Func{std::move(func)}
      , overload<Funcs...>{std::forward<Funcs>(funcs)...} {}

    using Func::operator();
    using overload<Funcs...>::operator();
};

template <typename... F>
overload(const F&...) -> overload<F...>;

} // namespace mirror

#endif // MIRROR_OVERLOAD_HPP

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

#if defined(MIRROR_YCM)
using __metaobject_id = unsigned;
#endif

namespace mirror {

using std::integral_constant;
using std::string_view;
using std::type_identity;

template <typename... T>
struct type_list {};

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

template <typename X>
consteval auto is_object(const X&) noexcept -> bool {
    return false;
}

template <typename X>
concept metaobject = is_object(X{});

template <__metaobject_id M>
consteval auto unwrap(wrapped_metaobject<M>) noexcept -> __metaobject_id {
    return M;
}

constinit const wrapped_metaobject<__reflexpr_id()> no_metaobject{};

consteval auto reflects_object(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_object(mo);
}

consteval auto has_value(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_object(mo);
}

template <__metaobject_id M>
constexpr auto extract(wrapped_metaobject<M> mo) noexcept {
    return mo;
}

consteval auto reflects_object_sequence(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_object_sequence(mo);
}

consteval auto reflects_named(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_named(mo);
}

consteval auto reflects_alias(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_alias(mo);
}

consteval auto reflects_typed(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_typed(mo);
}

consteval auto reflects_scope(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_scope(mo);
}

consteval auto reflects_scope_member(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_scope_member(mo);
}

template <__metaobject_id M>
consteval auto reflects_global_scope_member(wrapped_metaobject<M>) noexcept
  -> bool {
    if constexpr(__metaobject_is_meta_scope_member(M)) {
        return __metaobject_is_meta_global_scope(__metaobject_get_scope(M));
    } else {
        return false;
    }
}

consteval auto reflects_enumerator(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_enumerator(mo);
}

consteval auto reflects_record_member(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_record_member(mo);
}

consteval auto reflects_base(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_base(mo);
}

consteval auto reflects_namespace(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_namespace(mo);
}

template <__metaobject_id M>
consteval auto reflects_inline_namespace(wrapped_metaobject<M>) noexcept
  -> bool {
    if constexpr(__metaobject_is_meta_namespace(M)) {
        return __metaobject_is_inline(M);
    } else {
        return false;
    }
}

consteval auto reflects_global_scope(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_global_scope(mo);
}

consteval auto reflects_type(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_type(mo);
}

consteval auto reflects_enum(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_enum(mo);
}

consteval auto reflects_record(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_record(mo);
}

consteval auto reflects_class(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_class(mo);
}

consteval auto reflects_lambda(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_lambda(mo);
}

consteval auto reflects_constant(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_constant(mo);
}

consteval auto reflects_variable(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_variable(mo);
}

consteval auto reflects_lambda_capture(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_lambda_capture(mo);
}

consteval auto reflects_function_parameter(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_is_meta_function_parameter(mo);
}

consteval auto reflects_callable(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_callable(mo);
}

consteval auto reflects_function(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_function(mo);
}

consteval auto reflects_member_function(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_member_function(mo);
}

consteval auto reflects_special_member_function(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_is_meta_special_member_function(mo);
}

consteval auto reflects_constructor(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_constructor(mo);
}

consteval auto reflects_destructor(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_destructor(mo);
}

consteval auto reflects_operator(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_operator(mo);
}

consteval auto reflects_conversion_operator(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_is_meta_conversion_operator(mo);
}

consteval auto reflects_expression(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_expression(mo);
}

consteval auto reflects_parenthesized_expression(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_is_meta_parenthesized_expression(mo);
}

consteval auto reflects_construction_expression(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_is_meta_construction_expression(mo);
}

consteval auto reflects_function_call_expression(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_is_meta_function_call_expression(mo);
}

consteval auto reflects_specifier(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_meta_specifier(mo);
}

// unary operations
// boolean

consteval auto is_constexpr(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_constexpr(mo);
}

consteval auto is_noexcept(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_noexcept(mo);
}

consteval auto is_explicit(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_explicit(mo);
}

consteval auto is_inline(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_inline(mo);
}

consteval auto is_thread_local(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_thread_local(mo);
}

consteval auto is_static(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_static(mo);
}

consteval auto is_virtual(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_virtual(mo);
}

consteval auto is_pure_virtual(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_pure_virtual(mo);
}

consteval auto is_final(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_final(mo);
}

consteval auto is_private(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_private(mo);
}

consteval auto is_protected(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_protected(mo);
}

consteval auto is_public(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_public(mo);
}

consteval auto is_unnamed(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_unnamed(mo);
}

consteval auto is_enum(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_enum(mo);
}

consteval auto is_scoped_enum(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_scoped_enum(mo);
}

consteval auto is_union(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_union(mo);
}

consteval auto uses_class_key(__metaobject_id mo) noexcept -> bool {
    return __metaobject_uses_class_key(mo);
}

consteval auto uses_struct_key(__metaobject_id mo) noexcept -> bool {
    return __metaobject_uses_struct_key(mo);
}

consteval auto uses_default_copy_capture(__metaobject_id mo) noexcept -> bool {
    return __metaobject_uses_default_copy_capture(mo);
}

consteval auto uses_default_reference_capture(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_uses_default_reference_capture(mo);
}

consteval auto is_call_operator_const(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_call_operator_const(mo);
}

consteval auto is_explicitly_captured(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_explicitly_captured(mo);
}

consteval auto has_default_argument(__metaobject_id mo) noexcept -> bool {
    return __metaobject_has_default_argument(mo);
}

consteval auto is_const(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_const(mo);
}

consteval auto is_volatile(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_volatile(mo);
}

consteval auto has_lvalueref_qualifier(__metaobject_id mo) noexcept -> bool {
    return __metaobject_has_lvalueref_qualifier(mo);
}

consteval auto has_rvalueref_qualifier(__metaobject_id mo) noexcept -> bool {
    return __metaobject_has_rvalueref_qualifier(mo);
}

consteval auto is_implicitly_declared(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_implicitly_declared(mo);
}

consteval auto is_defaulted(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_defaulted(mo);
}

consteval auto is_deleted(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_deleted(mo);
}

consteval auto is_copy_constructor(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_copy_constructor(mo);
}

consteval auto is_move_constructor(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_move_constructor(mo);
}

consteval auto is_copy_assignment_operator(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_is_copy_assignment_operator(mo);
}

consteval auto is_move_assignment_operator(__metaobject_id mo) noexcept
  -> bool {
    return __metaobject_is_move_assignment_operator(mo);
}

consteval auto is_empty(__metaobject_id mo) noexcept -> bool {
    return __metaobject_is_empty(mo);
}

consteval auto has_one_element(__metaobject_id mo) noexcept -> bool {
    return __metaobject_get_size(mo) == 1Z;
}

consteval auto has_multiple_elements(__metaobject_id mo) noexcept -> bool {
    return __metaobject_get_size(mo) > 1Z;
}

template <__metaobject_id Ml, __metaobject_id Mr>
consteval auto
reflect_same(wrapped_metaobject<Ml>, wrapped_metaobject<Mr>) noexcept -> bool {
    return __metaobject_reflects_same(Ml, Mr);
}

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

// integer
consteval auto get_id(__metaobject_id mo) noexcept -> size_t {
    return __metaobject_get_id_value(mo);
}

consteval auto get_source_line(__metaobject_id mo) noexcept -> size_t {
    return __metaobject_get_source_line(mo);
}

consteval auto get_source_column(__metaobject_id mo) noexcept -> size_t {
    return __metaobject_get_source_column(mo);
}

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

template <__metaobject_id M>
consteval auto get_pointer(wrapped_metaobject<M>) noexcept requires(
  __metaobject_is_meta_variable(M) || __metaobject_is_meta_function(M)) {
    return _get_pointer<M>::value;
}

template <__metaobject_id M>
struct _get_constant
  : integral_constant<
      __unrefltype(__metaobject_get_constant(M)),
      __metaobject_get_constant(M)> {};

template <__metaobject_id M>
constexpr auto get_constant(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_constant(M)) {
    return _get_constant<M>::value;
}

template <__metaobject_id M>
constexpr auto get_value(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_constant(M)) {
    return _get_constant<M>::value;
}

template <__metaobject_id M>
constexpr const auto& get_value(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_variable(M)) {
    return *_get_pointer<M>::value;
}

template <__metaobject_id M, class C>
constexpr const auto& get_value(wrapped_metaobject<M>, const C& obj) noexcept
  requires(
    __metaobject_is_meta_record_member(M) && __metaobject_is_meta_variable(M)) {
    return obj.*_get_pointer<M>::value;
}

template <__metaobject_id M, typename T>
constexpr auto has_value(wrapped_metaobject<M> mo, const T value) noexcept
  -> bool {
    return get_value(mo) == value;
}

template <__metaobject_id M>
constexpr auto& get_reference(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_variable(M)) {
    return *_get_pointer<M>::value;
}

template <__metaobject_id M, class C>
constexpr auto& get_reference(wrapped_metaobject<M>, C& obj) noexcept requires(
  __metaobject_is_meta_record_member(M) && __metaobject_is_meta_variable(M)) {
    return obj.*_get_pointer<M>::value;
}

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

template <__metaobject_id M, typename... A>
constexpr auto invoke(wrapped_metaobject<M>, A&&... args) requires(
  __metaobject_is_meta_function(M) ||
  (__metaobject_is_meta_member_function(M) && __metaobject_is_static(M))) {
    return (*_get_pointer<M>::value)(std::forward<A>(args)...);
}

template <__metaobject_id M, typename C, typename... A>
constexpr auto invoke(wrapped_metaobject<M>, C& obj, A&&... args) requires(
  __metaobject_is_meta_member_function(M) && !__metaobject_is_static(M)) {
    return (obj.*_get_pointer<M>::value)(std::forward<A>(args)...);
}

template <__metaobject_id M, typename... A>
constexpr auto invoke(wrapped_metaobject<M>, A&&... args) -> __unrefltype(
  __metaobject_get_scope(M)) requires(__metaobject_is_meta_constructor(M)) {
    return __unrefltype(__metaobject_get_scope(M))(std::forward<A>(args)...);
}

// string
consteval auto get_debug_info(__metaobject_id mo) noexcept -> string_view {
    return {__metaobject_get_debug_info(mo)};
}

consteval auto get_source_file_name(__metaobject_id mo) noexcept
  -> string_view {
    return {
      __metaobject_get_source_file_name(mo),
      __metaobject_source_file_name_len(mo)};
}

consteval auto get_name(__metaobject_id mo) noexcept -> string_view {
    return {__metaobject_get_name(mo), __metaobject_name_len(mo)};
}

consteval auto get_display_name(__metaobject_id mo) noexcept -> string_view {
    return {
      __metaobject_get_display_name(mo), __metaobject_display_name_len(mo)};
}

// metaobject
template <__metaobject_id M>
constexpr auto get_scope(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_scope_member(M)) {
    return wrapped_metaobject<__metaobject_get_scope(M)>{};
}

template <__metaobject_id M>
constexpr auto get_type(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_typed(M)) {
    return wrapped_metaobject<__metaobject_get_type(M)>{};
}

template <__metaobject_id M>
constexpr auto get_underlying_type(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_enum(M)) {
    return wrapped_metaobject<__metaobject_get_underlying_type(M)>{};
}

template <__metaobject_id M>
constexpr auto get_aliased(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_alias(M)) {
    return wrapped_metaobject<__metaobject_get_aliased(M)>{};
}

template <__metaobject_id M>
constexpr auto remove_all_aliases(wrapped_metaobject<M> mo) noexcept {
    if constexpr(__metaobject_is_meta_alias(M)) {
        return remove_all_aliases(
          wrapped_metaobject<__metaobject_get_aliased(M)>{});
    } else {
        return mo;
    }
}

template <__metaobject_id M>
constexpr auto get_class(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_base(M)) {
    return wrapped_metaobject<__metaobject_get_class(M)>{};
}

template <__metaobject_id M>
constexpr auto get_subexpression(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_parenthesized_expression(M)) {
    return wrapped_metaobject<__metaobject_get_subexpression(M)>{};
}

template <__metaobject_id M>
constexpr auto get_callable(wrapped_metaobject<M>) noexcept requires(
  __metaobject_is_meta_construction_expression(M) ||
  __metaobject_is_meta_function_call_expression(M)) {
    return wrapped_metaobject<__metaobject_get_callable(M)>{};
}

template <__metaobject_id M>
constexpr auto get_base_classes(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_class(M)) {
    return wrapped_metaobject<__metaobject_get_base_classes(M)>{};
}

template <__metaobject_id M>
constexpr auto get_member_types(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_member_types(M)>{};
}

template <__metaobject_id M>
constexpr auto get_data_members(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_data_members(M)>{};
}

template <__metaobject_id M>
constexpr auto get_member_functions(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_member_functions(M)>{};
}

template <__metaobject_id M>
constexpr auto get_constructors(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_constructors(M)>{};
}

template <__metaobject_id M>
constexpr auto get_destructors(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_destructors(M)>{};
}

template <__metaobject_id M>
constexpr auto get_operators(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_record(M)) {
    return wrapped_metaobject<__metaobject_get_operators(M)>{};
}

template <__metaobject_id M>
constexpr auto get_enumerators(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_enum(M)) {
    return wrapped_metaobject<__metaobject_get_enumerators(M)>{};
}

template <__metaobject_id M>
constexpr auto get_parameters(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_callable(M)) {
    return wrapped_metaobject<__metaobject_get_parameters(M)>{};
}

template <__metaobject_id M>
constexpr auto get_captures(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_lambda(M)) {
    return wrapped_metaobject<__metaobject_get_captures(M)>{};
}

template <__metaobject_id M>
constexpr auto hide_private(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return wrapped_metaobject<__metaobject_hide_private(M)>{};
}

template <__metaobject_id M>
constexpr auto hide_protected(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return wrapped_metaobject<__metaobject_hide_protected(M)>{};
}

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

template <typename M>
using get_reflected_type_t = __unrefltype(unwrap(M{}));

template <__metaobject_id M>
consteval auto get_reflected_type(wrapped_metaobject<M>) noexcept
  requires(__metaobject_is_meta_type(M)) {
    return _get_reflected_type<M>{};
}

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

template <__metaobject_id M>
consteval auto get_sizeof(wrapped_metaobject<M> mo) noexcept
  requires(__metaobject_is_meta_type(M) || __metaobject_is_meta_typed(M)) {
    if constexpr(__metaobject_is_meta_typed(M)) {
        return get_sizeof(get_type(mo));
    } else {
        return sizeof(__unrefltype(M));
    }
}

template <typename T, __metaobject_id M>
consteval auto is_type(wrapped_metaobject<M>, type_identity<T> = {}) noexcept
  -> bool requires(__metaobject_is_meta_type(M)) {
    return std::is_same_v<__unrefltype(M), T>;
}

template <template <typename> class Trait, __metaobject_id M>
consteval auto has_type_trait(wrapped_metaobject<M>) noexcept
  -> bool requires(__metaobject_is_meta_type(M)) {
    return Trait<__unrefltype(M)>::value;
}

template <typename T, __metaobject_id M>
consteval auto has_type(wrapped_metaobject<M>, type_identity<T> = {}) noexcept
  -> bool {
    if constexpr(__metaobject_is_meta_typed(M)) {
        return std::is_same_v<__unrefltype(__metaobject_get_type(M)), T>;
    } else {
        return false;
    }
}

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

namespace mirror {

template <typename F>
struct placeholder_expr {
    F f;

    constexpr auto operator()(auto... args) const {
        return f(args...);
    }
};

template <typename F>
placeholder_expr(F) -> placeholder_expr<F>;

template <typename El, typename Er>
constexpr auto operator^(placeholder_expr<El> l, placeholder_expr<Er> r) {
    return placeholder_expr{overload(
      [l, r](auto x) { return l(x) ^ r(x); },
      [l, r](auto x, auto y) { return l(x, y) ^ r(x, y); })};
}

template <typename El, typename Er>
constexpr auto operator+(placeholder_expr<El> l, placeholder_expr<Er> r) {
    return placeholder_expr{overload(
      [l, r](auto x) { return l(x) + r(x); },
      [l, r](auto x, auto y) { return l(x, y) + r(x, y); })};
}

template <typename El, typename Er>
constexpr auto operator==(placeholder_expr<El> l, placeholder_expr<Er> r) {
    return placeholder_expr{overload(
      [l, r](auto x) { return l(x) == r(x); },
      [l, r](auto x, auto y) { return l(x, y) == r(x, y); })};
}

template <typename El, typename Er>
constexpr auto operator!=(placeholder_expr<El> l, placeholder_expr<Er> r) {
    return placeholder_expr{overload(
      [l, r](auto x) { return l(x) != r(x); },
      [l, r](auto x, auto y) { return l(x, y) != r(x, y); })};
}

template <typename El, typename Er>
constexpr auto operator<(placeholder_expr<El> l, placeholder_expr<Er> r) {
    return placeholder_expr{overload(
      [l, r](auto x) { return l(x) < r(x); },
      [l, r](auto x, auto y) { return l(x, y) < r(x, y); })};
}

template <>
struct placeholder_expr<std::integral_constant<size_t, 1>> {
    constexpr auto operator()(auto mo) const {
        return mo;
    }

    constexpr auto operator()(auto mo, auto) const {
        return mo;
    }
};

template <>
struct placeholder_expr<std::integral_constant<size_t, 2>> {
    constexpr auto operator()(auto, auto mo) const {
        return mo;
    }
};

static constinit const placeholder_expr<std::integral_constant<size_t, 1>> _1{};
static constinit const placeholder_expr<std::integral_constant<size_t, 2>> _2{};

template <typename X>
constexpr auto not_(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return !e(a...);
    }};
}

template <typename X>
constexpr auto reflects_object(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_object(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_object_sequence(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_object_sequence(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_named(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_named(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_alias(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_alias(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_scope(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_scope(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_typed(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_typed(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_scope_member(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_scope_member(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_global_scope_member(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_global_scope_member(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_enumerator(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_enumerator(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_record_member(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_record_member(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_base(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_base(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_namespace(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_namespace(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_inline_namespace(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_inline_namespace(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_global_scope(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_global_scope(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_global_type(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_global_type(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_enum(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_enum(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_record(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_record(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_class(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_class(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_lambda(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_lambda(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_constant(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_constant(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_variable(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_variable(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_lambda_capture(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_lambda_capture(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_function_parameter(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_function_parameter(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_callable(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_callable(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_function(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_function(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_member_function(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_member_function(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_special_member_function(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_special_member_function(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_constructor(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_constructor(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_destructor(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_destructor(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_operator(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_operator(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_conversion_operator(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_conversion_operator(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_expression(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_expression(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_parenthesized_expression(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_parenthesized_expression(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_function_call_expression(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_function_call_expression(e(a...));
    }};
}

template <typename X>
constexpr auto reflects_specifier(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return reflects_specifier(e(a...));
    }};
}

// unary operations
// boolean

template <typename X>
constexpr auto is_constexpr(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_constexpr(e(a...));
    }};
}

template <typename X>
constexpr auto is_noexcept(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_noexcept(e(a...));
    }};
}

template <typename X>
constexpr auto is_explicit(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_explicit(e(a...));
    }};
}

template <typename X>
constexpr auto is_inline(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_inline(e(a...));
    }};
}

template <typename X>
constexpr auto is_thread_local(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_thread_local(e(a...));
    }};
}

template <typename X>
constexpr auto is_static(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_static(e(a...));
    }};
}

template <typename X>
constexpr auto is_virtual(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_virtual(e(a...));
    }};
}

template <typename X>
constexpr auto is_pure_virtual(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_pure_virtual(e(a...));
    }};
}

template <typename X>
constexpr auto is_pure_final(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_pure_final(e(a...));
    }};
}

template <typename X>
constexpr auto is_private(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_private(e(a...));
    }};
}

template <typename X>
constexpr auto is_protected(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_protected(e(a...));
    }};
}

template <typename X>
constexpr auto is_public(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_public(e(a...));
    }};
}

template <typename X>
constexpr auto is_unnamed(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_unnamed(e(a...));
    }};
}

template <typename X>
constexpr auto is_enum(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_enum(e(a...));
    }};
}

template <typename X>
constexpr auto is_scoped_enum(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_scoped_enum(e(a...));
    }};
}

template <typename X>
constexpr auto is_union(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_union(e(a...));
    }};
}

template <typename X>
constexpr auto uses_class_key(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return uses_class_key(e(a...));
    }};
}

template <typename X>
constexpr auto uses_struct_key(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return uses_struct_key(e(a...));
    }};
}

template <typename X>
constexpr auto uses_default_copy_capture(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return uses_default_copy_capture(e(a...));
    }};
}

template <typename X>
constexpr auto uses_default_reference_capture(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return uses_default_reference_capture(e(a...));
    }};
}

template <typename X>
constexpr auto is_call_operator_const(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_call_operator_const(e(a...));
    }};
}

template <typename X>
constexpr auto is_explicitly_captured(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_explicitly_captured(e(a...));
    }};
}

template <typename X>
constexpr auto has_default_argument(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return has_default_argument(e(a...));
    }};
}

template <typename X>
constexpr auto is_const(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_const(e(a...));
    }};
}

template <typename X>
constexpr auto is_volatile(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_volatile(e(a...));
    }};
}

template <typename X>
constexpr auto has_lvalueref_qualifier(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return has_lvalueref_qualifier(e(a...));
    }};
}

template <typename X>
constexpr auto has_rvalueref_qualifier(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return has_rvalueref_qualifier(e(a...));
    }};
}

template <typename X>
constexpr auto is_implicitly_declared(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_implicitly_declared(e(a...));
    }};
}

template <typename X>
constexpr auto is_defaulted(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_defaulted(e(a...));
    }};
}

template <typename X>
constexpr auto is_deleted(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_deleted(e(a...));
    }};
}

template <typename X>
constexpr auto is_copy_constructor(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_copy_constructor(e(a...));
    }};
}

template <typename X>
constexpr auto is_move_constructor(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_move_constructor(e(a...));
    }};
}

template <typename X>
constexpr auto is_copy_assignment_operator(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_copy_assignment_operator(e(a...));
    }};
}

template <typename X>
constexpr auto is_move_assignment_operator(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_move_assignment_operator(e(a...));
    }};
}

template <typename X>
constexpr auto is_empty(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return is_empty(e(a...));
    }};
}

template <typename X>
constexpr auto has_one_element(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return has_one_element(e(a...));
    }};
}

template <typename X>
constexpr auto has_multiple_elements(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return has_multiple_elements(e(a...));
    }};
}

// integer
template <typename X>
constexpr auto get_id(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_id(e(a...));
    }};
}

template <typename X>
constexpr auto get_source_line(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_source_line(e(a...));
    }};
}

template <typename X>
constexpr auto get_source_column(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_source_column(e(a...));
    }};
}

template <typename X>
constexpr auto get_size(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_size(e(a...));
    }};
}

template <size_t I, typename X>
constexpr auto get_element(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_element<I>(e(a...));
    }};
}

template <typename X>
constexpr auto get_front(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_front(e(a...));
    }};
}

template <typename X>
constexpr auto get_constant(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_constant(e(a...));
    }};
}

template <typename X>
constexpr auto get_pointer(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_pointer(e(a...));
    }};
}

template <typename X>
constexpr auto get_value(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_value(e(a...));
    }};
}

template <typename X, typename T>
constexpr auto has_value(placeholder_expr<X> e, const T value) {
    return placeholder_expr{[e, value](auto... a) {
        return has_value(e(a...), value);
    }};
}

template <typename X>
constexpr auto get_reference(placeholder_expr<X> e) -> auto& {
    return placeholder_expr{[e](auto... a) {
        return get_reference(e(a...));
    }};
}

// string
template <typename X>
constexpr auto get_debug_info(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_debug_info(e(a...));
    }};
}

template <typename X>
constexpr auto get_source_file_name(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_source_file_name(e(a...));
    }};
}

template <typename X>
constexpr auto get_name(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_name(e(a...));
    }};
}

template <typename X>
constexpr auto has_name(placeholder_expr<X> e, string_view str) {
    return placeholder_expr{[e, str](auto... a) {
        return has_name(e(a...), str);
    }};
}

template <typename X>
constexpr auto get_display_name(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_display_name(e(a...));
    }};
}

template <typename X>
constexpr auto get_full_name(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_full_name(e(a...));
    }};
}

template <typename X>
constexpr auto to_string(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return std::string(e(a...));
    }};
}

// metaobject
template <typename X>
constexpr auto get_scope(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_scope(e(a...));
    }};
}

template <typename X>
constexpr auto get_type(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_type(e(a...));
    }};
}

template <typename X>
constexpr auto get_base_type(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_base_type(e(a...));
    }};
}

template <typename X>
constexpr auto get_element_type(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_element_type(e(a...));
    }};
}

template <typename X>
constexpr auto get_underlying_type(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_underlying_type(e(a...));
    }};
}

template <typename X>
constexpr auto get_aliased(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_aliased(e(a...));
    }};
}

template <typename X>
constexpr auto remove_all_aliases(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return remove_all_aliases(e(a...));
    }};
}

template <typename X>
constexpr auto get_class(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_class(e(a...));
    }};
}

template <typename X>
constexpr auto get_subexpression(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_subexpression(e(a...));
    }};
}

template <typename X>
constexpr auto get_callable(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_callable(e(a...));
    }};
}

template <typename X>
constexpr auto get_base_classes(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_base_classes(e(a...));
    }};
}

template <typename X>
constexpr auto get_member_types(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_member_types(e(a...));
    }};
}

template <typename X>
constexpr auto get_data_members(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_data_members(e(a...));
    }};
}

template <typename X>
constexpr auto get_member_functions(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_member_functions(e(a...));
    }};
}

template <typename X>
constexpr auto get_constructors(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_constructors(e(a...));
    }};
}

template <typename X>
constexpr auto get_destructors(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_destructors(e(a...));
    }};
}

template <typename X>
constexpr auto get_operators(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_operators(e(a...));
    }};
}

template <typename X>
constexpr auto get_enumerators(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_enumerators(e(a...));
    }};
}

template <typename X>
constexpr auto get_parameters(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_parameters(e(a...));
    }};
}

template <typename X>
constexpr auto get_captures(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_captures(e(a...));
    }};
}

template <typename X>
constexpr auto hide_private(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return hide_private(e(a...));
    }};
}

template <typename X>
constexpr auto hide_protected(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return hide_protected(e(a...));
    }};
}

template <typename X>
constexpr auto get_reflected_type(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_reflected_type(e(a...));
    }};
}

template <typename X, template <typename> class Transform>
constexpr auto get_transformed_type(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_transformed_type<Transform>(e(a...));
    }};
}

template <typename X>
constexpr auto get_sizeof(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_sizeof(e(a...));
    }};
}

template <typename T, typename X>
constexpr auto is_type(placeholder_expr<X> e, type_identity<T> tid = {}) {
    return placeholder_expr{[e, tid](auto... a) {
        return is_type(e(a...), tid);
    }};
}

template <template <typename> class Trait, typename X>
constexpr auto has_type_trait(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return has_type_trait<Trait>(e(a...));
    }};
}

template <typename T, typename X>
constexpr auto has_type(placeholder_expr<X> e, type_identity<T> tid = {}) {
    return placeholder_expr{[e, tid](auto... a) {
        return has_type(e(a...), tid);
    }};
}

template <template <typename> class Trait, typename X>
constexpr auto has_type_with_trait(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return has_type_with_trait<Trait>(e(a...));
    }};
}

template <typename X>
constexpr auto get_hash(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_hash(e(a...));
    }};
}

template <typename X, __metaobject_id Mo>
constexpr auto
is_applicable(placeholder_expr<X> e, wrapped_metaobject<Mo> mo) noexcept {
    return placeholder_expr{[e, mo](auto me) {
        return is_applicable(e(me), mo);
    }};
}

template <__metaobject_id Me, typename X>
constexpr auto
is_applicable(wrapped_metaobject<Me> me, placeholder_expr<X> e) noexcept {
    return placeholder_expr{[e, me](auto... a) {
        return is_applicable(me, e(a...));
    }};
}

template <typename X, __metaobject_id Mo>
constexpr auto
try_apply(placeholder_expr<X> e, wrapped_metaobject<Mo> mo) noexcept {
    return placeholder_expr{[e, mo](auto me) {
        return try_apply(e(me), mo);
    }};
}

template <__metaobject_id Me, typename X>
constexpr auto
try_apply(wrapped_metaobject<Me> me, placeholder_expr<X> e) noexcept {
    return placeholder_expr{[e, me](auto... a) {
        return try_apply(me, e(a...));
    }};
}

template <typename... X>
constexpr auto make_sequence(placeholder_expr<X>... e) {
    return placeholder_expr{[e...](auto... a) {
        return make_sequence(e(a...)...);
    }};
}

template <typename... X>
constexpr auto concat(placeholder_expr<X>... e) {
    return placeholder_expr{[e...](auto... a) {
        return concat(e(a...)...);
    }};
}

template <typename X, typename F, typename A>
constexpr auto fold(placeholder_expr<X> e, F transform, A aggregate) {
    return placeholder_expr{[e, transform, aggregate](auto... a) {
        return fold(e(a...), transform, aggregate);
    }};
}

template <typename X, typename F, typename S>
constexpr auto join(placeholder_expr<X> e, F transform, S separator) {
    return placeholder_expr{[e, transform, separator](auto... a) {
        return join(e(a...), transform, separator);
    }};
}

template <typename X, typename F, typename S, typename A>
constexpr auto
join(placeholder_expr<X> e, F transform, S separator, A aggregate) {
    return placeholder_expr{[e, transform, separator, aggregate](auto... a) {
        return join(e(a...), transform, separator, aggregate);
    }};
}

template <typename X, typename F>
constexpr auto is_sorted(placeholder_expr<X> e, F compare) {
    return placeholder_expr{[e, compare](auto... a) {
        return is_sorted(e(a...), compare);
    }};
}

template <typename X, typename F>
constexpr auto all_of(placeholder_expr<X> e, F predicate) {
    return placeholder_expr{[e, predicate](auto... a) {
        return all_of(e(a...), predicate);
    }};
}

template <typename X, typename F>
constexpr auto any_of(placeholder_expr<X> e, F predicate) {
    return placeholder_expr{[e, predicate](auto... a) {
        return any_of(e(a...), predicate);
    }};
}

template <typename X, typename F>
constexpr auto none_of(placeholder_expr<X> e, F predicate) {
    return placeholder_expr{[e, predicate](auto... a) {
        return none_of(e(a...), predicate);
    }};
}

template <typename X, typename F>
constexpr auto filter(placeholder_expr<X> e, F predicate) {
    return placeholder_expr{[e, predicate](auto... a) {
        return filter(e(a...), predicate);
    }};
}

template <typename X, typename F>
constexpr auto remove_if(placeholder_expr<X> e, F predicate) {
    return placeholder_expr{[e, predicate](auto... a) {
        return remove_if(e(a...), predicate);
    }};
}

template <typename X, typename F>
constexpr auto count_if(placeholder_expr<X> e, F predicate) {
    return placeholder_expr{[e, predicate](auto... a) {
        return count_if(e(a...), predicate);
    }};
}

template <typename X, typename F>
constexpr auto find_if(placeholder_expr<X> e, F predicate) {
    return placeholder_expr{[e, predicate](auto... a) {
        return find_if(e(a...), predicate);
    }};
}

template <typename X, typename F>
constexpr auto find_if_not(placeholder_expr<X> e, F predicate) {
    return placeholder_expr{[e, predicate](auto... a) {
        return find_if_not(e(a...), predicate);
    }};
}

template <typename X, typename F, typename C>
constexpr auto find_ranking(placeholder_expr<X> e, F transform, C compare) {
    return placeholder_expr{[e, transform, compare](auto... a) {
        return find_ranking(e(a...), transform, compare);
    }};
}

template <typename X, typename F>
constexpr auto find_ranking(placeholder_expr<X> e, F transform) {
    return placeholder_expr{[e, transform](auto... a) {
        return find_ranking(e(a...), transform);
    }};
}

template <typename X, typename F, typename C>
constexpr auto get_top_value(placeholder_expr<X> e, F transform, C compare) {
    return placeholder_expr{[e, transform, compare](auto... a) {
        return get_top_value(e(a...), transform, compare);
    }};
}

template <typename X, typename F>
constexpr auto get_top_value(placeholder_expr<X> e, F transform) {
    return placeholder_expr{[e, transform](auto... a) {
        return get_top_value(e(a...), transform);
    }};
}

template <typename T, typename X, typename C, typename F>
constexpr auto
choose(T fallback, placeholder_expr<X> e, C condition, F transform) {
    return placeholder_expr{[e, &fallback, condition, transform](auto... a) {
        return choose(std::move(fallback), e(a...), condition, transform);
    }};
}

template <typename X, typename F>
constexpr auto group_by(placeholder_expr<X> e, F transform) {
    return placeholder_expr{[e, transform](auto... a) {
        return group_by(e(a...), transform);
    }};
}

template <typename X, typename F, typename C>
constexpr auto sort_by(placeholder_expr<X> e, F transform, C compare) {
    return placeholder_expr{[e, transform, compare](auto... a) {
        return sort_by(e(a...), transform, compare);
    }};
}

template <typename X, typename F>
constexpr auto sort_by(placeholder_expr<X> e, F transform) {
    return placeholder_expr{[e, transform](auto... a) {
        return sort_by(e(a...), transform);
    }};
}

template <typename X, typename F>
constexpr auto reverse_sort_by(placeholder_expr<X> e, F transform) {
    return placeholder_expr{[e, transform](auto... a) {
        return reverse_sort_by(e(a...), transform);
    }};
}

template <typename X, typename F, typename C>
constexpr auto group_and_sort_by(placeholder_expr<X> e, F transform, C compare) {
    return placeholder_expr{[e, transform, compare](auto... a) {
        return group_and_sort_by(e(a...), transform, compare);
    }};
}

template <typename X, typename F>
constexpr auto group_and_sort_by(placeholder_expr<X> e, F transform) {
    return placeholder_expr{[e, transform](auto... a) {
        return group_and_sort_by(e(a...), transform);
    }};
}

template <typename X, typename F>
constexpr auto reverse_group_and_sort_by(placeholder_expr<X> e, F transform) {
    return placeholder_expr{[e, transform](auto... a) {
        return reverse_group_and_sort_by(e(a...), transform);
    }};
}

template <typename X>
constexpr auto flatten(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return flatten(e(a...));
    }};
}

template <typename Xl, typename Xr>
constexpr auto reflect_same(placeholder_expr<Xl> el, placeholder_expr<Xr> er) {
    return placeholder_expr{[el, er](auto... a) {
        return reflect_same(el(a...), er(a...));
    }};
}

} // namespace mirror

#endif // MIRROR_PLACEHOLDER_HPP
#include <optional>

namespace mirror {

template <typename E>
auto enum_to_string(E e) noexcept -> string_view {
    return choose(
      std::string_view{},
      get_enumerators(mirror(E)),
      has_value(_1, e),
      get_name(_1));
}

template <typename E>
auto string_to_enum(string_view s) noexcept -> std::optional<E> {
    return choose(
      std::optional<E>{},
      get_enumerators(mirror(E)),
      has_name(_1, s),
      get_value(_1));
}

} // namespace mirror

#endif // MIRROR_ENUM_UTILS_HPP


#ifndef MIRROR_FULL_NAME_HPP
#define MIRROR_FULL_NAME_HPP

#include <string>

namespace mirror {

template <__metaobject_id M>
auto get_full_name(wrapped_metaobject<M>) -> std::string;

template <__metaobject_id Mp>
auto get_qualified_name(wrapped_metaobject<Mp> mo) -> std::string
  requires(__metaobject_is_meta_named(Mp)) {
    if constexpr(reflects_global_scope_member(mo) || !reflects_scope_member(mo)) {
        return std::string{get_name(mo)};
    } else {
        const auto ms = get_scope(mo);
        if constexpr(reflects_inline_namespace(ms) || is_unnamed(ms)) {
            return get_full_name(get_scope(ms)) +
                   "::" + std::string(get_name(mo));
        } else {
            return get_full_name(ms) + "::" + std::string(get_name(mo));
        }
    }
}

namespace _full_type_name {

struct defaults {
    static auto left(std::string s = {}) {
        return s;
    }

    static auto base(std::string s = {}) {
        return s;
    }

    static auto right(std::string s = {}) {
        return s;
    }

    static auto extents(std::string s = {}) {
        return s;
    }

    static auto params(std::string s = {}) {
        return s;
    }
};

template <typename T>
struct decorate : defaults {
    static auto base(std::string = {}) {
        return get_qualified_name(remove_all_aliases(mirror(T)));
    }
};

template <typename T>
struct decorate_defaults {
    static auto left(std::string s = {}) {
        return decorate<T>::left(std::move(s));
    }
    static auto base(std::string s = {}) {
        return decorate<T>::base(std::move(s));
    }
    static auto right(std::string s = {}) {
        return decorate<T>::right(std::move(s));
    }
    static auto extents(std::string s = {}) {
        return decorate<T>::extents(std::move(s));
    }
    static auto params(std::string s = {}) {
        return decorate<T>::params(std::move(s));
    }
};

template <typename T>
struct decorate<T*> : decorate_defaults<T> {
    static auto right(std::string s = {}) {
        return decorate<T>::right(s) + "*";
    }
};

template <typename T>
struct decorate<T&> : decorate_defaults<T> {
    static auto right(std::string s = {}) {
        return decorate<T>::right(s) + "&";
    }
};

template <typename T>
struct decorate<T&&> : decorate_defaults<T> {
    static auto right(std::string s = {}) {
        return decorate<T>::right(s) + "&&";
    }
};

template <typename T>
struct decorate<T const> : decorate_defaults<T> {
    static auto right(std::string s = {}) {
        return decorate<T>::right(s) + " const";
    }
};

template <typename T>
struct decorate<T volatile> : decorate_defaults<T> {
    static auto right(std::string s = {}) {
        return decorate<T>::right(s) + " volatile";
    }
};

template <typename T>
struct decorate<T const volatile> : decorate_defaults<T> {
    static auto right(std::string s = {}) {
        return decorate<T>::right(s) + " const volatile";
    }
};

template <typename T>
struct decorate<T[]> : decorate_defaults<T> {
    static auto extents(std::string s = {}) {
        return decorate<T>::extents(s + "[]");
    }
};

template <typename T, std::size_t N>
struct decorate<T[N]> : decorate_defaults<T> {
    static auto extents(std::string s = {}) {
        return decorate<T>::extents(s + "[" + std::to_string(N) + "]");
    }
};

static inline auto make_list(type_list<>) -> std::string {
    return {};
}

template <typename P1, typename... P>
auto make_list(type_list<P1, P...>) -> std::string {
    return (
      get_full_name(mirror(P1)) + ... + (", " + get_full_name(mirror(P))));
}

template <typename R, typename... P>
struct decorate<R(P...)> : defaults {
    static auto left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents();
    }
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return s + "(" + make_list(type_list<P...>{}) + ")" + DR::params();
    }
};

template <typename R, typename... P>
struct decorate<R(P...) noexcept> : defaults {
    static auto left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents();
    }
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return s + "(" + make_list(type_list<P...>{}) + ") noexcept" +
               DR::params();
    }
};

template <typename R, typename... P>
struct decorate<R (*)(P...)> : defaults {
    static auto left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents() + "(";
    }
    static auto right(std::string s = {}) {
        return "*" + s;
    }
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" + make_list(type_list<P...>{}) + ")" +
               DR::params();
    }
};

template <typename R, typename... P>
struct decorate<R (*)(P...) noexcept> : defaults {
    static auto left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents() + "(";
    }
    static auto right(std::string s = {}) {
        return "*" + s;
    }
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" + make_list(type_list<P...>{}) + ") noexcept" +
               DR::params();
    }
};

template <typename R, typename C, typename... P>
struct decorate<R (C::*)(P...)> : defaults {
    static auto left(std::string s = {}) {
        using DR = decorate<R>;
        return s + DR::left() + DR::base() + DR::right() + DR::extents() + "(";
    }
    static auto base(std::string s = {}) {
        return get_full_name(mirror(C)) + "::" + s;
    }
    static auto right(std::string s = {}) {
        return "*" + s;
    }
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" + make_list(type_list<P...>{}) + ")" +
               DR::params();
    }
};

template <typename R, typename C, typename... P>
struct decorate<R (C::*)(P...)&> : decorate<R (C::*)(P...)> {
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" + make_list(type_list<P...>{}) + ") &" +
               DR::params();
    }
};

template <typename R, typename C, typename... P>
struct decorate<R (C::*)(P...) &&> : decorate<R (C::*)(P...)> {
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" + make_list(type_list<P...>{}) + ") &&" +
               DR::params();
    }
};

template <typename R, typename C, typename... P>
struct decorate<R (C::*)(P...) const> : decorate<R (C::*)(P...)> {
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" + make_list(type_list<P...>{}) + ") const" +
               DR::params();
    }
};

template <typename R, typename C, typename... P>
struct decorate<R (C::*)(P...) noexcept> : decorate<R (C::*)(P...)> {
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" + make_list(type_list<P...>{}) + ") noexcept" +
               DR::params();
    }
};

template <typename R, typename C, typename... P>
struct decorate<R (C::*)(P...)& noexcept> : decorate<R (C::*)(P...)> {
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" + make_list(type_list<P...>{}) + ") & noexcept" +
               DR::params();
    }
};

template <typename R, typename C, typename... P>
struct decorate<R (C::*)(P...)&& noexcept> : decorate<R (C::*)(P...)> {
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" + make_list(type_list<P...>{}) + ") && noexcept" +
               DR::params();
    }
};

template <typename R, typename C, typename... P>
struct decorate<R (C::*)(P...) const noexcept> : decorate<R (C::*)(P...)> {
    static auto params(std::string s = {}) {
        using DR = decorate<R>;
        return ")" + s + "(" + make_list(type_list<P...>{}) +
               ") const noexcept" + DR::params();
    }
};

template <typename T, typename C>
struct decorate<T C::*> : defaults {
    static auto left(std::string s = {}) {
        using DT = decorate<T>;
        return s + DT::left() + DT::base() + DT::right() + DT::extents();
    }
    static auto base(std::string s = {}) {
        return " " + get_full_name(mirror(C)) + "::" + s;
    }
    static auto right(std::string s = {}) {
        return "*" + s;
    }
};

template <template <typename...> class T, typename... P>
struct decorate<T<P...>> : defaults {
    static auto base(std::string = {}) {
        return get_qualified_name(remove_all_aliases(mirror(T<P...>)));
    }

    static auto right(std::string s = {}) {
        return "<" + make_list(type_list<P...>{}) + ">" + s;
    }
};

} // namespace _full_type_name

template <__metaobject_id Mp>
auto get_full_name(wrapped_metaobject<Mp> mo) -> std::string {
    if constexpr(reflects_type(mo)) {
        using D = _full_type_name::decorate<__unrefltype(Mp)>;
        return D::left() + D::base() + D::right() + D::extents() + D::params();
    } else if constexpr(reflects_named(mo)) {
        return get_qualified_name(mo);
    } else {
        return {};
    }
}

} // namespace mirror

#endif // MIRROR_FULL_NAME_HPP


#ifndef MIRROR_HASH_HPP
#define MIRROR_HASH_HPP


#ifndef MIRROR_SEQUENCE_HPP
#define MIRROR_SEQUENCE_HPP

#include <string>

namespace mirror {

template <__metaobject_id... M>
struct unpacked_metaobject_sequence {};

template <__metaobject_id M>
consteval auto is_object_sequence(wrapped_metaobject<M>) noexcept -> bool {
    return __metaobject_is_meta_object_sequence(M);
}

template <__metaobject_id... M>
consteval auto is_object_sequence(unpacked_metaobject_sequence<M...>) noexcept
  -> bool {
    return true;
}

template <typename... E>
consteval auto is_object_sequence(type_list<E...>) noexcept -> bool {
    return (... && (is_object(E{}) || is_object_sequence(E{})));
}

template <typename X>
consteval auto is_object_sequence(const X&) noexcept -> bool {
    return false;
}

template <typename X>
concept metaobject_sequence = is_object_sequence(X{});

template <__metaobject_id... M>
consteval auto is_empty(unpacked_metaobject_sequence<M...>) noexcept -> bool {
    return sizeof...(M) == 0Z;
}

template <__metaobject_id... M>
consteval auto has_one_element(unpacked_metaobject_sequence<M...>) noexcept
  -> bool {
    return sizeof...(M) == 1Z;
}

template <__metaobject_id... M>
consteval auto
has_multiple_elements(unpacked_metaobject_sequence<M...>) noexcept -> bool {
    return sizeof...(M) > 1Z;
}

template <__metaobject_id... M>
consteval auto get_size(unpacked_metaobject_sequence<M...>) noexcept -> size_t {
    return sizeof...(M);
}

template <typename... E>
consteval auto get_size(type_list<E...> tl) noexcept -> size_t
  requires(is_object_sequence(tl)) {
    return sizeof...(E);
}

template <__metaobject_id M>
constexpr auto unpack(wrapped_metaobject<M>) noexcept
  -> __unpack_metaobject_seq<unpacked_metaobject_sequence, M> requires(
    __metaobject_is_meta_object_sequence(M)) {
    return {};
}

template <__metaobject_id... M>
constexpr auto unpack(unpacked_metaobject_sequence<M...> ms) noexcept {
    return ms;
}

template <__metaobject_id... M>
constexpr auto make_sequence(wrapped_metaobject<M>...) noexcept
  -> unpacked_metaobject_sequence<M...> {
    return {};
}

// count if
template <__metaobject_id... M, typename F>
constexpr auto
count_if(unpacked_metaobject_sequence<M...>, F predicate) noexcept -> size_t {
    return (0Z + ... + (predicate(wrapped_metaobject<M>{}) ? 1Z : 0Z));
}

template <__metaobject_id M, typename F>
constexpr auto count_if(wrapped_metaobject<M> mo, F predicate) noexcept
  -> size_t requires(__metaobject_is_meta_object_sequence(M)) {
    return count_if(unpack(mo), predicate);
}

// transform
template <__metaobject_id... M, typename F>
constexpr auto
transform(unpacked_metaobject_sequence<M...>, F function) noexcept {
    return unpacked_metaobject_sequence<unwrap(
      function(wrapped_metaobject<M>{}))...>{};
}

template <__metaobject_id M, typename F>
constexpr auto transform(wrapped_metaobject<M> mo, F function) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return transform(unpack(mo), function);
}

template <typename... E, typename F>
constexpr auto transform(type_list<E...> tl, F function) noexcept
  requires(is_object_sequence(tl)) {
    return type_list<decltype(function(E{}))...>{};
}

// transform types
template <
  template <typename...>
  class Container,
  template <typename>
  class Transform,
  __metaobject_id... M>
constexpr auto
store_transformed_types(unpacked_metaobject_sequence<M...>) noexcept {
    return Container<typename Transform<__unrefltype(M)>::type...>{};
}

template <
  template <typename...>
  class Container,
  template <typename>
  class Transform,
  __metaobject_id M>
constexpr auto store_transformed_types(wrapped_metaobject<M> mo) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return store_transformed_types(unpack(mo));
}

template <template <typename> class Transform, __metaobject_id... M>
constexpr auto transform_types(unpacked_metaobject_sequence<M...> ms) noexcept {
    return store_transformed_types<type_list, Transform>(ms);
}

template <template <typename> class Transform, __metaobject_id M>
constexpr auto transform_types(wrapped_metaobject<M> mo) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return store_transformed_types<type_list, Transform>(unpack(mo));
}

// extract types
template <__metaobject_id... M>
constexpr auto extract_types(unpacked_metaobject_sequence<M...> ms) noexcept {
    return transform_types<std::type_identity>(ms);
}

template <__metaobject_id M>
constexpr auto extract_types(wrapped_metaobject<M> mo) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return transform_types<std::type_identity>(unpack(mo));
}

// fold
template <__metaobject_id... M, typename F, typename A>
constexpr auto
fold(unpacked_metaobject_sequence<M...>, F transform, A aggregate) {
    return aggregate(transform(wrapped_metaobject<M>{})...);
}

template <__metaobject_id M, typename F, typename A>
constexpr auto fold(
  wrapped_metaobject<M> mo,
  F transform,
  A aggregate) requires(__metaobject_is_meta_object_sequence(M)) {
    return fold(unpack(mo), transform, aggregate);
}

// join
template <typename F, typename S, typename A>
constexpr auto join(unpacked_metaobject_sequence<>, F, S, A) {
    return S{};
}

template <
  __metaobject_id M,
  __metaobject_id... Ms,
  typename F,
  typename S,
  typename A>
constexpr auto join(
  unpacked_metaobject_sequence<M, Ms...>,
  F transform,
  S separator,
  A aggregate) {
    return aggregate(
      transform(wrapped_metaobject<M>{}),
      aggregate(separator, transform(wrapped_metaobject<Ms>{}))...);
}

template <__metaobject_id... M, typename F, typename S>
constexpr auto
join(unpacked_metaobject_sequence<M...> ms, F transform, S separator) {
    return join(ms, std::move(transform), std::move(separator), [](auto... v) {
        return (... + v);
    });
}

template <__metaobject_id M, typename F, typename S>
constexpr auto join(
  wrapped_metaobject<M> mo,
  F transform,
  S separator) requires(__metaobject_is_meta_object_sequence(M)) {
    return join(unpack(mo), std::move(transform), std::move(separator));
}

// join to string
template <typename F, typename S>
auto join_to_string(unpacked_metaobject_sequence<>, const F&, std::string_view)
  -> std::string {
    return {};
}

template <__metaobject_id M, __metaobject_id... Ms, typename F>
auto join_to_string(
  unpacked_metaobject_sequence<M, Ms...>,
  F transform,
  std::string_view separator) -> std::string {
    std::string result;
    result.reserve(
      ((sizeof...(Ms) * separator.size()) + ... +
       transform(wrapped_metaobject<Ms>{}).size()));
    result.append(transform(wrapped_metaobject<M>{}));
    for_each(unpacked_metaobject_sequence<Ms...>{}, [&](auto mo) {
        result.append(separator);
        result.append(transform(mo));
    });

    return result;
}

template <__metaobject_id M, typename F>
auto join_to_string(
  wrapped_metaobject<M> mo,
  F transform,
  std::string_view separator) -> std::string
  requires(__metaobject_is_meta_object_sequence(M)) {
    return join_to_string(unpack(mo), std::move(transform), separator);
}

// for each
template <__metaobject_id... M, typename F>
constexpr void
for_each(unpacked_metaobject_sequence<M...>, F function) noexcept {
    (void)(..., function(wrapped_metaobject<M>{}));
}

template <__metaobject_id M, typename F>
constexpr void for_each(wrapped_metaobject<M> mo, F function) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return for_each(unpack(mo), std::move(function));
}

template <typename... E, typename F>
constexpr void for_each(type_list<E...>, F function) noexcept {
    (void)(..., function(E{}));
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
constexpr void for_each_info(wrapped_metaobject<M> mo, F function) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    std::size_t index{0};
    const auto count{__metaobject_get_size(M)};
    return for_each(unpack(mo), [&](auto me) {
        function(me, for_each_iteration_info(index++, count));
    });
}

// find if
template <typename F>
constexpr auto find_if(unpacked_metaobject_sequence<>, F) noexcept {
    return no_metaobject;
}

template <__metaobject_id M, __metaobject_id... Mt, typename F>
constexpr auto
find_if(unpacked_metaobject_sequence<M, Mt...>, F predicate) noexcept {
    if constexpr(predicate(wrapped_metaobject<M>{})) {
        return wrapped_metaobject<M>{};
    } else {
        return find_if(unpacked_metaobject_sequence<Mt...>{}, predicate);
    }
}

template <__metaobject_id M, typename F>
constexpr auto find_if(wrapped_metaobject<M> mo, F predicate) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return find_if(unpack(mo), predicate);
}

// find if not
template <typename F>
constexpr auto find_if_not(unpacked_metaobject_sequence<>, F) noexcept {
    return no_metaobject;
}

template <__metaobject_id M, __metaobject_id... Mt, typename F>
constexpr auto
find_if_not(unpacked_metaobject_sequence<M, Mt...>, F predicate) noexcept {
    if constexpr(!predicate(wrapped_metaobject<M>{})) {
        return wrapped_metaobject<M>{};
    } else {
        return find_if_not(unpacked_metaobject_sequence<Mt...>{}, predicate);
    }
}

template <__metaobject_id M, typename F>
constexpr auto find_if_not(wrapped_metaobject<M> mo, F predicate) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return find_if_not(unpack(mo), predicate);
}

// find ranking
template <__metaobject_id M, typename F, typename C>
constexpr auto find_ranking(unpacked_metaobject_sequence<M>, F, C) {
    return wrapped_metaobject<M>{};
}

template <__metaobject_id M0, __metaobject_id M1, typename F, typename C>
constexpr auto
find_ranking(unpacked_metaobject_sequence<M0, M1>, F transform, C compare) {
    const auto l{wrapped_metaobject<M0>{}};
    const auto r{wrapped_metaobject<M1>{}};
    if constexpr(compare(transform(l), transform(r))) {
        return r;
    } else {
        return l;
    }
}

template <
  __metaobject_id M0,
  __metaobject_id M1,
  __metaobject_id M2,
  __metaobject_id... Ms,
  typename F,
  typename C>
constexpr auto find_ranking(
  unpacked_metaobject_sequence<M0, M1, M2, Ms...>,
  F transform,
  C compare) {
    const auto l{wrapped_metaobject<M0>{}};
    const auto r{wrapped_metaobject<M1>{}};
    if constexpr(compare(transform(l), transform(r))) {
        return find_ranking(
          unpacked_metaobject_sequence<M1, M2, Ms...>{}, transform, compare);
    } else {
        return find_ranking(
          unpacked_metaobject_sequence<M0, M2, Ms...>{}, transform, compare);
    }
}

template <__metaobject_id M, typename F, typename C>
constexpr auto find_ranking(
  wrapped_metaobject<M> mo,
  F transform,
  C compare) requires(__metaobject_is_meta_object_sequence(M)) {
    return find_ranking(unpack(mo), transform, compare);
}

template <typename S, typename F>
constexpr auto
find_ranking(S seq, F transform) requires(is_object_sequence(seq)) {
    return find_ranking(seq, transform, [](auto l, auto r) { return l < r; });
}

// get top value
template <__metaobject_id... M, typename F, typename C>
constexpr auto
get_top_value(unpacked_metaobject_sequence<M...> seq, F transform, C compare) {
    return transform(find_ranking(seq, transform, compare));
}

template <__metaobject_id M, typename F, typename C>
constexpr auto get_top_value(
  wrapped_metaobject<M> mo,
  F transform,
  C compare) requires(__metaobject_is_meta_object_sequence(M)) {
    return get_top_value(unpack(mo), transform, compare);
}

template <typename S, typename F>
constexpr auto
get_top_value(S seq, F transform) requires(is_object_sequence(seq)) {
    return get_top_value(seq, transform, [](auto l, auto r) { return l < r; });
}

// filter
template <__metaobject_id... M, typename F>
constexpr auto do_filter(
  unpacked_metaobject_sequence<M...>,
  unpacked_metaobject_sequence<>,
  F) noexcept -> unpacked_metaobject_sequence<M...> {
    return {};
}

template <
  __metaobject_id... Mh,
  __metaobject_id M,
  __metaobject_id... Mt,
  typename F>
constexpr auto do_filter(
  unpacked_metaobject_sequence<Mh...>,
  unpacked_metaobject_sequence<M, Mt...>,
  F predicate) noexcept {
    if constexpr(predicate(wrapped_metaobject<M>{})) {
        return do_filter(
          unpacked_metaobject_sequence<Mh..., M>{},
          unpacked_metaobject_sequence<Mt...>{},
          predicate);
    } else {
        return do_filter(
          unpacked_metaobject_sequence<Mh...>{},
          unpacked_metaobject_sequence<Mt...>{},
          predicate);
    }
}

template <__metaobject_id... M, typename F>
constexpr auto
filter(unpacked_metaobject_sequence<M...> seq, F predicate) noexcept {
    return do_filter(unpacked_metaobject_sequence<>{}, seq, predicate);
}

template <__metaobject_id M, typename F>
constexpr auto filter(wrapped_metaobject<M> mo, F predicate) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return filter(unpack(mo), predicate);
}

// remove if
template <__metaobject_id... M, typename F>
constexpr auto
remove_if(unpacked_metaobject_sequence<M...> seq, F predicate) noexcept {
    return filter(seq, [predicate](auto mo) { return !predicate(mo); });
}

template <__metaobject_id M, typename F>
constexpr auto remove_if(wrapped_metaobject<M> mo, F predicate) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return remove_if(unpack(mo), predicate);
}

// is sorted
template <typename F>
constexpr auto is_sorted(unpacked_metaobject_sequence<>, F) {
    return true;
}

template <__metaobject_id M, typename F>
constexpr auto is_sorted(unpacked_metaobject_sequence<M>, F) {
    return true;
}

template <__metaobject_id M0, __metaobject_id M1, typename F>
constexpr auto is_sorted(unpacked_metaobject_sequence<M0, M1>, F compare) {
    return compare(wrapped_metaobject<M0>{}, wrapped_metaobject<M1>{});
}

template <
  __metaobject_id M0,
  __metaobject_id M1,
  __metaobject_id M2,
  __metaobject_id... Ms,
  typename F>
constexpr auto
is_sorted(unpacked_metaobject_sequence<M0, M1, M2, Ms...>, F compare) {
    return compare(wrapped_metaobject<M0>{}, wrapped_metaobject<M1>{}) &&
           is_sorted(unpacked_metaobject_sequence<M1, M2, Ms...>{}, compare);
}

template <__metaobject_id M, typename F>
constexpr auto is_sorted(wrapped_metaobject<M> mo, F compare) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return is_sorted(unpack(mo), compare);
}

// all of
template <__metaobject_id... M, typename F>
constexpr auto all_of(unpacked_metaobject_sequence<M...>, F predicate) noexcept
  -> bool {
    return (... && predicate(wrapped_metaobject<M>{}));
}

template <__metaobject_id M, typename F>
constexpr auto all_of(wrapped_metaobject<M> mo, F predicate) noexcept
  -> bool requires(__metaobject_is_meta_object_sequence(M)) {
    return all_of(unpack(mo), predicate);
}

template <typename... E, typename F>
constexpr auto all_of(type_list<E...> tl, F predicate) noexcept
  -> bool requires(is_object_sequence(tl)) {
    return (... && predicate(E{}));
}

// any_of
template <__metaobject_id... M, typename F>
constexpr auto any_of(unpacked_metaobject_sequence<M...>, F predicate) noexcept
  -> bool {
    return (... || predicate(wrapped_metaobject<M>{}));
}

template <__metaobject_id M, typename F>
constexpr auto any_of(wrapped_metaobject<M> mo, F predicate) noexcept
  -> bool requires(__metaobject_is_meta_object_sequence(M)) {
    return any_of(unpack(mo), predicate);
}

template <typename... E, typename F>
constexpr auto any_of(type_list<E...> tl, F predicate) noexcept
  -> bool requires(is_object_sequence(tl)) {
    return (... || predicate(E{}));
}

// none_of
template <__metaobject_id... M, typename F>
constexpr auto none_of(unpacked_metaobject_sequence<M...>, F predicate) noexcept
  -> bool {
    return !(... || predicate(wrapped_metaobject<M>{}));
}

template <__metaobject_id M, typename F>
constexpr auto none_of(wrapped_metaobject<M> mo, F predicate) noexcept
  -> bool requires(__metaobject_is_meta_object_sequence(M)) {
    return none_of(unpack(mo), predicate);
}

template <typename... E, typename F>
constexpr auto none_of(type_list<E...> tl, F predicate) noexcept
  -> bool requires(is_object_sequence(tl)) {
    return !(... && predicate(E{}));
}

// choose
template <typename T, __metaobject_id... M, typename C, typename F>
constexpr auto choose(
  T fallback,
  unpacked_metaobject_sequence<M...>,
  C condition,
  F transform) noexcept -> T {
    const auto function = [&fallback, condition, transform](auto mo) {
        if(condition(mo)) {
            fallback = transform(mo);
        }
    };
    (void)(..., function(wrapped_metaobject<M>{}));
    return fallback;
}

template <typename T, typename... E, typename C, typename F>
constexpr auto
choose(T fallback, type_list<E...> tl, C condition, F transform) noexcept -> T
  requires(is_object_sequence(tl)) {
    const auto function = [&fallback, condition, transform](auto mo) {
        if(condition(mo)) {
            fallback = transform(mo);
        }
    };
    (void)(..., function(E{}));
    return fallback;
}

template <typename T, __metaobject_id M, typename C, typename F>
constexpr auto
choose(T fallback, wrapped_metaobject<M> mo, C condition, F transform) noexcept
  -> T requires(__metaobject_is_meta_object_sequence(M)) {
    return choose(std::move(fallback), unpack(mo), condition, transform);
}

// concat
template <__metaobject_id... L, __metaobject_id... R>
constexpr auto concat(
  unpacked_metaobject_sequence<L...>,
  unpacked_metaobject_sequence<R...>) noexcept
  -> unpacked_metaobject_sequence<L..., R...> {
    return {};
}

template <typename... L, typename... R>
constexpr auto concat(type_list<L...>, type_list<R...>) noexcept
  -> type_list<L..., R...> {
    return {};
}

template <metaobject_sequence M>
constexpr auto concat(M ms) noexcept {
    return ms;
}

template <metaobject_sequence M, metaobject_sequence... Ms>
constexpr auto concat(M h, Ms... t) noexcept {
    return concat(unpack(h), concat(unpack(t)...));
}

// sort by
template <typename E, typename... L, typename F, typename C>
constexpr auto do_insert_by(type_list<L...>, type_list<>, F, C) {
    return type_list<L..., E>{};
}

template <
  typename E,
  typename... L,
  typename M,
  typename... R,
  typename F,
  typename C>
constexpr auto
do_insert_by(type_list<L...>, type_list<M, R...>, F transform, C compare) {
    if constexpr(compare(transform(E{}), transform(M{}))) {
        return type_list<L..., E, M, R...>{};
    } else {
        return do_insert_by<E>(
          type_list<L..., M>{}, type_list<R...>{}, transform, compare);
    }
}

template <typename... E, typename F, typename C>
constexpr auto do_sort_by(type_list<E...> result, type_list<>, F, C) {
    return result;
}

template <typename... L, typename E, typename... R, typename F, typename C>
constexpr auto
do_sort_by(type_list<L...>, type_list<E, R...>, F transform, C compare) {
    return do_sort_by(
      do_insert_by<E>(type_list<>{}, type_list<L...>{}, transform, compare),
      type_list<R...>{},
      transform,
      compare);
}

template <typename... E, typename F, typename C>
constexpr auto sort_by(type_list<E...> s, F transform, C compare) requires(
  is_object_sequence(s)) {
    return do_sort_by(type_list<>{}, s, transform, compare);
}

template <__metaobject_id... M, typename F, typename C>
constexpr auto
sort_by(unpacked_metaobject_sequence<M...>, F transform, C compare) {
    return sort_by(type_list<wrapped_metaobject<M>...>{}, transform, compare);
}

template <__metaobject_id M, typename F, typename C>
constexpr auto sort_by(
  wrapped_metaobject<M> mo,
  F transform,
  C compare) requires(__metaobject_is_meta_object_sequence(M)) {
    return sort_by(unpack(mo), transform, compare);
}

template <typename S, typename F>
constexpr auto sort_by(S s, F transform) requires(is_object_sequence(s)) {
    return sort_by(s, transform, [](auto l, auto r) { return l < r; });
}

template <typename S, typename F>
constexpr auto
reverse_sort_by(S s, F transform) requires(is_object_sequence(s)) {
    return sort_by(s, transform, [](auto l, auto r) { return l > r; });
}

// group by
template <typename... E, typename F, typename C>
constexpr auto
do_group_by(unpacked_metaobject_sequence<>, type_list<E...> result, F, C) {
    return result;
}

template <
  __metaobject_id M,
  __metaobject_id... Mt,
  typename... T,
  typename F,
  typename C>
constexpr auto do_group_by(
  unpacked_metaobject_sequence<M, Mt...> src,
  type_list<T...>,
  F transform,
  C equal) {
    const auto predicate = [=](auto mo) {
        return equal(transform(mo), transform(wrapped_metaobject<M>{}));
    };
    return do_group_by(
      remove_if(src, predicate),
      type_list<T..., decltype(filter(src, predicate))>{},
      transform,
      equal);
}

template <__metaobject_id... M, typename F, typename C>
constexpr auto
group_by(unpacked_metaobject_sequence<M...> s, F transform, C equal) {
    return do_group_by(s, type_list<>{}, transform, equal);
}

template <__metaobject_id M, typename F, typename C>
constexpr auto group_by(
  wrapped_metaobject<M> mo,
  F transform,
  C equal) requires(__metaobject_is_meta_object_sequence(M)) {
    return group_by(unpack(mo), transform, equal);
}

template <__metaobject_id... M, typename F>
constexpr auto group_by(unpacked_metaobject_sequence<M...> s, F transform) {
    return do_group_by(
      s, type_list<>{}, transform, [](auto l, auto r) { return l == r; });
}

template <__metaobject_id M, typename F>
constexpr auto group_by(wrapped_metaobject<M> ms, F transform) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return group_by(unpack(ms), transform);
}

// group and sort by
template <typename S, typename F, typename C>
constexpr auto
group_and_sort_by(S s, F transform, C compare) requires(is_object_sequence(s)) {
    return sort_by(
      group_by(s, transform),
      [transform](auto e) { return transform(get_front(e)); },
      compare);
}

template <typename S, typename F>
constexpr auto
group_and_sort_by(S s, F transform) requires(is_object_sequence(s)) {
    return group_and_sort_by(
      s, transform, [](auto l, auto r) { return l < r; });
}

template <typename S, typename F>
constexpr auto
reverse_group_and_sort_by(S s, F transform) requires(is_object_sequence(s)) {
    return group_and_sort_by(
      s, transform, [](auto l, auto r) { return l > r; });
}

// flatten
template <__metaobject_id... M>
constexpr auto flatten(unpacked_metaobject_sequence<M...>) requires(
  ...&& is_object_sequence(wrapped_metaobject<M>{})) {
    return concat(wrapped_metaobject<M>{}...);
}

template <typename... E>
constexpr auto flatten(type_list<E...> tl) requires(is_object_sequence(tl)) {
    return concat(E{}...);
}

template <size_t I, __metaobject_id M, __metaobject_id... Mt>
consteval auto get(mirror::unpacked_metaobject_sequence<M, Mt...>) noexcept {
    if constexpr(I == 0Z) {
        return mirror::wrapped_metaobject<M>{};
    } else {
        return get<I - 1Z>(mirror::unpacked_metaobject_sequence<Mt...>{});
    }
}

template <size_t I, __metaobject_id... M>
constexpr auto get_element(unpacked_metaobject_sequence<M...> mos) noexcept {
    return get<I>(mos);
}

template <__metaobject_id... M>
constexpr auto get_front(unpacked_metaobject_sequence<M...> mos) noexcept {
    return get<0Z>(mos);
}

template <size_t I, typename E, typename... Et>
consteval auto get(mirror::type_list<E, Et...>) noexcept {
    if constexpr(I == 0Z) {
        return E{};
    } else {
        return get<I - 1Z>(mirror::type_list<Et...>{});
    }
}

template <size_t I, typename... E>
constexpr auto get_element(type_list<E...> tl) noexcept
  requires(is_object_sequence(tl)) {
    return get<I>(tl);
}

template <typename... E>
constexpr auto get_front(type_list<E...> tl) noexcept
  requires(is_object_sequence(tl) && sizeof...(E) != 0Z) {
    return get<0Z>(tl);
}

} // namespace mirror

namespace std {

template <__metaobject_id... M>
struct tuple_size<mirror::unpacked_metaobject_sequence<M...>>
  : integral_constant<size_t, sizeof...(M)> {};

template <typename... E>
struct tuple_size<mirror::type_list<E...>>
  : integral_constant<size_t, sizeof...(E)> {};

template <__metaobject_id M, __metaobject_id... Mt>
struct tuple_element<0Z, mirror::unpacked_metaobject_sequence<M, Mt...>>
  : type_identity<mirror::wrapped_metaobject<M>> {};

template <size_t I, __metaobject_id M, __metaobject_id... Mt>
struct tuple_element<I, mirror::unpacked_metaobject_sequence<M, Mt...>>
  : tuple_element<I - 1Z, mirror::unpacked_metaobject_sequence<Mt...>> {};

template <typename E, typename... Et>
struct tuple_element<0Z, mirror::type_list<E, Et...>> : type_identity<E> {};

template <size_t I, typename E, typename... Et>
struct tuple_element<I, mirror::type_list<E, Et...>>
  : tuple_element<I - 1Z, mirror::type_list<Et...>> {};

} // namespace std

#endif // MIRROR_SEQUENCE_HPP
#include <functional>

namespace mirror {

// TODO: make the hashes platform-independent

using hash_t = std::uint64_t;

template <__metaobject_id M>
constexpr auto get_hash(wrapped_metaobject<M>) -> hash_t
  requires(__metaobject_is_meta_global_scope(M)) {
    return 95ULL;
}

template <__metaobject_id M>
constexpr auto get_hash(wrapped_metaobject<M> mo) -> hash_t requires(
  !__metaobject_is_meta_object_sequence(M) &&
  !__metaobject_is_meta_global_scope(M) && !__metaobject_is_meta_callable(M) &&
  !__metaobject_is_meta_function_call_expression(M) &&
  !__metaobject_is_meta_parenthesized_expression(M)) {
    return std::hash<std::string>{}(get_full_name(mo));
}

constexpr auto _do_get_hash(unpacked_metaobject_sequence<>, hash_t s)
  -> hash_t {
    return s;
}

template <__metaobject_id M, __metaobject_id... Ms>
constexpr auto _do_get_hash(unpacked_metaobject_sequence<M, Ms...>, hash_t s)
  -> hash_t {
    return s ^
           std::hash<std::string>{}(get_full_name(wrapped_metaobject<M>{})) ^
           _do_get_hash(unpacked_metaobject_sequence<Ms...>{}, s + 1);
}

template <__metaobject_id... M>
constexpr auto get_hash(unpacked_metaobject_sequence<M...> ms) {
    return _do_get_hash(ms, 0Z);
}

template <__metaobject_id M>
constexpr auto get_hash(wrapped_metaobject<M> mo) -> hash_t
  requires(__metaobject_is_meta_object_sequence(M)) {
    return get_hash(unpack(mo));
}

template <__metaobject_id M>
constexpr auto get_hash(wrapped_metaobject<M> mo) -> hash_t
  requires(__metaobject_is_meta_callable(M)) {
    return std::hash<std::string>{}(get_full_name(mo)) ^
           get_hash(transform(get_parameters(mo), get_type(_1)));
}

template <__metaobject_id M>
constexpr auto get_hash(wrapped_metaobject<M> mo) -> hash_t
  requires(__metaobject_is_meta_function_call_expression(M)) {
    return get_hash(get_callable(mo));
}

template <__metaobject_id M>
constexpr auto get_hash(wrapped_metaobject<M> mo) -> hash_t
  requires(__metaobject_is_meta_parenthesized_expression(M)) {
    return get_hash(get_subexpression(mo));
}

} // namespace mirror

#endif


#ifndef MIRROR_INIT_LIST_HPP
#define MIRROR_INIT_LIST_HPP

#include <initializer_list>

namespace mirror {

template <typename E, __metaobject_id... M, typename F, typename A>
constexpr auto apply_to_init_list_of(
  unpacked_metaobject_sequence<M...>,
  F transform,
  A aggregate) {
    return aggregate(
      std::initializer_list<E>{transform(wrapped_metaobject<M>{})...});
}

template <__metaobject_id... M, typename F, typename A>
constexpr auto apply_to_init_list(
  unpacked_metaobject_sequence<M...>,
  F transform,
  A aggregate) {
    return aggregate(
      std::initializer_list<
        std::common_type_t<decltype(transform(wrapped_metaobject<M>{}))...>>{
        transform(wrapped_metaobject<M>{})...});
}

template <__metaobject_id M, typename F, typename A>
constexpr auto apply_to_init_list(
  wrapped_metaobject<M> mo,
  F transform,
  A aggregate) requires(__metaobject_is_meta_object_sequence(M)) {
    return apply_to_init_list(unpack(mo), transform, aggregate);
}

} // namespace mirror

#endif // MIRROR_MAKE_ARRAY_HPP


#ifndef MIRROR_MAKE_ARRAY_HPP
#define MIRROR_MAKE_ARRAY_HPP

#include <array>

namespace mirror {

template <typename E, __metaobject_id... M, typename F>
constexpr auto
make_array_of(unpacked_metaobject_sequence<M...>, F transform) noexcept
  -> std::array<E, sizeof...(M)> {
    return {{transform(wrapped_metaobject<M>{})...}};
}

template <typename E, __metaobject_id M, typename F>
auto make_array_of(wrapped_metaobject<M> mo, F transform) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return make_array_of<E>(unpack(mo), transform);
}

template <__metaobject_id... M, typename F>
constexpr auto
make_array(unpacked_metaobject_sequence<M...>, F transform) noexcept
  -> std::array<
    std::common_type_t<decltype(transform(wrapped_metaobject<M>{}))...>,
    sizeof...(M)> {
    return {{transform(wrapped_metaobject<M>{})...}};
}

template <__metaobject_id M, typename F>
auto make_array(wrapped_metaobject<M> mo, F transform) noexcept
  requires(__metaobject_is_meta_object_sequence(M)) {
    return make_array(unpack(mo), transform);
}

} // namespace mirror

#endif // MIRROR_MAKE_ARRAY_HPP


#ifndef MIRROR_MAKE_TUPLE_HPP
#define MIRROR_MAKE_TUPLE_HPP

#include <tuple>

namespace mirror {

template <__metaobject_id... M>
constexpr auto make_value_tuple(unpacked_metaobject_sequence<M...>) {
    return std::tuple<
      std::remove_cv_t<std::remove_reference_t<__unrefltype(M)>>...>{};
}

template <__metaobject_id M>
constexpr auto make_value_tuple(wrapped_metaobject<M> mo) requires(
  __metaobject_is_meta_object_sequence(M)) {
    return make_value_tuple(unpack(mo));
}
} // namespace mirror

#endif // MIRROR_MAKE_TUPLE_HPP


#ifndef MIRROR_OPERATIONS_HPP
#define MIRROR_OPERATIONS_HPP


#ifndef MIRROR_TRAITS_HPP
#define MIRROR_TRAITS_HPP


#ifndef MIRROR_BITFIELD_HPP
#define MIRROR_BITFIELD_HPP

#include <initializer_list>
#include <type_traits>

namespace mirror {

template <typename Bit>
class bitfield {
public:
    using bit_type = Bit;

    using value_type = std::make_unsigned_t<std::underlying_type_t<bit_type>>;

    constexpr bitfield() noexcept = default;

    constexpr explicit bitfield(const value_type bits) noexcept
      : _bits{bits} {}

    constexpr bitfield(const bit_type _bit) noexcept
      : _bits{value_type(_bit)} {}

    constexpr bitfield(const bit_type _bit_a, const bit_type _bit_b) noexcept
      : _bits{value_type(_bit_a) | value_type(_bit_b)} {}

    constexpr bitfield(std::initializer_list<bit_type> bits) noexcept {
        for(const auto bit : bits) {
            (*this) |= bit;
        }
    }

    constexpr auto is_empty() const noexcept {
        return _bits == value_type(0);
    }

    explicit constexpr operator bool() const noexcept {
        return _bits != value_type(0);
    }

    explicit constexpr operator value_type() const noexcept {
        return _bits;
    }

    constexpr auto bits() const noexcept -> value_type {
        return _bits;
    }

    constexpr auto has(const bit_type bit) const noexcept {
        return (_bits & value_type(bit)) == value_type(bit);
    }

    constexpr auto has_not(const bit_type bit) const noexcept {
        return (_bits & value_type(bit)) != value_type(bit);
    }

    template <typename... B>
    constexpr auto has_all(const bit_type bit, B... bits) const noexcept
      -> bool {
        return (has(bit) && ... && has(bits));
    }

    constexpr auto has_all(const bitfield that) const noexcept {
        return (_bits & that._bits) == that._bits;
    }

    template <typename... B>
    constexpr auto has_any(const bit_type bit, B... bits) const noexcept
      -> bool {
        return (has(bit) || ... || has(bits));
    }

    constexpr auto has_some(const bitfield that) const noexcept {
        return (_bits & that._bits) != value_type{0};
    }

    template <typename... B>
    constexpr auto has_none(const bit_type bit, B... bits) const noexcept
      -> bool {
        return (has_not(bit) && ... && has_not(bits));
    }

    constexpr auto has_none(const bitfield that) const noexcept {
        return (_bits & that._bits) == value_type{0};
    }

    constexpr auto has_only(const bit_type bit) const noexcept {
        return _bits == value_type(bit);
    }

    constexpr auto has_at_most(const bit_type bit) const noexcept {
        return is_empty() || has_only(bit);
    }

    friend constexpr auto
    operator==(const bitfield a, const bitfield b) noexcept {
        return a._bits == b._bits;
    }

    friend constexpr auto
    operator!=(const bitfield a, const bitfield b) noexcept {
        return a._bits != b._bits;
    }

    friend constexpr auto operator|(const bitfield a, const bitfield b) noexcept
      -> bitfield {
        return bitfield(a._bits | b._bits);
    }

    auto operator|=(const bitfield b) noexcept -> bitfield& {
        _bits |= b._bits;
        return *this;
    }

    friend constexpr auto operator&(const bitfield a, const bitfield b) noexcept
      -> bitfield {
        return bitfield(a._bits & b._bits);
    }

    auto operator&=(const bitfield b) noexcept -> bitfield& {
        _bits &= b._bits;
        return *this;
    }

    friend constexpr auto operator~(const bitfield b) noexcept -> bitfield {
        return bitfield{value_type(~b._bits)};
    }

    auto clear(const bit_type b) noexcept -> bitfield& {
        _bits &= ~value_type(b); // NOLINT(hicpp-signed-bitwise)
        return *this;
    }

    auto clear() noexcept -> bitfield& {
        _bits = value_type(0);
        return *this;
    }

private:
    value_type _bits{0U};
};

} // namespace mirror

#endif // MIRROR_BITFIELD_HPP

#ifndef MIRROR_PREPROCESSOR_HPP
#define MIRROR_PREPROCESSOR_HPP

#define MIRROR_STRINGIFY(EXPR) MIRROR_DO_STRINGIFY(EXPR)
#define MIRROR_DO_STRINGIFY(EXPR) #EXPR

#define MIRROR_JOIN(L, R) MIRROR_DO_JOIN(L, R)
#define MIRROR_DO_JOIN(L, R) MIRROR_DO_JOIN2(L, R)
#define MIRROR_DO_JOIN2(L, R) L##R

#if defined(__clang__) || defined(__GNUC__)

#define MIRROR_PRAGMA(x) _Pragma(MIRROR_STRINGIFY(x))

#elif defined(_MSC_VER)

#define MIRROR_PRAGMA(x) __pragma(x)

#endif

#endif // MIRROR_PREPROCESSOR_HPP

#ifndef MIRROR_TRIBOOL_HPP
#define MIRROR_TRIBOOL_HPP

#include <optional>

namespace mirror {

enum class _tribool_value_t : unsigned char {
    _false = 0x00,
    _true = 0x01,
    _unknown = 0x02
};

struct indeterminate_t {};

static constexpr const indeterminate_t indeterminate{};

class tribool;

class weakbool {
    using _value_t = _tribool_value_t;

public:
    constexpr explicit operator bool() const noexcept {
        return _value != _value_t::_false;
    }

    constexpr auto operator!() const noexcept {
        return _value != _value_t::_true;
    }

    constexpr auto is(const indeterminate_t) const noexcept -> bool {
        return _value == _value_t::_unknown;
    }

private:
    _value_t _value;

    friend class tribool;

    constexpr explicit weakbool(const _value_t value) noexcept
      : _value{value} {}
};

class tribool {
    using _value_t = _tribool_value_t;

public:
    constexpr tribool() noexcept = default;

    constexpr tribool(const bool value) noexcept
      : _value{value ? _value_t::_true : _value_t::_false} {}

    constexpr tribool(const indeterminate_t) noexcept
      : _value{_value_t::_unknown} {}

    constexpr tribool(const std::optional<bool> value) noexcept
      : _value(
          !value.has_value() ? _value_t::_unknown
          : value.value()    ? _value_t::_true
                             : _value_t::_false) {}

    constexpr tribool(const bool value, const bool is_unknown) noexcept
      : _value(
          is_unknown ? _value_t::_unknown
          : value    ? _value_t::_true
                     : _value_t::_false) {}

    constexpr explicit operator bool() const noexcept {
        return _value == _value_t::_true;
    }

    constexpr auto operator!() const noexcept {
        return _value == _value_t::_false;
    }

    constexpr operator std::optional<bool>() const noexcept {
        using R = std::optional<bool>;
        return _value == _value_t::_true    ? R{true}
               : _value == _value_t::_false ? R{false}
                                            : R{};
    }

    constexpr auto operator*() const noexcept -> bool {
        return _value == _value_t::_unknown;
    }

    constexpr auto operator~() const noexcept -> weakbool {
        return weakbool{_value};
    }

    constexpr auto is(const bool value) const noexcept -> bool {
        return _value == (value ? _value_t::_true : _value_t::_false);
    }

    constexpr auto is(const indeterminate_t) const noexcept -> bool {
        return *(*this);
    }

    friend constexpr auto operator==(const tribool a, const tribool b) noexcept
      -> tribool {
        return {a._value == b._value, (*a || *b)};
    }

    friend constexpr auto operator!=(const tribool a, const tribool b) noexcept
      -> tribool {
        return {a._value != b._value, (*a || *b)};
    }

private:
    _value_t _value{_value_t::_false};
};

static constexpr auto has_value(tribool v) noexcept {
    return !v.is(indeterminate);
}

static constexpr auto extract(tribool v) noexcept -> bool {
    return bool(v);
}

constexpr auto operator&&(const tribool a, const tribool b) noexcept {
    return !a   ? tribool{false}
           : a  ? b
           : !b ? tribool{false}
                : tribool{indeterminate};
}

constexpr auto operator||(const tribool a, const tribool b) noexcept {
    return a    ? tribool{true}
           : !a ? b
           : b  ? tribool{true}
                : tribool{indeterminate};
}

} // namespace mirror

#endif // MIRROR_TRIBOOL_HPP
#include <cstdint>
#include <type_traits>

namespace mirror {

template <auto O>
struct map_operation;

enum class meta_trait : std::uint64_t {
    reflects_object = 1ULL << 0ULL,
    reflects_object_sequence = 1ULL << 1ULL,
    reflects_named = 1ULL << 2ULL,
    reflects_alias = 1ULL << 3ULL,
    reflects_typed = 1ULL << 4ULL,
    reflects_scope = 1ULL << 5ULL,
    reflects_scope_member = 1ULL << 6ULL,
    reflects_enumerator = 1ULL << 7ULL,
    reflects_record_member = 1ULL << 8ULL,
    reflects_base = 1ULL << 9ULL,
    reflects_namespace = 1ULL << 10ULL,
    reflects_global_scope = 1ULL << 11ULL,
    reflects_type = 1ULL << 12ULL,
    reflects_enum = 1ULL << 13ULL,
    reflects_record = 1ULL << 14ULL,
    reflects_class = 1ULL << 15ULL,
    reflects_lambda = 1ULL << 16ULL,
    reflects_constant = 1ULL << 17ULL,
    reflects_variable = 1ULL << 18ULL,
    reflects_lambda_capture = 1ULL << 19ULL,
    reflects_function_parameter = 1ULL << 20ULL,
    reflects_callable = 1ULL << 21ULL,
    reflects_function = 1ULL << 22ULL,
    reflects_member_function = 1ULL << 23ULL,
    reflects_special_member_function = 1ULL << 24ULL,
    reflects_constructor = 1ULL << 25ULL,
    reflects_destructor = 1ULL << 26ULL,
    reflects_operator = 1ULL << 27ULL,
    reflects_conversion_operator = 1ULL << 28ULL,
    reflects_expression = 1ULL << 29ULL,
    reflects_parenthesized_expression = 1ULL << 30ULL,
    reflects_function_call_expression = 1ULL << 31ULL,
    reflects_specifier = 1ULL << 32ULL
};

using meta_traits = bitfield<meta_trait>;

static constexpr auto operator|(meta_trait l, meta_trait r) noexcept
  -> meta_traits {
    return {l, r};
}
enum class type_trait : std::uint64_t {
    is_const = 1ULL << 0ULL,
    is_volatile = 1ULL << 1ULL,
    is_pointer = 1ULL << 2ULL,
    is_reference = 1ULL << 3ULL,
    is_fundamental = 1ULL << 4ULL,
    is_void = 1ULL << 5ULL
};

using type_traits = bitfield<type_trait>;

static constexpr auto operator|(type_trait l, type_trait r) noexcept
  -> type_traits {
    return {l, r};
}
enum class object_trait : std::uint64_t {
    is_call_operator_const = 1ULL << 0ULL,
    is_const = 1ULL << 1ULL,
    is_constexpr = 1ULL << 2ULL,
    is_copy_constructor = 1ULL << 3ULL,
    is_copy_assignment_operator = 1ULL << 4ULL,
    is_defaulted = 1ULL << 5ULL,
    is_deleted = 1ULL << 6ULL,
    is_empty = 1ULL << 7ULL,
    is_enum = 1ULL << 8ULL,
    is_explicit = 1ULL << 9ULL,
    is_explicitly_captured = 1ULL << 10ULL,
    is_final = 1ULL << 11ULL,
    is_implicitly_declared = 1ULL << 12ULL,
    is_inline = 1ULL << 13ULL,
    is_move_constructor = 1ULL << 14ULL,
    is_move_assignment_operator = 1ULL << 15ULL,
    is_noexcept = 1ULL << 16ULL,
    is_private = 1ULL << 17ULL,
    is_protected = 1ULL << 18ULL,
    is_public = 1ULL << 19ULL,
    is_pure_virtual = 1ULL << 20ULL,
    is_scoped_enum = 1ULL << 21ULL,
    is_static = 1ULL << 22ULL,
    is_thread_local = 1ULL << 23ULL,
    is_union = 1ULL << 24ULL,
    is_unnamed = 1ULL << 25ULL,
    is_virtual = 1ULL << 26ULL,
    is_volatile = 1ULL << 27ULL,
    has_default_argument = 1ULL << 28ULL,
    has_lvalueref_qualifier = 1ULL << 29ULL,
    has_rvalueref_qualifier = 1ULL << 30ULL,
    uses_class_key = 1ULL << 31ULL,
    uses_struct_key = 1ULL << 32ULL,
    uses_default_copy_capture = 1ULL << 33ULL,
    uses_default_reference_capture = 1ULL << 34ULL
};

using object_traits = bitfield<object_trait>;

static constexpr auto operator|(object_trait l, object_trait r) noexcept
  -> object_traits {
    return {l, r};
}
template <meta_trait>
struct map_meta_trait;

#define MIRROR_IMPLEMENT_MAP_TRAIT(NAME)                              \
    template <>                                                       \
    struct map_meta_trait<meta_trait::MIRROR_JOIN(reflects_, NAME)> { \
        static consteval auto apply(__metaobject_id mi) {             \
            return MIRROR_JOIN(__metaobject_is_meta_, NAME)(mi);      \
        }                                                             \
    };

MIRROR_IMPLEMENT_MAP_TRAIT(object)
MIRROR_IMPLEMENT_MAP_TRAIT(object_sequence)
MIRROR_IMPLEMENT_MAP_TRAIT(named)
MIRROR_IMPLEMENT_MAP_TRAIT(alias)
MIRROR_IMPLEMENT_MAP_TRAIT(typed)
MIRROR_IMPLEMENT_MAP_TRAIT(scope)
MIRROR_IMPLEMENT_MAP_TRAIT(scope_member)
MIRROR_IMPLEMENT_MAP_TRAIT(enumerator)
MIRROR_IMPLEMENT_MAP_TRAIT(record_member)
MIRROR_IMPLEMENT_MAP_TRAIT(base)
MIRROR_IMPLEMENT_MAP_TRAIT(namespace)
MIRROR_IMPLEMENT_MAP_TRAIT(global_scope)
MIRROR_IMPLEMENT_MAP_TRAIT(type)
MIRROR_IMPLEMENT_MAP_TRAIT(enum)
MIRROR_IMPLEMENT_MAP_TRAIT(record)
MIRROR_IMPLEMENT_MAP_TRAIT(class)
MIRROR_IMPLEMENT_MAP_TRAIT(lambda)
MIRROR_IMPLEMENT_MAP_TRAIT(constant)
MIRROR_IMPLEMENT_MAP_TRAIT(variable)
MIRROR_IMPLEMENT_MAP_TRAIT(lambda_capture)
MIRROR_IMPLEMENT_MAP_TRAIT(function_parameter)
MIRROR_IMPLEMENT_MAP_TRAIT(callable)
MIRROR_IMPLEMENT_MAP_TRAIT(function)
MIRROR_IMPLEMENT_MAP_TRAIT(member_function)
MIRROR_IMPLEMENT_MAP_TRAIT(special_member_function)
MIRROR_IMPLEMENT_MAP_TRAIT(constructor)
MIRROR_IMPLEMENT_MAP_TRAIT(destructor)
MIRROR_IMPLEMENT_MAP_TRAIT(operator)
MIRROR_IMPLEMENT_MAP_TRAIT(conversion_operator)
MIRROR_IMPLEMENT_MAP_TRAIT(expression)
MIRROR_IMPLEMENT_MAP_TRAIT(parenthesized_expression)
MIRROR_IMPLEMENT_MAP_TRAIT(function_call_expression)
MIRROR_IMPLEMENT_MAP_TRAIT(specifier)

#undef MIRROR_IMPLEMENT_MAP_TRAIT
template <type_trait>
struct map_type_trait;

#define MIRROR_IMPLEMENT_MAP_TRAIT(NAME)          \
    template <>                                   \
    struct map_type_trait<type_trait::NAME> {     \
        template <typename T>                     \
        static consteval auto apply() -> bool {   \
            return std::MIRROR_JOIN(NAME, _v)<T>; \
        }                                         \
    };

MIRROR_IMPLEMENT_MAP_TRAIT(is_const)
MIRROR_IMPLEMENT_MAP_TRAIT(is_volatile)
MIRROR_IMPLEMENT_MAP_TRAIT(is_pointer)
MIRROR_IMPLEMENT_MAP_TRAIT(is_reference)
MIRROR_IMPLEMENT_MAP_TRAIT(is_fundamental)
MIRROR_IMPLEMENT_MAP_TRAIT(is_void)

#undef MIRROR_IMPLEMENT_MAP_TRAIT
template <object_trait O>
struct map_object_trait : map_operation<O> {};

#define MIRROR_IMPLEMENT_MAP_TRAIT(NAME)                                  \
    template <>                                                           \
    struct map_operation<object_trait::NAME> {                            \
        static consteval auto is_applicable(__metaobject_id mo) -> bool { \
            return MIRROR_JOIN(__metaobject_, NAME)(bool, mo);            \
        }                                                                 \
        static consteval auto apply(__metaobject_id mo) -> bool {         \
            return MIRROR_JOIN(__metaobject_, NAME)(mo);                  \
        }                                                                 \
        static constexpr auto make_optional(bool v) -> tribool {          \
            return {v};                                                   \
        }                                                                 \
        static constexpr auto fallback() -> tribool {                     \
            return indeterminate;                                         \
        }                                                                 \
    };

MIRROR_IMPLEMENT_MAP_TRAIT(is_call_operator_const)
MIRROR_IMPLEMENT_MAP_TRAIT(is_const)
MIRROR_IMPLEMENT_MAP_TRAIT(is_constexpr)
MIRROR_IMPLEMENT_MAP_TRAIT(is_copy_constructor)
MIRROR_IMPLEMENT_MAP_TRAIT(is_copy_assignment_operator)
MIRROR_IMPLEMENT_MAP_TRAIT(is_defaulted)
MIRROR_IMPLEMENT_MAP_TRAIT(is_deleted)
MIRROR_IMPLEMENT_MAP_TRAIT(is_empty)
MIRROR_IMPLEMENT_MAP_TRAIT(is_enum)
MIRROR_IMPLEMENT_MAP_TRAIT(is_explicit)
MIRROR_IMPLEMENT_MAP_TRAIT(is_explicitly_captured)
MIRROR_IMPLEMENT_MAP_TRAIT(is_final)
MIRROR_IMPLEMENT_MAP_TRAIT(is_implicitly_declared)
MIRROR_IMPLEMENT_MAP_TRAIT(is_inline)
MIRROR_IMPLEMENT_MAP_TRAIT(is_move_constructor)
MIRROR_IMPLEMENT_MAP_TRAIT(is_move_assignment_operator)
MIRROR_IMPLEMENT_MAP_TRAIT(is_noexcept)
MIRROR_IMPLEMENT_MAP_TRAIT(is_private)
MIRROR_IMPLEMENT_MAP_TRAIT(is_protected)
MIRROR_IMPLEMENT_MAP_TRAIT(is_public)
MIRROR_IMPLEMENT_MAP_TRAIT(is_pure_virtual)
MIRROR_IMPLEMENT_MAP_TRAIT(is_scoped_enum)
MIRROR_IMPLEMENT_MAP_TRAIT(is_static)
MIRROR_IMPLEMENT_MAP_TRAIT(is_thread_local)
MIRROR_IMPLEMENT_MAP_TRAIT(is_union)
MIRROR_IMPLEMENT_MAP_TRAIT(is_unnamed)
MIRROR_IMPLEMENT_MAP_TRAIT(is_virtual)
MIRROR_IMPLEMENT_MAP_TRAIT(is_volatile)
MIRROR_IMPLEMENT_MAP_TRAIT(has_default_argument)
MIRROR_IMPLEMENT_MAP_TRAIT(has_lvalueref_qualifier)
MIRROR_IMPLEMENT_MAP_TRAIT(has_rvalueref_qualifier)
MIRROR_IMPLEMENT_MAP_TRAIT(uses_class_key)
MIRROR_IMPLEMENT_MAP_TRAIT(uses_struct_key)
MIRROR_IMPLEMENT_MAP_TRAIT(uses_default_copy_capture)
MIRROR_IMPLEMENT_MAP_TRAIT(uses_default_reference_capture)

#undef MIRROR_IMPLEMENT_MAP_TRAIT
struct trait {
    // meta
    using meta_trait::reflects_alias;
    using meta_trait::reflects_base;
    using meta_trait::reflects_callable;
    using meta_trait::reflects_class;
    using meta_trait::reflects_constant;
    using meta_trait::reflects_constructor;
    using meta_trait::reflects_conversion_operator;
    using meta_trait::reflects_destructor;
    using meta_trait::reflects_enum;
    using meta_trait::reflects_enumerator;
    using meta_trait::reflects_expression;
    using meta_trait::reflects_function;
    using meta_trait::reflects_function_call_expression;
    using meta_trait::reflects_function_parameter;
    using meta_trait::reflects_global_scope;
    using meta_trait::reflects_lambda;
    using meta_trait::reflects_lambda_capture;
    using meta_trait::reflects_member_function;
    using meta_trait::reflects_named;
    using meta_trait::reflects_namespace;
    using meta_trait::reflects_object;
    using meta_trait::reflects_object_sequence;
    using meta_trait::reflects_operator;
    using meta_trait::reflects_parenthesized_expression;
    using meta_trait::reflects_record;
    using meta_trait::reflects_record_member;
    using meta_trait::reflects_scope;
    using meta_trait::reflects_scope_member;
    using meta_trait::reflects_special_member_function;
    using meta_trait::reflects_specifier;
    using meta_trait::reflects_type;
    using meta_trait::reflects_typed;
    using meta_trait::reflects_variable;
    // type
    using type_trait::is_fundamental;
    using type_trait::is_pointer;
    using type_trait::is_reference;
    using type_trait::is_void;
    // object
    using object_trait::has_default_argument;
    using object_trait::has_lvalueref_qualifier;
    using object_trait::has_rvalueref_qualifier;
    using object_trait::is_call_operator_const;
    using object_trait::is_constexpr;
    using object_trait::is_copy_assignment_operator;
    using object_trait::is_copy_constructor;
    using object_trait::is_defaulted;
    using object_trait::is_deleted;
    using object_trait::is_empty;
    using object_trait::is_enum;
    using object_trait::is_explicit;
    using object_trait::is_explicitly_captured;
    using object_trait::is_final;
    using object_trait::is_implicitly_declared;
    using object_trait::is_inline;
    using object_trait::is_move_assignment_operator;
    using object_trait::is_move_constructor;
    using object_trait::is_noexcept;
    using object_trait::is_private;
    using object_trait::is_protected;
    using object_trait::is_public;
    using object_trait::is_pure_virtual;
    using object_trait::is_scoped_enum;
    using object_trait::is_static;
    using object_trait::is_thread_local;
    using object_trait::is_union;
    using object_trait::is_unnamed;
    using object_trait::is_virtual;
    using object_trait::uses_class_key;
    using object_trait::uses_default_copy_capture;
    using object_trait::uses_default_reference_capture;
    using object_trait::uses_struct_key;
};

template <meta_trait T>
consteval auto has_trait(__metaobject_id mo) noexcept -> bool {
    return map_meta_trait<T>::apply(mo);
}

template <__metaobject_id M>
constexpr auto get_traits(wrapped_metaobject<M> mo) noexcept -> meta_traits {
    meta_traits result{};
    for_each(get_enumerators(mirror(meta_trait)), [&](auto me) {
        if(has_trait<get_constant(me)>(mo)) {
            result |= get_constant(me);
        }
    });
    return result;
}

template <type_trait TT, typename T>
constexpr auto has_trait(std::type_identity<T>) noexcept -> bool {
    return map_type_trait<TT>::template apply<T>();
}

template <typename T>
constexpr auto get_traits(std::type_identity<T> tid) noexcept -> type_traits {
    type_traits result{};
    for_each(get_enumerators(mirror(type_trait)), [&](auto me) {
        if(has_trait<get_constant(me)>(tid)) {
            result |= get_constant(me);
        }
    });
    return result;
}

template <__metaobject_id M>
constexpr auto get_type_traits(wrapped_metaobject<M> mo) noexcept
  -> type_traits {
    if constexpr(reflects_type(mo)) {
        return get_traits(get_reflected_type(mo));
    } else {
        return {};
    }
}

} // namespace mirror

#endif
#include <concepts>
#include <optional>

namespace mirror {

using operation_boolean = object_trait;

using operations_boolean = bitfield<operation_boolean>;

enum class operation_integer : unsigned {
    get_constant = 1U << 0U,
    get_size = 1U << 1U,
    get_source_column = 1U << 2U,
    get_source_line = 1U << 3U
};

using operations_integer = bitfield<operation_integer>;

static constexpr auto
operator|(operation_integer l, operation_integer r) noexcept
  -> operations_integer {
    return {l, r};
}

enum class operation_pointer : unsigned {
    get_pointer = 1U << 0U
};

using operations_pointer = bitfield<operation_pointer>;

static constexpr auto
operator|(operation_pointer l, operation_pointer r) noexcept
  -> operations_pointer {
    return {l, r};
}

enum class operation_string : unsigned {
    // string
    get_debug_info = 1U << 0U,
    get_display_name = 1U << 1U,
    get_name = 1U << 2U,
    get_source_file_name = 1U << 3U
};

using operations_string = bitfield<operation_string>;

static constexpr auto operator|(operation_string l, operation_string r) noexcept
  -> operations_string {
    return {l, r};
}

enum class operation_metaobject : std::uint64_t {
    get_aliased = 1ULL << 0ULL,
    get_base_classes = 1ULL << 1ULL,
    get_callable = 1ULL << 2ULL,
    get_captures = 1ULL << 3ULL,
    get_data_members = 1ULL << 4ULL,
    get_class = 1ULL << 5ULL,
    get_constructors = 1ULL << 6ULL,
    get_destructors = 1ULL << 7ULL,
    get_member_functions = 1ULL << 8ULL,
    get_member_types = 1ULL << 9ULL,
    get_operators = 1ULL << 10ULL,
    get_parameters = 1ULL << 11ULL,
    get_enumerators = 1ULL << 12ULL,
    get_scope = 1ULL << 13ULL,
    get_subexpression = 1ULL << 14ULL,
    get_type = 1ULL << 15ULL,
    get_underlying_type = 1ULL << 16ULL,
    hide_private = 1ULL << 17ULL,
    hide_protected = 1ULL << 18ULL
};

using operations_metaobject = bitfield<operation_metaobject>;

static constexpr auto
operator|(operation_metaobject l, operation_metaobject r) noexcept
  -> operations_metaobject {
    return {l, r};
}

template <typename T>
concept metaobject_operation =
  (std::same_as<T, operation_boolean> || std::same_as<T, operation_integer> ||
   std::same_as<T, operation_pointer> || std::same_as<T, operation_string> ||
   std::same_as<T, operation_metaobject>);

template <auto O>
struct map_operation;
template <>
struct map_operation<operation_integer::get_constant> {
    template <__metaobject_id M>
    static consteval auto is_applicable(wrapped_metaobject<M>) -> bool {
        return __metaobject_get_constant(bool, M);
    }
    template <__metaobject_id M>
    static consteval auto apply(wrapped_metaobject<M>) {
        return _get_constant<M>::value;
    }
    template <typename T>
    static constexpr auto make_optional(T v) -> std::optional<T> {
        return {std::move(v)};
    }
    static constexpr auto fallback() -> std::optional<std::uintmax_t> {
        return {};
    }
};

#define MIRROR_IMPLEMENT_MAP_UNARY_OP(NAME)                               \
    template <>                                                           \
    struct map_operation<operation_integer::NAME> {                       \
        static consteval auto is_applicable(__metaobject_id mo) -> bool { \
            return MIRROR_JOIN(__metaobject_, NAME)(bool, mo);            \
        }                                                                 \
        static consteval auto apply(__metaobject_id mo) -> size_t {       \
            return MIRROR_JOIN(__metaobject_, NAME)(mo);                  \
        }                                                                 \
        static constexpr auto make_optional(size_t v)                     \
          -> std::optional<size_t> {                                      \
            return {v};                                                   \
        }                                                                 \
        static constexpr auto fallback() -> std::optional<size_t> {       \
            return {};                                                    \
        }                                                                 \
    };

MIRROR_IMPLEMENT_MAP_UNARY_OP(get_size)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_source_column)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_source_line)

#undef MIRROR_IMPLEMENT_MAP_UNARY_OP

template <>
struct map_operation<operation_pointer::get_pointer> {
    template <__metaobject_id M>
    static consteval auto is_applicable(wrapped_metaobject<M>) -> bool {
        return __metaobject_get_pointer(bool, M);
    }
    template <__metaobject_id M>
    static consteval auto apply(wrapped_metaobject<M>) {
        return _get_pointer<M>::value;
    }
    template <typename T>
    static constexpr auto make_optional(T v) -> std::optional<T> {
        return {std::move(v)};
    }
    static consteval auto fallback() {
        return nullptr;
    }
};
#define MIRROR_IMPLEMENT_MAP_UNARY_OP(NAME)                                   \
    template <>                                                               \
    struct map_operation<operation_string::NAME> {                            \
        static consteval auto is_applicable(__metaobject_id mo) -> bool {     \
            return MIRROR_JOIN(__metaobject_, NAME)(bool, mo);                \
        }                                                                     \
        static consteval auto apply(__metaobject_id mo) -> std::string_view { \
            return NAME(mo);                                                  \
        }                                                                     \
        static constexpr auto make_optional(std::string_view v)               \
          -> std::optional<std::string_view> {                                \
            return {v};                                                       \
        }                                                                     \
        static constexpr auto fallback() -> std::optional<std::string_view> { \
            return {};                                                        \
        }                                                                     \
    };

MIRROR_IMPLEMENT_MAP_UNARY_OP(get_debug_info)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_display_name)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_name)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_source_file_name)

#undef MIRROR_IMPLEMENT_MAP_UNARY_OP
#define MIRROR_IMPLEMENT_MAP_UNARY_OP(NAME)                                   \
    template <>                                                               \
    struct map_operation<operation_metaobject::NAME> {                        \
        template <__metaobject_id M>                                          \
        static consteval auto is_applicable(wrapped_metaobject<M>) -> bool {  \
            return MIRROR_JOIN(__metaobject_, NAME)(bool, M);                 \
        }                                                                     \
        template <__metaobject_id M>                                          \
        static consteval auto apply(wrapped_metaobject<M>) {                  \
            return wrapped_metaobject<MIRROR_JOIN(__metaobject_, NAME)(M)>{}; \
        }                                                                     \
        template <__metaobject_id M>                                          \
        static constexpr auto make_optional(wrapped_metaobject<M> mo) {       \
            return mo;                                                        \
        }                                                                     \
        static constexpr auto fallback() {                                    \
            return no_metaobject;                                             \
        }                                                                     \
    };

MIRROR_IMPLEMENT_MAP_UNARY_OP(get_aliased)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_base_classes)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_callable)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_captures)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_data_members)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_class)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_constructors)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_destructors)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_member_functions)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_member_types)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_operators)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_parameters)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_enumerators)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_scope)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_subexpression)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_type)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_underlying_type)
MIRROR_IMPLEMENT_MAP_UNARY_OP(hide_private)
MIRROR_IMPLEMENT_MAP_UNARY_OP(hide_protected)

#undef MIRROR_IMPLEMENT_MAP_UNARY_OP
struct operation {
    // boolean
    using operation_boolean::has_default_argument;
    using operation_boolean::has_lvalueref_qualifier;
    using operation_boolean::has_rvalueref_qualifier;
    using operation_boolean::is_call_operator_const;
    using operation_boolean::is_const;
    using operation_boolean::is_constexpr;
    using operation_boolean::is_copy_assignment_operator;
    using operation_boolean::is_copy_constructor;
    using operation_boolean::is_defaulted;
    using operation_boolean::is_deleted;
    using operation_boolean::is_empty;
    using operation_boolean::is_enum;
    using operation_boolean::is_explicit;
    using operation_boolean::is_explicitly_captured;
    using operation_boolean::is_final;
    using operation_boolean::is_implicitly_declared;
    using operation_boolean::is_inline;
    using operation_boolean::is_move_assignment_operator;
    using operation_boolean::is_move_constructor;
    using operation_boolean::is_noexcept;
    using operation_boolean::is_private;
    using operation_boolean::is_protected;
    using operation_boolean::is_public;
    using operation_boolean::is_pure_virtual;
    using operation_boolean::is_scoped_enum;
    using operation_boolean::is_static;
    using operation_boolean::is_thread_local;
    using operation_boolean::is_union;
    using operation_boolean::is_unnamed;
    using operation_boolean::is_virtual;
    using operation_boolean::is_volatile;
    using operation_boolean::uses_class_key;
    using operation_boolean::uses_default_copy_capture;
    using operation_boolean::uses_default_reference_capture;
    using operation_boolean::uses_struct_key;
    // integer
    using operation_integer::get_constant;
    using operation_integer::get_size;
    using operation_integer::get_source_column;
    using operation_integer::get_source_line;
    // pointer
    using operation_pointer::get_pointer;
    // string
    using operation_string::get_display_name;
    using operation_string::get_name;
    using operation_string::get_source_file_name;
    // metaobject
    using operation_metaobject::get_aliased;
    using operation_metaobject::get_base_classes;
    using operation_metaobject::get_callable;
    using operation_metaobject::get_captures;
    using operation_metaobject::get_class;
    using operation_metaobject::get_constructors;
    using operation_metaobject::get_data_members;
    using operation_metaobject::get_destructors;
    using operation_metaobject::get_enumerators;
    using operation_metaobject::get_member_functions;
    using operation_metaobject::get_member_types;
    using operation_metaobject::get_operators;
    using operation_metaobject::get_parameters;
    using operation_metaobject::get_scope;
    using operation_metaobject::get_subexpression;
    using operation_metaobject::get_type;
    using operation_metaobject::get_underlying_type;
    using operation_metaobject::hide_private;
    using operation_metaobject::hide_protected;
};
template <metaobject_operation auto O, __metaobject_id M>
constexpr auto is_applicable(wrapped_metaobject<M> mo) noexcept -> bool {
    return map_operation<O>::is_applicable(mo);
}

template <__metaobject_id Me, __metaobject_id Mo>
constexpr auto
is_applicable(wrapped_metaobject<Me> me, wrapped_metaobject<Mo> mo) noexcept
  -> bool {
    return is_applicable<get_constant(me)>(mo);
}

template <metaobject_operation auto O, __metaobject_id M>
constexpr auto apply(wrapped_metaobject<M> mo) noexcept
  requires(is_applicable(mo)) {
    return map_operation<O>::apply(mo);
}

template <metaobject_operation auto O, __metaobject_id M>
constexpr auto try_apply(wrapped_metaobject<M> mo) noexcept {
    using op = map_operation<O>;
    if constexpr(op::is_applicable(mo)) {
        return op::make_optional(op::apply(mo));
    } else {
        return op::fallback();
    }
}

template <__metaobject_id Me, __metaobject_id Mo>
constexpr auto
try_apply(wrapped_metaobject<Me> me, wrapped_metaobject<Mo> mo) noexcept {
    return try_apply<get_constant(me)>(mo);
}

constexpr auto all_metaobject_operation_kinds() noexcept {
    return make_sequence(
      remove_all_aliases(mirror(mirror::operation_boolean)),
      remove_all_aliases(mirror(mirror::operation_integer)),
      remove_all_aliases(mirror(mirror::operation_pointer)),
      remove_all_aliases(mirror(mirror::operation_string)),
      remove_all_aliases(mirror(mirror::operation_metaobject)));
}

constexpr auto all_metaobject_operations() noexcept {
    return flatten(
      transform(all_metaobject_operation_kinds(), get_enumerators(_1)));
}

template <typename F>
constexpr void for_each_metaobject_operation(F function) {
    for_each(all_metaobject_operation_kinds(), [&](auto muo) {
        for_each(get_enumerators(muo), function);
    });
}

} // namespace mirror

#endif
#ifndef MIRROR_PROGRAM_ARGS_HPP
#define MIRROR_PROGRAM_ARGS_HPP


#ifndef MIRROR_FROM_STRING_HPP
#define MIRROR_FROM_STRING_HPP


#ifndef MIRROR_EXTRACT_HPP
#define MIRROR_EXTRACT_HPP

#include <concepts>
#include <memory>
#include <optional>
#include <string_view>
#include <system_error>
#include <type_traits>
#include <variant>

namespace mirror {


template <typename T>
struct extracted_traits;

template <typename T>
using extracted_type_t = std::remove_cv_t<typename extracted_traits<
  std::remove_cv_t<std::remove_reference_t<T>>>::value_type>;

template <typename E, typename V>
static constexpr const auto has_value_type_v =
  std::is_convertible_v<extracted_type_t<E>, V>;

// nullptr
template <>
struct extracted_traits<nullptr_t> {
    using value_type = void;
};

constexpr auto has_value(const nullptr_t) noexcept -> bool {
    return false;
}

constexpr auto extract(const nullptr_t) noexcept -> int {
    return 0;
}

// c-str
template <>
struct extracted_traits<char*> {
    using value_type = std::string_view;
};

static constexpr auto has_value(const char* p) noexcept -> bool {
    return p != nullptr;
}

static constexpr auto extract(const char* s) noexcept -> std::string_view {
    return {s};
}

// pointer
template <typename T>
struct extracted_traits<T*> {
    using value_type = T;
};

template <typename T>
constexpr auto has_value(const T* p) noexcept -> bool {
    return p != nullptr;
}

template <typename T>
constexpr auto extract(const T* p) noexcept -> const T& {
    return *p;
}

// unique_ptr
template <typename T, typename D>
struct extracted_traits<std::unique_ptr<T, D>> {
    using value_type = T;
};

template <typename T, typename D>
constexpr auto has_value(const std::unique_ptr<T, D>& p) noexcept -> bool {
    return p != nullptr;
}

template <typename T, typename D>
constexpr auto extract(const std::unique_ptr<T, D>& p) noexcept -> const T& {
    return *p;
}

// shared_ptr
template <typename T>
struct extracted_traits<std::shared_ptr<T>> {
    using value_type = T;
};

template <typename T>
constexpr auto has_value(const std::shared_ptr<T>& p) noexcept -> bool {
    return p != nullptr;
}

template <typename T, typename D>
constexpr auto extract(const std::shared_ptr<T>& p) noexcept -> const T& {
    return *p;
}

// optional
template <typename T>
struct extracted_traits<std::optional<T>> {
    using value_type = T;
};

template <typename T>
constexpr auto has_value(const std::optional<T>& o) noexcept -> bool {
    return o.has_value();
}

template <typename T>
constexpr auto extract(const std::optional<T>& o) noexcept -> const T& {
    return *o;
}

// variant (expected)
template <typename T, typename E>
struct extracted_traits<std::variant<T, E>> {
    using value_type = T;
};

template <typename T, typename E>
constexpr auto has_value(const std::variant<T, E>& v) noexcept -> bool {
    return std::holds_alternative<T>(v);
}

template <typename T, typename E>
constexpr auto extract(const std::variant<T, E>& v) noexcept -> const T& {
    return std::get<T>(v);
}

template <typename T, typename E>
constexpr auto extract(std::variant<T, E>& v) noexcept -> T& {
    return std::get<T>(v);
}

template <typename T, typename E>
constexpr auto get_error(const std::variant<T, E>& v) noexcept -> const E& {
    return std::get<E>(v);
}

// clang-format off
template <typename T>
concept extractable = requires(T v) {
    { has_value(v) } -> std::convertible_to<bool>;
	{ std::declval<mirror::extracted_type_t<T>>() };
	extract(v);
};
// clang-format on

template <typename V>
consteval auto has_value_type(const extractable auto& v) noexcept -> bool {
    return has_value_type_v<decltype(v), V>;
}

} // namespace mirror

#endif
#ifndef MIRROR_IS_WITHIN_LIMITS_HPP
#define MIRROR_IS_WITHIN_LIMITS_HPP


#ifndef MIRROR_DIAGNOSTIC_HPP
#define MIRROR_DIAGNOSTIC_HPP


#if defined(__clang__)
#define MIRROR_DIAG_PRAGMA(EXPR) MIRROR_PRAGMA(clang diagnostic EXPR)
#elif defined(__GNUC__)
#define MIRROR_DIAG_PRAGMA(EXPR) MIRROR_PRAGMA(GCC diagnostic EXPR)
#endif

#if defined(__clang__) || defined(__GNUC__)

#define MIRROR_DIAG_OFF(EXPR) \
    MIRROR_DIAG_PRAGMA(ignored MIRROR_STRINGIFY(MIRROR_JOIN(-W, EXPR)))

#define MIRROR_DIAG_PUSH() MIRROR_DIAG_PRAGMA(push)
#define MIRROR_DIAG_POP() MIRROR_DIAG_PRAGMA(pop)

#endif

#endif // MIRROR_DIAGNOSTIC_HPP
#include <cstdint>
#include <limits>
#include <optional>
#include <type_traits>
#include <utility>

MIRROR_DIAG_PUSH()
#if defined(__clang__)
MIRROR_DIAG_OFF(shorten-64-to-32)
#elif defined(__GNUC__)
MIRROR_DIAG_OFF(sign-compare)
#endif

namespace mirror {
template <typename Dst, typename Src>
struct implicitly_within_limits
  : std::integral_constant<
      bool,
      (((std::is_integral_v<Dst> && std::is_integral_v<Src>) ||
        (std::is_floating_point_v<Dst> && std::is_floating_point_v<Src>)) &&
       (std::is_signed_v<Dst> ==
        std::is_signed_v<Src>)&&(sizeof(Dst) >= sizeof(Src)))> {};

template <typename Dst>
struct implicitly_within_limits<Dst, bool> : std::is_integral<Dst> {};

template <>
struct implicitly_within_limits<float, std::int16_t> : std::true_type {};

template <>
struct implicitly_within_limits<float, std::int32_t> : std::true_type {};

template <>
struct implicitly_within_limits<double, std::int16_t> : std::true_type {};

template <>
struct implicitly_within_limits<double, std::int32_t> : std::true_type {};

template <>
struct implicitly_within_limits<double, std::int64_t> : std::true_type {};
template <
  typename Dst,
  typename Src,
  bool DIsInt,
  bool SIsInt,
  bool DIsSig,
  bool SIsSig>
struct within_limits_num {
    static constexpr auto check(const Src) noexcept {
        return implicitly_within_limits<Dst, Src>::value;
    }
};
template <typename Dst, typename Src, bool IsInt, bool IsSig>
struct within_limits_num<Dst, Src, IsInt, IsInt, IsSig, IsSig> {
    static constexpr auto check(const Src value) noexcept {
        using dnl = std::numeric_limits<Dst>;

        return (dnl::min() <= value) && (value <= dnl::max());
    }
};
template <typename Dst, typename Src, bool IsInt>
struct within_limits_num<Dst, Src, IsInt, IsInt, false, true> {
    static constexpr auto check(const Src value) noexcept {
        using Dnl = std::numeric_limits<Dst>;
        using Tmp = std::make_unsigned_t<Src>;

        return (value < Src(0)) ? false : (Tmp(value) < Dnl::max());
    }
};
template <typename Dst, typename Src, bool IsInt>
struct within_limits_num<Dst, Src, IsInt, IsInt, true, false> {
    static constexpr auto check(const Src value) noexcept {
        using dnl = std::numeric_limits<Dst>;

        return (value < dnl::max());
    }
};
template <typename Dst, typename Src>
struct within_limits
  : within_limits_num<
      Dst,
      Src,
      std::is_integral_v<Dst>,
      std::is_integral_v<Src>,
      std::is_signed_v<Dst>,
      std::is_signed_v<Src>> {};
template <typename T>
struct within_limits<T, T> {
    static constexpr auto check(const T&) noexcept {
        return true;
    }
};
template <typename Dst, typename Src>
static constexpr auto is_within_limits(const Src value) noexcept {
    return implicitly_within_limits<Dst, Src>::value ||
           within_limits<Dst, Src>::check(value);
}
template <typename Dst, typename Src>
static constexpr auto limit_cast(Src value) noexcept
  -> std::enable_if_t<std::is_convertible_v<Src, Dst>, Dst> {
    is_within_limits<Dst>(value), Dst(std::move(value));
}
template <typename Src>
static constexpr auto signedness_cast(Src value) noexcept {
    return limit_cast<std::conditional_t<
      std::is_signed_v<Src>,
      std::make_unsigned_t<Src>,
      std::make_signed_t<Src>>>(value);
}
template <typename Dst, typename Src>
static constexpr auto convert_if_fits(Src value) noexcept
  -> std::enable_if_t<std::is_convertible_v<Src, Dst>, std::optional<Dst>> {

    if(is_within_limits<Dst>(value)) {
        return {Dst(std::move(value))};
    }
    return {};
}
} // namespace mirror

MIRROR_DIAG_POP()

#endif // MIRROR_IS_WITHIN_LIMITS_HPP
#include <algorithm>
#include <array>
#include <charconv>
#include <chrono>
#include <cstdlib>
#include <string>
#include <string_view>

namespace mirror {
static inline auto
from_string(const std::string_view src, const std::type_identity<bool>) noexcept
  -> std::variant<bool, std::errc> {

    const std::array<const std::string_view, 5> true_strs{
      {{"true"}, {"True"}, {"1"}, {"t"}, {"T"}}};
    if(std::find(true_strs.begin(), true_strs.end(), src) != true_strs.end()) {
        return {true};
    }

    const std::array<const std::string_view, 5> false_strs{
      {{"false"}, {"False"}, {"0"}, {"f"}, {"F"}}};
    if(std::find(false_strs.begin(), false_strs.end(), src) != false_strs.end()) {
        return {false};
    }

    return {std::errc::invalid_argument};
}

static inline auto from_string(
  const std::string_view src,
  const std::type_identity<tribool>) noexcept
  -> std::variant<tribool, std::errc> {
    if(const auto val{from_string(src, std::type_identity<bool>{})};
       has_value(val)) {
        return {tribool{extract(val)}};
    }

    const std::array<const std::string_view, 4> unknown_strs{
      {{"indeterminate"}, {"Indeterminate"}, {"unknown"}, {"-"}}};
    if(
      std::find(unknown_strs.begin(), unknown_strs.end(), src) !=
      unknown_strs.end()) {
        return {indeterminate};
    }

    return {std::errc::invalid_argument};
}

static inline auto
from_string(const std::string_view src, const std::type_identity<char>) noexcept
  -> std::variant<char, std::errc> {
    if(src.size() == 1) {
        return {src.front()};
    }
    return {std::errc::invalid_argument};
}

template <typename T>
static inline auto
from_string(const std::string_view src, const std::type_identity<T>) noexcept
  -> std::variant<T, std::errc> requires(std::is_integral_v<T>) {
    T value{};
    const auto res{
      std::from_chars<T>(src.data(), src.data() + src.size(), value, 10)};
    if(res.ec == std::errc{}) {
        if(std::string_view{res.ptr}.empty()) {
            return {value};
        }
        return {std::errc::invalid_argument};
    }
    return {res.ec};
}

template <typename T>
static inline auto
from_string(const std::string_view src, const std::type_identity<T>) noexcept
  -> std::variant<T, std::errc> requires(std::is_enum_v<T>) {
    if(const auto converted{string_to_enum<T>(src)}) {
        return {extract(converted)};
    }
    return {std::errc::invalid_argument};
}

static inline auto from_string(
  const std::string_view src,
  const std::type_identity<std::string_view>) noexcept
  -> std::variant<std::string_view, std::errc> {
    return {src};
}

static inline auto from_string(
  const std::string_view src,
  const std::type_identity<std::string>) noexcept
  -> std::variant<std::string, std::errc> {
    return {std::string{src}};
}

template <typename Rep, typename Period>
static inline auto convert_from_string(
  const std::string_view src,
  const std::string_view suffix,
  const std::type_identity<std::chrono::duration<Rep, Period>>) noexcept
  -> std::optional<std::chrono::duration<Rep, Period>> {
    using D = std::chrono::duration<Rep, Period>;

    Rep value{};
    const auto res{
      std::from_chars<Rep>(src.data(), src.data() + src.size(), value, 10)};
    if(std::string_view{res.ptr} == suffix) {
        if(res.ec == std::errc{}) {
            return {D{value}};
        }
    }
    return {};
}

template <typename Rep, typename Period>
static inline auto from_string(
  const std::string_view src,
  const std::type_identity<std::chrono::duration<Rep, Period>>) noexcept
  -> std::variant<std::chrono::duration<Rep, Period>, std::errc> {

    using D = std::chrono::duration<Rep, Period>;

    if(const auto d{convert_from_string(
         src,
         "s",
         std::type_identity<std::chrono::duration<Rep, std::ratio<1>>>())}) {
        return {std::chrono::duration_cast<D>(*d)};
    }

    if(const auto d{convert_from_string(
         src,
         "min",
         std::type_identity<std::chrono::duration<Rep, std::ratio<60>>>())}) {
        return {std::chrono::duration_cast<D>(*d)};
    }

    if(const auto d{convert_from_string(
         src,
         "hr",
         std::type_identity<std::chrono::duration<Rep, std::ratio<3600>>>())}) {
        return {std::chrono::duration_cast<D>(*d)};
    }

    if(const auto d{convert_from_string(
         src,
         "day",
         std::type_identity<
           std::chrono::duration<Rep, std::ratio<86400LL>>>())}) {
        return {std::chrono::duration_cast<D>(*d)};
    }

    if(const auto d{convert_from_string(
         src,
         "ms",
         std::type_identity<std::chrono::duration<Rep, std::milli>>())}) {
        return {std::chrono::duration_cast<D>(*d)};
    }

    if(const auto d{convert_from_string(
         src,
         "μs",
         std::type_identity<std::chrono::duration<Rep, std::micro>>())}) {
        return {std::chrono::duration_cast<D>(*d)};
    }

    return {std::errc::invalid_argument};
}

template <typename T>
auto from_string(const std::string_view src) noexcept {
    return from_string(src, std::type_identity<T>{});
}

template <typename T>
auto from_extractable_string(
  const extractable auto src,
  std::type_identity<T> tid = {}) noexcept -> std::optional<T> {
    if(has_value_type<std::string_view>(src) && has_value(src)) {
        if(auto converted{from_string(extract(src), tid)};
           has_value(converted)) {
            return {std::move(extract(converted))};
        }
    }
    return {};
}
} // namespace mirror

#endif // MIRROR_FROM_STRING_HPP
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

namespace mirror {
class program_args;
class program_arg_iterator;

class program_arg {
public:
    constexpr program_arg() noexcept = default;

    program_arg(const int argi, const int argc, const char** argv) noexcept
      : _argi{argi}
      , _argc{argc}
      , _argv{argv} {}

    using value_type = std::string_view;

    auto has_value() const noexcept -> bool {
        return (0 < _argi) && (_argi < _argc) && (_argv != nullptr) &&
               (_argv[_argi] != nullptr);
    }

    operator bool() const noexcept {
        return has_value();
    }

    auto position() const noexcept {
        return _argi;
    }

    auto is_first() const noexcept -> bool {
        return _argi == 1;
    }

    auto is_last() const noexcept -> bool {
        return _argi == _argc - 1;
    }

    auto get() const noexcept -> value_type {
        if(has_value()) {
            return value_type(_argv[_argi]);
        }
        return {};
    }

    operator value_type() const noexcept {
        return get();
    }

    auto next() const noexcept -> program_arg {
        return {_argi + 1, _argc, _argv};
    }

    auto prev() const noexcept -> program_arg {
        return {_argi - 1, _argc, _argv};
    }

    auto starts_with(value_type str) const noexcept -> bool {
        return get().starts_with(str);
    }

    auto ends_with(value_type str) const noexcept -> bool {
        return get().ends_with(str);
    }

    auto is_long_tag(value_type str) const noexcept -> bool {
        return get().starts_with("--") && get().ends_with(str) &&
               (get().size() == str.size() + 2);
    }

    auto operator==(const value_type& v) const noexcept {
        return get() == v;
    }

    auto operator!=(const value_type& v) const noexcept {
        return get() != v;
    }

private:
    int _argi{0};
    int _argc{0};
    const char** _argv{nullptr};

    friend class program_arg_iterator;
    friend class program_args;
};
static inline auto to_string(const program_arg& arg) {
    return std::string{arg.get()};
}
static inline auto operator<<(std::ostream& out, const program_arg& arg)
  -> std::ostream& {
    return out << arg.get();
}
class program_arg_iterator {
    using this_class = program_arg_iterator;

public:
    constexpr program_arg_iterator(const program_arg arg) noexcept
      : _a{arg} {}

    using value_type = program_arg;

    using difference_type = int;

    using reference = program_arg&;

    using const_reference = const program_arg&;

    using pointer = program_arg*;

    using const_pointer = const program_arg*;

    using iterator_category = std::random_access_iterator_tag;

    friend constexpr auto
    operator==(const this_class& l, const this_class& r) noexcept {
        return _cmp(l._a, r._a) == 0;
    }

    friend constexpr auto
    operator!=(const this_class& l, const this_class& r) noexcept {
        return _cmp(l._a, r._a) != 0;
    }

    friend constexpr auto
    operator<(const this_class& l, const this_class& r) noexcept {
        return _cmp(l._a, r._a) < 0;
    }

    friend constexpr auto
    operator<=(const this_class& l, const this_class& r) noexcept {
        return _cmp(l._a, r._a) <= 0;
    }

    friend constexpr auto
    operator>(const this_class& l, const this_class& r) noexcept {
        return _cmp(l._a, r._a) > 0;
    }

    friend constexpr auto
    operator>=(const this_class& l, const this_class& r) noexcept {
        return _cmp(l._a, r._a) >= 0;
    }

    friend constexpr auto
    operator-(const this_class& l, const this_class& r) noexcept
      -> difference_type {
        return _cmp(l._a, r._a);
    }

    constexpr auto operator++() noexcept -> this_class& {
        ++_a._argi;
        return *this;
    }

    constexpr auto operator--() noexcept -> this_class& {
        --_a._argi;
        return *this;
    }

    constexpr auto operator++(int) noexcept -> this_class {
        this_class result{*this};
        ++_a._argi;
        return result;
    }

    constexpr auto operator--(int) noexcept -> this_class {
        this_class result{*this};
        --_a._argi;
        return result;
    }

    constexpr auto operator+=(const difference_type dist) noexcept
      -> this_class& {
        _a._argi += dist;
        return *this;
    }

    constexpr auto operator-=(const difference_type dist) noexcept
      -> this_class& {
        _a._argi -= dist;
        return *this;
    }

    constexpr auto operator+(const difference_type dist) noexcept
      -> this_class {
        this_class result{*this};
        result._a._argi += dist;
        return result;
    }

    constexpr auto operator-(const difference_type dist) noexcept
      -> this_class {
        this_class result{*this};
        result._a._argi -= dist;
        return result;
    }

    constexpr auto operator*() noexcept -> reference {
        return _a;
    }

    constexpr auto operator*() const noexcept -> const_reference {
        return _a;
    }

private:
    static constexpr auto
    _cmp(const program_arg& l, const program_arg& r) noexcept -> int {
        return l._argi - r._argi;
    }

    program_arg _a{};
};
class program_args {
public:
    program_args() noexcept = default;

    program_args(const int argn, char** args) noexcept
      : _argc{argn}
      , _argv{const_cast<const char**>(args)} {}

    program_args(const int argn, const char** args) noexcept
      : _argc{argn}
      , _argv{args} {}

    using value_type = std::string_view;

    using size_type = int;

    using iterator = program_arg_iterator;

    auto argc() const noexcept -> int {
        return _argc;
    }

    auto argv() const noexcept -> const char** {
        return _argv;
    }

    auto empty() const noexcept -> bool {
        return _argc <= 0;
    }

    auto none() const noexcept -> bool {
        return _argc <= 1;
    }

    auto size() const noexcept -> int {
        return _argc;
    }

    auto get(const int pos) const noexcept -> program_arg {
        return {pos, _argc, _argv};
    }

    auto operator[](const int pos) const noexcept -> program_arg {
        return get(pos);
    }

    auto command() const noexcept -> program_arg {
        return get(0);
    }

    auto first() const noexcept -> program_arg {
        return {1, _argc, _argv};
    }

    auto begin() const noexcept -> iterator {
        return {program_arg(1, _argc, _argv)};
    }

    auto end() const noexcept -> iterator {
        return {program_arg(_argc, _argc, _argv)};
    }

    auto find(const std::string_view what) const noexcept -> program_arg {
        int i = 1;
        while(i < _argc) {
            if((_argv != nullptr) && (_argv[i] != nullptr)) {
                if(std::string_view(_argv[i]) == what) {
                    break;
                }
            }
            ++i;
        }
        return {i, _argc, _argv};
    }

private:
    const int _argc{0};
    const char** _argv{nullptr};
};
} // namespace mirror

#endif // MIRROR_PROGRAM_ARGS_HPP

#endif // MIRROR_ALL_HPP

