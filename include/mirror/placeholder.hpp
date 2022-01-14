/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_PLACEHOLDER_HPP
#define MIRROR_PLACEHOLDER_HPP

#include "primitives.hpp"

namespace mirror {

template <typename F>
struct placeholder_expr {
    F f;

    template <__metaobject_id M>
    constexpr auto operator()(wrapped_metaobject<M> mo) const {
        return f(mo);
    }
};

template <typename F>
placeholder_expr(F) -> placeholder_expr<F>;

template <typename El, typename Er>
constexpr auto operator^(placeholder_expr<El> l, placeholder_expr<Er> r) {
    return placeholder_expr{[l, r](auto x) {
        return l(x) ^ r(x);
    }};
}

template <typename El, typename Er>
constexpr auto operator+(placeholder_expr<El> l, placeholder_expr<Er> r) {
    return placeholder_expr{[l, r](auto x) {
        return l(x) + r(x);
    }};
}

template <>
struct placeholder_expr<std::integral_constant<size_t, 1>> {
    template <__metaobject_id M>
    constexpr auto operator()(wrapped_metaobject<M> mo) const {
        return mo;
    }
};

static constinit const placeholder_expr<std::integral_constant<size_t, 1>> _1{};

template <typename X>
constexpr auto not_(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return !e(mo);
    }};
}

template <typename X>
constexpr auto reflects_object(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_object(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_object_sequence(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_object_sequence(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_named(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_named(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_alias(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_alias(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_scope(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_scope(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_typed(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_typed(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_scope_member(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_scope_member(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_global_scope_member(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_global_scope_member(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_enumerator(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_enumerator(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_record_member(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_record_member(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_base(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_base(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_namespace(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_namespace(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_inline_namespace(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_inline_namespace(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_global_scope(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_global_scope(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_global_type(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_global_type(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_enum(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_enum(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_record(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_record(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_class(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_class(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_lambda(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_lambda(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_constant(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_constant(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_variable(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_variable(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_lambda_capture(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_lambda_capture(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_function_parameter(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_function_parameter(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_callable(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_callable(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_function(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_function(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_member_function(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_member_function(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_special_member_function(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_special_member_function(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_constructor(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_constructor(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_destructor(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_destructor(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_operator(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_operator(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_conversion_operator(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_conversion_operator(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_expression(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_expression(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_parenthesized_expression(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_parenthesized_expression(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_function_call_expression(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_function_call_expression(e(mo));
    }};
}

template <typename X>
constexpr auto reflects_specifier(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return reflects_specifier(e(mo));
    }};
}

// unary operations
// boolean

template <typename X>
constexpr auto is_constexpr(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_constexpr(e(mo));
    }};
}

template <typename X>
constexpr auto is_noexcept(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_noexcept(e(mo));
    }};
}

template <typename X>
constexpr auto is_explicit(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_explicit(e(mo));
    }};
}

template <typename X>
constexpr auto is_inline(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_inline(e(mo));
    }};
}

template <typename X>
constexpr auto is_thread_local(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_thread_local(e(mo));
    }};
}

template <typename X>
constexpr auto is_static(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_static(e(mo));
    }};
}

template <typename X>
constexpr auto is_virtual(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_virtual(e(mo));
    }};
}

template <typename X>
constexpr auto is_pure_virtual(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_pure_virtual(e(mo));
    }};
}

template <typename X>
constexpr auto is_pure_final(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_pure_final(e(mo));
    }};
}

template <typename X>
constexpr auto is_private(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_private(e(mo));
    }};
}

template <typename X>
constexpr auto is_protected(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_protected(e(mo));
    }};
}

template <typename X>
constexpr auto is_public(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_public(e(mo));
    }};
}

template <typename X>
constexpr auto is_unnamed(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_unnamed(e(mo));
    }};
}

template <typename X>
constexpr auto is_enum(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_enum(e(mo));
    }};
}

template <typename X>
constexpr auto is_scoped_enum(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_scoped_enum(e(mo));
    }};
}

template <typename X>
constexpr auto is_union(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_union(e(mo));
    }};
}

template <typename X>
constexpr auto uses_class_key(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return uses_class_key(e(mo));
    }};
}

template <typename X>
constexpr auto uses_struct_key(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return uses_struct_key(e(mo));
    }};
}

template <typename X>
constexpr auto uses_default_copy_capture(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return uses_default_copy_capture(e(mo));
    }};
}

template <typename X>
constexpr auto uses_default_reference_capture(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return uses_default_reference_capture(e(mo));
    }};
}

template <typename X>
constexpr auto is_call_operator_const(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_call_operator_const(e(mo));
    }};
}

template <typename X>
constexpr auto is_explicitly_captured(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_explicitly_captured(e(mo));
    }};
}

template <typename X>
constexpr auto has_default_argument(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return has_default_argument(e(mo));
    }};
}

template <typename X>
constexpr auto is_const(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_const(e(mo));
    }};
}

template <typename X>
constexpr auto is_volatile(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_volatile(e(mo));
    }};
}

template <typename X>
constexpr auto has_lvalueref_qualifier(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return has_lvalueref_qualifier(e(mo));
    }};
}

template <typename X>
constexpr auto has_rvalueref_qualifier(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return has_rvalueref_qualifier(e(mo));
    }};
}

template <typename X>
constexpr auto is_implicitly_declared(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_implicitly_declared(e(mo));
    }};
}

template <typename X>
constexpr auto is_defaulted(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_defaulted(e(mo));
    }};
}

template <typename X>
constexpr auto is_deleted(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_deleted(e(mo));
    }};
}

template <typename X>
constexpr auto is_copy_constructor(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_copy_constructor(e(mo));
    }};
}

