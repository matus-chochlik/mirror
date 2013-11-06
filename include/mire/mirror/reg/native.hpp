
/**
 *  @file mire/mirror/reg/native.cpp
 *  @brief Pre-registering of native C++ types.
 *
 *  @note This is an automatically generated header file, do not modify manually.
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRROR_REG_NATIVE_1311042119_HPP
#define MIRROR_REG_NATIVE_1311042119_HPP

#include <mire/mirror/tags.hpp>
#include <mire/mirror/reg/global_scope.hpp>

namespace mirror {
namespace _reg {

namespace _void {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef void original_type;
		struct base_name
		{
			static constexpr const char* c_str = "void";
			static constexpr std::size_t size  = 4;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X void_;
		};

		template <typename X>
		struct named_mem_var
		{
			X void_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : void_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _void
template <>
struct _type_reg<void>
{
	typedef _void::_ type;
};


namespace _bool {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef bool original_type;
		struct base_name
		{
			static constexpr const char* c_str = "bool";
			static constexpr std::size_t size  = 4;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X bool_;
		};

		template <typename X>
		struct named_mem_var
		{
			X bool_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : bool_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _bool
template <>
struct _type_reg<bool>
{
	typedef _bool::_ type;
};


namespace _char {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef char original_type;
		struct base_name
		{
			static constexpr const char* c_str = "char";
			static constexpr std::size_t size  = 4;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X char_;
		};

		template <typename X>
		struct named_mem_var
		{
			X char_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : char_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _char
template <>
struct _type_reg<char>
{
	typedef _char::_ type;
};


namespace _signed_char {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef signed char original_type;
		struct base_name
		{
			static constexpr const char* c_str = "signed char";
			static constexpr std::size_t size  = 11;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X signed_char_;
		};

		template <typename X>
		struct named_mem_var
		{
			X signed_char_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : signed_char_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _signed_char
template <>
struct _type_reg<signed char>
{
	typedef _signed_char::_ type;
};


namespace _unsigned_char {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef unsigned char original_type;
		struct base_name
		{
			static constexpr const char* c_str = "unsigned char";
			static constexpr std::size_t size  = 13;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X unsigned_char_;
		};

		template <typename X>
		struct named_mem_var
		{
			X unsigned_char_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : unsigned_char_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _unsigned_char
template <>
struct _type_reg<unsigned char>
{
	typedef _unsigned_char::_ type;
};


namespace _wchar_t {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef wchar_t original_type;
		struct base_name
		{
			static constexpr const char* c_str = "wchar_t";
			static constexpr std::size_t size  = 7;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X wchar_t_;
		};

		template <typename X>
		struct named_mem_var
		{
			X wchar_t_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : wchar_t_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _wchar_t
template <>
struct _type_reg<wchar_t>
{
	typedef _wchar_t::_ type;
};


namespace _char16_t {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef char16_t original_type;
		struct base_name
		{
			static constexpr const char* c_str = "char16_t";
			static constexpr std::size_t size  = 8;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X char16_t_;
		};

		template <typename X>
		struct named_mem_var
		{
			X char16_t_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : char16_t_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _char16_t
template <>
struct _type_reg<char16_t>
{
	typedef _char16_t::_ type;
};


namespace _char32_t {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef char32_t original_type;
		struct base_name
		{
			static constexpr const char* c_str = "char32_t";
			static constexpr std::size_t size  = 8;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X char32_t_;
		};

		template <typename X>
		struct named_mem_var
		{
			X char32_t_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : char32_t_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _char32_t
template <>
struct _type_reg<char32_t>
{
	typedef _char32_t::_ type;
};


namespace _short_int {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef short int original_type;
		struct base_name
		{
			static constexpr const char* c_str = "short int";
			static constexpr std::size_t size  = 9;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X short_int_;
		};

		template <typename X>
		struct named_mem_var
		{
			X short_int_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : short_int_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _short_int
template <>
struct _type_reg<short int>
{
	typedef _short_int::_ type;
};


namespace _unsigned_short_int {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef unsigned short int original_type;
		struct base_name
		{
			static constexpr const char* c_str = "unsigned short int";
			static constexpr std::size_t size  = 18;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X unsigned_short_int_;
		};

		template <typename X>
		struct named_mem_var
		{
			X unsigned_short_int_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : unsigned_short_int_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _unsigned_short_int
template <>
struct _type_reg<unsigned short int>
{
	typedef _unsigned_short_int::_ type;
};


namespace _int {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef int original_type;
		struct base_name
		{
			static constexpr const char* c_str = "int";
			static constexpr std::size_t size  = 3;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X int_;
		};

		template <typename X>
		struct named_mem_var
		{
			X int_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : int_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _int
template <>
struct _type_reg<int>
{
	typedef _int::_ type;
};


namespace _unsigned_int {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef unsigned int original_type;
		struct base_name
		{
			static constexpr const char* c_str = "unsigned int";
			static constexpr std::size_t size  = 12;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X unsigned_int_;
		};

		template <typename X>
		struct named_mem_var
		{
			X unsigned_int_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : unsigned_int_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _unsigned_int
template <>
struct _type_reg<unsigned int>
{
	typedef _unsigned_int::_ type;
};


namespace _long_int {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef long int original_type;
		struct base_name
		{
			static constexpr const char* c_str = "long int";
			static constexpr std::size_t size  = 8;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X long_int_;
		};

		template <typename X>
		struct named_mem_var
		{
			X long_int_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : long_int_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _long_int
template <>
struct _type_reg<long int>
{
	typedef _long_int::_ type;
};


namespace _unsigned_long_int {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef unsigned long int original_type;
		struct base_name
		{
			static constexpr const char* c_str = "unsigned long int";
			static constexpr std::size_t size  = 17;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X unsigned_long_int_;
		};

		template <typename X>
		struct named_mem_var
		{
			X unsigned_long_int_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : unsigned_long_int_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _unsigned_long_int
template <>
struct _type_reg<unsigned long int>
{
	typedef _unsigned_long_int::_ type;
};


namespace _long_long_int {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef long long int original_type;
		struct base_name
		{
			static constexpr const char* c_str = "long long int";
			static constexpr std::size_t size  = 13;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X long_long_int_;
		};

		template <typename X>
		struct named_mem_var
		{
			X long_long_int_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : long_long_int_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _long_long_int
template <>
struct _type_reg<long long int>
{
	typedef _long_long_int::_ type;
};


namespace _unsigned_long_long_int {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef unsigned long long int original_type;
		struct base_name
		{
			static constexpr const char* c_str = "unsigned long long int";
			static constexpr std::size_t size  = 22;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X unsigned_long_long_int_;
		};

		template <typename X>
		struct named_mem_var
		{
			X unsigned_long_long_int_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : unsigned_long_long_int_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _unsigned_long_long_int
template <>
struct _type_reg<unsigned long long int>
{
	typedef _unsigned_long_long_int::_ type;
};


namespace _float {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef float original_type;
		struct base_name
		{
			static constexpr const char* c_str = "float";
			static constexpr std::size_t size  = 5;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X float_;
		};

		template <typename X>
		struct named_mem_var
		{
			X float_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : float_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _float
template <>
struct _type_reg<float>
{
	typedef _float::_ type;
};


namespace _double {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef double original_type;
		struct base_name
		{
			static constexpr const char* c_str = "double";
			static constexpr std::size_t size  = 6;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X double_;
		};

		template <typename X>
		struct named_mem_var
		{
			X double_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : double_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _double
template <>
struct _type_reg<double>
{
	typedef _double::_ type;
};


namespace _long_double {
	struct _
	{
		typedef meta_type_tag category;
		typedef _reg::_ scope;
		typedef long double original_type;
		struct base_name
		{
			static constexpr const char* c_str = "long double";
			static constexpr std::size_t size  = 11;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X long_double_;
		};

		template <typename X>
		struct named_mem_var
		{
			X long_double_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : long_double_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _long_double
template <>
struct _type_reg<long double>
{
	typedef _long_double::_ type;
};

} // namespace _reg
} // namespace mirror
#endif // include guard
