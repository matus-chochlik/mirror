/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[lagoon_weak_bool_1
class weak_bool
{
public:
	constexpr inline
	weak_bool(bool b)
	noexcept;

	constexpr inline
	weak_bool(__mirror_none n)
	noexcept; /*< Constructs a ['none] tribool >*/

	constexpr inline
	bool is_none(void) const /*< Indicates if the value is ['none]. >*/
	noexcept;

	explicit constexpr inline
	operator bool (void) const /*< Not equal to [^false] >*/
	noexcept;

	constexpr inline
	bool operator ! (void) const /*< Not equal to [^true] >*/
	noexcept;

	friend constexpr
	weak_bool operator || (weak_bool a, weak_bool b)
	noexcept;

	friend constexpr
	weak_bool operator && (weak_bool a, weak_bool b)
	noexcept;

	friend constexpr
	bool operator == (weak_bool a, weak_bool b)
	noexcept;

	friend constexpr
	bool operator != (weak_bool a, weak_bool b)
	noexcept;

	friend constexpr
	bool operator <  (weak_bool a, weak_bool b)
	noexcept;
};
//]
//[lagoon_weak_bool_2
static constexpr inline
bool is_none(__weak_bool w)
noexcept;
//]
//[lagoon_tribool_1
class tribool
{
public:
	constexpr inline
	tribool(void) /*< Constructs a ['none] [^tribool] >*/
	noexcept;

	constexpr inline
	tribool(bool b) /*< Constructs a [^true] or [^false] [^tribool] >*/
	noexcept;

	constexpr inline
	tribool(__mirror_none n) /*< Constructs a ['none] [^tribool] >*/
	noexcept;

	constexpr inline
	tribool(weak_bool w)
	noexcept;

	constexpr inline
	bool is_none(void) const /*< Indicates if the value is ['none] >*/
	noexcept;

	explicit constexpr inline
	operator bool (void) const /*< Equal to [^true] >*/
	noexcept;

	constexpr inline
	bool operator ! (void) const /*< Equal to [^false] >*/
	noexcept;

	constexpr inline
	~__weak_bool operator ~ (void) const
	noexcept;

	friend constexpr
	tribool operator || (tribool a, tribool b)
	noexcept;

	friend constexpr
	tribool operator && (tribool a, tribool b)
	noexcept;

	friend constexpr
	bool operator == (tribool a, tribool b)
	noexcept;

	friend constexpr
	bool operator != (tribool a, tribool b)
	noexcept;

	friend constexpr
	bool operator <  (tribool a, tribool b)
	noexcept;
};
//]
//[lagoon_tribool_2
static constexpr inline
bool is_none(__tribool t)
noexcept;
//]
//[lagoon_none
constexpr __tribool none = tribool{__mirror_none{}};
//]

