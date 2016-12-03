/**
 * @file mirror/add.hpp
 * @brief Implementation of the `add` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_ADD_1105240825_HPP
#define MIRROR_ADD_1105240825_HPP

#include "int_const.hpp"
#include "conditional.hpp"

namespace mirror {
namespace _aux {

template <typename ... P>
struct op_add
 : identity<int_const<decltype((... + P::value)), (... + P::value)>>
{ };

} // namespace _aux

template <typename ... P>
using add = eval<_aux::op_add<P...>>;

} // namespace mirror

#endif //include guard

