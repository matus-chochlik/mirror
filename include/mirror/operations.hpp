/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_OPERATIONS_HPP
#define MIRROR_OPERATIONS_HPP

#include "preprocessor.hpp"
#include "primitives.hpp"
#include <optional>

namespace mirror {

enum class metaobject_unary_op {
    // boolean
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
    uses_class_key,
    uses_struct_key,
    uses_default_copy_capture,
    uses_default_reference_capture,
    // integral/constant/pointer
    get_constant,
    get_pointer,
    get_size,
    get_source_column,
    get_source_line,
    // string
    get_display_name,
    get_name,
    get_source_file_name,
    // metaobject
    get_aliased,
    get_base_classes,
    get_callable,
    get_captures,
    get_data_members,
    get_class,
    get_constructors,
    get_destructors,
    get_member_functions,
    get_member_types,
    get_operators,
    get_parameters,
    get_scope,
    get_subexpression,
    get_type,
    get_underlying_type,
    hide_private,
    hide_protected
};

template <metaobject_unary_op>
struct map_unary_op;

#define MIRROR_IMPLEMENT_MAP_UNARY_OP(NAME)                                  \
    template <>                                                              \
    struct map_unary_op<metaobject_unary_op::NAME> {                         \
        using result_type = bool;                                            \
        template <__metaobject_id M>                                         \
        static consteval auto is_applicable(wrapped_metaobject<M>) -> bool { \
            return MIRROR_JOIN(__metaobject_, NAME)(bool, M);                \
        }                                                                    \
        template <__metaobject_id M>                                         \
        static consteval auto apply(wrapped_metaobject<M>) -> bool {         \
            return MIRROR_JOIN(__metaobject_, NAME)(M);                      \
        }                                                                    \
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
MIRROR_IMPLEMENT_MAP_UNARY_OP(uses_class_key)
MIRROR_IMPLEMENT_MAP_UNARY_OP(uses_struct_key)
MIRROR_IMPLEMENT_MAP_UNARY_OP(uses_default_copy_capture)
MIRROR_IMPLEMENT_MAP_UNARY_OP(uses_default_reference_capture)

#undef MIRROR_IMPLEMENT_MAP_UNARY_OP
//------------------------------------------------------------------------------
template <>
struct map_unary_op<metaobject_unary_op::get_constant> {
    using result_type = std::uintmax_t;
    template <__metaobject_id M>
    static consteval auto is_applicable(wrapped_metaobject<M>) -> bool {
        return __metaobject_get_constant(bool, M);
    }
    template <__metaobject_id M>
    static consteval auto apply(wrapped_metaobject<M>) {
        return _get_constant<M>::value;
    }
};

template <>
struct map_unary_op<metaobject_unary_op::get_pointer> {
    using result_type = std::uintmax_t;
    template <__metaobject_id M>
    static consteval auto is_applicable(wrapped_metaobject<M>) -> bool {
        return __metaobject_get_pointer(bool, M);
    }
    template <__metaobject_id M>
    static consteval auto apply(wrapped_metaobject<M>) {
        return _get_pointer<M>::value;
    }
};

#define MIRROR_IMPLEMENT_MAP_UNARY_OP(NAME)                                  \
    template <>                                                              \
    struct map_unary_op<metaobject_unary_op::NAME> {                         \
        using result_type = size_t;                                          \
        template <__metaobject_id M>                                         \
        static consteval auto is_applicable(wrapped_metaobject<M>) -> bool { \
            return MIRROR_JOIN(__metaobject_, NAME)(bool, M);                \
        }                                                                    \
        template <__metaobject_id M>                                         \
        static consteval auto apply(wrapped_metaobject<M>) -> size_t {       \
            return MIRROR_JOIN(__metaobject_, NAME)(M);                      \
        }                                                                    \
    };

MIRROR_IMPLEMENT_MAP_UNARY_OP(get_size)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_source_column)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_source_line)

#undef MIRROR_IMPLEMENT_MAP_UNARY_OP
//------------------------------------------------------------------------------
#define MIRROR_IMPLEMENT_MAP_UNARY_OP(NAME)                                  \
    template <>                                                              \
    struct map_unary_op<metaobject_unary_op::NAME> {                         \
        using result_type = std::string_view;                                \
        template <__metaobject_id M>                                         \
        static consteval auto is_applicable(wrapped_metaobject<M>) -> bool { \
            return MIRROR_JOIN(__metaobject_, NAME)(bool, M);                \
        }                                                                    \
        template <__metaobject_id M>                                         \
        static consteval auto apply(wrapped_metaobject<M>)                   \
          -> std::string_view {                                              \
            return MIRROR_JOIN(NAME, _view)(M);                              \
        }                                                                    \
    };

MIRROR_IMPLEMENT_MAP_UNARY_OP(get_display_name)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_name)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_source_file_name)

#undef MIRROR_IMPLEMENT_MAP_UNARY_OP
//------------------------------------------------------------------------------
#define MIRROR_IMPLEMENT_MAP_UNARY_OP(NAME)                                   \
    template <>                                                               \
    struct map_unary_op<metaobject_unary_op::NAME> {                          \
        using result_type = decltype(no_metaobject);                          \
        template <__metaobject_id M>                                          \
        static consteval auto is_applicable(wrapped_metaobject<M>) -> bool {  \
            return MIRROR_JOIN(__metaobject_, NAME)(bool, M);                 \
        }                                                                     \
        template <__metaobject_id M>                                          \
        static consteval auto apply(wrapped_metaobject<M>) {                  \
            return wrapped_metaobject<MIRROR_JOIN(__metaobject_, NAME)(M)>{}; \
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
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_scope)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_subexpression)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_type)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_underlying_type)
MIRROR_IMPLEMENT_MAP_UNARY_OP(hide_private)
MIRROR_IMPLEMENT_MAP_UNARY_OP(hide_protected)

#undef MIRROR_IMPLEMENT_MAP_UNARY_OP
//------------------------------------------------------------------------------
template <metaobject_unary_op O, __metaobject_id M>
constexpr auto is_applicable(wrapped_metaobject<M> mo) noexcept {
    return map_unary_op<O>::is_applicable(mo);
}

template <metaobject_unary_op O, __metaobject_id M>
constexpr auto apply(wrapped_metaobject<M> mo) noexcept
  requires(is_applicable(mo)) {
    return map_unary_op<O>::apply(mo);
}

template <metaobject_unary_op O, __metaobject_id M>
constexpr auto try_apply(wrapped_metaobject<M> mo) noexcept {
    if constexpr(is_applicable<O>(mo)) {
        return std::optional{map_unary_op<O>::apply(mo)};
    } else {
        return std::optional<typename map_unary_op<O>::result_type>{};
    }
}

} // namespace mirror

#endif
