/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_for_each_none
template <>
struct for_each<__none>
{
public:
	template <typename Func>
	static Func apply(Func func); /*<
	Equivalent to ``return func;``
	>*/
};
//]
//[mirror_op_for_each_range
template <typename ... P>
struct for_each<__range<P...>>
{
public:
	template <typename Func>
	static Func apply(Func func); /*<
	Equivalent to
	``
	func(__wrap_if_not_special<P>{})...;
	return func;
	``
	>*/
};
//]
//[mirror_op_for_each_string
template <typename Char, Char ... C>
struct for_each<__basic_string<Char, C...>>
{
public:
	template <typename Func>
	static Func apply(Func func); /*<
	Equivalent to
	``
	func(__int_const<Char, C>{})...;
	return func;
	``
	>*/
};
//]