template <typename X>
constexpr auto is_move_constructor(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_move_constructor(e(mo));
    }};
}

template <typename X>
constexpr auto is_copy_assignment_operator(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_copy_assignment_operator(e(mo));
    }};
}

template <typename X>
constexpr auto is_move_assignment_operator(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_move_assignment_operator(e(mo));
    }};
}

template <typename X>
constexpr auto is_empty(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return is_empty(e(mo));
    }};
}

// integer
template <typename X>
constexpr auto get_id(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_id(e(mo));
    }};
}

template <typename X>
constexpr auto get_source_line(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_source_line(e(mo));
    }};
}

template <typename X>
constexpr auto get_source_column(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_source_column(e(mo));
    }};
}

template <typename X>
constexpr auto get_size(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_size(e(mo));
    }};
}

template <typename X>
constexpr auto get_pointer(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_pointer(e(mo));
    }};
}

template <typename X>
constexpr auto get_constant(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_constant(e(mo));
    }};
}

// string
template <typename X>
constexpr auto get_debug_info(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_debug_info(e(mo));
    }};
}

template <typename X>
constexpr auto get_source_file_name(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_source_file_name(e(mo));
    }};
}

template <typename X>
constexpr auto get_name(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_name(e(mo));
    }};
}

template <typename X>
constexpr auto get_display_name(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_display_name(e(mo));
    }};
}

template <typename X>
constexpr auto get_full_name(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_full_name(e(mo));
    }};
}

template <typename X>
constexpr auto to_string(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return std::string(e(mo));
    }};
}

// metaobject
template <typename X>
constexpr auto get_scope(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_scope(e(mo));
    }};
}

template <typename X>
constexpr auto get_type(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_type(e(mo));
    }};
}

template <typename X>
constexpr auto get_base_type(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_base_type(e(mo));
    }};
}

template <typename X>
constexpr auto get_element_type(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_element_type(e(mo));
    }};
}

template <typename X>
constexpr auto get_underlying_type(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_underlying_type(e(mo));
    }};
}

template <typename X>
constexpr auto get_aliased(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_aliased(e(mo));
    }};
}

template <typename X>
constexpr auto remove_all_aliases(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return remove_all_aliases(e(mo));
    }};
}

template <typename X>
constexpr auto get_class(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_class(e(mo));
    }};
}

template <typename X>
constexpr auto get_subexpression(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_subexpression(e(mo));
    }};
}

template <typename X>
constexpr auto get_callable(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_callable(e(mo));
    }};
}

template <typename X>
constexpr auto get_base_classes(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_base_classes(e(mo));
    }};
}

template <typename X>
constexpr auto get_member_types(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_member_types(e(mo));
    }};
}

template <typename X>
constexpr auto get_data_members(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_data_members(e(mo));
    }};
}

template <typename X>
constexpr auto get_member_functions(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_member_functions(e(mo));
    }};
}

template <typename X>
constexpr auto get_constructors(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_constructors(e(mo));
    }};
}

template <typename X>
constexpr auto get_destructors(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_destructors(e(mo));
    }};
}

template <typename X>
constexpr auto get_operators(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_operators(e(mo));
    }};
}

