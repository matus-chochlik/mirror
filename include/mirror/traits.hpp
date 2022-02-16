/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_TRAITS_HPP
#define MIRROR_TRAITS_HPP

#include "bitfield.hpp"
#include "preprocessor.hpp"
#include "sequence.hpp"
#include "tribool.hpp"
#include <cstdint>
#include <type_traits>

namespace mirror {

template <auto O>
struct map_operation;

/// @brief Enumeration of metaobject trait operations.
/// @ingroup classification
/// @see meta_traits
/// @see has_trait
/// @see metaobject_operation
enum class meta_trait : std::uint64_t {
    /// @brief Indicates if the argument is a metaobject.
    /// @see mirror::reflects_object
    reflects_object = 1ULL << 0ULL,
    /// @brief Indicates if the argument reflects a sequence of metaobjects.
    /// @see mirror::reflects_object_sequence
    reflects_object_sequence = 1ULL << 1ULL,
    /// @brief Indicates if a metaobject reflects a named base-level entity.
    /// @see mirror::reflects_named
    reflects_named = 1ULL << 2ULL,
    /// @brief Indicates if a metaobject reflects a base-level alias.
    /// @see mirror::reflects_alias
    reflects_alias = 1ULL << 3ULL,
    /// @brief Indicates if a metaobject reflects a base-level entity with a type.
    /// @see mirror::reflects_typed
    reflects_typed = 1ULL << 4ULL,
    /// @brief Indicates if a metaobject reflects a base-level scope.
    /// @see mirror::reflects_scope
    reflects_scope = 1ULL << 5ULL,
    /// @brief Indicates if a metaobject reflects a base-level scope member.
    /// @see mirror::reflects_scope_member
    reflects_scope_member = 1ULL << 6ULL,
    /// @brief Indicates if a metaobject reflects an enumerator.
    /// @see mirror::reflects_enumerator
    reflects_enumerator = 1ULL << 7ULL,
    /// @brief Indicates if a metaobject reflects a record member.
    /// @see mirror::reflects_record_member
    reflects_record_member = 1ULL << 8ULL,
    /// @brief Indicates if a metaobject reflects a base class specifier.
    /// @see mirror::reflects_base
    reflects_base = 1ULL << 9ULL,
    /// @brief Indicates if a metaobject reflects a namespace.
    /// @see mirror::reflects_namespace
    reflects_namespace = 1ULL << 10ULL,
    /// @brief Indicates if a metaobject reflects the global scope.
    /// @see mirror::reflects_global_scope
    reflects_global_scope = 1ULL << 11ULL,
    /// @brief Indicates if a metaobject reflects a type.
    /// @see mirror::reflects_type
    reflects_type = 1ULL << 12ULL,
    /// @brief Indicates if a metaobject reflects an enumeration type.
    /// @see mirror::reflects_enum
    reflects_enum = 1ULL << 13ULL,
    /// @brief Indicates if a metaobject reflects a record types (union or class).
    /// @see mirror::reflects_record
    reflects_record = 1ULL << 14ULL,
    /// @brief Indicates if a metaobject reflects a class.
    /// @see mirror::reflects_class
    reflects_class = 1ULL << 15ULL,
    /// @brief Indicates if a metaobject reflects a lambda closure type.
    /// @see mirror::reflects_lambda
    reflects_lambda = 1ULL << 16ULL,
    /// @brief Indicates if a metaobject reflects a constant.
    /// @see mirror::reflects_constant
    reflects_constant = 1ULL << 17ULL,
    /// @brief Indicates if a metaobject reflects a variable.
    /// @see mirror::reflects_variable
    reflects_variable = 1ULL << 18ULL,
    /// @brief Indicates if a metaobject reflects a lambda capture.
    /// @see mirror::reflects_lambda_capture
    reflects_lambda_capture = 1ULL << 19ULL,
    /// @brief Indicates if a metaobject reflects a function parameter.
    /// @see mirror::reflects_function_parameter
    reflects_function_parameter = 1ULL << 20ULL,
    /// @brief Indicates if a metaobject reflects a callable base-level entity.
    /// @see mirror::reflects_callable
    reflects_callable = 1ULL << 21ULL,
    /// @brief Indicates if a metaobject reflects a function.
    /// @see mirror::reflects_function
    reflects_function = 1ULL << 22ULL,
    /// @brief Indicates if a metaobject reflects a record member function.
    /// @see mirror::reflects_member_function
    reflects_member_function = 1ULL << 23ULL,
    /// @brief Indicates if a metaobject reflects a special member function.
    /// @see mirror::reflects_special_member_function
    reflects_special_member_function = 1ULL << 24ULL,
    /// @brief Indicates if a metaobject reflects a constructor.
    /// @see mirror::reflects_constructor
    reflects_constructor = 1ULL << 25ULL,
    /// @brief Indicates if a metaobject reflects a destructor.
    /// @see mirror::reflects_destructor
    reflects_destructor = 1ULL << 26ULL,
    /// @brief Indicates if a metaobject reflects an operator.
    /// @see mirror::reflects_operator
    reflects_operator = 1ULL << 27ULL,
    /// @brief Indicates if a metaobject reflects a conversion operator.
    /// @see mirror::reflects_conversion_operator
    reflects_conversion_operator = 1ULL << 28ULL,
    /// @brief Indicates if a metaobject reflects an expression.
    /// @see mirror::reflects_expression
    reflects_expression = 1ULL << 29ULL,
    /// @brief Indicates if a metaobject reflects a parenthesized expression.
    /// @see mirror::reflects_parenthesized_expression
    reflects_parenthesized_expression = 1ULL << 30ULL,
    /// @brief Indicates if a metaobject reflects a function call expression.
    /// @see mirror::reflects_function_call_expression
    reflects_function_call_expression = 1ULL << 31ULL,
    /// @brief Indicates if a metaobject reflects a specifier.
    /// @see mirror::reflects_specifier
    reflects_specifier = 1ULL << 32ULL
};

/// @brief Metaobject trait bitfield.
/// @ingroup classification
/// @see meta_trait
/// @see get_traits
using meta_traits = bitfield<meta_trait>;

static constexpr auto operator|(meta_trait l, meta_trait r) noexcept
  -> meta_traits {
    return {l, r};
}
//------------------------------------------------------------------------------
/// @brief Enumeration of supported type traits.
/// @ingroup classification
/// @see type_traits
/// @see meta_trait
enum class type_trait : std::uint64_t {
    is_const = 1ULL << 0ULL,
    is_volatile = 1ULL << 1ULL,
    is_pointer = 1ULL << 2ULL,
    is_reference = 1ULL << 3ULL,
    is_fundamental = 1ULL << 4ULL,
    is_void = 1ULL << 5ULL
};

/// @brief Type trait bitfield.
/// @ingroup classification
/// @see type_trait
using type_traits = bitfield<type_trait>;

static constexpr auto operator|(type_trait l, type_trait r) noexcept
  -> type_traits {
    return {l, r};
}
//------------------------------------------------------------------------------
/// @brief Enumeration of boolean-returning unary operations applicable to metaobjects.
/// @ingroup classification
/// @see operation
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
enum class object_trait : std::uint64_t {
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
/// @see trait
/// @see object_trait
/// @see operation_boolean
using object_traits = bitfield<object_trait>;

static constexpr auto operator|(object_trait l, object_trait r) noexcept
  -> object_traits {
    return {l, r};
}
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
/// @brief Class unifying the *_trait enumerators.
/// @ingroup operations
/// @see meta_trait
/// @see type_trait
/// @see object_trait
/// This class can be used to access the enumerators of the trait
/// enumerations. Instead of @c meta_trait::name use simply
/// @c trait::name. Same for the enumerators from type_trait,
/// and object_trait.
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

#if defined(MIRROR_DOXYGEN)
/// @brief Indicates if a metaobject has the specified trait.
/// @ingroup classification
/// @see meta_trait
/// @see metaobject_operation
/// @see get_traits
template <meta_trait T>
consteval auto has_trait(metaobject auto mo) noexcept -> bool;
#else
template <meta_trait T>
consteval auto has_trait(__metaobject_id mo) noexcept -> bool {
    return map_meta_trait<T>::apply(mo);
}
#endif

#if defined(MIRROR_DOXYGEN)
/// @brief Gets all metaobject traits.
/// @ingroup classification
/// @see meta_traits
/// @see metaobject_operation
/// @see has_trait
constexpr auto get_traits(metaobject auto mo) noexcept -> meta_traits;
#else
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
#endif

/// @brief Indicates if a type has the specified trait.
/// @ingroup classification
/// @see type_trait
/// @see get_traits
template <type_trait TT, typename T>
constexpr auto has_trait(std::type_identity<T>) noexcept -> bool {
    return map_type_trait<TT>::template apply<T>();
}

/// @brief Gets all type traits.
/// @ingroup classification
/// @see type_traits
/// @see get_type_traits
/// @see meta_traits
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

#if defined(MIRROR_DOXYGEN)
/// @brief Gets all type traits if metaobject reflects a type.
/// @ingroup classification
/// @see type_traits
/// @see get_traits
constexpr auto get_type_traits(metaobject auto mo) noexcept -> type_traits;
#else
template <__metaobject_id M>
constexpr auto get_type_traits(wrapped_metaobject<M> mo) noexcept
  -> type_traits {
    if constexpr(reflects_type(mo)) {
        return get_traits(get_reflected_type(mo));
    } else {
        return {};
    }
}
#endif

} // namespace mirror

#endif
