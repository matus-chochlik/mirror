/**
 *  @file mire/mirror/intrinsic.hpp
 *  @brief Implementation of intrinsic meta-functions
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRROR_INTRINSIC_1310291537_HPP
#define MIRROR_INTRINSIC_1310291537_HPP

#include <mirror/fwd.hpp>
#include <mirror/stddef.hpp>

namespace mirror {

#define MIRRORED(NAME) mirror::meta<mirror::_reg::_##NAME::_, void>
// TODO: define only optionally
#define mirrored(NAME) MIRRORED(NAME)

template <typename T>
struct mirrored_t
{
	typedef meta<typename _reg::_type_reg<T>::type, T> type;
};

namespace _aux {

template <typename X>
struct _get_meta<mirror::mirrored_t<X>>
{
	typedef typename mirror::mirrored_t<X>::type type;
};

template <typename X>
struct _get_meta<mirror::scope<X>>
{
	typedef typename mirror::scope<X>::type type;
};

} // namespace _aux

template <typename X, typename M>
struct category<meta<X, M>>
{
	typedef typename X::category type;
};

template <typename X>
struct category<spec<X>>
{
	typedef X type;
};

template <typename X>
struct category
 : category<typename _aux::_get_meta<X>::type>
{ };

template <typename X>
struct keyword<spec<X>>
{
	static constexpr const char* c_str = X::_kw_c_str;
	static constexpr std::size_t size  = X::_kw_size;
};

template <typename X>
struct keyword
 : keyword<typename _aux::_get_meta<X>::type>
{ };

template <typename X, typename M>
struct base_name<meta<X, M>>
{
	static constexpr const char* c_str = X::base_name::c_str;
	static constexpr std::size_t size  = X::base_name::size;
};

template <typename X>
struct base_name
 : base_name<typename _aux::_get_meta<X>::type>
{ };

template <typename X, typename M>
struct full_name<meta<X, M>>
{
	static constexpr const char* c_str = X::full_name::c_str;
	static constexpr std::size_t size  = X::full_name::size;
};

template <typename X>
struct full_name
 : full_name<typename _aux::_get_meta<X>::type>
{ };

template <typename X, typename M>
struct scope<meta<X, M>>
{
	typedef meta<typename X::scope, void> type;
};

template <typename X>
struct scope
 : scope<typename _aux::_get_meta<X>::type>
{ };

template <typename X, typename M, typename P>
struct named_typedef<meta<X, M>, P>
{
	typedef typename X::template named_typedef<P> type;
};

template <typename X, typename P>
struct named_typedef
 : named_typedef<typename _aux::_get_meta<X>::type, P>
{ };

template <typename X, typename M, typename P>
struct named_mem_var<meta<X, M>, P>
{
	typedef typename X::template named_mem_var<P> type;
};

template <typename X, typename P>
struct named_mem_var
 : named_mem_var<typename _aux::_get_meta<X>::type, P>
{ };

} // namespace mirror

#endif // include guard
