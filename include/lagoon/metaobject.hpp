/**
 * @file lagoon/metaobject.hpp
 * @brief Declaration of the `metaobject` interface
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef LAGOON_METAOBJECT_1105240825_HPP
#define LAGOON_METAOBJECT_1105240825_HPP

#include <memory>
#include <utility>
#include <string_view>

namespace lagoon {

struct metaobject;
class shared_metaobject_sequence;

class shared_metaobject
{
private:
	std::shared_ptr<metaobject> _mo;
public:
	shared_metaobject(std::shared_ptr<metaobject> mo)
	 : _mo(std::move(mo))
	{ }

	bool is_none(void) const;

	explicit
	operator bool (void) const { return !is_none(); }
	bool operator ! (void) const { return is_none(); }

	std::string_view get_base_name(void);
	std::string_view get_full_name(void);
	std::string_view get_display_name(void);

	shared_metaobject get_type(void);
	shared_metaobject get_scope(void);
	shared_metaobject get_aliased(void);

	shared_metaobject_sequence get_data_members(void);
	shared_metaobject_sequence get_member_types(void);
};

template <typename ConcreteMO, typename ... P>
static inline
shared_metaobject make_shared_metaobject(P&& ... p)
{
	return std::shared_ptr<metaobject>(
		std::make_shared<ConcreteMO>(std::forward<P>(p)...)
	);
}

struct metaobject
{
	virtual ~metaobject(void) = default;

	virtual bool is_none(void) const = 0;
	virtual std::string_view get_base_name(void) = 0;
	virtual std::string_view get_full_name(void) = 0;
	virtual std::string_view get_display_name(void) = 0;

	virtual shared_metaobject get_type(void) = 0;
	virtual shared_metaobject get_scope(void) = 0;
	virtual shared_metaobject get_aliased(void) = 0;

	virtual shared_metaobject_sequence get_data_members(void) = 0;
	virtual shared_metaobject_sequence get_member_types(void) = 0;
};

struct metaobject_sequence;

class shared_metaobject_sequence
{
private:
	std::shared_ptr<metaobject_sequence> _mos;
public:
	shared_metaobject_sequence(std::shared_ptr<metaobject_sequence> mos)
	 : _mos(std::move(mos))
	{ }

	typedef unsigned size_type;

	bool is_none(void) const;

	explicit
	operator bool (void) const { return !is_none(); }
	bool operator ! (void) const { return is_none(); }

	size_type get_size(void);
	size_type size(void) { return get_size(); }

	shared_metaobject get_element(size_type i);
	shared_metaobject at(size_type i) { return get_element(i); }
};

template <typename ConcreteMOS, typename ... P>
static inline
shared_metaobject_sequence make_shared_metaobject_sequence(P&& ... p)
{
	return std::shared_ptr<metaobject_sequence>(
		std::make_shared<ConcreteMOS>(std::forward<P>(p)...)
	);
}

struct metaobject_sequence
{
	typedef unsigned size_type;

	virtual ~metaobject_sequence(void) = default;

	virtual bool is_none(void) const = 0;
	virtual size_type get_size(void) = 0;
	virtual shared_metaobject get_element(size_type i) = 0;
};

} // namespace lagoon

#include <lagoon/metaobject.inl>

#endif //include guard

