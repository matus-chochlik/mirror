/**
 * @example dazzle/014_print_data_members.cpp
 * @brief Shows how to print out the values of class data members
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <dazzle/metaobject.hpp>
#include <dazzle/reflection.hpp>
#include <dazzle/string.hpp>
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

namespace {

using namespace dazzle;

template <typename T>
class print_data_members
{
private:
	struct _printer {
		std::ostream& out;
		T& v;

		template <typename MO>
		void operator()(MO mo) const
		{
			if(mo.is_static()) {
				out << "static ";
			}
			out << mo.get_type().get_base_name();
			out << " ";
			out << mo.get_base_name();
			out << " = ";

			if constexpr(mo.is_static()) {
				out << (*mo.get_pointer().value());
			} else {
				out << (v.*mo.get_pointer().value());
			}
			out << std::endl;
		}
	};
public:
	std::ostream& operator()(std::ostream& out, T& v, bool all) const
	{
		_printer print{out, v};

		auto mt = DAZZLED(T);

		if(all) {
			mt.get_data_members().for_each(print);
		} else {
			mt.get_public_data_members().for_each(print);
		}
		return out;
	}
};

} // namespace dazzle

void print_S(void)
{
	print_data_members<S> pdm;

	S x = {false, 'X', 1234.56, 78.9f};
	S y = {true, 'Y', 11.1111, 2222.22f};

	pdm(std::cout, x, true) << std::endl;
	pdm(std::cout, y,false) << std::endl;
}

void print_C(void)
{
	print_data_members<C> pdm;

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
