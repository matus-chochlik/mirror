/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_OPERATIONS_HPP
#define MIRROR_OPERATIONS_HPP

#include "primitives.hpp"
#include <optional>

namespace mirror {

enum class metaobject_unary_op {
    is_call_operator_const,
    is_const,
    is_constexpr,
    is_copy_constructor,
    is_copy_assignment_operator,
    is_defaulted,
    is_deleted,
    is_empty,
    is_enum,
    is_explicit,
    is_explicitly_captured,
    is_final,
    is_implicitly_declared,
    is_inline,
    is_move_constructor,
    is_move_assignment_operator,
    is_noexcept,
    is_private,
    is_protected,
    is_public,
    is_pure_virtual,
    is_scoped_enum,
    is_static,
    is_thread_local,
    is_union,
    is_unnamed,
    is_virtual,
    is_volatile,
    has_default_argument,
    has_lvalueref_qualifier,
    has_rvalueref_qualifier,
    hide_private,
    hide_protected,
    uses_class_key,
    uses_struct_key,
    uses_default_copy_capture,
    uses_default_reference_capture
};

template <metaobject_unary_op>
struct map_unary_op;

#define MIRROR_IMPLEMENT_MAP_UNARY_OP(NAME)                               \
    template <>                                                           \
    struct map_unary_op<metaobject_unary_op::NAME> {                      \
        using result_type = bool;                                         \
        static consteval auto is_applicable(__metaobject_id mi) -> bool { \
            return __metaobject_##NAME(bool, mi);                         \
        }                                                                 \
        static consteval auto apply(__metaobject_id mi) -> bool {         \
            return __metaobject_##NAME(mi);                               \
        }                                                                 \
    };

MIRROR_IMPLEMENT_MAP_UNARY_OP(is_call_operator_const)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_const)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_constexpr)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_copy_constructor)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_copy_assignment_operator)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_defaulted)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_deleted)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_empty)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_enum)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_explicit)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_explicitly_captured)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_final)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_implicitly_declared)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_inline)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_move_constructor)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_move_assignment_operator)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_noexcept)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_private)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_protected)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_public)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_pure_virtual)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_scoped_enum)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_static)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_thread_local)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_union)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_unnamed)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_virtual)
MIRROR_IMPLEMENT_MAP_UNARY_OP(is_volatile)
MIRROR_IMPLEMENT_MAP_UNARY_OP(has_default_argument)
MIRROR_IMPLEMENT_MAP_UNARY_OP(has_lvalueref_qualifier)
MIRROR_IMPLEMENT_MAP_UNARY_OP(has_rvalueref_qualifier)
MIRROR_IMPLEMENT_MAP_UNARY_OP(hide_private)
MIRROR_IMPLEMENT_MAP_UNARY_OP(hide_protected)
MIRROR_IMPLEMENT_MAP_UNARY_OP(uses_class_key)
MIRROR_IMPLEMENT_MAP_UNARY_OP(uses_struct_key)
MIRROR_IMPLEMENT_MAP_UNARY_OP(uses_default_copy_capture)
MIRROR_IMPLEMENT_MAP_UNARY_OP(uses_default_reference_capture)

#undef MIRROR_IMPLEMENT_MAP_UNARY_OP

template <metaobject_unary_op O, __metaobject_id M>
constexpr auto is_applicable(wrapped_metaobject<M>) noexcept {
    return map_unary_op<O>::is_applicable(M);
}

template <metaobject_unary_op O, __metaobject_id M>
constexpr auto apply(wrapped_metaobject<M> mo) noexcept
  requires(is_applicable(mo)) {
    return map_unary_op<O>::apply(M);
}

template <metaobject_unary_op O, __metaobject_id M>
constexpr auto try_apply(wrapped_metaobject<M> mo) noexcept
  -> std::optional<typename map_unary_op<O>::result_type> {
    if constexpr(is_applicable<O>(mo)) {
        return {map_unary_op<O>::apply(M)};
    }
    return {};
}

} // namespace mirror

#endif
