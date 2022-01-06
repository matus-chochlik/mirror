/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_OPERATIONS_HPP
#define MIRROR_OPERATIONS_HPP

#include "bitfield.hpp"
#include "preprocessor.hpp"
#include "sequence.hpp"
#include "tribool.hpp"
#include <concepts>
#include <optional>

namespace mirror {

/// @brief Enumeration of boolean-returning unary operations applicable to metaobjects.
/// @ingroup operations
/// @see operation_integer
/// @see operation_pointer
/// @see operation_string
/// @see operation_metaobject
/// @see metaobject_ops_boolean
/// @see metaobject_operation
/// @see is_applicable
/// @see apply
/// @see try_apply
/// @see meta_traits
enum class operation_boolean : std::uint64_t {
    /// @brief Indicates if the reflected lambda closure's call operator is @c const.
    is_call_operator_const = 1ULL << 0ULL,
    /// @brief Indicates if the reflected member function is @c const.
    is_const = 1ULL << 1ULL,
    /// @brief Indicates if the reflected base-level entity is @c constexpr.
    is_constexpr = 1ULL << 2ULL,
    /// @brief Indicates if the reflected constructor is copy constructor.
    is_copy_constructor = 1ULL << 3ULL,
    /// @brief Indicates if the reflected operator is copy assignment operator.
    is_copy_assignment_operator = 1ULL << 4ULL,
    /// @brief Indicates if the reflected special member function is defaulted.
    is_defaulted = 1ULL << 5ULL,
    /// @brief Indicates if the reflected function is deleted.
    is_deleted = 1ULL << 6ULL,
    /// @brief Indicates if the metaobject sequence is empty.
    is_empty = 1ULL << 7ULL,
    /// @brief Indicates if the reflected base-level entity is an @c enum.
    is_enum = 1ULL << 8ULL,
    /// @brief Indicates if the reflected base-level entity is @c explicit.
    is_explicit = 1ULL << 9ULL,
    /// @brief Indicates if the reflected lambda capture is explicitly captured.
    is_explicitly_captured = 1ULL << 10ULL,
    /// @brief Indicates if the reflected base-level entity is @c final.
    is_final = 1ULL << 11ULL,
    /// @brief Indicates if the reflected special member function is implicitly declared.
    is_implicitly_declared = 1ULL << 12ULL,
    /// @brief Indicates if the reflected base-level entity is @c inline.
    is_inline = 1ULL << 13ULL,
    /// @brief Indicates if the reflected constructor is move constructor.
    is_move_constructor = 1ULL << 14ULL,
    /// @brief Indicates if the reflected operator is move assignment operator.
    is_move_assignment_operator = 1ULL << 15ULL,
    /// @brief Indicates if the reflected base-level entity is @c noexcept.
    is_noexcept = 1ULL << 16ULL,
    /// @brief Indicates if the reflected base-level entity is @c private.
    is_private = 1ULL << 17ULL,
    /// @brief Indicates if the reflected base-level entity is @c protected.
    is_protected = 1ULL << 18ULL,
    /// @brief Indicates if the reflected base-level entity is @c public.
    is_public = 1ULL << 19ULL,
    /// @brief Indicates if the reflected base-level entity is pure @c virtual.
    is_pure_virtual = 1ULL << 20ULL,
    /// @brief Indicates if the reflected base-level entity is a scoped @c enum.
    is_scoped_enum = 1ULL << 21ULL,
    /// @brief Indicates if the reflected base-level entity is @c static.
    is_static = 1ULL << 22ULL,
    /// @brief Indicates if the reflected base-level entity is @c thread_local.
    is_thread_local = 1ULL << 23ULL,
    /// @brief Indicates if the reflected base-level entity is an @c union.
    is_union = 1ULL << 24ULL,
    /// @brief Indicates if the reflected base-level entity is unnamed.
    is_unnamed = 1ULL << 25ULL,
    /// @brief Indicates if the reflected base-level entity is @c virtual.
    is_virtual = 1ULL << 26ULL,
    /// @brief Indicates if the reflected member function is @c volatile.
    is_volatile = 1ULL << 27ULL,
    /// @brief Indicates if the reflected function parameter has default argument.
    has_default_argument = 1ULL << 28ULL,
    /// @brief Indicates if the reflected member function has lvalue-ref qualifier.
    has_lvalueref_qualifier = 1ULL << 29ULL,
    /// @brief Indicates if the reflected member function has rvalue-ref qualifier.
    has_rvalueref_qualifier = 1ULL << 30ULL,
    /// @brief Indicates if the reflected record type uses a @c class specifier.
    uses_class_key = 1ULL << 31ULL,
    /// @brief Indicates if the reflected record type uses a @c struct specifier.
    uses_struct_key = 1ULL << 32ULL,
    /// @brief Indicates if the reflected lambda uses default capture by copy.
    uses_default_copy_capture = 1ULL << 33ULL,
    /// @brief Indicates if the reflected lambda uses default capture by reference.
    uses_default_reference_capture = 1ULL << 34ULL
};

/// @brief Bitfield of boolean-returning unary operations applicable to metaobjects.
/// @ingroup classification
/// @see operation_boolean
/// @see operations_integer
/// @see operations_pointer
/// @see operations_string
/// @see operations_metaobject
using operations_boolean = bitfield<operation_boolean>;

/// @brief Alias for operation_boolean.
/// @ingroup classification
/// @see operation_boolean
/// @see traits
using trait = operation_boolean;

/// @brief Alias for operations_boolean.
/// @ingroup classification
/// @see trait
/// @see operation_boolean
using traits = bitfield<trait>;

static constexpr auto
operator|(operation_boolean l, operation_boolean r) noexcept
  -> operations_boolean {
    return {l, r};
}

/// @brief Enumeration of integer-returning unary operations applicable to metaobjects.
/// @ingroup operations
/// @see operation_boolean
/// @see operation_pointer
/// @see operation_string
/// @see operation_metaobject
/// @see metaobject_operation
/// @see is_applicable
/// @see apply
/// @see try_apply
/// @see meta_traits
enum class operation_integer : unsigned {
    /// @brief Returns the value of the reflected base-level constant.
    get_constant = 1U << 0U,
    /// @brief Returns a pointer to the reflected base-level entity.
    get_size = 1U << 1U,
    /// @brief Returns source file column of the reflected entity if available.
    get_source_column = 1U << 2U,
    /// @brief Returns source file line of the reflected entity if available.
    get_source_line = 1U << 3U
};

/// @brief Bitfield of integer-returning unary operations applicable to metaobjects.
/// @ingroup classification
/// @see operation_integer
/// @see operations_boolean
/// @see operations_pointer
/// @see operations_string
/// @see operations_metaobject
using operations_integer = bitfield<operation_integer>;

static constexpr auto
operator|(operation_integer l, operation_integer r) noexcept
  -> operations_integer {
    return {l, r};
}

/// @brief Enumeration of pointer -returning unary operations applicable to metaobjects.
/// @ingroup operations
/// @see operation_boolean
/// @see operation_integer
/// @see operation_string
/// @see operation_metaobject
/// @see metaobject_operation
/// @see is_applicable
/// @see apply
/// @see try_apply
/// @see meta_traits
enum class operation_pointer : unsigned {
    /// @brief Returns a pointer to the reflected base-level entity.
    get_pointer = 1U << 0U
};

/// @brief Bitfield of pointer-returning unary operations applicable to metaobjects.
/// @ingroup classification
/// @see operation_pointer
/// @see operations_boolean
/// @see operations_integer
/// @see operations_string
/// @see operations_metaobject
using operations_pointer = bitfield<operation_pointer>;

static constexpr auto
operator|(operation_pointer l, operation_pointer r) noexcept
  -> operations_pointer {
    return {l, r};
}

/// @brief Enumeration of string-returning unary operations applicable to metaobjects.
/// @ingroup operations
/// @see operation_boolean
/// @see operation_integer
/// @see operation_pointer
/// @see operation_metaobject
/// @see metaobject_operation
/// @see is_applicable
/// @see apply
/// @see try_apply
/// @see meta_traits
enum class operation_string : unsigned {
    // string
    /// @brief Returns the user-friendly name of the reflected base-level entity.
    get_display_name = 1U << 0U,
    /// @brief Returns the unqualified "base name" of the reflected base-level entity.
    get_name = 1U << 1U,
    /// @brief Returns source file column of the reflected entity if available.
    get_source_file_name = 1U << 2U
};

/// @brief Bitfield of string-returning unary operations applicable to metaobjects.
/// @ingroup classification
/// @see operation_string
/// @see operations_boolean
/// @see operations_integer
/// @see operations_pointer
/// @see operations_metaobject
using operations_string = bitfield<operation_string>;

static constexpr auto operator|(operation_string l, operation_string r) noexcept
  -> operations_string {
    return {l, r};
}

/// @brief Enumeration of metaobject-returning unary operations applicable to metaobjects.
/// @ingroup operations
/// @see operation_boolean
/// @see operation_integer
/// @see operation_pointer
/// @see operation_string
/// @see metaobject_operation
/// @see is_applicable
/// @see apply
/// @see try_apply
/// @see meta_traits
enum class operation_metaobject : std::uint64_t {
    /// @brief Returns a reflection of the aliased entity reflected by a reflected alias.
    get_aliased = 1ULL << 0ULL,
    /// @brief Returns a sequence of base class specifier reflections of a reflected class.
    get_base_classes = 1ULL << 1ULL,
    /// @brief Returns the reflection of the sub-expression of a parenthesized expression.
    get_callable = 1ULL << 2ULL,
    /// @brief Returns a sequence of capture reflections of a reflected closure.
    get_captures = 1ULL << 3ULL,
    /// @brief Returns a sequence of member type reflections of a reflected class.
    get_data_members = 1ULL << 4ULL,
    /// @brief Returns the reflection of the class in a reflected base class specifier.
    get_class = 1ULL << 5ULL,
    /// @brief Returns a sequence of constructor reflections of a reflected class.
    get_constructors = 1ULL << 6ULL,
    /// @brief Returns a sequence of destructors reflections of a reflected class.
    get_destructors = 1ULL << 7ULL,
    /// @brief Returns a sequence of member function reflections of a reflected class.
    get_member_functions = 1ULL << 8ULL,
    /// @brief Returns a sequence of member type reflections of a reflected class.
    get_member_types = 1ULL << 9ULL,
    /// @brief Returns a sequence of operator reflections of a reflected class.
    get_operators = 1ULL << 10ULL,
    /// @brief Returns a sequence of parameter reflections of a reflected callable.
    get_parameters = 1ULL << 11ULL,
    /// @brief Returns a sequence of enumerator reflections of a reflected enum.
    get_enumerators = 1ULL << 12ULL,
    /// @brief Returns the reflection of the scope in a reflected entity.
    get_scope = 1ULL << 13ULL,
    /// @brief Returns a reflection of the scope of a reflected scope member.
    get_subexpression = 1ULL << 14ULL,
    /// @brief Returns a reflection of the type of a reflected typed entity.
    get_type = 1ULL << 15ULL,
    /// @brief Returns a reflection of the underlying type of a reflected enum,
    get_underlying_type = 1ULL << 16ULL,
    /// @brief Returns a sequence with private elements filtered out.
    hide_private = 1ULL << 17ULL,
    /// @brief Returns a sequence with private and protected elements filtered out.
    hide_protected = 1ULL << 18ULL
};

/// @brief Bitfield of metaobject-returning unary operations applicable to metaobjects.
/// @ingroup classification
/// @see operation_metaobject
/// @see operations_boolean
/// @see operations_integer
/// @see operations_pointer
/// @see operations_metaobject
using operations_metaobject = bitfield<operation_metaobject>;

static constexpr auto
operator|(operation_metaobject l, operation_metaobject r) noexcept
  -> operations_metaobject {
    return {l, r};
}

/// @brief Unary metaobject operation enumeration type.
/// @ingroup operations
/// @see operation_boolean
/// @see operation_integer
/// @see operation_pointer
/// @see operation_string
/// @see operation_metaobject
template <typename T>
concept metaobject_operation =
  (std::same_as<T, operation_boolean> || std::same_as<T, operation_integer> ||
   std::same_as<T, operation_pointer> || std::same_as<T, operation_string> ||
   std::same_as<T, operation_metaobject>);

template <metaobject_operation auto O>
struct map_operation;

#define MIRROR_IMPLEMENT_MAP_UNARY_OP(NAME)                                  \
    template <>                                                              \
    struct map_operation<operation_boolean::NAME> {                          \
        template <__metaobject_id M>                                         \
        static consteval auto is_applicable(wrapped_metaobject<M>) -> bool { \
            return MIRROR_JOIN(__metaobject_, NAME)(bool, M);                \
        }                                                                    \
        template <__metaobject_id M>                                         \
        static consteval auto apply(wrapped_metaobject<M>) -> bool {         \
            return MIRROR_JOIN(__metaobject_, NAME)(M);                      \
        }                                                                    \
        static constexpr auto make_optional(bool v) -> tribool {             \
            return {v};                                                      \
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

#define MIRROR_IMPLEMENT_MAP_UNARY_OP(NAME)                                  \
    template <>                                                              \
    struct map_operation<operation_integer::NAME> {                          \
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
//------------------------------------------------------------------------------
#define MIRROR_IMPLEMENT_MAP_UNARY_OP(NAME)                                   \
    template <>                                                               \
    struct map_operation<operation_string::NAME> {                            \
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
//------------------------------------------------------------------------------
/// @brief Indicates if the specified operation is applicable to metaobject.
/// @ingroup operations
/// @see operation_boolean
/// @see operation_integer
/// @see operation_pointer
/// @see operation_string
/// @see operation_metaobject
/// @see metaobject_operation
/// @see apply
/// @see try_apply
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

/// @brief Calls the specified unary operation on a metaobject.
/// @ingroup operations
/// @see operation_boolean
/// @see operation_integer
/// @see operation_pointer
/// @see operation_string
/// @see operation_metaobject
/// @see metaobject_operation
/// @see is_applicable
/// @see try_apply
template <metaobject_operation auto O, __metaobject_id M>
constexpr auto apply(wrapped_metaobject<M> mo) noexcept
  requires(is_applicable(mo)) {
    return map_operation<O>::apply(mo);
}

/// @brief Calls the specified unary operation on a metaobject if it's applicable.
/// @ingroup operations
/// @see operation_boolean
/// @see operation_integer
/// @see operation_pointer
/// @see operation_string
/// @see operation_metaobject
/// @see metaobject_operation
/// @see is_applicable
/// @see apply
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

/// @brief Calls the specified function on each operation meta-enumerator
/// @ingroup operations
/// @see metaobject_operation
/// @see is_applicable
/// @see apply
template <typename F>
constexpr void for_each_metaobject_operation(F function) {
    for_each(
      make_sequence(
        mirror(mirror::operation_boolean),
        mirror(mirror::operation_integer),
        mirror(mirror::operation_pointer),
        mirror(mirror::operation_string),
        mirror(mirror::operation_metaobject)),
      [&](auto muo) { for_each(get_enumerators(muo), function); });
}

} // namespace mirror

#endif
