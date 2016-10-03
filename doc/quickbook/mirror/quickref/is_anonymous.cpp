/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_is_anonymous
template <__std_meta_Named N>
using is_anonymous<__metaobject<N>>
 = __bool_<__std_meta_is_anonymous_v<N>>;

template <__std_meta_Object O>
using is_anonymous<__metaobject<O>> = __true_ /*<
Metaobjects not conforming to the [^__std_meta_Named] concept are also
considered anonymous.
>*/;

using is_anonymous<__none> = __true_;
//]

