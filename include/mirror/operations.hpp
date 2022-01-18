/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_OPERATIONS_HPP
#define MIRROR_OPERATIONS_HPP

#include "placeholder.hpp"
#include "traits.hpp"
#include <concepts>
#include <optional>

namespace mirror {

/// @brief Alias for object_trait.
/// @ingroup operations
/// @see operations_boolean
/// @see traits
using operation_boolean = object_trait;

/// @brief Alias for object_traits.
/// @ingroup classification
/// @see trait
/// @see operation_boolean
/// @see operation_integer
/// @see operation_pointer
/// @see operation_string
/// @see operation_metadata
using operations_boolean = bitfield<operation_boolean>;

/// @brief Enumeration of integer-returning unary operations applicable to metaobjects.
/// @ingroup operations
/// @see operation
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

/// @brief Enumeration of pointer-returning unary operations applicable to metaobjects.
/// @ingroup operations
/// @see operation
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
/// @see operation
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
    /// @brief Returns the debug-info (in JSON format) for a metaobject.
    get_debug_info = 1U << 0U,
    /// @brief Returns the user-friendly name of the reflected base-level entity.
    get_display_name = 1U << 1U,
    /// @brief Returns the unqualified "base name" of the reflected base-level entity.
    get_name = 1U << 2U,
    /// @brief Returns source file column of the reflected entity if available.
    get_source_file_name = 1U << 3U
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
/// @see operation
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

template <auto O>
struct map_operation;
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

MIRROR_IMPLEMENT_MAP_UNARY_OP(get_debug_info)
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
/// @brief Class unifying the operation_* enumerators.
/// @ingroup operations
/// @see operation_boolean
/// @see operation_integer
/// @see operation_pointer
/// @see operation_string
/// @see operation_metaobject
/// This class can be used to access the enumerators of the operation
/// enumerations. Instead of @c operation_boolean::op_name use simply
/// @c operation::op_name. Same for the enumerators from operation_integer,
/// operation_pointer, operation_string and operation_metaobject.
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

/// @brief Calls the specified function on each operation meta-enumerator
/// @ingroup operations
/// @see metaobject_operation
/// @see is_applicable
/// @see apply
template <typename F>
constexpr void for_each_metaobject_operation(F function) {
    for_each(all_metaobject_operation_kinds(), [&](auto muo) {
        for_each(get_enumerators(muo), function);
    });
}

} // namespace mirror

#endif
