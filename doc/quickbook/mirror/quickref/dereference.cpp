/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[mirror_op_dereference_metaobject
template <__std_meta_Variable MO>
struct dereference<__metaobject<MO>>
{
	static auto& apply(void); /*<
	Available only if the metaobject reflects a namespace level variable
	or a static data member. Returns a reference to the reflected variable.
	>*/

	template <typename T>
	static auto& apply(T &parent); /*<
	Available only if the metaobject reflects a class data member.
	Returns a reference to the reflected data member in the specified
	[^parent] instance. In case of static data members the [^parent]
	argument is ignored.
	>*/
};
//]
