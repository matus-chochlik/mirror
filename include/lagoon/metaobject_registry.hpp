/**
 * @file lagoon/metaobject_registry.hpp
 * @brief Declaration of the `metaobject_registry` class
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef LAGOON_METAOBJECT_REGISTRY_1105240825_HPP
#define LAGOON_METAOBJECT_REGISTRY_1105240825_HPP

#include "base_registry.hpp"
#include <mirror/none.hpp>
#include <mirror/range.hpp>

namespace lagoon {

class metaobject_registry;

namespace _aux {

struct mo_reg_self_add
{
private:
	friend class lagoon::metaobject_registry;
	metaobject_registry* registry;
public:
	template <typename MO>
	auto add(MO mo);

	template <typename MO>
	auto operator << (MO mo) { return add(mo); }
};

struct mo_reg_bacl_add
{
private:
	metaobject_registry* _r;
public:
	template <typename MO>
	auto add(MO mo);

	template <typename MO>
	auto operator << (MO mo) { return add(mo); }
};

struct mo_reg_dame_add
{
private:
	metaobject_registry* _r;
public:
	template <typename MO>
	auto add(MO mo);

	template <typename MO>
	auto operator << (MO mo) { return add(mo); }
};

struct mo_reg_mety_add
{
private:
	metaobject_registry* _r;
public:
	template <typename MO>
	auto add(MO mo);

	template <typename MO>
	auto operator << (MO mo) { return add(mo); }
};

struct mo_reg_enrs_add
{
private:
	metaobject_registry* _r;
public:
	template <typename MO>
	auto add(MO mo);

	template <typename MO>
	auto operator << (MO mo) { return add(mo); }
};

} // namespace _aux

class metaobject_registry
 : public base_registry
{
private:
	template <typename ... X>
	static void _eat(X ...) { }

	template <typename MO>
	shared_metaobject _add(fingerprint, MO);

	void _add_range(mirror::none) { }

	template <typename ... MO>
	void _add_range(mirror::range<MO...>);

	template <typename PMO>
	void _add_inh_range(PMO, mirror::none) { }

	template <typename PMO, typename ... MO>
	void _add_inh_range(PMO, mirror::range<MO...>);
public:
	union {
		_aux::mo_reg_self_add self;
		_aux::mo_reg_bacl_add base_classes;
		_aux::mo_reg_dame_add data_members;
		_aux::mo_reg_dame_add member_types;
		_aux::mo_reg_enrs_add enumerators;
	};

	metaobject_registry(void)
	{ self.registry = this; }

	shared_metaobject add(mirror::none);

	template <typename MO>
	shared_metaobject add(MO);

	template <typename MO>
	shared_metaobject operator << (MO mo) { return add(mo); }

	template <typename MO>
	void add_base_classes_of(MO);

	template <typename MO>
	void add_data_members_of(MO);

	template <typename MO>
	void add_member_types_of(MO);

	template <typename MO>
	void add_enumerators_of(MO);

	shared_metaobject_sequence wrap_sequence(mirror::none);

	template <typename MOS>
	shared_metaobject_sequence wrap_sequence(MOS);

	template <typename PMO, typename MOS>
	shared_metaobject_sequence wrap_inheritance_sequence(PMO, MOS);
};

namespace _aux {

template <typename MO>
inline auto mo_reg_self_add::add(MO mo) { return registry->add(mo); }

template <typename MO>
inline auto mo_reg_bacl_add::add(MO mo) { return _r->add_base_classes_of(mo); }

template <typename MO>
inline auto mo_reg_dame_add::add(MO mo) { return _r->add_data_members_of(mo); }

template <typename MO>
inline auto mo_reg_mety_add::add(MO mo) { return _r->add_member_types_of(mo); }

template <typename MO>
inline auto mo_reg_enrs_add::add(MO mo) { return _r->add_enumerators_of(mo); }

} // namespace _aux

} // namespace lagoon

#include <lagoon/metaobject_registry.inl>

#endif //include guard

