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

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

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

#if !defined(_LIBCPP_HAS_NO_REFLECTION) && \
  !defined(_LIBCPP_HAS_NO_REFLECTION_EXT)

namespace mirror {

using std::integral_constant;
using std::string_view;
using std::type_identity;

template <__metaobject_id _Mp>
struct metaobject {};

template <__metaobject_id _Mp>
consteval bool reflects_object(metaobject<_Mp>) {
    return __metaobject_is_meta_object(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_object_sequence(metaobject<_Mp>) {
    return __metaobject_is_meta_object_sequence(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_named(metaobject<_Mp>) {
    return __metaobject_is_meta_named(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_alias(metaobject<_Mp>) {
    return __metaobject_is_meta_alias(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_scope(metaobject<_Mp>) {
    return __metaobject_is_meta_scope(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_typed(metaobject<_Mp>) {
    return __metaobject_is_meta_typed(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_scope_member(metaobject<_Mp>) {
    return __metaobject_is_meta_scope_member(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_global_scope_member(metaobject<_Mp>) {
    if constexpr(__metaobject_is_meta_scope_member(_Mp)) {
        return __metaobject_is_meta_global_scope(__metaobject_get_scope(_Mp));
    } else {
        return false;
    }
}

template <__metaobject_id _Mp>
consteval bool reflects_enumerator(metaobject<_Mp>) {
    return __metaobject_is_meta_enumerator(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_record_member(metaobject<_Mp>) {
    return __metaobject_is_meta_record_member(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_base(metaobject<_Mp>) {
    return __metaobject_is_meta_base(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_namespace(metaobject<_Mp>) {
    return __metaobject_is_meta_namespace(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_inline_namespace(metaobject<_Mp>) {
    if constexpr(__metaobject_is_meta_namespace(_Mp)) {
        return __metaobject_is_inline(_Mp);
    } else {
        return false;
    }
}

template <__metaobject_id _Mp>
consteval bool reflects_global_scope(metaobject<_Mp>) {
    return __metaobject_is_meta_global_scope(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_type(metaobject<_Mp>) {
    return __metaobject_is_meta_type(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_enum(metaobject<_Mp>) {
    return __metaobject_is_meta_enum(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_record(metaobject<_Mp>) {
    return __metaobject_is_meta_record(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_class(metaobject<_Mp>) {
    return __metaobject_is_meta_class(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_lambda(metaobject<_Mp>) {
    return __metaobject_is_meta_lambda(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_constant(metaobject<_Mp>) {
    return __metaobject_is_meta_constant(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_variable(metaobject<_Mp>) {
    return __metaobject_is_meta_variable(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_lambda_capture(metaobject<_Mp>) {
    return __metaobject_is_meta_lambda_capture(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_function_parameter(metaobject<_Mp>) {
    return __metaobject_is_meta_function_parameter(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_callable(metaobject<_Mp>) {
    return __metaobject_is_meta_callable(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_function(metaobject<_Mp>) {
    return __metaobject_is_meta_function(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_member_function(metaobject<_Mp>) {
    return __metaobject_is_meta_member_function(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_special_member_function(metaobject<_Mp>) {
    return __metaobject_is_meta_special_member_function(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_constructor(metaobject<_Mp>) {
    return __metaobject_is_meta_constructor(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_destructor(metaobject<_Mp>) {
    return __metaobject_is_meta_destructor(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_operator(metaobject<_Mp>) {
    return __metaobject_is_meta_operator(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_conversion_operator(metaobject<_Mp>) {
    return __metaobject_is_meta_conversion_operator(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_expression(metaobject<_Mp>) {
    return __metaobject_is_meta_expression(_Mp);
}

template <__metaobject_id _Mp>
consteval bool reflects_specifier(metaobject<_Mp>) {
    return __metaobject_is_meta_specifier(_Mp);
}

// unary operations
// boolean
template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<
    __metaobject_is_meta_variable(_Mp) || __metaobject_is_meta_callable(_Mp)>>
consteval bool is_constexpr(metaobject<_Mp>) {
    return __metaobject_is_constexpr(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<
    __metaobject_is_meta_constructor(_Mp) ||
    __metaobject_is_meta_conversion_operator(_Mp)>>
consteval bool is_explicit(metaobject<_Mp>) {
    return __metaobject_is_explicit(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<
    __metaobject_is_meta_namespace(_Mp) || __metaobject_is_meta_callable(_Mp)>>
consteval bool is_inline(metaobject<_Mp>) {
    return __metaobject_is_inline(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<
    __metaobject_is_meta_variable(_Mp) ||
    __metaobject_is_meta_member_function(_Mp)>>
consteval bool is_static(metaobject<_Mp>) {
    return __metaobject_is_static(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<
    __metaobject_is_meta_base(_Mp) || __metaobject_is_meta_destructor(_Mp) ||
    __metaobject_is_meta_member_function(_Mp)>>
consteval bool is_virtual(metaobject<_Mp>) {
    return __metaobject_is_virtual(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<
    __metaobject_is_meta_destructor(_Mp) ||
    __metaobject_is_meta_member_function(_Mp)>>
consteval bool is_pure_virtual(metaobject<_Mp>) {
    return __metaobject_is_pure_virtual(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<
    __metaobject_is_meta_class(_Mp) || __metaobject_is_meta_member_function(_Mp)>>
consteval bool is_final(metaobject<_Mp>) {
    return __metaobject_is_final(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<
    __metaobject_is_meta_record_member(_Mp) || __metaobject_is_meta_base(_Mp)>>
consteval bool is_private(metaobject<_Mp>) {
    return __metaobject_is_private(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<
    __metaobject_is_meta_record_member(_Mp) || __metaobject_is_meta_base(_Mp)>>
consteval bool is_protected(metaobject<_Mp>) {
    return __metaobject_is_protected(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<
    __metaobject_is_meta_record_member(_Mp) || __metaobject_is_meta_base(_Mp)>>
consteval bool is_public(metaobject<_Mp>) {
    return __metaobject_is_public(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_named(_Mp)>>
consteval bool is_unnamed(metaobject<_Mp>) {
    return __metaobject_is_unnamed(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_type(_Mp)>>
consteval bool is_enum(metaobject<_Mp>) {
    return __metaobject_is_enum(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_type(_Mp)>>
consteval bool is_scoped_enum(metaobject<_Mp>) {
    return __metaobject_is_scoped_enum(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_type(_Mp)>>
consteval bool is_union(metaobject<_Mp>) {
    return __metaobject_is_union(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_type(_Mp)>>
consteval bool uses_class_key(metaobject<_Mp>) {
    return __metaobject_uses_class_key(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_type(_Mp)>>
consteval bool uses_struct_key(metaobject<_Mp>) {
    return __metaobject_uses_struct_key(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_lambda(_Mp)>>
consteval bool uses_default_copy_capture(metaobject<_Mp>) {
    return __metaobject_uses_default_copy_capture(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_lambda(_Mp)>>
consteval bool uses_default_reference_capture(metaobject<_Mp>) {
    return __metaobject_uses_default_reference_capture(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_lambda(_Mp)>>
consteval bool is_call_operator_const(metaobject<_Mp>) {
    return __metaobject_is_call_operator_const(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_member_function(_Mp)>>
consteval bool is_const(metaobject<_Mp>) {
    return __metaobject_is_const(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_member_function(_Mp)>>
consteval bool is_volatile(metaobject<_Mp>) {
    return __metaobject_is_volatile(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_member_function(_Mp)>>
consteval bool has_lvalueref_qualifier(metaobject<_Mp>) {
    return __metaobject_has_lvalueref_qualifier(_Mp);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_member_function(_Mp)>>
consteval bool has_rvalueref_qualifier(metaobject<_Mp>) {
    return __metaobject_has_rvalueref_qualifier(_Mp);
}

template <__metaobject_id _Ml, __metaobject_id _Mr>
consteval bool reflects_same(metaobject<_Ml>, metaobject<_Mr>) {
    return __metaobject_reflects_same(_Ml, _Mr);
}

// integer
template <__metaobject_id _Mp>
consteval size_t get_id(metaobject<_Mp>) {
    return __metaobject_get_id_value(_Mp);
}

template <__metaobject_id _Mp>
consteval size_t get_source_line(metaobject<_Mp>) {
    return __metaobject_get_source_line(_Mp);
}

template <__metaobject_id _Mp>
consteval size_t get_source_column(metaobject<_Mp>) {
    return __metaobject_get_source_column(_Mp);
}

template <__metaobject_id _Mp>
struct _get_pointer
  : integral_constant<
      __unrefltype(__metaobject_get_pointer(_Mp)),
      __metaobject_get_pointer(_Mp)> {};

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<
    __metaobject_is_meta_variable(_Mp) || __metaobject_is_meta_function(_Mp)>>
consteval auto get_pointer(metaobject<_Mp>) {
    return _get_pointer<_Mp>::value;
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_variable(_Mp)>>
constexpr const auto& get_value(metaobject<_Mp>) {
    return *_get_pointer<_Mp>::value;
}

template <
  __metaobject_id _Mp,
  class _Cp,
  typename = std::enable_if_t<
    __metaobject_is_meta_record_member(_Mp) &&
    __metaobject_is_meta_variable(_Mp)>>
constexpr const auto& get_value(metaobject<_Mp>, const _Cp& obj) {
    return obj.*_get_pointer<_Mp>::value;
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_variable(_Mp)>>
constexpr auto& get_reference(metaobject<_Mp>) {
    return *_get_pointer<_Mp>::value;
}

template <
  __metaobject_id _Mp,
  class _Cp,
  typename = std::enable_if_t<
    __metaobject_is_meta_record_member(_Mp) &&
    __metaobject_is_meta_variable(_Mp)>>
constexpr auto& get_reference(metaobject<_Mp>, _Cp& obj) {
    return obj.*_get_pointer<_Mp>::value;
}

template <__metaobject_id _Mp>
struct _get_constant
  : integral_constant<
      __unrefltype(__metaobject_get_constant(_Mp)),
      __metaobject_get_constant(_Mp)> {};

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_constant(_Mp)>>
constexpr auto get_constant(metaobject<_Mp>) {
    return _get_constant<_Mp>::value;
}

template <
  __metaobject_id _Mp,
  typename _Cp,
  typename... _Ap,
  typename = std::enable_if_t<__metaobject_is_meta_member_function(_Mp)>>
constexpr auto invoke_on(metaobject<_Mp> mo, _Cp& obj, _Ap&&... args) {
    if constexpr(is_static(mo)) {
        return (*_get_pointer<_Mp>::value)(std::forward<_Ap>(args)...);
    } else {
        return (obj.*_get_pointer<_Mp>::value)(std::forward<_Ap>(args)...);
    }
}

template <
  __metaobject_id _Mp,
  typename... _Ap,
  typename = std::enable_if_t<
    __metaobject_is_meta_function(_Mp) ||
    (__metaobject_is_meta_member_function(_Mp) && __metaobject_is_static(_Mp))>>
constexpr auto invoke(metaobject<_Mp>, _Ap&&... args) {
    return (*_get_pointer<_Mp>::value)(std::forward<_Ap>(args)...);
}

template <
  __metaobject_id _Mp,
  typename _Cp,
  typename... _Ap,
  typename = std::enable_if_t<
    __metaobject_is_meta_member_function(_Mp) && !__metaobject_is_static(_Mp)>>
constexpr auto invoke(metaobject<_Mp>, _Cp& obj, _Ap&&... args) {
    return (obj.*_get_pointer<_Mp>::value)(std::forward<_Ap>(args)...);
}

template <__metaobject_id _Mp, typename... _Ap>
constexpr std::enable_if_t<
  __metaobject_is_meta_constructor(_Mp),
  __unrefltype(__metaobject_get_scope(_Mp))>
invoke(metaobject<_Mp>, _Ap&&... args) {
    return __unrefltype(__metaobject_get_scope(_Mp))(
      std::forward<_Ap>(args)...);
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_object_sequence(_Mp)>>
consteval size_t get_size(metaobject<_Mp>) {
    return __metaobject_get_size(_Mp);
}

// string
consteval string_view get_source_file_name_view(__metaobject_id mo) {
    return {
      __metaobject_get_source_file_name(mo),
      __metaobject_source_file_name_len(mo)};
}

template <__metaobject_id _Mp>
consteval string_view get_source_file_name(metaobject<_Mp>) {
    return get_source_file_name_view(_Mp);
}

consteval string_view get_name_view(__metaobject_id mo) {
    return {__metaobject_get_name(mo), __metaobject_name_len(mo)};
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_named(_Mp)>>
consteval string_view get_name(metaobject<_Mp>) {
    return get_name_view(_Mp);
}

consteval string_view get_display_name_view(__metaobject_id mo) {
    return {
      __metaobject_get_display_name(mo), __metaobject_display_name_len(mo)};
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_named(_Mp)>>
consteval string_view get_display_name(metaobject<_Mp>) {
    return get_display_name_view(_Mp);
}

// metaobject
template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_scope_member(_Mp)>>
constexpr auto get_scope(metaobject<_Mp>) {
    return metaobject<__metaobject_get_scope(_Mp)>{};
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_typed(_Mp)>>
constexpr auto get_type(metaobject<_Mp>) {
    return metaobject<__metaobject_get_type(_Mp)>{};
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_enum(_Mp)>>
constexpr auto get_underlying_type(metaobject<_Mp>) {
    return metaobject<__metaobject_get_underlying_type(_Mp)>{};
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_alias(_Mp)>>
constexpr auto get_aliased(metaobject<_Mp>) {
    return metaobject<__metaobject_get_aliased(_Mp)>{};
}

template <__metaobject_id _Mp>
constexpr auto remove_all_aliases(metaobject<_Mp> mo) {
    if constexpr(__metaobject_is_meta_alias(_Mp)) {
        return remove_all_aliases(metaobject<__metaobject_get_aliased(_Mp)>{});
    } else {
        return mo;
    }
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_base(_Mp)>>
constexpr auto get_class(metaobject<_Mp>) {
    return metaobject<__metaobject_get_class(_Mp)>{};
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_class(_Mp)>>
constexpr auto get_base_classes(metaobject<_Mp>) {
    return metaobject<__metaobject_get_base_classes(_Mp)>{};
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_record(_Mp)>>
constexpr auto get_member_types(metaobject<_Mp>) {
    return metaobject<__metaobject_get_member_types(_Mp)>{};
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_record(_Mp)>>
constexpr auto get_data_members(metaobject<_Mp>) {
    return metaobject<__metaobject_get_data_members(_Mp)>{};
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_record(_Mp)>>
constexpr auto get_member_functions(metaobject<_Mp>) {
    return metaobject<__metaobject_get_member_functions(_Mp)>{};
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_record(_Mp)>>
constexpr auto get_constructors(metaobject<_Mp>) {
    return metaobject<__metaobject_get_constructors(_Mp)>{};
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_record(_Mp)>>
constexpr auto get_destructors(metaobject<_Mp>) {
    return metaobject<__metaobject_get_destructors(_Mp)>{};
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_record(_Mp)>>
constexpr auto get_operators(metaobject<_Mp>) {
    return metaobject<__metaobject_get_operators(_Mp)>{};
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_enum(_Mp)>>
constexpr auto get_enumerators(metaobject<_Mp>) {
    return metaobject<__metaobject_get_enumerators(_Mp)>{};
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_callable(_Mp)>>
constexpr auto get_parameters(metaobject<_Mp>) {
    return metaobject<__metaobject_get_parameters(_Mp)>{};
}

template <
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_lambda(_Mp)>>
constexpr auto get_captures(metaobject<_Mp>) {
    return metaobject<__metaobject_get_captures(_Mp)>{};
}

template <
  size_t _I,
  __metaobject_id _Mp,
  typename = std::enable_if_t<__metaobject_is_meta_object_sequence(_Mp)>>
constexpr auto get_element(metaobject<_Mp>) {
    return metaobject<__metaobject_get_element(_Mp, _I)>{};
}

// unpacking
template <__metaobject_id... _Mp>
struct unpacked_metaobject_sequence {};

template <__metaobject_id _Mp>
constexpr auto unpack(metaobject<_Mp>) {
    return __unpack_metaobject_seq<unpacked_metaobject_sequence, _Mp>{};
}

// unpacked range operations
template <__metaobject_id... _Mp, typename _Fp>
void for_each(unpacked_metaobject_sequence<_Mp...>, _Fp function) {
    (void)(..., function(metaobject<_Mp>{}));
}

template <
  __metaobject_id _Mp,
  typename _Fp,
  typename = std::enable_if_t<__metaobject_is_meta_object_sequence(_Mp)>>
void for_each(metaobject<_Mp> mo, _Fp function) {
    return for_each(unpack(mo), std::move(function));
}

template <typename _Tp, __metaobject_id... _Mp, typename _Fp, typename... _Pp>
_Tp select(
  unpacked_metaobject_sequence<_Mp...>,
  _Fp function,
  _Tp fallback,
  _Pp&&... param) {
    (..., function(fallback, metaobject<_Mp>{}, std::forward<_Pp>(param)...));
    return fallback;
}

template <typename _Tp, __metaobject_id _Mp, typename _Fp, typename... _Pp>
std::enable_if_t<__metaobject_is_meta_object_sequence(_Mp), _Tp>
select(metaobject<_Mp> mo, _Fp function, _Tp fallback, _Pp&&... param) {
    return select(
      unpack(mo),
      std::move(function),
      std::move(fallback),
      std::forward<_Pp>(param)...);
}

// type unreflection
template <__metaobject_id _Mp>
struct get_reflected_type : type_identity<__unrefltype(_Mp)> {};

template <__metaobject_id _Mp>
consteval auto get_reflected_type_id(metaobject<_Mp>) {
    return get_reflected_type<_Mp>{};
}

// reflection "operator"
#define mirror(...) \
    ::mirror::metaobject<__reflexpr_id(__VA_ARGS__)> {}

} // namespace mirror

#endif // !_LIBCPP_HAS_NO_REFLECTION && !_LIBCPP_HAS_NO_REFLECTION_EXT

#endif // MIRROR_PRIMITIVES_HPP
