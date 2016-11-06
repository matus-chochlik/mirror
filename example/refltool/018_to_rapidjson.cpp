/**
 * @example refltool/018_to_rapidjson.cpp
 * @brief Shows how serialize values to JSON with the to_rapidjson function
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <refltool/to_rapidjson.hpp>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include <iostream>

enum gender
{
	female, male
};

enum marital_status
{
	single, married, divorced, widowed, unknown
};

struct person
{
	std::string first_name;
	std::string middle_name;
	std::string surname;

	gender sex;
	marital_status status;

	unsigned age;

	bool drivers_license;
};

int main(void)
{
	using namespace refltool;

	// create a list of persons
	std::vector<person> pers;
	pers.push_back({"John", "X", "Doe", male, unknown, 40, false});
	pers.push_back({"Jane", "Y", "Roe", female, unknown, 28, true});
	pers.push_back({"Johnny", "B", "Goode", male, single, 19, false});
	pers.push_back({"James", "T", "Kirk", male, divorced, 60, true});


	// compose rapidjson document
	rapidjson::Document doc;
	to_rapidjson(doc, pers);

	// write to stdout
	rapidjson::OStreamWrapper osw(std::cout);
	rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
	doc.Accept(writer);

	std::cout << std::endl;

	return 0;
}

