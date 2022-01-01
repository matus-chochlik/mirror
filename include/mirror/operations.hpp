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
#include "sequence.hpp"
#include "tribool.hpp"
#include <concepts>
#include <optional>

namespace mirror {

/// @brief Enumeration of boolean-returning unary operations applicable to metaobjects.
/// @ingroup operations
/// @see unary_op_integer
/// @see unary_op_pointer
/// @see unary_op_string
/// @see unary_op_metaobject
/// @see metaobject_unary_op
/// @see is_applicable
/// @see apply
/// @see try_apply
/// @see metaobject_traits
enum class unary_op_boolean {
    /// @brief Indicates if the reflected lambda closure's call operator is @c const.
    is_call_operator_const,
    /// @brief Indicates if the reflected member function is @c const.
    is_const,
    /// @brief Indicates if the reflected base-level entity is @c constexpr.
    is_constexpr,
    /// @brief Indicates if the reflected constructor is copy constructor.
    is_copy_constructor,
    /// @brief Indicates if the reflected operator is copy assignment operator.
    is_copy_assignment_operator,
    /// @brief Indicates if the reflected special member function is defaulted.
    is_defaulted,
    /// @brief Indicates if the reflected function is deleted.
    is_deleted,
    /// @brief Indicates if the metaobject sequence is empty.
    is_empty,
    /// @brief Indicates if the reflected base-level entity is an @c enum.
    is_enum,
    /// @brief Indicates if the reflected base-level entity is @c explicit.
    is_explicit,
    /// @brief Indicates if the reflected lambda capture is explicitly captured.
    is_explicitly_captured,
    /// @brief Indicates if the reflected base-level entity is @c final.
    is_final,
    /// @brief Indicates if the reflected special member function is implicitly declared.
    is_implicitly_declared,
    /// @brief Indicates if the reflected base-level entity is @c inline.
    is_inline,
    /// @brief Indicates if the reflected constructor is move constructor.
    is_move_constructor,
    /// @brief Indicates if the reflected operator is move assignment operator.
    is_move_assignment_operator,
    /// @brief Indicates if the reflected base-level entity is @c noexcept.
    is_noexcept,
    /// @brief Indicates if the reflected base-level entity is @c private.
    is_private,
    /// @brief Indicates if the reflected base-level entity is @c protected.
    is_protected,
    /// @brief Indicates if the reflected base-level entity is @c public.
    is_public,
    /// @brief Indicates if the reflected base-level entity is pure @c virtual.
    is_pure_virtual,
    /// @brief Indicates if the reflected base-level entity is a scoped @c enum.
    is_scoped_enum,
    /// @brief Indicates if the reflected base-level entity is @c static.
    is_static,
    /// @brief Indicates if the reflected base-level entity is @c thread_local.
    is_thread_local,
    /// @brief Indicates if the reflected base-level entity is an @c union.
    is_union,
    /// @brief Indicates if the reflected base-level entity is unnamed.
    is_unnamed,
    /// @brief Indicates if the reflected base-level entity is @c virtual.
    is_virtual,
    /// @brief Indicates if the reflected member function is @c volatile.
    is_volatile,
    /// @brief Indicates if the reflected function parameter has default argument.
    has_default_argument,
    /// @brief Indicates if the reflected member function has lvalue-ref qualifier.
    has_lvalueref_qualifier,
    /// @brief Indicates if the reflected member function has rvalue-ref qualifier.
    has_rvalueref_qualifier,
    /// @brief Indicates if the reflected record type uses a @c class specifier.
    uses_class_key,
    /// @brief Indicates if the reflected record type uses a @c struct specifier.
    uses_struct_key,
    /// @brief Indicates if the reflected lambda uses default capture by copy.
    uses_default_copy_capture,
    /// @brief Indicates if the reflected lambda uses default capture by reference.
    uses_default_reference_capture
};

/// @brief Enumeration of integer-returning unary operations applicable to metaobjects.
/// @ingroup operations
/// @see unary_op_boolean
/// @see unary_op_pointer
/// @see unary_op_string
/// @see unary_op_metaobject
/// @see metaobject_unary_op
/// @see is_applicable
/// @see apply
/// @see try_apply
/// @see metaobject_traits
enum class unary_op_integer {
    /// @brief Returns the value of the reflected base-level constant.
    get_constant,
    /// @brief Returns a pointer to the reflected base-level entity.
    get_size,
    /// @brief Returns source file column of the reflected entity if available.
    get_source_column,
    /// @brief Returns source file line of the reflected entity if available.
    get_source_line
};

/// @brief Enumeration of pointer -returning unary operations applicable to metaobjects.
/// @ingroup operations
/// @see unary_op_boolean
/// @see unary_op_integer
/// @see unary_op_string
/// @see unary_op_metaobject
/// @see metaobject_unary_op
/// @see is_applicable
/// @see apply
/// @see try_apply
/// @see metaobject_traits
enum class unary_op_pointer {
    /// @brief Returns a pointer to the reflected base-level entity.
    get_pointer
};

/// @brief Enumeration of string-returning unary operations applicable to metaobjects.
/// @ingroup operations
/// @see unary_op_boolean
/// @see unary_op_integer
/// @see unary_op_pointer
/// @see unary_op_metaobject
/// @see metaobject_unary_op
/// @see is_applicable
/// @see apply
/// @see try_apply
/// @see metaobject_traits
enum class unary_op_string {
    // string
    /// @brief Returns the user-friendly name of the reflected base-level entity.
    get_display_name,
    /// @brief Returns the unqualified "base name" of the reflected base-level entity.
    get_name,
    /// @brief Returns source file column of the reflected entity if available.
    get_source_file_name
};

/// @brief Enumeration of metaobject-returning unary operations applicable to metaobjects.
/// @ingroup operations
/// @see unary_op_boolean
/// @see unary_op_integer
/// @see unary_op_pointer
/// @see unary_op_string
/// @see metaobject_unary_op
/// @see is_applicable
/// @see apply
/// @see try_apply
/// @see metaobject_traits
enum class unary_op_metaobject {
    /// @brief Returns a reflection of the aliased entity reflected by a reflected alias.
    get_aliased,
    /// @brief Returns a sequence of base class specifier reflections of a reflected class.
    get_base_classes,
    /// @brief Returns the reflection of the sub-expression of a parenthesized expression.
    get_callable,
    /// @brief Returns a sequence of capture reflections of a reflected closure.
    get_captures,
    /// @brief Returns a sequence of member type reflections of a reflected class.
    get_data_members,
    /// @brief Returns the reflection of the class in a reflected base class specifier.
    get_class,
    /// @brief Returns a sequence of constructor reflections of a reflected class.
    get_constructors,
    /// @brief Returns a sequence of destructors reflections of a reflected class.
    get_destructors,
    /// @brief Returns a sequence of member function reflections of a reflected class.
    get_member_functions,
    /// @brief Returns a sequence of member type reflections of a reflected class.
    get_member_types,
    /// @brief Returns a sequence of operator reflections of a reflected class.
    get_operators,
    /// @brief Returns a sequence of parameter reflections of a reflected callable.
    get_parameters,
    get_scope,
    /// @brief Returns a reflection of the scope of a reflected scope member.
    get_subexpression,
    /// @brief Returns a reflection of the type of a reflected typed entity.
    get_type,
    /// @brief Returns a reflection of the underlying type of a reflected enum,
    get_underlying_type,
    /// @brief Returns a sequence with private elements filtered out.
    hide_private,
    /// @brief Returns a sequence with private and protected elements filtered out.
    hide_protected
};

/// @brief Unary metaobject operation enumeration type.
/// @ingroup operations
/// @see unary_op_boolean
/// @see unary_op_integer
/// @see unary_op_pointer
/// @see unary_op_string
/// @see unary_op_metaobject
template <typename T>
concept metaobject_unary_op =
  (std::same_as<T, unary_op_boolean> || std::same_as<T, unary_op_integer> ||
   std::same_as<T, unary_op_pointer> || std::same_as<T, unary_op_string> ||
   std::same_as<T, unary_op_metaobject>);

template <metaobject_unary_op auto O>
struct map_unary_op;

#define MIRROR_IMPLEMENT_MAP_UNARY_OP(NAME)                                  \
    template <>                                                              \
    struct map_unary_op<unary_op_boolean::NAME> {                            \
        template <__metaobject_id M>                                         \
        static consteval auto is_applicable(wrapped_metaobject<M>) -> bool { \
            return MIRROR_JOIN(__metaobject_, NAME)(bool, M);                \
        }                                                                    \
        template <__metaobject_id M>                                         \
        static consteval auto apply(wrapped_metaobject<M>) -> bool {         \
            return MIRROR_JOIN(__metaobject_, NAME)(M);                      \
        }                                                                    \
        static constexpr auto make_optional(bool v) -> tribool {             \
            return v;                                                        \
        }                                                                    \
        static constexpr auto fallback() -> tribool {                        \
            return indeterminate;                                            \
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
struct map_unary_op<unary_op_integer::get_constant> {
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

#define MIRROR_IMPLEMENT_MAP_UNARY_OP(NAME)                                  \
    template <>                                                              \
    struct map_unary_op<unary_op_integer::NAME> {                            \
        template <__metaobject_id M>                                         \
        static consteval auto is_applicable(wrapped_metaobject<M>) -> bool { \
            return MIRROR_JOIN(__metaobject_, NAME)(bool, M);                \
        }                                                                    \
        template <__metaobject_id M>                                         \
        static consteval auto apply(wrapped_metaobject<M>) -> size_t {       \
            return MIRROR_JOIN(__metaobject_, NAME)(M);                      \
        }                                                                    \
        static constexpr auto make_optional(size_t v)                        \
          -> std::optional<size_t> {                                         \
            return {v};                                                      \
        }                                                                    \
        static constexpr auto fallback() -> std::optional<size_t> {          \
            return {};                                                       \
        }                                                                    \
    };

MIRROR_IMPLEMENT_MAP_UNARY_OP(get_size)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_source_column)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_source_line)

#undef MIRROR_IMPLEMENT_MAP_UNARY_OP

template <>
struct map_unary_op<unary_op_pointer::get_pointer> {
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
//------------------------------------------------------------------------------
#define MIRROR_IMPLEMENT_MAP_UNARY_OP(NAME)                                   \
    template <>                                                               \
    struct map_unary_op<unary_op_string::NAME> {                              \
        template <__metaobject_id M>                                          \
        static consteval auto is_applicable(wrapped_metaobject<M>) -> bool {  \
            return MIRROR_JOIN(__metaobject_, NAME)(bool, M);                 \
        }                                                                     \
        template <__metaobject_id M>                                          \
        static consteval auto apply(wrapped_metaobject<M>)                    \
          -> std::string_view {                                               \
            return MIRROR_JOIN(NAME, _view)(M);                               \
        }                                                                     \
        static constexpr auto make_optional(std::string_view v)               \
          -> std::optional<std::string_view> {                                \
            return {v};                                                       \
        }                                                                     \
        static constexpr auto fallback() -> std::optional<std::string_view> { \
            return {};                                                        \
        }                                                                     \
    };

MIRROR_IMPLEMENT_MAP_UNARY_OP(get_display_name)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_name)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_source_file_name)

#undef MIRROR_IMPLEMENT_MAP_UNARY_OP
//------------------------------------------------------------------------------
#define MIRROR_IMPLEMENT_MAP_UNARY_OP(NAME)                                   \
    template <>                                                               \
    struct map_unary_op<unary_op_metaobject::NAME> {                          \
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
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_scope)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_subexpression)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_type)
MIRROR_IMPLEMENT_MAP_UNARY_OP(get_underlying_type)
MIRROR_IMPLEMENT_MAP_UNARY_OP(hide_private)
MIRROR_IMPLEMENT_MAP_UNARY_OP(hide_protected)

