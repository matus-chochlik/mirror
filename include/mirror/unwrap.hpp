/**
 * @file mirror/unwrap.hpp
 * @brief Implementation of the `unwrap_if_not_special` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_UNWRAP_1105240825_HPP
#define MIRROR_UNWRAP_1105240825_HPP

#include "identity.hpp"

namespace mirror {
namespace _aux {

template <typename T>
struct op_unwrap_identity
 : identity<T>
{ };

template <typename T>
struct op_unwrap_identity<identity<T>>
 : identity<T>
{ };

} // namespace _aux

template <typename T>
using unwrap_identity = eval<_aux::op_unwrap_identity<T>>;

} // namespace mirror

#endif //include guard

