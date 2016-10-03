/**
 * @file mirror/not.hpp
 * @brief Implementation of the `not_` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_NOT_1105240825_HPP
#define MIRROR_NOT_1105240825_HPP

#include "int_const.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <typename P>
struct op_not;

template <bool B>
struct op_not<bool_<B>>
 : bool_<!B>
{ };

template <>
struct op_not<none>
 : none
{ };

} // namespace _aux

template <typename P>
using not_ = eval<_aux::op_not<P>>;

} // namespace mirror

#endif //include guard

