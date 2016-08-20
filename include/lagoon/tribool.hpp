/**
 * @file lagoon/tribool.hpp
 * @brief Declaration of tri-state boolean
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef LAGOON_TRIBOOL_1105240825_HPP
#define LAGOON_TRIBOOL_1105240825_HPP

#include <mirror/none.hpp>

namespace lagoon {
namespace _aux {

enum class tribool : unsigned char
{
	false_ = 0x00,
	true_ = 0x01,
	none = 0x02
};

static constexpr inline
tribool make_tribool(void)
noexcept
{
	return tribool::none;
}

static constexpr inline
tribool make_tribool(bool b)
noexcept
{
	return b?tribool::true_:tribool::false_;
}

static constexpr inline
tribool make_tribool(mirror::none)
noexcept
{
	return tribool::none;
}

static constexpr inline
bool is_true(tribool t)
noexcept
{
	return t == tribool::true_;
}

static constexpr inline
bool is_false(tribool t)
noexcept
{
	return t == tribool::false_;
}

static constexpr inline
bool is_none(tribool t)
noexcept
{
	return t == tribool::none;
}

static constexpr inline
bool strong_equal(tribool a, tribool b)
noexcept
{
	return (a == b) &&
		(a != tribool::none) &&
		(b != tribool::none);
}

static constexpr inline
bool strong_nonequal(tribool a, tribool b)
noexcept
{
	return (a != b) &&
		(a != tribool::none) &&
		(b != tribool::none);
}

} // namespace _aux

class tribool;

class weak_bool
{
private:
	_aux::tribool _v;

	friend class tribool;

	constexpr inline
	weak_bool(_aux::tribool v)
	noexcept
	 : _v(v)
	{ }
public:
	constexpr inline
	weak_bool(bool b)
	noexcept
	 : _v(_aux::make_tribool(b))
	{ }

	constexpr inline
	weak_bool(mirror::none n)
	noexcept
	 : _v(_aux::make_tribool(n))
	{ }

	constexpr inline
	bool is_none(void) const
	noexcept { return _aux::is_none(_v); }

	explicit constexpr inline
	operator bool (void) const
	noexcept { return !_aux::is_false(_v); }

	constexpr inline
	bool operator ! (void) const
	noexcept { return !_aux::is_true(_v); }

	friend constexpr
	bool operator == (weak_bool a, weak_bool b)
	noexcept { return a._v == b._v; }

	friend constexpr
	bool operator != (weak_bool a, weak_bool b)
	noexcept { return a._v != b._v; }

	friend constexpr
	bool operator <  (weak_bool a, weak_bool b)
	noexcept { return a._v <  b._v; }
};

static constexpr inline
bool is_none(weak_bool w)
noexcept
{
	return w.is_none();
}

class tribool
{
private:
	_aux::tribool _v;
public:
	constexpr inline
	tribool(void)
	noexcept
	 : _v(_aux::make_tribool())
	{ }

	constexpr inline
	tribool(bool b)
	noexcept
	 : _v(_aux::make_tribool(b))
	{ }

	constexpr inline
	tribool(mirror::none n)
	noexcept
	 : _v(_aux::make_tribool(n))
	{ }

	constexpr inline
	bool is_none(void) const
	noexcept { return _aux::is_none(_v); }

	explicit constexpr inline
	operator bool (void) const
	noexcept { return _aux::is_true(_v); }

	constexpr inline
	bool operator ! (void) const
	noexcept { return _aux::is_false(_v); }

	constexpr inline
	weak_bool operator ~ (void) const
	noexcept { return {_v}; }

	friend constexpr
	bool operator == (tribool a, tribool b)
	noexcept { return strong_equal(a._v, b._v); }

	friend constexpr
	bool operator != (tribool a, tribool b)
	noexcept { return strong_nonequal(a._v, b._v); }

	friend constexpr
	bool operator <  (tribool a, tribool b)
	noexcept { return a._v <  b._v; }
};

static constexpr inline
bool is_none(tribool t)
noexcept
{
	return t.is_none();
}

} // namespace lagoon

#endif //include guard

