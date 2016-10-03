/**
 * @file mirror/get_full_name.hpp
 * @brief Implementation of `get_full_name` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_FULL_NAME_1105240825_HPP
#define MIRROR_GET_FULL_NAME_1105240825_HPP

#include "reflection.hpp"
#include "get_base_name.hpp"
#include "get_aliased.hpp"
#include "get_scope.hpp"
#include "get_reflected_type.hpp"
#include "is_anonymous.hpp"
#include "is_empty.hpp"
#include "is_scoped_enum.hpp"
#include "is_enum.hpp"
#include "int_to_str.hpp"
#include "traits.hpp"
#include "concat.hpp"
#include "join.hpp"
#include "not.hpp"
#include "and.hpp"
#include "or.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_scope_spec;

template <>
struct op_get_scope_spec<none>
 : empty_string
{ };

template <typename MO>
struct op_get_scope_spec
 : lazy_conditional<
	is_none<get_scope<MO>>,
	get_base_name<MO>,
	concat<
		lazy_conditional<
			or_<
				is_anonymous<get_scope<MO>>,
				and_<
					is_enum<get_scope<MO>>,
					not_<is_scoped_enum<get_scope<MO>>>
				>
			>,
			op_get_scope_spec<get_scope<get_scope<MO>>>,
			op_get_scope_spec<get_scope<MO>>
		>, string<':',':'>, get_base_name<MO>
	>
> { };

template <typename X>
struct op_get_full_name;

template <typename MO, typename T>
struct do_get_full_name;

template <typename MO, typename T>
struct decor
{
	template <typename Str>
	struct left : Str { };

	template <typename Str>
	struct base : op_get_scope_spec<MO> { };

	template <typename Str>
	struct right : Str { };

	template <typename Str>
	struct extent : Str { };

	template <typename Str>
	struct params : Str { };
};

template <typename MO, typename T, typename S>
using apply_decor_left = eval<typename decor<MO, T>::template left<S>>;

template <typename MO, typename T, typename S>
using apply_decor_base = eval<typename decor<MO, T>::template base<S>>;

template <typename MO, typename T, typename S>
using apply_decor_right = eval<typename decor<MO, T>::template right<S>>;

template <typename MO, typename T, typename S>
using apply_decor_extent  = eval<typename decor<MO, T>::template extent<S>>;

template <typename MO, typename T, typename S>
using apply_decor_params  = eval<typename decor<MO, T>::template params<S>>;

template <typename MO, typename T>
struct decor<MO, T*>
{
	using MT = get_aliased<MIRRORED(T)>;

	template <typename Str>
	struct left : apply_decor_left<MT, T, Str> { };

	template <typename Str>
	struct base : apply_decor_base<MT, T, Str> { };

	template <typename Str>
	struct right
	 : apply_decor_right<
		MT, T, concat<string<'*'>, Str>
	> { };

	template <typename Str>
	struct extent : apply_decor_extent<MT, T, Str> { };

	template <typename Str>
	struct params : apply_decor_params<MT, T, Str> { };
};

template <typename MO, typename T>
struct decor<MO, T&>
{
	using MT = get_aliased<MIRRORED(T)>;

	template <typename Str>
	struct left : apply_decor_left<MT, T, Str> { };

	template <typename Str>
	struct base : apply_decor_base<MT, T, Str> { };

	template <typename Str>
	struct right
	 : apply_decor_right<
		MT, T, concat<string<'&'>, Str>
	> { };

	template <typename Str>
	struct extent : apply_decor_extent<MT, T, Str> { };

	template <typename Str>
	struct params : apply_decor_params<MT, T, Str> { };
};

template <typename MO, typename T>
struct decor<MO, T&&>
{
	using MT = get_aliased<MIRRORED(T)>;

	template <typename Str>
	struct left : apply_decor_left<MT, T, Str> { };

	template <typename Str>
	struct base : apply_decor_base<MT, T, Str> { };

	template <typename Str>
	struct right
	 : apply_decor_right<
		MT, T, concat<string<'&','&'>, Str>
	> { };

	template <typename Str>
	struct extent : apply_decor_extent<MT, T, Str> { };

	template <typename Str>
	struct params : apply_decor_params<MT, T, Str> { };
};

template <typename MO, typename T>
struct decor<MO, T const>
{
	using MT = get_aliased<MIRRORED(T)>;

	template <typename Str>
	struct left : apply_decor_left<MT, T, Str> { };

	template <typename Str>
	struct base : apply_decor_base<MT, T, Str> { };

	template <typename Str>
	struct right
	 : apply_decor_right<
		MT, T, concat<
			string<' ','c','o','n','s','t'>,
			Str
		>
	> { };

	template <typename Str>
	struct extent : apply_decor_extent<MT, T, Str> { };

	template <typename Str>
	struct params : apply_decor_params<MT, T, Str> { };
};

template <typename MO, typename T>
struct decor<MO, T volatile>
{
	using MT = get_aliased<MIRRORED(T)>;

	template <typename Str>
	struct left : apply_decor_left<MT, T, Str> { };

	template <typename Str>
	struct base : apply_decor_base<MT, T, Str> { };

	template <typename Str>
	struct right
	 : apply_decor_right<
		MT, T, concat<
			string<' ','v','o','l','a','t','i','l','e'>,
			Str
		>
	> { };

	template <typename Str>
	struct extent : apply_decor_extent<MT, T, Str> { };

	template <typename Str>
	struct params : apply_decor_params<MT, T, Str> { };
};

template <typename MO, typename T>
struct decor<MO, T const volatile>
{
	using MT = get_aliased<MIRRORED(T)>;

	template <typename Str>
	struct left : apply_decor_left<MT, T, Str> { };

	template <typename Str>
	struct base : apply_decor_base<MT, T, Str> { };

	template <typename Str>
	struct right
	 : apply_decor_right<
		MT, T, concat<
			string<' ','c','o','n','s','t'>,
			string<' ','v','o','l','a','t','i','l','e'>,
			Str
		>
	> { };

	template <typename Str>
	struct extent : apply_decor_extent<MT, T, Str> { };

	template <typename Str>
	struct params : apply_decor_params<MT, T, Str> { };
};

template <typename MO, typename T>
struct decor<MO, T[]>
{
	using MT = get_aliased<MIRRORED(T)>;

	template <typename Str>
	struct left : apply_decor_left<MT, T, Str> { };

	template <typename Str>
	struct base : apply_decor_base<MT, T, Str> { };

	template <typename Str>
	struct right : apply_decor_right<MT, T, Str> { };

	template <typename Str>
	struct extent : apply_decor_extent<
		MT, T, concat<Str, string<'[',']'>>
	> { };

	template <typename Str>
	struct params : apply_decor_params<MT, T, Str> { };
};

template <typename MO, typename T, unsigned N>
struct decor<MO, T[N]>
{
	using MT = get_aliased<MIRRORED(T)>;

	template <typename Str>
	struct left : apply_decor_left<MT, T, Str> { };

	template <typename Str>
	struct base : apply_decor_base<MT, T, Str> { };

	template <typename Str>
	struct right : apply_decor_right<MT, T, Str> { };

	template <typename Str>
	struct extent : apply_decor_extent<
		MT, T, concat<Str, string<'['>, uint_to_dec_str<N>, string<']'>>
	> { };

	template <typename Str>
	struct params : apply_decor_params<MT, T, Str> { };
};

template <typename MO, typename R, typename ... P>
struct decor<MO, R(P...)>
{
	using MR = get_aliased<MIRRORED(R)>;

	template <typename Str>
	struct left : concat<
		Str,
		apply_decor_left<MR, R, empty_string>,
		apply_decor_base<MR, R, empty_string>,
		apply_decor_right<MR, R, empty_string>,
		apply_decor_extent<MR, R, empty_string>
	> { };

	template <typename Str>
	struct base : Str { };

	template <typename Str>
	struct right : Str { };

	template <typename Str>
	struct extent : Str { };

	template <typename Str>
	struct params : concat<
		Str,
		string<'('>, join<
			string<','>,
			eval<op_get_full_name<get_aliased<MIRRORED(P)>>>...
		>, string<')'>,
		apply_decor_params<MR, R, empty_string>
	> { };
};

template <typename MO, typename R, typename ... P>
struct decor<MO, R(*)(P...)>
{
	using MR = get_aliased<MIRRORED(R)>;

	template <typename Str>
	struct left : concat<
		Str,
		apply_decor_left<MR, R, empty_string>,
		apply_decor_base<MR, R, empty_string>,
		apply_decor_right<MR, R, empty_string>,
		apply_decor_extent<MR, R, empty_string>,
		string<'('>
	> { };

	template <typename Str>
	struct base : Str { };

	template <typename Str>
	struct right : concat<string<'*'>, Str> { };

	template <typename Str>
	struct extent : Str { };

	template <typename Str>
	struct params : concat<
		string<')'>, Str,
		string<'('>, join<
			string<','>,
			eval<op_get_full_name<get_aliased<MIRRORED(P)>>>...
		>, string<')'>,
		apply_decor_params<MR, R, empty_string>
	> { };
};

template <typename MO, template <typename...> class T, typename ... P>
struct decor<MO, T<P...>>
{
	template <typename Str>
	struct left : Str { };

	template <typename Str>
	struct base : op_get_scope_spec<get_aliased<MIRRORED(T<P...>)>> { };

	template <typename Str>
	struct right : concat<
		string<'<'>, join<
			string<','>,
			eval<op_get_full_name<get_aliased<MIRRORED(P)>>>...
		>, string<'>'>, Str
	> { };

	template <typename Str>
	struct extent : Str { };

	template <typename Str>
	struct params : Str { };
};

template <>
struct do_get_full_name<none, none>
 : empty_string
{ };

template <typename MO, typename T>
struct do_get_full_name
 : concat<
	apply_decor_left<MO, T, empty_string>,
	apply_decor_base<MO, T, empty_string>,
	apply_decor_right<MO, T, empty_string>,
	apply_decor_extent<MO, T, empty_string>,
	apply_decor_params<MO, T, empty_string>
>
{ };

template <>
struct op_get_full_name<none>
 : empty_string
{ };

template <typename MO>
struct op_get_full_name<metaobject<MO>>
 : do_get_full_name<
	metaobject<MO>,
	get_reflected_type<metaobject<MO>>
>
{ };

} // namespace _aux

template <typename X>
using get_full_name = eval<_aux::op_get_full_name<X>>;

} // namespace mirror

#endif //include guard

