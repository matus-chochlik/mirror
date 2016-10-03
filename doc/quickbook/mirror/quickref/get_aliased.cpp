/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_get_aliased
template <__std_meta_Alias A>
using get_aliased<__metaobject<A>>
 = __metaobject<__std_meta_get_aliased_m<A>>;

template <__std_meta_Object O>
using get_aliased<__metaobject<O>> = none /*<
For metaobjects which do not reflect aliases [^__none] is returned.
>*/;

using get_aliased<__none> = __none;
//]

