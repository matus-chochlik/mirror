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

#include "get_base_name.hpp"
#include "get_scope.hpp"
#include "get_reflected_type.hpp"
#include "conditional.hpp"
#include "traits.hpp"
#include "concat.hpp"
#include "int_to_str.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_full_name;

template <typename MO, typename T>
struct do_get_full_name;

template <typename T>
struct decor
{
	template <typename Str>
	struct left : Str { };

	template <typename Str>
	struct right : Str { };

	template <typename Str>
	struct extent : Str { };

	template <typename Str>
	struct params : Str { };
};

template <typename T, typename S>
using apply_decor_left = eval<typename decor<T>::template left<S>>;

template <typename T, typename S>
using apply_decor_right = eval<typename decor<T>::template right<S>>;

template <typename T, typename S>
using apply_decor_extent  = eval<typename decor<T>::template extent<S>>;

template <typename T, typename S>
using apply_decor_params  = eval<typename decor<T>::template params<S>>;

template <typename T>
struct decor<T*>
{
	template <typename Str>
	struct left : apply_decor_left<T, Str> { };

	template <typename Str>
	struct right
	 : apply_decor_right<
		T, concat<string<'*'>, Str>
	> { };

	template <typename Str>
	struct extent : apply_decor_extent<T, Str> { };

	template <typename Str>
	struct params : apply_decor_params<T, Str> { };
};

template <typename T>
struct decor<T&>
{
	template <typename Str>
	struct left : apply_decor_left<T, Str> { };

	template <typename Str>
	struct right
	 : apply_decor_right<
		T, concat<string<'&'>, Str>
	> { };

	template <typename Str>
	struct extent : apply_decor_extent<T, Str> { };

	template <typename Str>
	struct params : apply_decor_params<T, Str> { };
};

template <typename T>
struct decor<T const>
{
	template <typename Str>
	struct left : apply_decor_left<T, Str> { };

	template <typename Str>
	struct right
	 : apply_decor_right<
		T, concat<
			string<' ','c','o','n','s','t'>,
			Str
		>
	> { };

	template <typename Str>
	struct extent : apply_decor_extent<T, Str> { };

	template <typename Str>
	struct params : apply_decor_params<T, Str> { };
};

template <typename T>
struct decor<T volatile>
{
	template <typename Str>
	struct left : apply_decor_left<T, Str> { };

	template <typename Str>
	struct right
	 : apply_decor_right<
		T, concat<
			string<' ','v','o','l','a','t','i','l','e'>,
			Str
		>
	> { };

	template <typename Str>
	struct extent : apply_decor_extent<T, Str> { };

	template <typename Str>
	struct params : apply_decor_params<T, Str> { };
};

template <typename T>
struct decor<T const volatile>
{
	template <typename Str>
	struct left : apply_decor_left<T, Str> { };

	template <typename Str>
	struct right
	 : apply_decor_right<
		T, concat<
			string<' ','c','o','n','s','t'>,
			string<' ','v','o','l','a','t','i','l','e'>,
			Str
		>
	> { };

	template <typename Str>
	struct extent : apply_decor_extent<T, Str> { };

	template <typename Str>
	struct params : apply_decor_params<T, Str> { };
};

template <typename T>
struct decor<T[]>
{
	template <typename Str>
	struct left : apply_decor_left<T, Str> { };

	template <typename Str>
	struct right : apply_decor_right<T, Str> { };

	template <typename Str>
	struct extent : apply_decor_extent<
		T, concat<Str, string<'[',']'>>
	> { };

	template <typename Str>
	struct params : apply_decor_params<T, Str> { };
};

template <typename T, unsigned N>
struct decor<T[N]>
{
	template <typename Str>
	struct left : apply_decor_left<T, Str> { };

	template <typename Str>
	struct right : apply_decor_right<T, Str> { };

	template <typename Str>
	struct extent : apply_decor_extent<
		T, concat<Str, string<'['>, uint_to_dec_str<N>, string<']'>>
	> { };

	template <typename Str>
	struct params : apply_decor_params<T, Str> { };
};

template <>
struct do_get_full_name<none, none>
 : empty_string
{ };

template <typename MO, typename T>
struct do_get_full_name
 : concat<
	apply_decor_left<T, empty_string>,
	get_base_name<MO>,
	apply_decor_right<T, empty_string>,
	apply_decor_extent<T, empty_string>
>
{ };

template <>
struct op_get_full_name<none>
 : empty_string
{ };

template <typename MO>
struct op_get_full_name<metaobject<MO>>
 : do_get_full_name<
	metaobject<std::meta::get_underlying_object_m<MO>>,
	get_reflected_type<metaobject<MO>>
>
{ };

} // namespace _aux

template <typename X>
using get_full_name = eval<_aux::op_get_full_name<X>>;

} // namespace mirror

#endif //include guard

