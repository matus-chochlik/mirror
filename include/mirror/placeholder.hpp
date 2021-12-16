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

template <size_t I>
struct placeholder_t {};

static constinit const placeholder_t<1> _1{};
static constinit const placeholder_t<2> _2{};

consteval auto reflects_object(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_object(mo);
    };
}

consteval auto reflects_object_sequence(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_object_sequence(mo);
    };
}

consteval auto reflects_named(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_named(mo);
    };
}

consteval auto reflects_alias(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_alias(mo);
    };
}

consteval auto reflects_scope(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_scope(mo);
    };
}

consteval auto reflects_typed(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_typed(mo);
    };
}

consteval auto reflects_scope_member(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_scope_member(mo);
    };
}

consteval auto reflects_global_scope_member(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_global_scope_member(mo);
    };
}

consteval auto reflects_enumerator(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_enumerator(mo);
    };
}

consteval auto reflects_record_member(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_record_member(mo);
    };
}

consteval auto reflects_base(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_base(mo);
    };
}

consteval auto reflects_namespace(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_namespace(mo);
    };
}

consteval auto reflects_inline_namespace(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_inline_namespace(mo);
    };
}

consteval auto reflects_global_scope(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_global_scope(mo);
    };
}

consteval auto reflects_global_type(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_global_type(mo);
    };
}

consteval auto reflects_enum(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_enum(mo);
    };
}

consteval auto reflects_record(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_record(mo);
    };
}

consteval auto reflects_class(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_class(mo);
    };
}

consteval auto reflects_lambda(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_lambda(mo);
    };
}

consteval auto reflects_constant(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_constant(mo);
    };
}

consteval auto reflects_variable(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_variable(mo);
    };
}

consteval auto reflects_lambda_capture(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_lambda_capture(mo);
    };
}

consteval auto reflects_function_parameter(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_function_parameter(mo);
    };
}

consteval auto reflects_callable(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_callable(mo);
    };
}

consteval auto reflects_function(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_function(mo);
    };
}

consteval auto reflects_member_function(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_member_function(mo);
    };
}

consteval auto reflects_special_member_function(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_special_member_function(mo);
    };
}

consteval auto reflects_constructor(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_constructor(mo);
    };
}

consteval auto reflects_destructor(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_destructor(mo);
    };
}

consteval auto reflects_operator(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_operator(mo);
    };
}

consteval auto reflects_conversion_operator(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_conversion_operator(mo);
    };
}

consteval auto reflects_expression(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_expression(mo);
    };
}

consteval auto reflects_specifier(placeholder_t<1>) {
    return [](auto mo) {
        return reflects_specifier(mo);
    };
}

// unary operations
// boolean

consteval auto is_constexpr(placeholder_t<1>) {
    return [](auto mo) {
        return is_constexpr(mo);
    };
}

consteval auto is_noexcept(placeholder_t<1>) {
    return [](auto mo) {
        return is_noexcept(mo);
    };
}

consteval auto is_explicit(placeholder_t<1>) {
    return [](auto mo) {
        return is_explicit(mo);
    };
}

consteval auto is_inline(placeholder_t<1>) {
    return [](auto mo) {
        return is_inline(mo);
    };
}

consteval auto is_thread_local(placeholder_t<1>) {
    return [](auto mo) {
        return is_thread_local(mo);
    };
}

consteval auto is_static(placeholder_t<1>) {
    return [](auto mo) {
        return is_static(mo);
    };
}

consteval auto is_virtual(placeholder_t<1>) {
    return [](auto mo) {
        return is_virtual(mo);
    };
}

consteval auto is_pure_virtual(placeholder_t<1>) {
    return [](auto mo) {
        return is_pure_virtual(mo);
    };
}

consteval auto is_pure_final(placeholder_t<1>) {
    return [](auto mo) {
        return is_pure_final(mo);
    };
}

consteval auto is_private(placeholder_t<1>) {
    return [](auto mo) {
        return is_private(mo);
    };
}

consteval auto is_protected(placeholder_t<1>) {
    return [](auto mo) {
        return is_protected(mo);
    };
}

consteval auto is_public(placeholder_t<1>) {
    return [](auto mo) {
        return is_public(mo);
    };
}

consteval auto is_unnamed(placeholder_t<1>) {
    return [](auto mo) {
        return is_unnamed(mo);
    };
}

consteval auto is_enum(placeholder_t<1>) {
    return [](auto mo) {
        return is_enum(mo);
    };
}

consteval auto is_scoped_enum(placeholder_t<1>) {
    return [](auto mo) {
        return is_scoped_enum(mo);
    };
}

consteval auto is_union(placeholder_t<1>) {
    return [](auto mo) {
        return is_union(mo);
    };
}

consteval auto uses_class_key(placeholder_t<1>) {
    return [](auto mo) {
        return uses_class_key(mo);
    };
}

consteval auto uses_struct_key(placeholder_t<1>) {
    return [](auto mo) {
        return uses_struct_key(mo);
    };
}

consteval auto uses_default_copy_capture(placeholder_t<1>) {
    return [](auto mo) {
        return uses_default_copy_capture(mo);
    };
}

consteval auto uses_default_reference_capture(placeholder_t<1>) {
    return [](auto mo) {
        return uses_default_reference_capture(mo);
    };
}

consteval auto is_call_operator_const(placeholder_t<1>) {
    return [](auto mo) {
        return is_call_operator_const(mo);
    };
}

consteval auto is_explicitly_captured(placeholder_t<1>) {
    return [](auto mo) {
        return is_explicitly_captured(mo);
    };
}

consteval auto is_const(placeholder_t<1>) {
    return [](auto mo) {
        return is_const(mo);
    };
}

