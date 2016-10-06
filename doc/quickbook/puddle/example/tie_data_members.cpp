/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

//[puddle_example_tie_data_members_1
#include <puddle/metaobject_ops.hpp>
#include <puddle/sequence_ops.hpp>
#include <puddle/reflection.hpp>
#include <cassert>
#include <tuple>
//]
//[puddle_example_tie_data_members_2
namespace {

using namespace puddle;

template <typename T>
struct tie_data_members
{
private:
	template <typename ... MDMs>
	static auto _do_tie(T& v, __mirror_range<MDMs...>)
	{
		return std::tie(__dereference(MDMs{}, v)...);
	}
public:
	auto operator()(T& v) const
	{
		auto MDMs = __unpack(__get_data_members(__PUDDLED(T)));
		return _do_tie(v, MDMs);
	}
};

} // namespace
//]
//[puddle_example_tie_data_members_3
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
//]
//[puddle_example_tie_data_members_4
int main(void)
{
	tie_data_members<Point> tdm;

	Point i{1,0,0}, j{0,1,0}, k{0,0,1}, l{1,1,1}, m{0,0,0};

	tdm(m) = plus(tdm(i), tdm(j), tdm(k));

	bool equal = (tdm(l) == tdm(m));
	assert(equal);

	return equal?0:1;
}
//]
