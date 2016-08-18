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

#include "metaobject_traits.hpp"
#include <memory>
#include <utility>
#include <iterator>
#include <string_view>
#include <cassert>

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

	const metaobject_traits& traits(void) const;

	bool reflects_specifier(void) const {
		return traits().reflects_specifier;
	}
	bool reflects_global_scope(void) const {
		return traits().reflects_global_scope;
	}
	bool reflects_namespace(void) const {
		return traits().reflects_namespace;
	}
	bool reflects_type(void) const {
		return traits().reflects_type;
	}
	bool reflects_alias(void) const {
		return traits().reflects_alias;
	}
	bool reflects_variable(void) const {
		return traits().reflects_variable;
	}
	bool reflects_constant(void) const {
		return traits().reflects_variable;
	}
	bool reflects_enum_member(void) const {
		return traits().reflects_enum_member;
	}
	bool reflects_record_member(void) const {
		return traits().reflects_record_member;
	}
	bool reflects_inheritance(void) const {
		return traits().reflects_inheritance;
	}

	bool is_anonymous(void) const {
		return traits().is_anonymous;
	}
	bool is_class(void) const {
		return traits().is_class;
	}
	bool is_struct(void) const {
		return traits().is_struct;
	}
	bool is_union(void) const {
		return traits().is_union;
	}
	bool is_enum(void) const {
		return traits().is_enum;
	}
	bool is_scoped_enum(void) const {
		return traits().is_scoped_enum;
	}

	std::string_view get_base_name(void) const;
	std::string_view get_full_name(void) const;
	std::string_view get_display_name(void) const;

	shared_metaobject get_type(void) const;
	shared_metaobject get_scope(void) const;
	shared_metaobject get_aliased(void) const;
	shared_metaobject get_base_class(void) const;

	shared_metaobject get_access_specifier(void) const;

	shared_metaobject_sequence get_base_classes(void) const;
	shared_metaobject_sequence get_data_members(void) const;
	shared_metaobject_sequence get_member_types(void) const;
	shared_metaobject_sequence get_enumerators(void) const;
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

	virtual const metaobject_traits& traits(void) = 0;

	virtual std::string_view get_base_name(void) = 0;
	virtual std::string_view get_full_name(void) = 0;
	virtual std::string_view get_display_name(void) = 0;

	virtual shared_metaobject get_type(void) = 0;
	virtual shared_metaobject get_scope(void) = 0;
	virtual shared_metaobject get_aliased(void) = 0;
	virtual shared_metaobject get_base_class(void) = 0;

	virtual shared_metaobject get_access_specifier(void) = 0;

	virtual shared_metaobject_sequence get_base_classes(void) = 0;
	virtual shared_metaobject_sequence get_data_members(void) = 0;
	virtual shared_metaobject_sequence get_member_types(void) = 0;
	virtual shared_metaobject_sequence get_enumerators(void) = 0;
};

struct metaobject_sequence;
class shared_metaobject_sequence;

class shared_metaobject_sequence_iterator
{
private:
	const shared_metaobject_sequence* _psq;
	const shared_metaobject_sequence& _seq(void)
	{
		assert(_psq != nullptr);
		return *_psq;
	}
	unsigned _pos;
	shared_metaobject _cur;
	shared_metaobject _load(unsigned pos);

	typedef shared_metaobject_sequence_iterator _self;
public:
	typedef int difference_type;
	typedef shared_metaobject value_type;
	typedef const value_type* pointer;
	typedef const value_type& reference;
	typedef std::forward_iterator_tag iterator_category;

	shared_metaobject_sequence_iterator(void)
	noexcept;

	shared_metaobject_sequence_iterator(
		const shared_metaobject_sequence& seq,
		unsigned pos
	) noexcept;

	static difference_type difference(const _self& a, const _self& b)
	noexcept;

	friend difference_type operator - (const _self& a, const _self& b)
	noexcept { return difference(a, b); }

	friend bool operator == (const _self& a, const _self& b)
	noexcept { return difference(a, b) == 0; }

	friend bool operator != (const _self& a, const _self& b)
	noexcept { return difference(a, b) != 0; }

	friend bool operator <  (const _self& a, const _self& b)
	noexcept { return difference(a, b) <  0; }

	friend bool operator <= (const _self& a, const _self& b)
	noexcept { return difference(a, b) <= 0; }

	friend bool operator >  (const _self& a, const _self& b)
	noexcept { return difference(a, b) >  0; }

	friend bool operator >= (const _self& a, const _self& b)
	noexcept { return difference(a, b) >= 0; }

	void increment(void)
	noexcept;

	_self& operator ++ (void)
	noexcept { increment(); return *this; }

	reference operator * (void)
	noexcept { return _cur; }
};

class shared_metaobject_sequence
{
private:
	std::shared_ptr<metaobject_sequence> _mos;
public:
	shared_metaobject_sequence(std::shared_ptr<metaobject_sequence> mos)
	 : _mos(std::move(mos))
	{ }

	typedef unsigned size_type;
	typedef shared_metaobject_sequence_iterator iterator;

	bool is_none(void) const;

	explicit
	operator bool (void) const { return !is_none(); }
	bool operator ! (void) const { return is_none(); }

	size_type get_size(void) const;
	size_type size(void) const { return get_size(); }

	shared_metaobject get_element(size_type i) const;
	shared_metaobject at(size_type i) const { return get_element(i); }

	iterator begin(void) const { return iterator(*this, 0); }
	iterator end(void) const { return iterator(*this, size()); }
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

