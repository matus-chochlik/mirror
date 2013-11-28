/**
 *  @file mire/tags/specifier.hpp
 *  @brief Declaration of specifier tags.
 *
 *  @note This is an automatically generated header file, do not modify manually.
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRE_TAGS_SPECIFIER_1311042119_HPP
#define MIRE_TAGS_SPECIFIER_1311042119_HPP

namespace mire {
namespace tags {

struct spec_none_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "";
		static constexpr std::size_t size  = 0;
	};
};

struct spec_extern_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "extern";
		static constexpr std::size_t size  = 6;
	};
};

struct spec_static_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "static";
		static constexpr std::size_t size  = 6;
	};
};

struct spec_mutable_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "mutable";
		static constexpr std::size_t size  = 7;
	};
};

struct spec_register_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "register";
		static constexpr std::size_t size  = 8;
	};
};

struct spec_thread_local_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "thread local";
		static constexpr std::size_t size  = 12;
	};
};

struct spec_constexpr_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "constexpr";
		static constexpr std::size_t size  = 9;
	};
};

struct spec_const_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "const";
		static constexpr std::size_t size  = 5;
	};
};

struct spec_virtual_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "virtual";
		static constexpr std::size_t size  = 7;
	};
};

struct spec_private_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "private";
		static constexpr std::size_t size  = 7;
	};
};

struct spec_protected_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "protected";
		static constexpr std::size_t size  = 9;
	};
};

struct spec_public_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "public";
		static constexpr std::size_t size  = 6;
	};
};

struct spec_class_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "class";
		static constexpr std::size_t size  = 5;
	};
};

struct spec_struct_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "struct";
		static constexpr std::size_t size  = 6;
	};
};

struct spec_union_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "union";
		static constexpr std::size_t size  = 5;
	};
};

struct spec_enum_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "enum";
		static constexpr std::size_t size  = 4;
	};
};

struct spec_enum_class_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "enum class";
		static constexpr std::size_t size  = 10;
	};
};

struct spec_typedef_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "typedef";
		static constexpr std::size_t size  = 7;
	};
};

} // namespace tags
} // namespace mire
#endif // include guard
