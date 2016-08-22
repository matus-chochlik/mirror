/**
 * .file lagoon/fingerprint.inl
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <puddle/string.hpp>
#include <puddle/hash.hpp>
#include <puddle/meta_named_ops.hpp>

namespace lagoon {

inline
fingerprint
get_fingerprint(mirror::none n)
{
	return puddle::hash(n);
}

template <typename MO>
inline
fingerprint
get_fingerprint(mirror::metaobject<MO> mo)
{
	return puddle::hash(puddle::get_full_name(mo));
}

template <typename MO1, typename MO2>
inline
fingerprint
get_fingerprint(mirror::metaobject<MO1> mo1, mirror::metaobject<MO2> mo2)
{
	return puddle::hash(
		puddle::get_full_name(mo2),
		puddle::string<'@'>,
		puddle::get_full_name(mo1)
	);
}

} // namespace lagoon
