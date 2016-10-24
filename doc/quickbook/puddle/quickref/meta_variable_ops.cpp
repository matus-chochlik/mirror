/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[puddle_op_get_pointer
template <typename X>
static constexpr inline
__mirror_get_pointer<X> get_pointer(X)
noexcept;
//]
//[puddle_op_dereference_0
template <typename MO>
static constexpr inline
auto& dereference(MO); /*<
Equivalent to:
``
__mirror_dereference<MO>::apply();
``
>*/
//]
//[puddle_op_dereference_inst
template <typename MO, typename T>
static constexpr inline
auto& dereference(MO, T& inst); /*<
Equivalent to:
``
__mirror_dereference<MO>::apply(inst);
``
>*/
//]
