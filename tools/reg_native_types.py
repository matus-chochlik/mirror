#!/usr/bin/python
# coding=utf-8
#  Copyright 2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
def print_file_header():
	import datetime
	print(
"""\
/**
 *  @file mire/reg/native.cpp
 *  @brief Pre-registering of native C++ types.
 *
 *  @note This is an automatically generated header file, do not modify manually.
 *
 *  Copyright 2012-%(year)s Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRE_REG_NATIVE_1311042119_HPP
#define MIRE_REG_NATIVE_1311042119_HPP

#include <mire/reg/global_scope.hpp>
""" % {'year': datetime.datetime.now().year}
	)

def print_reg_code(type_name, kind):
	type_name_ = str('_').join(type_name.split(' '))
	print(
"""
namespace _%(type_name_)s {
	struct _ : mire::reg::defaults
	{
		typedef meta_%(kind)s_tag category;
		typedef mire::reg::_ scope;
		typedef %(type_name)s original_type;
		struct base_name
		{
			static constexpr const char* c_str = "%(type_name)s";
			static constexpr std::size_t size  = %(name_size)d;
		};
		struct full_name
		{
			static constexpr const char* c_str = base_name::c_str;
			static constexpr std::size_t size  = base_name::size;
		};

		template <typename X>
		struct named_typedef
		{
			typedef X %(type_name_)s_;
		};

		template <typename X>
		struct named_mem_var
		{
			X %(type_name_)s_;

			named_mem_var(void) = default;

			template <typename ... P>
			named_mem_var(P&& ... p)
			 : %(type_name_)s_(std::forward<P>(p)...)
			{ }
		};
	};
} // namespace _%(type_name_)s
template <>
struct _type_reg<%(type_name)s>
{
	typedef _%(type_name_)s::_ type;
};
""" %		{
			'type_name_': type_name_,
			'type_name': type_name,
			'name_size': len(type_name),
			'kind': kind
		}
	)

def print_file_footer():
	print("""#endif // include guard""")


def main():
	native_types = [
		"void", "bool",
		"char", "signed char", "unsigned char",
		"wchar_t", "char16_t", "char32_t",
		"short int", "unsigned short int",
		"int", "unsigned int",
		"long int", "unsigned long int",
		"long long int", "unsigned long long int",
		"float", "double", "long double"
	]

	try:
		print_file_header()
		print("namespace mire {")
		print("namespace reg {")
		for native_type in native_types:
			print_reg_code(native_type, "type")
		print("} // namespace reg")
		print("} // namespace mire")
		print_file_footer()
		return 0

	except RuntimeError as rte:
		print("Runtime error: " + str(rte))
		return 1

if __name__ == "__main__": main()
