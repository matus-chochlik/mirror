/**
 * @file mirror/get_source_column.hpp
 * @brief Implementation of `get_source_column` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_SOURCE_COLUMN_1105240825_HPP
#define MIRROR_GET_SOURCE_COLUMN_1105240825_HPP

#include "metaobject.hpp"
#include "int_const.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_source_column;

template <typename MO>
struct op_get_source_column<metaobject<MO>>
 : unsigned_<reflbase::get_source_column_v<MO>>
{ };

template <>
struct op_get_source_column<none>
 : unsigned_<0>
{ };

} // namespace _aux

template <typename X>
using get_source_column = eval<_aux::op_get_source_column<X>>;

} // namespace mirror

#endif //include guard

