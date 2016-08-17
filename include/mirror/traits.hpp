/**
 * @file mirror/traits.hpp
 * @brief Implementation of traits
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_TRAITS_1105240825_HPP
#define MIRROR_TRAITS_1105240825_HPP

#include "int_const.hpp"
#include "string.hpp"
#include "range.hpp"
#include "metaobjects.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_is_int_const
 : false_
{ };

template <typename Int, Int I>
struct op_is_int_const<int_const<Int, I>>
 : true_
{ };

template <typename X>
struct op_is_string
 : false_
{ };

template <typename Char, Char ... C>
struct op_is_string<basic_string<Char, C...>>
 : true_
{ };

template <typename X>
struct op_is_range
 : false_
{ };

template <typename ... P>
struct op_is_range<range<P...>>
 : true_
{ };

template <typename X>
struct op_is_none
 : false_
{ };

template <>
struct op_is_none<none>
 : true_
{ };

template <typename X>
struct op_is_metaobject
 : false_
{ };

template <typename MO>
struct op_is_metaobject<metaobject<MO>>
 : true_
{ };

template <typename MOS>
struct op_is_metaobject<metaobject_sequence<MOS>>
 : true_
{ };

template <typename X>
struct op_is_metaobject_sequence
 : false_
{ };

template <typename MOS>
struct op_is_metaobject_sequence<metaobject_sequence<MOS>>
 : true_
{ };

template <typename X>
struct op_reflects_specifier
 : false_
{ };

template <typename MO>
struct op_reflects_specifier<metaobject<MO>>
 : bool_<std::meta::Specifier<MO>>
{ };

template <typename X>
struct op_reflects_global_scope
 : false_
{ };

template <typename MO>
struct op_reflects_global_scope<metaobject<MO>>
 : bool_<std::meta::GlobalScope<MO>>
{ };

template <typename X>
struct op_reflects_namespace
 : false_
{ };

template <typename MO>
struct op_reflects_namespace<metaobject<MO>>
 : bool_<std::meta::Namespace<MO>>
{ };

template <typename X>
struct op_reflects_type
 : false_
{ };

template <typename MO>
struct op_reflects_type<metaobject<MO>>
 : bool_<std::meta::Type<MO>>
{ };

template <typename X>
struct op_reflects_variable
 : false_
{ };

template <typename MO>
struct op_reflects_variable<metaobject<MO>>
 : bool_<std::meta::Variable<MO>>
{ };

template <typename X>
struct op_reflects_enum_member
 : false_
{ };

template <typename MO>
struct op_reflects_enum_member<metaobject<MO>>
 : bool_<std::meta::EnumMember<MO>>
{ };

template <typename X>
struct op_reflects_record_member
 : false_
{ };

template <typename MO>
struct op_reflects_record_member<metaobject<MO>>
 : bool_<std::meta::RecordMember<MO>>
{ };

template <typename X>
struct op_reflects_inheritance
 : false_
{ };

template <typename MO>
struct op_reflects_inheritance<metaobject<MO>>
 : bool_<std::meta::Inheritance<MO>>
{ };

} // namespace _aux

template <typename X>
using is_int_const = eval<_aux::op_is_int_const<X>>;

template <typename X>
using is_string = eval<_aux::op_is_string<X>>;

template <typename X>
using is_range = eval<_aux::op_is_range<X>>;

template <typename X>
using is_none = eval<_aux::op_is_none<X>>;

template <typename X>
using is_metaobject = eval<_aux::op_is_metaobject<X>>;

template <typename X>
using is_metaobject_sequence = eval<_aux::op_is_metaobject_sequence<X>>;

template <typename X>
using reflects_specifier = eval<_aux::op_reflects_specifier<X>>;

template <typename X>
using reflects_global_scope = eval<_aux::op_reflects_global_scope<X>>;

template <typename X>
using reflects_namespace = eval<_aux::op_reflects_namespace<X>>;

template <typename X>
using reflects_type = eval<_aux::op_reflects_type<X>>;

template <typename X>
using reflects_variable = eval<_aux::op_reflects_variable<X>>;

template <typename X>
using reflects_enum_member = eval<_aux::op_reflects_enum_member<X>>;

template <typename X>
using reflects_record_member = eval<_aux::op_reflects_record_member<X>>;

template <typename X>
using reflects_inheritance = eval<_aux::op_reflects_inheritance<X>>;

} // namespace mirror

#endif //include guard