#undef MIRROR_IMPLEMENT_MAP_UNARY_OP
//------------------------------------------------------------------------------
/// @brief Indicates if the specified operation is applicable to metaobject.
/// @ingroup operations
/// @see unary_op_boolean
/// @see unary_op_integer
/// @see unary_op_pointer
/// @see unary_op_string
/// @see unary_op_metaobject
/// @see metaobject_unary_op
/// @see apply
/// @see try_apply
template <metaobject_unary_op auto O, __metaobject_id M>
constexpr auto is_applicable(wrapped_metaobject<M> mo) noexcept -> bool {
    return map_unary_op<O>::is_applicable(mo);
}

/// @brief Calls the specified unary operation on a metaobject.
/// @ingroup operations
/// @see unary_op_boolean
/// @see unary_op_integer
/// @see unary_op_pointer
/// @see unary_op_string
/// @see unary_op_metaobject
/// @see metaobject_unary_op
/// @see is_applicable
/// @see try_apply
template <metaobject_unary_op auto O, __metaobject_id M>
constexpr auto apply(wrapped_metaobject<M> mo) noexcept
  requires(is_applicable(mo)) {
    return map_unary_op<O>::apply(mo);
}

/// @brief Calls the specified unary operation on a metaobject if it's applicable.
/// @ingroup operations
/// @see unary_op_boolean
/// @see unary_op_integer
/// @see unary_op_pointer
/// @see unary_op_string
/// @see unary_op_metaobject
/// @see metaobject_unary_op
/// @see is_applicable
/// @see apply
template <metaobject_unary_op auto O, __metaobject_id M>
constexpr auto try_apply(wrapped_metaobject<M> mo) noexcept {
    using op = map_unary_op<O>;
    if constexpr(op::is_applicable(mo)) {
        return op::make_optional(op::apply(mo));
    } else {
        return op::fallback();
    }
}

/// @brief Calls the specified function on each unary_op meta-enumerator
/// @ingroup operations
/// @see metaobject_unary_op
/// @see is_applicable
/// @see apply
template <typename F>
constexpr void for_each_metaobject_unary_op(F function) {
    for_each(
      make_sequence(
        mirror(mirror::unary_op_boolean),
        mirror(mirror::unary_op_integer),
        mirror(mirror::unary_op_pointer),
        mirror(mirror::unary_op_string),
        mirror(mirror::unary_op_metaobject)),
      [&](auto muo) { for_each(get_enumerators(muo), function); });
}

} // namespace mirror

#endif
