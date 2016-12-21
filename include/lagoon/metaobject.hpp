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
#include "any_constant.hpp"
#include "tribool.hpp"
#include <reflbase/string_view_fix.hpp>
#include <memory>
#include <utility>
#include <iterator>
#include <cassert>

namespace lagoon {

struct metaobject;
class shared_metaobject_sequence;
using fingerprint = std::uint64_t;

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

	fingerprint get_fingerprint(void) const;

	const metaobject_traits* traits(void) const;

#define LAGOON_IMPLEMENT_TRAIT_GETTER(TRAIT) \
	tribool TRAIT (void) const { \
		if(auto *ts = traits()) { \
			return {ts->TRAIT}; \
		} else return none; \
	}

	LAGOON_IMPLEMENT_TRAIT_GETTER(has_source_info)
	LAGOON_IMPLEMENT_TRAIT_GETTER(reflects_specifier)
	LAGOON_IMPLEMENT_TRAIT_GETTER(reflects_global_scope)
	LAGOON_IMPLEMENT_TRAIT_GETTER(reflects_namespace)
	LAGOON_IMPLEMENT_TRAIT_GETTER(reflects_type)
	LAGOON_IMPLEMENT_TRAIT_GETTER(reflects_tag_type)
	LAGOON_IMPLEMENT_TRAIT_GETTER(reflects_record)
	LAGOON_IMPLEMENT_TRAIT_GETTER(reflects_class)
	LAGOON_IMPLEMENT_TRAIT_GETTER(reflects_enum)
	LAGOON_IMPLEMENT_TRAIT_GETTER(reflects_alias)
	LAGOON_IMPLEMENT_TRAIT_GETTER(reflects_variable)
	LAGOON_IMPLEMENT_TRAIT_GETTER(reflects_constant)
	LAGOON_IMPLEMENT_TRAIT_GETTER(reflects_enum_member)
	LAGOON_IMPLEMENT_TRAIT_GETTER(reflects_record_member)
	LAGOON_IMPLEMENT_TRAIT_GETTER(reflects_inheritance)

	LAGOON_IMPLEMENT_TRAIT_GETTER(is_anonymous)
	LAGOON_IMPLEMENT_TRAIT_GETTER(is_class)
	LAGOON_IMPLEMENT_TRAIT_GETTER(is_struct)
	LAGOON_IMPLEMENT_TRAIT_GETTER(is_union)
	LAGOON_IMPLEMENT_TRAIT_GETTER(is_enum)
	LAGOON_IMPLEMENT_TRAIT_GETTER(is_scoped_enum)
	LAGOON_IMPLEMENT_TRAIT_GETTER(is_static)
	LAGOON_IMPLEMENT_TRAIT_GETTER(is_virtual)
#undef  LAGOON_IMPLEMENT_TRAIT_GETTER

	std::string_view get_source_file(void) const;
	unsigned get_source_line(void) const;
	unsigned get_source_column(void) const;

	std::string_view get_base_name(void) const;
	std::string_view get_full_name(void) const;
	std::string_view get_display_name(void) const;

	any_constant get_constant(void) const;

	shared_metaobject get_type(void) const;
	shared_metaobject get_scope(void) const;
	shared_metaobject get_aliased(void) const;
	shared_metaobject get_base_class(void) const;

	shared_metaobject get_elaborated_type_specifier(void) const;
	shared_metaobject get_access_specifier(void) const;

	shared_metaobject_sequence get_base_classes(void) const;
	shared_metaobject_sequence get_data_members(void) const;
	shared_metaobject_sequence get_member_types(void) const;
	shared_metaobject_sequence get_enumerators(void) const;

	shared_metaobject_sequence get_members(void) const;
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

	virtual fingerprint get_fingerprint(void) = 0;

	virtual const metaobject_traits* traits(void) = 0;

	virtual std::string_view get_source_file(void) = 0;
	virtual unsigned get_source_line(void) = 0;
	virtual unsigned get_source_column(void) = 0;

	virtual std::string_view get_base_name(void) = 0;
	virtual std::string_view get_full_name(void) = 0;
	virtual std::string_view get_display_name(void) = 0;

	virtual any_constant get_constant(void) = 0;

	virtual shared_metaobject get_type(void) = 0;
	virtual shared_metaobject get_scope(void) = 0;
	virtual shared_metaobject get_aliased(void) = 0;
	virtual shared_metaobject get_base_class(void) = 0;

	virtual shared_metaobject get_elaborated_type_specifier(void) = 0;
	virtual shared_metaobject get_access_specifier(void) = 0;

	virtual shared_metaobject_sequence get_base_classes(void) = 0;
	virtual shared_metaobject_sequence get_data_members(void) = 0;
	virtual shared_metaobject_sequence get_member_types(void) = 0;
	virtual shared_metaobject_sequence get_enumerators(void) = 0;

	virtual shared_metaobject_sequence get_members(void) = 0;
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

	using _self = shared_metaobject_sequence_iterator;
public:
	using difference_type = int;
	using value_type = shared_metaobject;
	using pointer = const value_type*;
	using reference = const value_type&;
	using iterator_category = std::forward_iterator_tag;

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

	using size_type = unsigned;
	using iterator = shared_metaobject_sequence_iterator;

	bool is_none(void) const;

	explicit
	operator bool (void) const { return !is_none(); }
	bool operator ! (void) const { return is_none(); }

	size_type get_size(void) const;
	size_type size(void) const { return get_size(); }

	bool is_empty(void) const { return get_size() == 0; }
	bool empty(void) const { return is_empty(); }

	shared_metaobject get_element(size_type i) const;
	shared_metaobject at(size_type i) const { return get_element(i); }

	iterator begin(void) const { return iterator(*this, 0); }
	iterator end(void) const { return iterator(*this, size()); }
};

template <typename ConcreteMOS, typename ... P>
static inline
shared_metaobject_sequence make_shared_sequence(P&& ... p)
{
	return std::shared_ptr<metaobject_sequence>(
		std::make_shared<ConcreteMOS>(std::forward<P>(p)...)
	);
}

struct metaobject_sequence
{
	using size_type = unsigned;

	virtual ~metaobject_sequence(void) = default;

	virtual bool is_none(void) const = 0;
	virtual size_type get_size(void) = 0;
	virtual shared_metaobject get_element(size_type i) = 0;
};

} // namespace lagoon

#include <lagoon/metaobject.inl>

#endif //include guard

