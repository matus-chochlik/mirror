/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_get_scope
template <__std_meta_ScopeMember SM>
using get_scope<__metaobject<SM>>
 = __metaobject<__std_meta_get_scope_m<SM>>;

template <__std_meta_Object O>
using get_scope<__metaobject<O>> = none /*<
For metaobjects which do not reflect scope members [^__none] is returned.
>*/;

using get_scope<__none> = __none;
//]

