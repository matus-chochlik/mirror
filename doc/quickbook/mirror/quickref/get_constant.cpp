/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_get_constant
template <__std_meta_Constant C>
using get_constant<__metaobject<C>> = __int_const<__unspecified /*<
The type of the constant value reflected by the argument.
>*/, __unspecified /*<
The value of the constant reflected by the argument.
>*/>;

template <__std_meta_Object O>
using get_constant<__metaobject<O>> = __none /*<
For metaobjects which do not reflect constant values [^__none] is returned.
>*/;

using get_constant<__none> = none;
//]

