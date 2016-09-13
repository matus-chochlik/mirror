/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_get_elaborated_type_specifier
template <__std_meta_TagType T>
using get_elaborated_type_specifier<__metaobject<T>>
 = __metaobject<__std_meta_get_elaborated_type_specifier<T>>;

template <__std_meta_RecordMember M>
using get_elaborated_type_specifier<__metaobject<M>>
 = __metaobject<__std_meta_get_elaborated_type_specifier>;

template <__std_meta_Object O>
using get_elaborated_type_specifier<__metaobject<O>> = __none /*<
For other metaobjects [^__none] is returned.
>*/;

using get_elaborated_type_specifier<__none> = none;
//]

