/**
 * @example dazzle/005_tie_data_members.cpp
 * @brief Shows how to tie references to data members into a tuple
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <dazzle/metaobject.hpp>
#include <dazzle/reflection.hpp>
#include <cassert>
#include <tuple>

namespace {

using namespace dazzle;

template <typename T>
struct tie_data_members
{
	auto operator()(T& v) const
	{
		return DAZZLED(T).get_data_members().apply_on(
			[&v](auto ... mdm)
			{
				return std::tie(mdm.dereference(v)...);
			}
		);
	}
};

} // namespace

struct Point
{
	int x, y, z;
};

static inline
auto plus(
	std::tuple<int&, int&, int&> a,
	std::tuple<int&, int&, int&> b,
	std::tuple<int&, int&, int&> c
)
{
	using namespace std;
	return make_tuple(
		get<0>(a)+get<0>(b)+get<0>(c),
		get<1>(a)+get<1>(b)+get<1>(c),
		get<2>(a)+get<2>(b)+get<2>(c)
	);
}

int main(void)
{
	tie_data_members<Point> tdm;

	Point i{1,0,0}, j{0,1,0}, k{0,0,1}, l{1,1,1}, m{0,0,0};

	tdm(m) = plus(tdm(i), tdm(j), tdm(k));

	bool equal = (tdm(l) == tdm(m));
	assert(equal);

	return equal?0:1;
}

