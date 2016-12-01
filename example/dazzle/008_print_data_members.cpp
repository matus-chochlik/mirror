/**
 * @example dazzle/008_print_data_members.cpp
 * @brief Shows how to print out the values of class data members
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <dazzle/metaobject.hpp>
#include <dazzle/reflection.hpp>
#include <dazzle/int_const.hpp>
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
	std::ostream& operator()(std::ostream& out, S& v) const
	{
		auto mdms = DAZZLED(T).get_data_members();
		_printer print{out, v};

		mdms.for_each(print);

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
