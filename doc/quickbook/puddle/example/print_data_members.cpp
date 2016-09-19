/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

//[puddle_example_print_data_members_1
#include <puddle/metaobject_ops.hpp>
#include <puddle/sequence_ops.hpp>
#include <puddle/reflection.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <iostream>
//]
//[puddle_example_print_data_members_2
struct S {
	static const int a = -321;
	bool b;
	char c;
	double d;
	float e;
};

const int S::a;
//]
//[puddle_example_print_data_members_3
template <typename T>
class print_data_members
{
private:
	struct _printer {
		std::ostream& out;
		T& v;

		template <typename MO>
		void _print_value(MO mo, __mirror_true_/*is_static*/) const
		{
			out << (*__value(__get_pointer(mo)));
		}

		template <typename MO>
		void _print_value(MO mo, __mirror_false_/*is_static*/) const
		{
			out << (v.*__value(__get_pointer(mo)));
		}

		template <typename MO>
		void operator()(MO mo) const
		{
			if(__is_static(mo)) {
				out << "static ";
			}
			out << __c_str(__get_base_name(__get_type(mo)));
			out << " ";
			out << c_str(get_base_name(mo));
			out << " = ";
			_print_value(mo, is_static(mo));
			out << std::endl;
		}
	};
public:
	std::ostream& operator()(std::ostream& out, S& v) const
	{
		auto MDMs = __unpack(__get_data_members(__PUDDLED(T)));
		_printer print{out, v};

		__for_each(MDMs, print);

		return out;
	}
};
//]
//[puddle_example_print_data_members_4
int main(void)
{
	puddle::print_data_members<S> pdm;

	S x = {false, 'X', 1234.56, 78.9f};
	S y = {true, 'Y', 11.1111, 2222.22f};

	pdm(std::cout, x) << std::endl;
	pdm(std::cout, y) << std::endl;

	return 0;
}
//]
//[puddle_example_print_data_members_output
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
//]
