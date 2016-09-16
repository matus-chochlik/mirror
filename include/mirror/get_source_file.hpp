/**
 * @file mirror/get_source_file.hpp
 * @brief Implementation of `get_source_file` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_SOURCE_FILE_1105240825_HPP
#define MIRROR_GET_SOURCE_FILE_1105240825_HPP

#include "metaobject.hpp"
#include "none.hpp"
#include "to_string.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_source_file;

template <typename MO>
struct op_get_source_file<metaobject<MO>>
 : to_string<reflbase::get_source_file<MO>>
{ };

template <>
struct op_get_source_file<none>
 : empty_string
{ };

} // namespace _aux

template <typename X>
using get_source_file = eval<_aux::op_get_source_file<X>>;

} // namespace mirror

#endif //include guard

