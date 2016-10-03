/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_is_virtual
template <__std_meta_Inheritance I>
using is_virtual<__metaobject<I>>
 = __bool_<__std_meta_is_virtual_v<I>>;

template <__std_meta_Object O>
using is_virtual<__metaobject<O>> = __false_ /*<
Metaobjects not conforming to the [^__std_meta_Inheritance] concept are
considered non-virtual.
>*/;

using is_virtual<__none> = __false_;
//]

