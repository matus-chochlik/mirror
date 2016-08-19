/**
 * .file lagoon/fingerprint.inl
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <mirror/hash.hpp>
#include <mirror/get_full_name.hpp>

namespace lagoon {

inline
fingerprint
get_fingerprint(mirror::none)
{
	return mirror::hash<mirror::none>::value;
}

template <typename MO>
inline
fingerprint
get_fingerprint(mirror::metaobject<MO>)
{
	return mirror::hash<
		mirror::get_full_name<mirror::metaobject<MO>>
	>::value;
}

template <typename MO1, typename MO2>
inline
fingerprint
get_fingerprint(mirror::metaobject<MO1>, mirror::metaobject<MO2>)
{
	return mirror::hash<
		mirror::get_full_name<mirror::metaobject<MO2>>,
		mirror::string<'@'>,
		mirror::get_full_name<mirror::metaobject<MO1>>
	>::value;
}

} // namespace lagoon
