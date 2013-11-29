/**
 *  @file mire/mirror/traits.hpp
 *  @brief Metaobject traits
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_TRAITS_1310291537_HPP
#define MIRE_MIRROR_TRAITS_1310291537_HPP

#include <mire/ct/int_const.hpp>
#include <mire/ct/lambda.hpp>
#include <mire/mirror/evaluate.hpp>
#include <mire/mirror/tags.hpp>

namespace mire {
namespace mirror {

/** @defgroup mirror_traits Mirror metaobject traits
 *
 *  Metafunctions in this group can be used to detect if a type is a model
 *  of Metaobject and if so determine its properties, like the main category,
 *  whether it is Named, Scoped, ClassMember, etc.
 */

// *is_metaobject*
namespace _aux {

	template <typename X>
	struct is_metaobject
	 : ct::false_type
	{ };

	template <typename R, typename M>
	struct is_metaobject<meta<R, M>>
	 : ct::true_type
	{ };

	template <typename T>
	struct is_metaobject<spec<T>>
	 : ct::true_type
	{ };

} // namespace _aux

/// Returns true_type if the argument @c X is a Metaobject, false_type otherwise
/**
 *  @ingroup mirror_traits
 */
template <typename X>
struct is_metaobject
#ifndef MIRROR_DOCUMENTATION_ONLY
 : _aux::is_metaobject<typename evaluate<X>::type>
#else
 : BooleanConstant
#endif
{ };

// *is_specifier*
namespace _aux {

	template <typename X>
	struct is_specifier
	 : ct::false_type
	{ };

	template <typename T>
	struct is_specifier<spec<T>>
	 : ct::true_type
	{ };

} // namespace _aux

/// Returns true_type if the argument @c X is a Specifier, false_type otherwise
/**
 *  @ingroup mirror_traits
 */
template <typename X>
struct is_specifier
#ifndef MIRROR_DOCUMENTATION_ONLY
 : _aux::is_specifier<typename evaluate<X>::type>
#else
 : BooleanConstant
#endif
{ };

// *category*
namespace _aux {

	template <typename X>
	struct category
	{
		typedef void type;
	};

	template <typename R, typename M>
	struct category<meta<R, M>>
	{
		typedef typename R::category type;
	};

} // namespace _aux


/// Returns the main category of a Metaobject
/**
 *  @ingroup mirror_traits
 */
template <typename Metaobject>
struct category
#ifndef MIRROR_DOCUMENTATION_ONLY
 : _aux::category<typename evaluate<Metaobject>::type>
{ };
#else
{
	/// The main category of the Metaobject passed as argument
	typedef MetaobjectCategory type;
};
#endif

// *is_a*
namespace _aux {

template <typename Reg, typename MOC1, typename MOC2>
struct same_ctg
 : ct::false_type
{ };

template <typename Reg>
struct same_ctg<Reg, meta_global_scope_tag, meta_namespace_tag>
 : ct::true_type
{ };

template <typename Reg>
struct same_ctg<Reg, meta_class_tag, meta_type_tag>
 : ct::true_type
{ };

template <typename Reg, typename MOC>
struct same_ctg<Reg, MOC, MOC>
 : ct::true_type
{ };

template <typename Reg>
struct same_ctg<Reg, meta_typedef_tag, meta_typedef_tag>
 : ct::true_type
{ };

template <typename Reg, typename MOC>
struct same_ctg<Reg, meta_typedef_tag, MOC>
 : same_ctg<
	typename Reg::typedef_type,
	typename Reg::typedef_type::category,
	MOC
>
{ };

template <typename X, typename MOC>
struct is_a
 : ct::false_type
{ };

template <typename Reg, typename M, typename MOC>
struct is_a<meta<Reg, M>, MOC>
 : same_ctg<Reg, typename Reg::category, MOC>
{ };

} // namespace _aux

/// Returns true_type if the argument @c X falls into a @c MetaobjectCategory
/**
 *  @ingroup mirror_traits
 */
template <typename X, typename MetaobjectCategory>
struct is_a
#ifndef MIRROR_DOCUMENTATION_ONLY
 : _aux::is_a<typename evaluate<X>::type, MetaobjectCategory>
#else
 : BooleanConstant
#endif
{ };

// *has_name*
namespace _aux {

	template <typename X>
	struct has_name
	 : ct::false_type
	{ };

	template <typename R, typename M>
	struct has_name<meta<R, M>>
	 : R::has_name
	{ };

} // namespace _aux

// *has_type_trait*
namespace _aux {

	template <typename X, template <typename> class Trait>
	struct has_type_trait;

	template <typename R, typename M, template <typename> class Trait>
	struct has_type_trait<meta<R, M>, Trait>
	 : Trait<M>
	{ };

} // namespace _aux

/// Returns true type if the type reflected by @c Metaobject has the type @c Trait
/**
 *  @note This metafunction should be used only on Metaobjects reflecting types.
 *
 *  @ingroup mirror_traits
 */
template <typename Metaobject, template <typename> class Trait>
struct has_type_trait
#ifndef MIRROR_DOCUMENTATION_ONLY
 : _aux::has_type_trait<typename evaluate<Metaobject>::type, Trait>
#else
 : BooleanConstant
#endif
{ };

// *modify_type*
namespace _aux {

	template <typename X, template <typename> class Modifier>
	struct modify_type;

	template <typename R, typename M, template <typename> class Modifier>
	struct modify_type<meta<R, M>, Modifier>
	 : meta<R, typename Modifier<M>::type>
	{ };

} // namespace _aux