consteval auto is_volatile(placeholder_t<1>) {
    return [](auto mo) {
        return is_volatile(mo);
    };
}

consteval auto has_lvalueref_qualifier(placeholder_t<1>) {
    return [](auto mo) {
        return has_lvalueref_qualifier(mo);
    };
}

consteval auto has_rvalueref_qualifier(placeholder_t<1>) {
    return [](auto mo) {
        return has_rvalueref_qualifier(mo);
    };
}

consteval auto is_implicitly_declared(placeholder_t<1>) {
    return [](auto mo) {
        return is_implicitly_declared(mo);
    };
}

consteval auto is_defaulted(placeholder_t<1>) {
    return [](auto mo) {
        return is_defaulted(mo);
    };
}

consteval auto is_deleted(placeholder_t<1>) {
    return [](auto mo) {
        return is_deleted(mo);
    };
}

consteval auto is_copy_constructor(placeholder_t<1>) {
    return [](auto mo) {
        return is_copy_constructor(mo);
    };
}

consteval auto is_move_constructor(placeholder_t<1>) {
    return [](auto mo) {
        return is_move_constructor(mo);
    };
}

consteval auto is_copy_assignment_operator(placeholder_t<1>) {
    return [](auto mo) {
        return is_copy_assignment_operator(mo);
    };
}

consteval auto is_move_assignment_operator(placeholder_t<1>) {
    return [](auto mo) {
        return is_move_assignment_operator(mo);
    };
}

consteval auto is_empty(placeholder_t<1>) {
    return [](auto mo) {
        return is_empty(mo);
    };
}

// integer
consteval auto get_id(placeholder_t<1>) {
    return [](auto mo) {
        return get_id(mo);
    };
}

consteval auto get_source_line(placeholder_t<1>) {
    return [](auto mo) {
        return get_source_line(mo);
    };
}

consteval auto get_source_column(placeholder_t<1>) {
    return [](auto mo) {
        return get_source_column(mo);
    };
}

consteval auto get_size(placeholder_t<1>) {
    return [](auto mo) {
        return get_size(mo);
    };
}

consteval auto get_pointer(placeholder_t<1>) {
    return [](auto mo) {
        return get_pointer(mo);
    };
}

consteval auto get_constant(placeholder_t<1>) {
    return [](auto mo) {
        return get_constant(mo);
    };
}

// string
consteval auto get_source_file_name(placeholder_t<1>) {
    return [](auto mo) {
        return get_source_file_name(mo);
    };
}

consteval auto get_name(placeholder_t<1>) {
    return [](auto mo) {
        return get_name(mo);
    };
}

consteval auto get_display_name(placeholder_t<1>) {
    return [](auto mo) {
        return get_display_name(mo);
    };
}

// metaobject
consteval auto get_scope(placeholder_t<1>) {
    return [](auto mo) {
        return get_scope(mo);
    };
}

consteval auto get_type(placeholder_t<1>) {
    return [](auto mo) {
        return get_type(mo);
    };
}

consteval auto get_underlying_type(placeholder_t<1>) {
    return [](auto mo) {
        return get_underlying_type(mo);
    };
}

consteval auto get_aliased(placeholder_t<1>) {
    return [](auto mo) {
        return get_aliased(mo);
    };
}

consteval auto remove_all_aliases(placeholder_t<1>) {
    return [](auto mo) {
        return remove_all_aliases(mo);
    };
}

consteval auto get_class(placeholder_t<1>) {
    return [](auto mo) {
        return get_class(mo);
    };
}

consteval auto get_base_classes(placeholder_t<1>) {
    return [](auto mo) {
        return get_base_classes(mo);
    };
}

consteval auto get_member_types(placeholder_t<1>) {
    return [](auto mo) {
        return get_member_types(mo);
    };
}

consteval auto get_data_members(placeholder_t<1>) {
    return [](auto mo) {
        return get_data_members(mo);
    };
}

consteval auto get_member_functions(placeholder_t<1>) {
    return [](auto mo) {
        return get_member_functions(mo);
    };
}

consteval auto get_constructors(placeholder_t<1>) {
    return [](auto mo) {
        return get_constructors(mo);
    };
}

consteval auto get_destructors(placeholder_t<1>) {
    return [](auto mo) {
        return get_destructors(mo);
    };
}

consteval auto get_operators(placeholder_t<1>) {
    return [](auto mo) {
        return get_operators(mo);
    };
}

consteval auto get_enumerators(placeholder_t<1>) {
    return [](auto mo) {
        return get_enumerators(mo);
    };
}

consteval auto get_parameters(placeholder_t<1>) {
    return [](auto mo) {
        return get_parameters(mo);
    };
}

consteval auto get_captures(placeholder_t<1>) {
    return [](auto mo) {
        return get_captures(mo);
    };
}

consteval auto hide_private(placeholder_t<1>) {
    return [](auto mo) {
        return hide_private(mo);
    };
}

consteval auto hide_protected(placeholder_t<1>) {
    return [](auto mo) {
        return hide_protected(mo);
    };
}

consteval auto get_reflected_type(placeholder_t<1>) {
    return [](auto mo) {
        return get_reflected_type(mo);
    };
}

template <template <typename> class Transform>
consteval auto get_transformed_type(placeholder_t<1>) {
    return [](auto mo) {
        return get_transformed_type<Transform>(mo);
    };
}

template <typename T>
consteval auto is_type(placeholder_t<1>, type_identity<T> tid = {}) {
    return [tid](auto mo) {
        return is_type(mo, tid);
    };
}

template <typename T>
consteval auto has_type(placeholder_t<1>, type_identity<T> tid = {}) {
    return [tid](auto mo) {
        return has_type(mo, tid);
    };
}

} // namespace mirror

#endif // MIRROR_PLACEHOLDER_HPP
