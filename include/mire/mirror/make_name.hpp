/**
 *  @file mire/mirror/make_name.hpp
 *  @brief Helper metafunctions for building derived type names.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_MAKE_NAME_1310291537_HPP
#define MIRE_MIRROR_MAKE_NAME_1310291537_HPP

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/evaluate.hpp>

#include <mire/ct/range.hpp>
#include <mire/ct/string.hpp>
#include <mire/ct/concat.hpp>
#include <mire/ct/prepend.hpp>
#include <mire/ct/int_to_str.hpp>

namespace mire {
namespace mirror {
namespace _aux {

// make_name temp data
template <
	typename Left = ct::empty_string,
	typename Main = ct::empty_string,
	typename Right = ct::empty_string,
	typename Exts = ct::empty_string,
	typename Args = ct::empty_string
> struct make_name_data
{
	typedef Left left;
	typedef Main main;
	typedef Right right;
	typedef Exts exts;
	typedef Args args;
};

// make_name helper
template <typename MakeData>
struct finish_name
 : ct::concat<
	typename MakeData::left,
	typename MakeData::main,
	typename MakeData::right,
	typename MakeData::exts,
	typename MakeData::args
>
{ };

// make_name helper
template <template <typename> class GetName, typename MakeData, typename Meta>
struct do_make_name;

// make_name
template <template <typename> class GetName, typename Meta>
struct make_name
 : finish_name<
	do_make_name<
		GetName,
		make_name_data<>,
		typename mirror::evaluate<Meta>::type
	>
>
{ };


// <T>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M
> struct do_make_name<GetName, MakeData, mirror::meta<R, M>>
 : make_name_data<
	typename MakeData::left,
	typename GetName<R>::type,
	typename MakeData::right,
	typename MakeData::exts,
	typename MakeData::args
>
{ };

// right prefix helper
template <
	template <typename> class GetName,
	typename MakeData,
	typename Meta,
	typename prefix
> struct do_make_name_rt_pfx
 : do_make_name<
	GetName,
	make_name_data<
		typename MakeData::left,
		typename MakeData::main,
		typename ct::concat<
			prefix,
			typename MakeData::right
		>::type,
		typename MakeData::exts,
		typename MakeData::args
	>,
	Meta
>
{ };

// <T const> helper
template <
	template <typename> class GetName,
	typename MakeData,
	typename Meta
> struct do_make_name_const
 : do_make_name_rt_pfx<
	GetName,
	MakeData,
	Meta,
	ct::string<' ','c','o','n','s','t'>
>
{ };

// <T volatile> helper
template <
	template <typename> class GetName,
	typename MakeData,
	typename Meta
> struct do_make_name_volatile
 : do_make_name_rt_pfx<
	GetName,
	MakeData,
	Meta,
	ct::string<' ','v','o','l','a','t','i','l','e'>
>
{ };

// <T const volatile> helper
template <
	template <typename> class GetName,
	typename MakeData,
	typename Meta
> struct do_make_name_cv
 : do_make_name_rt_pfx<
	GetName,
	MakeData,
	Meta,
	ct::string<' ','c','o','n','s','t',' ','v','o','l','a','t','i','l','e'>
>
{ };

// <T*> helper
template <
	template <typename> class GetName,
	typename MakeData,
	typename Meta
> struct do_make_name_ptr
 : do_make_name_rt_pfx<
	GetName,
	MakeData,
	Meta,
	ct::string<' ','*'>
>
{ };

// <T&> helper
template <
	template <typename> class GetName,
	typename MakeData,
	typename Meta
> struct do_make_name_lvref
 : do_make_name_rt_pfx<
	GetName,
	MakeData,
	Meta,
	ct::string<' ','&'>
>
{ };

// <T&&> helper
template <
	template <typename> class GetName,
	typename MakeData,
	typename Meta
> struct do_make_name_rvref
 : do_make_name_rt_pfx<
	GetName,
	MakeData,
	Meta,
	ct::string<' ','&','&'>
>
{ };

// <T[]> helper
template <
	template <typename> class GetName,
	typename MakeData,
	typename Meta
> struct do_make_name_array
 : do_make_name<
	GetName,
	make_name_data<
		typename MakeData::left,
		typename MakeData::main,
		typename MakeData::right,
		typename ct::concat<
			typename MakeData::exts,
			ct::string<' ','[',']'>
		>::type,
		typename MakeData::args
	>,
	Meta
>
{ };

// <T[N]> helper
template <
	template <typename> class GetName,
	typename MakeData,
	typename Meta,
	size_t N
> struct do_make_name_array_N
 : do_make_name<
	GetName,
	make_name_data<
		typename MakeData::left,
		typename MakeData::main,
		typename MakeData::right,
		typename ct::concat<
			typename MakeData::exts,
			ct::string<' ','['>,
			ct::int_to_str10_c<size_t, N, char>,
			ct::string<']'>
		>::type,
		typename MakeData::args
	>,
	Meta
>
{ };

// <T(&)[N]> helper
template <
	template <typename> class GetName,
	typename MakeData,
	typename Meta,
	size_t N
> struct do_make_name_array_N_ref
 : do_make_name<
	GetName,
	make_name_data<
		typename MakeData::left,
		typename MakeData::main,
		typename ct::concat<
			typename MakeData::right,
			ct::string<' ','(','&',')'>
		>::type,
		typename ct::concat<
			typename MakeData::exts,
			ct::string<' ','['>,
			ct::int_to_str10_c<size_t, N, char>,
			ct::string<']'>
		>::type,
		typename MakeData::args
	>,
	Meta
>
{ };

// <T const>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M
> struct do_make_name<GetName, MakeData, mirror::meta<R, M const>>
 : do_make_name_const<GetName, MakeData, mirror::meta<R, M>>
{ };

// <T volatile>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M
> struct do_make_name<GetName, MakeData, mirror::meta<R, M volatile>>
 : do_make_name_volatile<GetName, MakeData, mirror::meta<R, M>>
{ };

// <T const volatile>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M
> struct do_make_name<GetName, MakeData, mirror::meta<R, M const volatile>>
 : do_make_name_cv<GetName, MakeData, mirror::meta<R, M>>
{ };

// <T*>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M
> struct do_make_name<GetName, MakeData, mirror::meta<R, M *>>
 : do_make_name_ptr<GetName, MakeData, mirror::meta<R, M>>
{ };

// <T&>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M
> struct do_make_name<GetName, MakeData, mirror::meta<R, M &>>
 : do_make_name_lvref<GetName, MakeData, mirror::meta<R, M>>
{ };

// <T&&>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M
> struct do_make_name<GetName, MakeData, mirror::meta<R, M &&>>
 : do_make_name_rvref<GetName, MakeData, mirror::meta<R, M>>
{ };

// <T[]>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M
> struct do_make_name<GetName, MakeData, mirror::meta<R, M[]>>
 : do_make_name_array<GetName, MakeData, mirror::meta<R, M>>
{ };

// <T const[]>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M
> struct do_make_name<GetName, MakeData, mirror::meta<R, M const[]>>
 : do_make_name_array<GetName, MakeData, mirror::meta<R, M const>>
{ };

// <T volatile[]>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M
> struct do_make_name<GetName, MakeData, mirror::meta<R, M volatile []>>
 : do_make_name_array<GetName, MakeData, mirror::meta<R, M volatile>>
{ };

// <T const volatile[]>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M
> struct do_make_name<GetName, MakeData, mirror::meta<R, M const volatile []>>
 : do_make_name_array<GetName, MakeData, mirror::meta<R, M const volatile>>
{ };

// <T[N]>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M,
	size_t N
> struct do_make_name<GetName, MakeData, mirror::meta<R, M[N]>>
 : do_make_name_array_N<GetName, MakeData, mirror::meta<R, M>, N>
{ };

// <T const[N]>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M,
	size_t N
> struct do_make_name<GetName, MakeData, mirror::meta<R, M const [N]>>
 : do_make_name_array_N<GetName, MakeData, mirror::meta<R, M const>, N>
{ };

// <T volatile[N]>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M,
	size_t N
> struct do_make_name<GetName, MakeData, mirror::meta<R, M volatile [N]>>
 : do_make_name_array_N<GetName, MakeData, mirror::meta<R, M volatile>, N>
{ };

// <T const volatile[N]>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M,
	size_t N
> struct do_make_name<GetName, MakeData, mirror::meta<R, M const volatile [N]>>
 : do_make_name_array_N<GetName, MakeData, mirror::meta<R, M const volatile>, N>
{ };

// <T(&)[N]>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M,
	size_t N
> struct do_make_name<GetName, MakeData, mirror::meta<R, M(&)[N]>>
 : do_make_name_array_N_ref<GetName, MakeData, mirror::meta<R, M>, N>
{ };

// <T const(&)[N]>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M,
	size_t N
> struct do_make_name<GetName, MakeData, mirror::meta<R, M const (&)[N]>>
 : do_make_name_array_N_ref<GetName, MakeData, mirror::meta<R, M const>, N>
{ };

// <T volatile(&)[N]>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M,
	size_t N
> struct do_make_name<GetName, MakeData, mirror::meta<R, M volatile (&)[N]>>
 : do_make_name_array_N_ref<GetName, MakeData, mirror::meta<R, M volatile>, N>
{ };

// <T const volatile(&)[N]>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M,
	size_t N
> struct do_make_name<GetName, MakeData, mirror::meta<R, M const volatile (&)[N]>>
 : do_make_name_array_N_ref<GetName, MakeData, mirror::meta<R, M const volatile>, N>
{ };

template <template <typename> class GetName, typename Ps>
struct do_make_name_fn_args;

template <template <typename> class GetName>
struct do_make_name_fn_args<GetName, ct::range<>>
 : ct::string<'(', 'v','o','i','d',')'>
{ };

template <template <typename> class GetName, typename P0, typename ... P>
struct do_make_name_fn_args<GetName, ct::range<P0, P...>>
 : ct::concat<
	ct::string<'('>,
	make_name<GetName, mirror::mirrored_t<P0>>,
	ct::prepend_c<
		make_name<GetName, mirror::mirrored_t<P>>,
		char, ',',' '
	>...,
	ct::string<')'>
>
{ };

// <T (P...)>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename RV,
	typename ... P
> struct do_make_name<GetName, MakeData, mirror::meta<R, RV(P...)>>
 : make_name_data<
	make_name<GetName, mirror::mirrored_t<RV>>,
	typename MakeData::main,
	typename MakeData::right,
	ct::concat<
		ct::string<' '>,
		typename GetName<R>::type,
		typename MakeData::exts
	>,
	typename do_make_name_fn_args<GetName, ct::range<P...>>::type
>
{ };

// <T (*)(P...)>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename RV,
	typename ... P
> struct do_make_name<GetName, MakeData, mirror::meta<R, RV(*)(P...)>>
 : do_make_name<
	GetName,
	make_name_data<
		typename MakeData::left,
		ct::string<'('>,
		ct::concat<
			typename MakeData::right,
			ct::string<' ','*'>
		>,
		ct::string<')'>,
		typename MakeData::args
	>,
	mirror::meta<R, RV(P...)>
>
{ };

// <T (*(*)(P0...))(P1...)>
template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename RV,
	typename ... P0,
	typename ... P1
> struct do_make_name<GetName, MakeData, mirror::meta<R, RV(*(*)(P1...))(P0...)>>
 : make_name_data<
	typename do_make_name<GetName, MakeData, mirror::meta<R, RV(*)(P0...)>>::left,
	typename do_make_name<GetName, MakeData, mirror::meta<R, RV(*)(P0...)>>::main,
	ct::concat<
		ct::string<' ','*','('>,
		typename do_make_name<GetName, MakeData, mirror::meta<R, RV(*)(P0...)>>::right
	>,
	typename do_make_name<GetName, MakeData, mirror::meta<R, RV(*)(P0...)>>::exts,
	ct::concat<
		typename do_make_name_fn_args<GetName, ct::range<P1...>>::type,
		ct::string<')'>,
		typename do_make_name<GetName, MakeData, mirror::meta<R, RV(*)(P0...)>>::args
	>
>
{ };

// <T<P...>>
template <
	template <typename> class GetName,
	typename MakeData,
	typename Meta,
	typename IsTpl
> struct do_make_name_tpl;

template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	template <typename ...> class T,
	typename P0,
	typename ... P
> struct do_make_name_tpl<
	GetName,
	MakeData,
	meta<R, T<P0, P...>>,
	ct::true_type
>: make_name_data<
	typename MakeData::left,
	typename GetName<R>::type,
	typename ct::concat<
		ct::string<'<'>,
		make_name<GetName, mirror::mirrored_t<P0>>,
		ct::prepend_c<
			make_name<GetName, mirror::mirrored_t<P>>,
			char, ',',' '
		>...,
		ct::string<'>'>
	>::type,
	typename MakeData::exts,
	typename MakeData::args
>
{ };

template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	typename M
> struct do_make_name_tpl<
	GetName,
	MakeData,
	meta<R, M>,
	ct::false_type
>: make_name_data<
	typename MakeData::left,
	typename GetName<R>::type,
	typename MakeData::right,
	typename MakeData::exts,
	typename MakeData::args
>
{ };

template <
	template <typename> class GetName,
	typename MakeData,
	typename R,
	template <typename ...P> class T,
	typename ... P
> struct do_make_name<GetName, MakeData, mirror::meta<R, T<P...>>>
 : do_make_name_tpl<
	GetName,
	MakeData,
	mirror::meta<R, T<P...>>,
	typename R::is_template
>
{ };

} // namespace _aux
} // namespace mirror
} // namespace mire

#endif // include guard
