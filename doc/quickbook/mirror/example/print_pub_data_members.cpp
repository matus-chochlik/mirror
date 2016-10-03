/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

//[mirror_example_print_pub_data_members_1
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
//]
//[mirror_example_print_pub_data_members_2
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
//]
//[mirror_example_print_pub_data_members_3
namespace mirror {

template <typename T>
class print_pub_data_members
{
private:
	struct _printer {
		std::ostream& out;
		T& v;

		template <typename MO>
		void _print_value(MO, __true_/*is_static*/) const
		{
			out << (*__value<__get_pointer<MO>>);
		}

		template <typename MO>
		void _print_value(MO, __false_/*is_static*/) const
		{
			out << (v.*__value<__get_pointer<MO>>);
		}

		template <typename MO>
		void operator()(MO mo) const
		{
			if(__value<__is_static<MO>>) {
				out << "static ";
			}
			out << __c_str<__get_base_name<__get_type<MO>>>;
			out << " ";
			out << c_str<get_base_name<MO>>;
			out << " = ";
			_print_value(mo, is_static<MO>{});
			out << std::endl;
		}
	};
public:
	std::ostream& operator()(std::ostream& out, S& v) const
	{
		_printer print{out, v};

		using MT = __MIRRORED(T);

		if(all) {
			__for_each<__get_data_members<MT>>::apply(print);
		} else {
			for_each<__get_public_data_members<MT>>::apply(print);
		}
		return out;

		return out;
	}
};

} // namespace mirror
//]
//[mirror_example_print_pub_data_members_4
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
//]
//[mirror_example_print_pub_data_members_output
static int a = -321
bool b = 0
char c = X
double d = 1234.56
float e = 78.9

static int a = -321
bool b = 1
char c = Y
double d = 11.1111
float e = 2222.22

int _a = 0
static bool _b = 0
char _c = A
double d = 2345.67
float e = 8.9

double d = 2345.67
float e = 8.9

int _a = 1
static bool _b = 0
char _c = B
double d = 22.2222
float e = 3333.33

double d = 22.2222
float e = 3333.33
//]

