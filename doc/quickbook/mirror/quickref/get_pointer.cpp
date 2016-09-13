/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_get_pointer
template <__std_meta_Variable C>
using get_pointer<__metaobject<C>> = __int_const<__unspecified /*<
The type of the pointer to the variable reflected by the argument.
If the argument reflects a class member, then this is a pointer-to-data-member
type.
>*/, __unspecified /*<
The pointer constant value, as if taken with the [^&] operator.
>*/>;

template <__std_meta_Object O>
using get_pointer<__metaobject<O>> = __none /*<
For metaobjects which do not reflect constant values [^__none] is returned.
>*/;

using get_pointer<__none> = none;
//]

