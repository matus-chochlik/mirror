/**
 * @example mirror/007_print_data_members.cpp
 * @brief Shows how to print out the values of class data members
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <mirror/for_each.hpp>
#include <mirror/get_pointer.hpp>
#include <mirror/get_type.hpp>
#include <mirror/get_base_name.hpp>
#include <mirror/get_data_members.hpp>
#include <mirror/is_static.hpp>
#include <mirror/c_str.hpp>
#include <mirror/value.hpp>
#include <mirror/reflection.hpp>
#include <mirror/range.hpp>
#include <mirror/unpack.hpp>
#include <iostream>

struct S {
	static const int a = -321;
	bool b;
	char c;
	double d;
	float e;
};

const int S::a;

namespace {

using namespace mirror;

template <typename T>
class print_data_members
{
private:
	struct _printer {
		std::ostream& out;
		T& v;

		template <typename MO>
		void operator()(MO) const
		{
			if(value<is_static<MO>>) {
				out << "static ";
			}
			out << c_str<get_base_name<get_type<MO>>>;
			out << " ";
			out << c_str<get_base_name<MO>>;
			out << " = ";

			if constexpr(value<is_static<MO>>) {
				out << (*value<get_pointer<MO>>);
			} else {
				out << (v.*value<get_pointer<MO>>);
			}
			out << std::endl;
		}
	};
public:
	std::ostream& operator()(std::ostream& out, T& v) const
	{
		using MDMs = get_data_members<MIRRORED(T)>;
		_printer print{out, v};

		for_each<MDMs>::apply(print);

		return out;
	}
};

} // namespace

int main(void)
{
	print_data_members<S> pdm;

	S x = {false, 'X', 1234.56, 78.9f};
	S y = {true, 'Y', 11.1111, 2222.22f};

	pdm(std::cout, x) << std::endl;
	pdm(std::cout, y) << std::endl;

	return 0;
}
