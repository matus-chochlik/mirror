/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_tr_is_int_const
template <typename Int, Int I>
using is_int_const<__int_const<Int, I>> = __true_;

template <typename X>
using is_int_const = __false_;
//]
//[mirror_tr_is_string
template <typename Char, Char ... C>
using is_string<__basic_string<Char, C...>> = __true_;

template <typename X>
using is_string = __false_;
//]
//[mirror_tr_is_range
template <typename ... P>
using is_range<__range<P...>> = __true_;

template <typename X>
using is_range = __false_;
//]
//[mirror_tr_is_none
template <>
using is_none<__none> = __true_;

template <typename X>
using is_none = __false_;
//]
//[mirror_tr_is_metaobject
template <__std_meta_Object O>
using is_metaobject<__metaobject<O>> = __true_;

template <typename X>
using is_metaobject = __false_;
//]
//[mirror_tr_is_metaobject_sequence
template <__std_meta_ObjectSequence S>
using is_metaobject_sequence<__metaobject_sequence<S>> = __true_;

template <typename X>
using is_metaobject_sequence = __false_;
//]
//[mirror_tr_reflects_alias
template <__std_meta_Object O>
using reflects_alias<__metaobject<O>>
 = __bool_<__std_meta_Alias<O>>;

template <typename X>
using reflects_alias = __false_;
//]
//[mirror_tr_reflects_global_scope
template <__std_meta_Object O>
using reflects_global_scope<__metaobject<O>>
 = __bool_<__std_meta_GlobalScope<O>>;

template <typename X>
using reflects_global_scope = __false_;
//]
//[mirror_tr_reflects_namespace
template <__std_meta_Object O>
using reflects_namespace<__metaobject<O>>
 = __bool_<__std_meta_Namespace<O>>;

template <typename X>
using reflects_namespace = __false_;
//]
//[mirror_tr_reflects_type
template <__std_meta_Object O>
using reflects_type<__metaobject<O>>
 = __bool_<__std_meta_Type<O>>;

template <typename X>
using reflects_type = __false_;
//]
//[mirror_tr_reflects_tag_type
template <__std_meta_Object O>
using reflects_tag_type<__metaobject<O>>
 = __bool_<__std_meta_TagType<O>>;

template <typename X>
using reflects_tag_type = __false_;
//]
//[mirror_tr_reflects_enum
template <__std_meta_Object O>
using reflects_enum<__metaobject<O>>
 = __bool_<__std_meta_Enum<O>>;

template <typename X>
using reflects_enum = __false_;
//]
//[mirror_tr_reflects_record
template <__std_meta_Object O>
using reflects_record<__metaobject<O>>
 = __bool_<__std_meta_Record<O>>;

template <typename X>
using reflects_record = __false_;
//]
//[mirror_tr_reflects_class
template <__std_meta_Object O>
using reflects_class<__metaobject<O>>
 = __bool_<__std_meta_Class<O>>;

template <typename X>
using reflects_class = __false_;
//]
//[mirror_tr_reflects_enum_member
template <__std_meta_Object O>
using reflects_enum_member<__metaobject<O>>
 = __bool_<__std_meta_EnumMember<O>>;

template <typename X>
using reflects_enum_member = __false_;
//]
//[mirror_tr_reflects_record_member
template <__std_meta_Object O>
using reflects_record_member<__metaobject<O>>
 = __bool_<__std_meta_RecordMember<O>>;

template <typename X>
using reflects_record_member = __false_;
//]
//[mirror_tr_reflects_variable
template <__std_meta_Object O>
using reflects_variable<__metaobject<O>>
 = __bool_<__std_meta_Variable<O>>;

template <typename X>
using reflects_variable = __false_;
//]
//[mirror_tr_reflects_constant
template <__std_meta_Object O>
using reflects_constant<__metaobject<O>>
 = __bool_<__std_meta_Constant<O>>;

template <typename X>
using reflects_constant = __false_;
//]
//[mirror_tr_reflects_specifier
template <__std_meta_Object O>
using reflects_specifier<__metaobject<O>>
 = __bool_<__std_meta_Specifier<O>>;

template <typename X>
using reflects_specifier = __false_;
//]
//[mirror_tr_reflects_inheritance
template <__std_meta_Object O>
using reflects_inheritance<__metaobject<O>>
 = __bool_<__std_meta_Inheritance<O>>;

template <typename X>
using reflects_inheritance = __false_;
//]