template <typename X>
constexpr auto get_enumerators(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_enumerators(e(mo));
    }};
}

template <typename X>
constexpr auto get_parameters(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_parameters(e(mo));
    }};
}

template <typename X>
constexpr auto get_captures(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_captures(e(mo));
    }};
}

template <typename X>
constexpr auto hide_private(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return hide_private(e(mo));
    }};
}

template <typename X>
constexpr auto hide_protected(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return hide_protected(e(mo));
    }};
}

template <typename X>
constexpr auto get_reflected_type(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_reflected_type(e(mo));
    }};
}

template <typename X, template <typename> class Transform>
constexpr auto get_transformed_type(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_transformed_type<Transform>(e(mo));
    }};
}

template <typename T, typename X>
constexpr auto is_type(placeholder_expr<X> e, type_identity<T> tid = {}) {
    return placeholder_expr{[e, tid](auto mo) {
        return is_type(e(mo), tid);
    }};
}

template <template <typename> class Trait, typename X>
constexpr auto has_type_trait(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return has_type_trait<Trait>(e(mo));
    }};
}

template <typename T, typename X>
constexpr auto has_type(placeholder_expr<X> e, type_identity<T> tid = {}) {
    return placeholder_expr{[e, tid](auto mo) {
        return has_type(e(mo), tid);
    }};
}

template <template <typename> class Trait, typename X>
constexpr auto has_type_with_trait(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return has_type_with_trait<Trait>(e(mo));
    }};
}

template <typename X>
constexpr auto get_hash(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return get_hash(e(mo));
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
    return placeholder_expr{[e, me](auto mo) {
        return is_applicable(me, e(mo));
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
    return placeholder_expr{[e, me](auto mo) {
        return try_apply(me, e(mo));
    }};
}

template <typename... X>
constexpr auto make_sequence(placeholder_expr<X>... e) {
    return placeholder_expr{[e...](auto mo) {
        return make_sequence(e(mo)...);
    }};
}

template <typename... X>
constexpr auto concat(placeholder_expr<X>... e) {
    return placeholder_expr{[e...](auto mo) {
        return concat(e(mo)...);
    }};
}

template <typename X, typename F, typename A>
constexpr auto fold(placeholder_expr<X> e, F transform, A aggregate) {
    return placeholder_expr{[e, transform, aggregate](auto mo) {
        return fold(e(mo), transform, aggregate);
    }};
}

template <typename X, typename F, typename S>
constexpr auto join(placeholder_expr<X> e, F transform, S separator) {
    return placeholder_expr{[e, transform, separator](auto mo) {
        return join(e(mo), transform, separator);
    }};
}

template <typename X, typename F, typename S, typename A>
constexpr auto
join(placeholder_expr<X> e, F transform, S separator, A aggregate) {
    return placeholder_expr{[e, transform, separator, aggregate](auto mo) {
        return join(e(mo), transform, separator, aggregate);
    }};
}

template <typename X, typename F>
constexpr auto all_of(placeholder_expr<X> e, F predicate) {
    return placeholder_expr{[e, predicate](auto mo) {
        return all_of(e(mo), predicate);
    }};
}

template <typename X, typename F>
constexpr auto any_of(placeholder_expr<X> e, F predicate) {
    return placeholder_expr{[e, predicate](auto mo) {
        return any_of(e(mo), predicate);
    }};
}

template <typename X, typename F>
constexpr auto none_of(placeholder_expr<X> e, F predicate) {
    return placeholder_expr{[e, predicate](auto mo) {
        return none_of(e(mo), predicate);
    }};
}

template <typename X, typename F>
constexpr auto filter(placeholder_expr<X> e, F predicate) {
    return placeholder_expr{[e, predicate](auto mo) {
        return filter(e(mo), predicate);
    }};
}

template <typename X, typename Function, typename Fallback, typename... P>
constexpr auto select(
  placeholder_expr<X> e,
  Function function,
  Fallback fallback,
  P&&... param) {
    return placeholder_expr{[e, &function, &fallback, &param...](auto mo) {
        return select(
          e(mo),
          std::move(function),
          std::move(fallback),
          std::forward<P>(param)...);
    }};
}

template <typename X>
constexpr auto flatten(placeholder_expr<X> e) {
    return placeholder_expr{[e](auto mo) {
        return flatten(e(mo));
    }};
}

} // namespace mirror

#endif // MIRROR_PLACEHOLDER_HPP
