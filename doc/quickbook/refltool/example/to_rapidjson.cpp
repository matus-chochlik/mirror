/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[refltool_example_to_rapidjson_1
#include <refltool/to_rapidjson.hpp>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include <iostream>
//]
//[refltool_example_to_rapidjson_2
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
//]
//[refltool_example_to_rapidjson_3
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
	__to_rapidjson(doc, pers);

	// write to stdout
	rapidjson::OStreamWrapper osw(std::cout);
	rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
	doc.Accept(writer);

	std::cout << std::endl;

	return 0;
}
//]
//[refltool_example_to_rapidjson_output
[
    {
        "first_name": "John",
        "middle_name": "X",
        "surname": "Doe",
        "sex": "male",
        "status": "unknown",
        "age": 40,
        "drivers_license": false
    },
    {
        "first_name": "Jane",
        "middle_name": "Y",
        "surname": "Roe",
        "sex": "female",
        "status": "unknown",
        "age": 28,
        "drivers_license": true
    },
    {
        "first_name": "Johnny",
        "middle_name": "B",
        "surname": "Goode",
        "sex": "male",
        "status": "single",
        "age": 19,
        "drivers_license": false
    },
    {
        "first_name": "James",
        "middle_name": "T",
        "surname": "Kirk",
        "sex": "male",
        "status": "divorced",
        "age": 60,
        "drivers_license": true
    }
]
//]
