/**
 * @file lagoon/fingerprint.hpp
 * @brief Declaration of metaobject fingerprints
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef LAGOON_FINGERPRINT_1105240825_HPP
#define LAGOON_FINGERPRINT_1105240825_HPP

#include <mirror/none.hpp>
#include <mirror/metaobject.hpp>
#include <cstdint>

namespace lagoon {

using fingerprint = std::uint64_t;

fingerprint get_fingerprint(mirror::none);

template <typename MO>
fingerprint get_fingerprint(mirror::metaobject<MO>);

template <typename MO1, typename MO2>
fingerprint get_fingerprint(mirror::metaobject<MO1>, mirror::metaobject<MO2>);

} // namespace lagoon

#include <lagoon/fingerprint.inl>

#endif //include guard

