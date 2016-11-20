/**
 * @example refltool/032_from_rapidxml.cpp
 * @brief Shows how to deserialize from XML with the from_rapidxml function
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <refltool/from_rapidxml.hpp>
#include <refltool/enum_to_string.hpp>
#include <iostream>

enum vertex_attrib_type
{
	position,
	normal,
	tangential,
	bitangential,
	tex_coord
};

struct vertex_attrib_data
{
	vertex_attrib_type type;
	unsigned values_per_vertex;

	std::vector<float> data;
};

enum draw_method
{
	draw_arrays,
	draw_elements
};

enum primitive_type
{
	points,
	lines,
	line_strip,
	line_loop,
	triangles,
	triangle_strip,
	triangle_fan
};

enum face_winding
{
	cw, ccw
};

struct draw_operation
{
	draw_method method;
	primitive_type mode;
	face_winding winding;
	unsigned offset;
	unsigned count;
};

struct geometry
{
	std::vector<vertex_attrib_data> vertex_arrays;
	std::vector<unsigned> indices;
	std::vector<draw_operation> draw_ops;
};

static std::vector<char> get_simple_cube_xml(void);

int main(void)
{
	using namespace refltool;

	auto input = get_simple_cube_xml();

	// parse rapidxml document
	rapidxml::xml_document<> doc;
	doc.parse<rapidxml::parse_non_destructive>(input.data());

	geometry cube;

	if(from_rapidxml(doc.first_node(), cube)) {
		std::cout
			<< "Geometry loaded successfully"
			<< std::endl;
		std::cout
			<< "Vertex arrays: "
			<< cube.vertex_arrays.size()
			<< std::endl;
		std::cout
			<< "Indices: "
			<< cube.indices.size()
			<< std::endl;
		std::cout
			<< "Draw commands: "
			<< cube.draw_ops.size()
			<< std::endl;
		std::cout
			<< "First attrib type: "
			<< enum_to_string(cube.vertex_arrays.front().type)
			<< std::endl;
	}

	return 0;
}

static std::vector<char> get_simple_cube_xml(void) {
	std::string xml =
		"<cube>"
		"<vertex_arrays>"
			"<pos type='position' values_per_vertex='3'>"
			"<data>"
				"<x>0</x><y>0</y><z>0</z>"
				"<x>1</x><y>0</y><z>0</z>"
				"<x>0</x><y>1</y><z>0</z>"
				"<x>1</x><y>1</y><z>0</z>"
				"<x>0</x><y>0</y><z>1</z>"
				"<x>1</x><y>0</y><z>1</z>"
				"<x>0</x><y>1</y><z>1</z>"
				"<x>1</x><y>1</y><z>1</z>"
			"</data>"
			"</pos>"
		"</vertex_arrays>"
		"<indices>"
			"<A>0</A><E>4</E><C>2</C><G>6</G>"
			"<F>5</F><B>1</B><H>7</H><D>3</D>"
			"<A>0</A><B>1</B><E>4</E><F>5</F>"
			"<G>6</G><H>7</H><C>2</C><D>3</D>"
			"<B>1</B><A>0</A><D>3</D><C>2</C>"
			"<E>4</E><F>5</F><G>6</G><H>7</H>"
		"</indices>"
		"<draw_ops>"
			"<xneg"
				" method='draw_elements'"
				" mode='triangle_strip'"
				" winding='ccw'"
				" offset='0' count='4'"
			"/>"
			"<xpos"
				" method='draw_elements'"
				" mode='triangle_strip'"
				" winding='ccw'"
				" offset='4' count='4'"
			"/>"
			"<yneg"
				" method='draw_elements'"
				" mode='triangle_strip'"
				" winding='ccw'"
				" offset='8' count='4'"
			"/>"
			"<ypos"
				" method='draw_elements'"
				" mode='triangle_strip'"
				" winding='ccw'"
				" offset='12' count='4'"
			"/>"
			"<zneg"
				" method='draw_elements'"
				" mode='triangle_strip'"
				" winding='ccw'"
				" offset='16' count='4'"
			"/>"
			"<zpos"
				" method='draw_elements'"
				" mode='triangle_strip'"
				" winding='ccw'"
				" offset='20' count='4'"
			"/>"
		"</draw_ops>"
		"</cube>";
	return {xml.begin(), xml.end()};

}

