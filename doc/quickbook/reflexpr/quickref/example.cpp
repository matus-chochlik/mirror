/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[reflexpr_example_is_metaobject
using namespace std;

assert(!is_metaobject_v<void>);
assert(!is_metaobject_v<int>);
assert(!is_metaobject_v<string>);

assert( is_metaobject_v<__reflexpr(std)>);
assert( is_metaobject_v<reflexpr(int)>);
//]

//[reflexpr_example_Named
using namespace std::meta;

assert( __Named<__reflexpr()>);
assert( Named<reflexpr(::)>);
assert( Named<reflexpr(int)>);
assert( Named<reflexpr(std)>);
assert( Named<reflexpr(virtual)>);

assert( __is_anonymous_v<__reflexpr()>); /*<
The global scope is [^__Named], but anonymous.
>*/
assert( is_anonymous_v<reflexpr(::)>);
assert(!is_anonymous_v<reflexpr(int)>);
assert(!is_anonymous_v<reflexpr(std)>);
assert(!is_anonymous_v<reflexpr(virtual)>); /*<
The ["name] of a specifier is its keyword.
>*/
assert( is_anonymous_v<reflexpr(int(int,int))>); /*<
Function pointer types (not [link reflexpr.quickref.c_Alias aliases])
are considered anonymous.
>*/

cout << __get_base_name_v<__reflexpr(::)> << std::endl;           // ""
cout << get_base_name_v<reflexpr(std)> << std::endl;          // "std"
cout << get_base_name_v<reflexpr(int)> << std::endl;          // "int"
cout << get_base_name_v<reflexpr(float)> << std::endl;        // "float"
cout << get_base_name_v<reflexpr(std::string)> << std::endl;  // "string"
cout << get_base_name_v<reflexpr(virtual)> << std::endl;      // "virtual"

/*< The [^get_base_name] operation strips all scope or const and volatile
qualifiers, array angle brackets, pointer type asterisks, reference type
ampersands, etc. >*/
cout << __get_base_name_v<reflexpr(int)> << std::endl;                  // "int"
cout << get_base_name_v<reflexpr(int*)> << std::endl;                 // "int"
cout << get_base_name_v<reflexpr(const int)> << std::endl;            // "int"
cout << get_base_name_v<reflexpr(volatile int)> << std::endl;         // "int"
cout << get_base_name_v<reflexpr(int[10])> << std::endl;              // "int"
cout << get_base_name_v<reflexpr(int* const*[3][2][1])> << std::endl; // "int"

cout << get_base_name_v<reflexpr(pair<int, int>)> << std::endl;       // "pair"
cout << get_base_name_v<reflexpr(int(int,int))> << std::endl;         // ""
//]
