/**
 * @example dazzle/010_print_member_types.cpp
 * @brief Shows how to print out class member types
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

using namespace dazzle;

template <typename T>
class print_member_types
{
private:
	struct _printer {
		std::ostream& out;

		template <typename MO>
		void operator()(MO mo) const
		{
			out << mo.get_base_name();
			if(mo.reflects_alias())
			{
				out << " -> ";
				out << mo.get_aliased().get_full_name();
			}
			out << std::endl;
		}
	};
public:
	std::ostream& operator()(std::ostream& out, bool all) const
	{
		_printer print{out};

		auto mt = DAZZLED(T);

		if(all) {
			mt.get_member_types().for_each(print);
		} else {
			mt.get_public_member_types().for_each(print);
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
