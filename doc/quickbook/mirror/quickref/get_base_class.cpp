/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_get_base_class
template <__std_meta_Inheritance I>
using get_base_class<__metaobject<I>>
 = __metaobject<__std_meta_get_base_class_m<I>>;

template <__std_meta_Object O>
using get_base_class<__metaobject<O>> = none /*<
For metaobjects which do not reflect class inheritance [^__none] is returned.
>*/;

using get_base_class<__none> = __none;
//]

