/**
 * @file lagoon/base_registry.hpp
 * @brief Declaration of the `base_registry` class
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef LAGOON_BASE_REGISTRY_1105240825_HPP
#define LAGOON_BASE_REGISTRY_1105240825_HPP

#include "metaobject.hpp"
#include "fingerprint.hpp"
#include <cstdint>
#include <vector>
#include <map>

namespace lagoon {
namespace _aux {

template <typename T>
class flat_set
{
private:
	std::vector<T> _v;
public:
	using size_type = typename std::vector<T>::size_type;

	void clear(void) { return _v.clear(); }
	size_type size(void) const { return _v.size(); }
	const T& operator [] (size_type i) const { return _v[i]; }

	void insert(T v);
};

} // namespace _aux

class base_registry
{
protected:
	std::map<fingerprint, shared_metaobject> _mos;
	std::map<fingerprint, _aux::flat_set<fingerprint>> _mems;

	base_registry(void) = default;
public:
	const shared_metaobject& get_none(void) const;
	const shared_metaobject_sequence& get_none_seq(void) const;

	shared_metaobject get_proxy(fingerprint n);
	shared_metaobject get(fingerprint n);
	shared_metaobject find(fingerprint n);

	shared_metaobject_sequence make_mem_seq(fingerprint n);
};

} // namespace lagoon

#include <lagoon/base_registry.inl>

#endif //include guard

