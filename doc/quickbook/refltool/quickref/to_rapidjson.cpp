/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[refltool_to_rapidjson_value
// to_rapidjson
template <typename Encoding, typename Allocator, typename T>
__rapidjson_GenericValue<Encoding, Allocator>& to_rapidjson(
	__rapidjson_GenericValue<Encoding, Allocator>& rjval,
	Allocator& alloc,
	const T& val
);
//]
//[refltool_to_rapidjson_doc
template <typename Encoding, typename T>
__rapidjson_GenericDocument<Encoding>& to_rapidjson(
	__rapidjson_GenericDocument<Encoding>& rjdoc,
	const T& val
);
//]
//[refltool_rapidjson_compositor
template <typename T>
struct rapidjson_compositor
{
	template <typename Encoding, typename Allocator>
	void operator()(
		__rapidjson_GenericValue<Encoding, Allocator>& rjval,
		Allocator& alloc,
		const T& v
	) const;
};
//]

