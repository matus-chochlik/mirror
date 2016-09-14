/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_is_static
template <__std_meta_Variable V>
using is_static<__metaobject<V>>
 = __bool_<__std_meta_is_static_v<V>>;

template <__std_meta_Object O>
using is_static<__metaobject<O>> = __false_ /*<
Metaobjects not conforming to the [^__std_meta_Variable] concept are
considered non-static.
>*/;

using is_static<__none> = __false_;
//]

