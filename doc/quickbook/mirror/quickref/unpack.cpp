/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_unpack
template <__std_meta_ObjectSequence S>
using unpack<__metaobject_sequence<S>>
 = __std_meta_unpack_sequence_t<S, __range>;

using unpack<__none> = __empty_range;
//]

