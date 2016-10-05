/**
 * @example mirror/014_print_data_members.cpp
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
#include <mirror/get_public_data_members.hpp>
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

class C {
private:
	int _a;
	static bool _b;
protected:
	const char _c;
public:
	double d;
	float e;

	C(int a, char c, double _d, float _e)
	 : _a(a), _c(c), d(_d), e(_e)
	{ }

	int get_a(void) const { return _a; }
};

bool C::_b = false;

namespace mirror {

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
	std::ostream& operator()(std::ostream& out, T& v, bool all) const
	{
		_printer print{out, v};

		using MT = MIRRORED(T);

		if(all) {
			for_each<get_data_members<MT>>::apply(print);
		} else {
			for_each<get_public_data_members<MT>>::apply(print);
		}
		return out;
	}
};

} // namespace mirror

void print_S(void)
{
	mirror::print_data_members<S> pdm;

	S x = {false, 'X', 1234.56, 78.9f};
	S y = {true, 'Y', 11.1111, 2222.22f};

	pdm(std::cout, x, true) << std::endl;
	pdm(std::cout, y,false) << std::endl;
}

void print_C(void)
{
	mirror::print_data_members<C> pdm;

	C x(0, 'A', 2345.67, 8.9f);
	C y(1, 'B', 22.2222, 3333.33f);

	pdm(std::cout, x, true) << std::endl;
	pdm(std::cout, x,false) << std::endl;
	pdm(std::cout, y, true) << std::endl;
	pdm(std::cout, y,false) << std::endl;
}

int main(void)
{
	print_S();
	print_C();

	return 0;
}
