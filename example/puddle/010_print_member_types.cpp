/**
 * @example puddle/010_print_member_types.cpp
 * @brief Shows how to print out class member types
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <puddle/metaobject_ops.hpp>
#include <puddle/sequence_ops.hpp>
#include <puddle/reflection.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <iostream>

struct S {
	struct a { };
	typedef int b;
	using c = char;
};

class C {
private:
	struct _x { };
protected:
	typedef const _x _y;
public:
	using z = _y*;
};

namespace {

using namespace puddle;

template <typename T>
class print_member_types
{
private:
	struct _printer {
		std::ostream& out;

		template <typename MO>
		void operator()(MO mo) const
		{
			out << c_str(get_base_name(mo));
			if(reflects_alias(mo))
			{
				out << " -> ";
				out << c_str(get_full_name(get_aliased(mo)));
			}
			out << std::endl;
		}
	};
public:
	std::ostream& operator()(std::ostream& out, bool all) const
	{
		_printer print{out};

		auto mt = PUDDLED(T);

		if(all) {
			for_each(get_member_types(mt), print);
		} else {
			for_each(get_public_member_types(mt), print);
		}
		return out;
	}
};

} // namespace

void print_S(void)
{
	print_member_types<S> pdm;

	pdm(std::cout, true) << std::endl;
	pdm(std::cout,false) << std::endl;
}

void print_C(void)
{
	print_member_types<C> pdm;

	pdm(std::cout, true) << std::endl;
	pdm(std::cout,false) << std::endl;
}

int main(void)
{
	print_S();
	print_C();

	return 0;
}
