/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_PLACEHOLDER_HPP
#define MIRROR_PLACEHOLDER_HPP

#include "overload.hpp"
#include "primitives.hpp"

namespace mirror {

template <typename F>
struct placeholder_expr {
    F f;

    template <__metaobject_id M>
    constexpr auto operator()(wrapped_metaobject<M> mo) const {
        return f(mo);
    }

    template <__metaobject_id Ml, __metaobject_id Mr>
    constexpr auto
    operator()(wrapped_metaobject<Ml> ml, wrapped_metaobject<Mr> mr) const {
        return f(ml, mr);
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
    template <__metaobject_id M>
    constexpr auto operator()(wrapped_metaobject<M> mo) const {
        return mo;
    }

    template <__metaobject_id Ml, __metaobject_id Mr>
    constexpr auto
    operator()(wrapped_metaobject<Ml> mo, wrapped_metaobject<Mr>) const {
        return mo;
    }
};

template <>
struct placeholder_expr<std::integral_constant<size_t, 2>> {
    template <__metaobject_id Ml, __metaobject_id Mr>
    constexpr auto
    operator()(wrapped_metaobject<Ml>, wrapped_metaobject<Mr> mo) const {
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

template <typename X>
constexpr auto get_pointer(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_pointer(e(a...));
    }};
}

template <typename X>
constexpr auto get_constant(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return get_constant(e(a...));
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

template <typename X, typename Function, typename Fallback, typename... P>
constexpr auto select(
  placeholder_expr<X> e,
  Function function,
  Fallback fallback,
  P&&... param) {
    return placeholder_expr{[e, &function, &fallback, &param...](auto... a) {
        return select(
          e(a...),
          std::move(function),
          std::move(fallback),
          std::forward<P>(param)...);
    }};
}

template <typename X>
constexpr auto flatten(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto... a) {
        return flatten(e(a...));
    }};
}

} // namespace mirror

#endif // MIRROR_PLACEHOLDER_HPP
