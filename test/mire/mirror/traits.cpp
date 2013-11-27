/**
 *  .file test/mire/mirror/traits.cpp
 *  .brief Test case for mirror compile-time metaobject traits
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_MIRROR_traits
#include <boost/test/unit_test.hpp>

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/traits.hpp>
#include <mire/mirror/original_type.hpp>
#include <mire/reg/native.hpp>
#include <mire/reg/std/vector.hpp>
#include <mire/reg/std/string.hpp>

#include <type_traits>

BOOST_AUTO_TEST_SUITE(mire_mirror_traits)

BOOST_AUTO_TEST_CASE(mire_mirror_traits_is_metaobject)
{
	using namespace mire::mirror;

	BOOST_CHECK((!is_metaobject<int>::value));
	BOOST_CHECK(( is_metaobject<mirrored_t<int>>::value));
	BOOST_CHECK(( is_metaobject<mirrored_t<std::vector<long>>>::value));
	BOOST_CHECK(( is_metaobject<mirrored_t<std::string>>::value));
}

BOOST_AUTO_TEST_CASE(mire_mirror_traits_category)
{
	using namespace mire::mirror;

	BOOST_CHECK((std::is_same<
		category<MIRRORED_GLOBAL_SCOPE()>::type,
		meta_global_scope_tag
	>::value));

	BOOST_CHECK((std::is_same<
		category<MIRRORED(std)>::type,
		meta_namespace_tag
	>::value));

	BOOST_CHECK((std::is_same<
		category<mirrored_t<float>>::type,
		meta_type_tag
	>::value));

	BOOST_CHECK((std::is_same<
		category<mirrored_t<std::string>>::type,
		meta_typedef_tag
	>::value));

	BOOST_CHECK((std::is_same<
		category<mirrored_t<std::wstring>>::type,
		meta_class_tag
	>::value));

	// TODO
}

BOOST_AUTO_TEST_CASE(mire_mirror_traits_is_a)
{
	using namespace mire::mirror;

	BOOST_CHECK((is_a<
		MIRRORED_GLOBAL_SCOPE(),
		meta_global_scope_tag
	>::value));

	BOOST_CHECK((is_a<
		MIRRORED_GLOBAL_SCOPE(),
		meta_namespace_tag
	>::value));

	BOOST_CHECK((!is_a<
		MIRRORED(std),
		meta_global_scope_tag
	>::value));

	BOOST_CHECK((!is_a<
		MIRRORED(std),
		meta_type_tag
	>::value));

	BOOST_CHECK((is_a<
		MIRRORED(std),
		meta_namespace_tag
	>::value));

	BOOST_CHECK((is_a<
		mirrored_t<int>,
		meta_type_tag
	>::value));

	BOOST_CHECK((is_a<
		mirrored_t<std::string>,
		meta_type_tag
	>::value));

	BOOST_CHECK((is_a<
		mirrored_t<std::string>,
		meta_typedef_tag
	>::value));

	BOOST_CHECK((is_a<
		mirrored_t<std::string>,
		meta_class_tag
	>::value));

	BOOST_CHECK(( is_a<
		mirrored_t<std::vector<int>>,
		meta_type_tag
	>::value));

	BOOST_CHECK((!is_a<
		mirrored_t<std::vector<int>>,
		meta_typedef_tag
	>::value));

	BOOST_CHECK((is_a<
		mirrored_t<std::vector<int>>,
		meta_class_tag
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_mirror_traits_has_type_trait)
{
	using namespace mire::mirror;

	BOOST_CHECK(( has_type_trait<mirrored_t<int>, std::is_integral>::value));
	BOOST_CHECK((!has_type_trait<mirrored_t<int>, std::is_void>::value));
	BOOST_CHECK((!has_type_trait<mirrored_t<int>, std::is_floating_point>::value));
	BOOST_CHECK((!has_type_trait<mirrored_t<int>, std::is_pointer>::value));
	BOOST_CHECK((!has_type_trait<mirrored_t<int>, std::is_reference>::value));

	BOOST_CHECK((!has_type_trait<mirrored_t<float*>, std::is_integral>::value));
	BOOST_CHECK((!has_type_trait<mirrored_t<float*>, std::is_void>::value));
	BOOST_CHECK(( has_type_trait<mirrored_t<float*>, std::is_pointer>::value));
	BOOST_CHECK((!has_type_trait<mirrored_t<float*>, std::is_reference>::value));

	BOOST_CHECK((!has_type_trait<mirrored_t<float&>, std::is_integral>::value));
	BOOST_CHECK((!has_type_trait<mirrored_t<float&>, std::is_floating_point>::value));
	BOOST_CHECK((!has_type_trait<mirrored_t<float&>, std::is_pointer>::value));
	BOOST_CHECK(( has_type_trait<mirrored_t<float&>, std::is_reference>::value));
}

BOOST_AUTO_TEST_CASE(mire_mirror_traits_modify_type)
{
	using namespace mire::mirror;

	BOOST_CHECK((std::is_same<
		original_type<
			modify_type<mirrored_t<int>, std::add_pointer>
		>::type,
		int*
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<
			modify_type<mirrored_t<int[10]>, std::decay>
		>::type,
		int*
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<
			modify_type<mirrored_t<int const>, std::remove_cv>
		>::type,
		int
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<
			modify_type<
				modify_type<
					mirrored_t<int>,
					std::add_const
				>,
				std::add_pointer
			>
		>::type,
		int const *
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<
			modify_type<
				modify_type<
					mirrored_t<int>,
					std::add_pointer
				>,
				std::add_const
			>
		>::type,
		int * const
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_mirror_traits_apply_on_type)
{
	using namespace mire::mirror;
	using mire::ct::arg;

	BOOST_CHECK((std::is_same<
		original_type<
			apply_on_type<
				mirrored_t<int>,
				std::add_pointer<
					std::add_const
						<std::add_pointer<arg<0>>
					>
				>
			>
		>::type,
		int * const *
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<
			apply_on_type<
				mirrored_t<std::string>,
				std::add_volatile<
					std::add_pointer<
						std::add_const<
							std::add_pointer<arg<0>>
						>
					>
				>
			>
		>::type,
		std::string * const * volatile
	>::value));

	BOOST_CHECK((std::is_same<
		original_type<
			apply_on_type<
				mirrored_t<std::string * const * volatile>,
				std::remove_volatile<
					std::remove_pointer<
						std::remove_const<
							std::remove_pointer<arg<0>>
						>
					>
				>
			>
		>::type,
		std::string
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_mirror_traits_has_name)
{
	using namespace mire::mirror;

	BOOST_CHECK((!has_name<int>::value));
	BOOST_CHECK(( has_name<MIRRORED_GLOBAL_SCOPE()>::value));
	BOOST_CHECK(( has_name<MIRRORED(std)>::value));
	BOOST_CHECK(( has_name<mirrored_t<int>>::value));
	BOOST_CHECK(( has_name<mirrored_t<std::vector<std::string>>>::value));
	BOOST_CHECK(( has_name<MIRRORED(std::vector)>::value));
}

BOOST_AUTO_TEST_CASE(mire_mirror_traits_has_scope)
{
	using namespace mire::mirror;

	BOOST_CHECK((!has_scope<int>::value));
	BOOST_CHECK(( has_scope<mirrored_t<int>>::value));
	BOOST_CHECK(( has_scope<mirrored_t<std::vector<wchar_t>>>::value));
	BOOST_CHECK(( has_scope<mirrored_t<std::string>>::value));
	BOOST_CHECK(( has_scope<mirrored_t<std::wstring>>::value));
}

BOOST_AUTO_TEST_CASE(mire_mirror_traits_is_scope)
{
	using namespace mire::mirror;

	BOOST_CHECK((!is_scope<int>::value));
	BOOST_CHECK((!is_scope<mirrored_t<int>>::value));
	BOOST_CHECK(( is_scope<mirrored_t<std::vector<wchar_t>>>::value));
	BOOST_CHECK((!is_scope<mirrored_t<std::vector<wchar_t>*>>::value));
	BOOST_CHECK((!is_scope<mirrored_t<std::vector<wchar_t>&>>::value));
	BOOST_CHECK(( is_scope<mirrored_t<std::string>>::value));
	BOOST_CHECK(( is_scope<mirrored_t<const std::string>>::value));
	BOOST_CHECK((!is_scope<mirrored_t<const std::string&>>::value));
	BOOST_CHECK(( is_scope<mirrored_t<std::wstring>>::value));
	BOOST_CHECK((!is_scope<mirrored_t<std::wstring&&>>::value));
	BOOST_CHECK((!is_scope<mirrored_t<std::wstring[]>>::value));
	BOOST_CHECK((!is_scope<mirrored_t<std::wstring[10]>>::value));
	BOOST_CHECK(( is_scope<MIRRORED_GLOBAL_SCOPE()>::value));
}

//TODO

BOOST_AUTO_TEST_SUITE_END()

