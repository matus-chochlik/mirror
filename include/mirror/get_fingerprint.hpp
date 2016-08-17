/**
 * @file mirror/get_fingerprint.hpp
 * @brief Implementation of `get_fingerprint` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_FINGERPRINT_1105240825_HPP
#define MIRROR_GET_FINGERPRINT_1105240825_HPP

#include <reflexpr>
#include "string_view.hpp"
#include "get_full_name.hpp"

namespace mirror {

// TODO: do something better here
using fingerprint = ::std::string_view;

template <typename X>
constexpr fingerprint get_fingerprint = string_view<get_full_name<X>>;


} // namespace mirror

#endif //include guard