/// Modifies the type reflected by @c Metaobject with @c the Modifier metafunction
/**
 *  @note This metafunction should be used only on Metaobjects reflecting types.
 *
 *  @ingroup mirror_traits
 */
template <typename Metaobject, template <typename> class Modifier>
struct modify_type
#ifndef MIRROR_DOCUMENTATION_ONLY
 : _aux::modify_type<typename evaluate<Metaobject>::type, Modifier>
#else
 : Metaobject
#endif
{ };

// *apply_on_type*
namespace _aux {

	template <typename X, typename Expr>
	struct apply_on_type;

	template <typename R, typename M, typename Expr>
	struct apply_on_type<meta<R, M>, Expr>
	 : meta<R, typename ct::apply<Expr, M>::type>
	{ };

} // namespace _aux

/// Modifies the type reflected by @c Metaobject with the unary @c Expression
/**
 *  @note This metafunction should be used only on Metaobjects reflecting types.
 *
 *  @ingroup mirror_traits
 */
template <typename Metaobject, typename Expression>
struct apply_on_type
#ifndef MIRROR_DOCUMENTATION_ONLY
 : _aux::apply_on_type<typename evaluate<Metaobject>::type, Expression>
#else
 : Metaobject
#endif
{ };

/// Returns true_type if the argument @c X is a Named, false_type otherwise
/**
 *  @ingroup mirror_traits
 */
template <typename X>
struct has_name
#ifndef MIRROR_DOCUMENTATION_ONLY
 : _aux::has_name<typename evaluate<X>::type>
#else
 : BooleanConstant
#endif
{ };

// *has_scope*
namespace _aux {

	template <typename X>
	struct has_scope
	 : ct::false_type
	{ };

	template <typename R, typename M>
	struct has_scope<meta<R, M>>
	 : R::has_scope
	{ };

} // namespace _aux

/// Returns true_type if the argument @c X is a Scoped, false_type otherwise
/**
 *  @ingroup mirror_traits
 */
template <typename X>
struct has_scope
#ifndef MIRROR_DOCUMENTATION_ONLY
 : _aux::has_scope<typename evaluate<X>::type>
#else
 : BooleanConstant
#endif
{ };

// *is_scope*
namespace _aux {

	template <typename X>
	struct is_scope
	 : ct::false_type
	{ };

	template <typename R, typename M>
	struct is_scope<meta<R, M*>>
	 : ct::false_type
	{ };

	template <typename R, typename M>
	struct is_scope<meta<R, M&>>
	 : ct::false_type
	{ };

	template <typename R, typename M>
	struct is_scope<meta<R, M&&>>
	 : ct::false_type
	{ };

	template <typename R, typename M>
	struct is_scope<meta<R, M[]>>
	 : ct::false_type
	{ };

	template <typename R, typename M, size_t N>
	struct is_scope<meta<R, M[N]>>
	 : ct::false_type
	{ };

	template <typename Reg, typename MOC>
	struct is_scope_hlp
	 : Reg::is_scope
	{ };

	template <typename Reg>
	struct is_scope_hlp<Reg, meta_typedef_tag>
	 : Reg::typedef_type::is_scope
	{ };

	template <typename R, typename M>
	struct is_scope<meta<R, M>>
	 : is_scope_hlp<R, typename R::category>
	{ };

} // namespace _aux


/// Returns true_type if the argument @c X is a Scope, false_type otherwise
/**
 *  @ingroup mirror_traits
 */
template <typename X>
struct is_scope
#ifndef MIRROR_DOCUMENTATION_ONLY
 : _aux::is_scope<typename evaluate<X>::type>
#else
 : BooleanConstant
#endif
{ };

// *is_class_member*
namespace _aux {

	template <typename X>
	struct is_class_member
	 : ct::false_type
	{ };

	template <typename R, typename M>
	struct is_class_member<meta<R, M>>
	 : R::is_class_member
	{ };

} // namespace _aux

/// Returns true_type if the argument @c X is a ClassMember, false_type otherwise
/**
 *  @ingroup mirror_traits
 */
template <typename X>
struct is_class_member
#ifndef MIRROR_DOCUMENTATION_ONLY
 : _aux::is_class_member<typename evaluate<X>::type>
#else
 : BooleanConstant
#endif
{ };

// *has_template*
namespace _aux {

	template <typename X>
	struct has_template
	 : ct::false_type
	{ };

	template <typename R, template <typename...> class T, typename ... P>
	struct has_template<meta<R, T<P...>>>
	 : R::is_template
	{ };

	template <typename R, typename M>
	struct has_template<meta<R, M>>
	 : R::has_template
	{ };

} // namespace _aux

/// Returns true_type if the argument @c X is templated, false_type otherwise
/**
 *  @ingroup mirror_traits
 */
template <typename X>
struct has_template
#ifndef MIRROR_DOCUMENTATION_ONLY
 : _aux::has_template<typename evaluate<X>::type>
#else
 : BooleanConstant
#endif
{ };

// *is_template*
namespace _aux {

	template <typename X>
	struct is_template
	 : ct::false_type
	{ };

	template <typename R>
	struct is_template<meta<R, void>>
	 : R::is_template
	{ };

	template <typename R, typename M>
	struct is_template<meta<R, M>>
	 : ct::false_type
	{ };

} // namespace _aux

/// Returns true_type if the argument @c X is a Template, false_type otherwise
/**
 *  @ingroup mirror_traits
 */
template <typename X>
struct is_template
#ifndef MIRROR_DOCUMENTATION_ONLY
 : _aux::is_template<typename evaluate<X>::type>
#else
 : BooleanConstant
#endif
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
