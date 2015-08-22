/**
* Author: Lahav Schlesinger
**/

/* 
* In this file we have the declaration of the Utilities namespace
*/


#ifndef UTILITIES_HPP_
#define UTILITIES_HPP_

#include <string>


/*
This namespace holds "general" methods.
*/
namespace Utilities {

	//Returns 'true' if the given string is an integer and won't overflow an 'int'. 
	//If so, it stored in 'number' that integer.
	bool isInteger(const std::string& str, int& number);
}

#endif