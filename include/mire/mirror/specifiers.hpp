
/**
 *  @file mire/mirror/specifiers.cpp
 *  @brief Declaration of specifiers.
 *
 *  @note This is an automatically generated header file, do not modify manually.
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRROR_SPECIFIERS_1311042119_HPP
#define MIRROR_SPECIFIERS_1311042119_HPP

namespace mirror {

struct spec_none_tag
{
	static constexpr const char* _kw_c_str = "";
	static constexpr std::size_t _kw_size  = 0;
};


struct spec_extern_tag
{
	static constexpr const char* _kw_c_str = "extern";
	static constexpr std::size_t _kw_size  = 6;
};


struct spec_static_tag
{
	static constexpr const char* _kw_c_str = "static";
	static constexpr std::size_t _kw_size  = 6;
};


struct spec_mutable_tag
{
	static constexpr const char* _kw_c_str = "mutable";
	static constexpr std::size_t _kw_size  = 7;
};


struct spec_register_tag
{
	static constexpr const char* _kw_c_str = "register";
	static constexpr std::size_t _kw_size  = 8;
};


struct spec_thread_local_tag
{
	static constexpr const char* _kw_c_str = "thread local";
	static constexpr std::size_t _kw_size  = 12;
};


struct spec_constexpr_tag
{
	static constexpr const char* _kw_c_str = "constexpr";
	static constexpr std::size_t _kw_size  = 9;
};


struct spec_const_tag
{
	static constexpr const char* _kw_c_str = "const";
	static constexpr std::size_t _kw_size  = 5;
};


struct spec_virtual_tag
{
	static constexpr const char* _kw_c_str = "virtual";
	static constexpr std::size_t _kw_size  = 7;
};


struct spec_private_tag
{
	static constexpr const char* _kw_c_str = "private";
	static constexpr std::size_t _kw_size  = 7;
};


struct spec_protected_tag
{
	static constexpr const char* _kw_c_str = "protected";
	static constexpr std::size_t _kw_size  = 9;
};


struct spec_public_tag
{
	static constexpr const char* _kw_c_str = "public";
	static constexpr std::size_t _kw_size  = 6;
};


struct spec_class_tag
{
	static constexpr const char* _kw_c_str = "class";
	static constexpr std::size_t _kw_size  = 5;
};


struct spec_struct_tag
{
	static constexpr const char* _kw_c_str = "struct";
	static constexpr std::size_t _kw_size  = 6;
};


struct spec_union_tag
{
	static constexpr const char* _kw_c_str = "union";
	static constexpr std::size_t _kw_size  = 5;
};


struct spec_enum_tag
{
	static constexpr const char* _kw_c_str = "enum";
	static constexpr std::size_t _kw_size  = 4;
};


struct spec_enum_class_tag
{
	static constexpr const char* _kw_c_str = "enum class";
	static constexpr std::size_t _kw_size  = 10;
};

} // namespace mirror
#endif // include guard
