/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[refltool_from_rapidjson_value
template <typename Encoding, typename Allocator, typename T>
bool from_rapidjson(
	const __rapidjson_GenericValue<Encoding, Allocator>& rjval,
	T& val
);
//]
//[refltool_rapidjson_loader
template <typename T>
struct rapidjson_loader
{
	template <typename Encoding, typename Allocator>
	bool operator()(
		const __rapidjson_GenericValue<Encoding, Allocator>& rjval,
		T& val
	) const;
};
//]

