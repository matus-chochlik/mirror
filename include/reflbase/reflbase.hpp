/**
 * @file reflbase/reflbase.hpp
 * @brief Implementation switching and customization layer for reflexpr
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef REFLBASE_REFLBASE_1105240825_HPP
#define REFLBASE_REFLBASE_1105240825_HPP

#ifndef REFLBASE_USE_REFLEXPR
# if defined(__cpp_reflection) && __cpp_reflection
#  define REFLBASE_USE_REFLEXPR 1
# else
#  define REFLBASE_USE_REFLEXPR 0
# endif
#endif

#if REFLBASE_USE_REFLEXPR
# include "reflexpr.hpp"
#else
# include "reflfake.hpp"
#endif

namespace reflbase {

template <typename X>
constexpr const auto is_metaobject_v = is_metaobject<X>::value;

template <typename X>
constexpr const auto get_source_file_v = get_source_file<X>::value;

template <typename X>
constexpr const auto get_source_line_v = get_source_line<X>::value;

template <typename X>
constexpr const auto get_source_column_v = get_source_column<X>::value;

template <typename X>
constexpr const auto get_size_v = get_size<X>::value;

template <typename X, unsigned I>
using get_element_m = typename get_element<X, I>::type;

template <typename X, template <class...> class Tpl>
using unpack_sequence_t = typename unpack_sequence<X, Tpl>::type;

template <typename X>
constexpr const auto is_anonymous_v = is_anonymous<X>::value;

template <typename X>
constexpr const auto get_base_name_v = get_base_name<X>::value;

template <typename X>
constexpr const auto get_display_name_v = get_display_name<X>::value;

template <typename X>
using get_aliased_m = typename get_aliased<X>::type;

template <typename X>
using get_scope_m = typename get_scope<X>::type;

template <typename X>
using get_type_m = typename get_type<X>::type;

template <typename X>
using get_elaborated_type_specifier_m
 = typename get_elaborated_type_specifier<X>::type;

template <typename X>
constexpr const auto is_enum_v = is_enum<X>::value;

template <typename X>
constexpr const auto is_scoped_enum_v = is_scoped_enum<X>::value;

template <typename X>
constexpr const auto is_struct_v = is_struct<X>::value;

template <typename X>
constexpr const auto is_class_v = is_class<X>::value;

template <typename X>
constexpr const auto is_union_v = is_union<X>::value;

template <typename X>
using get_enumerators_m = typename get_enumerators<X>::type;

template <typename X>
using get_member_types_m = typename get_member_types<X>::type;

template <typename X>
using get_public_member_types_m = typename get_public_member_types<X>::type;

template <typename X>
using get_data_members_m = typename get_data_members<X>::type;

template <typename X>
using get_public_data_members_m = typename get_public_data_members<X>::type;

template <typename X>
using get_base_classes_m = typename get_base_classes<X>::type;

template <typename X>
using get_public_base_classes_m = typename get_public_base_classes<X>::type;

template <typename X>
using get_reflected_type_t = typename get_reflected_type<X>::type;

template <typename X>
constexpr const auto get_pointer_v = get_pointer<X>::value;

template <typename X>
constexpr const auto get_constant_v = get_constant<X>::value;

template <typename X>
using get_base_class_m = typename get_base_class<X>::type;

template <typename X>
using get_access_specifier_m = typename get_access_specifier<X>::type;

template <typename X>
constexpr const auto is_public_v = is_public<X>::value;

template <typename X>
constexpr const auto is_protected_v = is_protected<X>::value;

template <typename X>
constexpr const auto is_private_v = is_private<X>::value;

template <typename X>
constexpr const auto is_static_v = is_static<X>::value;

template <typename X>
constexpr const auto is_virtual_v = is_virtual<X>::value;

} // namespace reflbase

#endif //include guard

