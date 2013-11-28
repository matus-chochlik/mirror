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
 *  @file mire/tags/specifier.hpp
 *  @brief Declaration of specifier tags.
 *
 *  @note This is an automatically generated header file, do not modify manually.
 *
 *  Copyright 2012-%(year)s Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MIRE_TAGS_SPECIFIER_1311042119_HPP
#define MIRE_TAGS_SPECIFIER_1311042119_HPP
""" % {'year': datetime.datetime.now().year}
	)

def print_reg_code(spec_name):
	spec_name_ = str('_').join(spec_name.split(' '))
	print(
"""\
struct spec_%(spec_name_)s_tag
{
	struct _kw
	{
		static constexpr const char* c_str = "%(spec_name)s";
		static constexpr std::size_t size  = %(name_size)d;
	};
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
	struct _kw
	{
		static constexpr const char* c_str = "";
		static constexpr std::size_t size  = 0;
	};
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
		"enum class",
		"typedef"
	]

	try:
		print_file_header()
		print("namespace mire {")
		print("namespace tags {")
		print_reg_code_none()
		for specifier in specifiers:
			print_reg_code(specifier)
		print("} // namespace tags")
		print("} // namespace mire")
		print_file_footer()
		return 0

	except RuntimeError as rte:
		print("Runtime error: " + str(rte))
		return 1

if __name__ == "__main__": main()
