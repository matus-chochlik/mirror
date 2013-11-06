#!/usr/bin/python
# coding=utf-8
#  Copyright 2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

def print_file_header():
	import datetime
	print(
"""
/**
 *  @file mire/mirror/specifiers.cpp
 *  @brief Declaration of specifiers.
 *
 *  @note This is an automatically generated header file, do not modify manually.
 *
 *  Copyright 2012-%(year)s Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRROR_SPECIFIERS_1311042119_HPP
#define MIRROR_SPECIFIERS_1311042119_HPP
""" % {'year': datetime.datetime.now().year}
	)

def print_reg_code(spec_name):
	spec_name_ = str('_').join(spec_name.split(' '))
	print(
"""
struct spec_%(spec_name_)s_tag
{
	static constexpr const char* _kw_c_str = "%(spec_name)s";
	static constexpr std::size_t _kw_size  = %(name_size)d;
};
""" %		{
			'spec_name_': spec_name_,
			'spec_name': spec_name,
			'name_size': len(spec_name),
		}
	)

def print_reg_code_none():
	print(
"""
struct spec_none_tag
{
	static constexpr const char* _kw_c_str = "";
	static constexpr std::size_t _kw_size  = 0;
};
"""
	)

def print_file_footer():
	print("""#endif // include guard""")


def main():
	specifiers = [
		"extern",
		"static",
		"mutable",
		"register",
		"thread local",
		"constexpr",
		"const",
		"virtual",
		"private",
		"protected",
		"public",
		"class",
		"struct",
		"union",
		"enum",
		"enum class"
	]

	try:
		print_file_header()
		print("namespace mirror {")
		print_reg_code_none()
		for specifier in specifiers:
			print_reg_code(specifier)
		print("} // namespace mirror")
		print_file_footer()
		return 0

	except RuntimeError as rte:
		print("Runtime error: " + str(rte))
		return 1

if __name__ == "__main__": main()
