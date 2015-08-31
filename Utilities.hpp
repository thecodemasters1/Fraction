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
This namespace holds some general-use methods.
*/
namespace Utilities {

	//Returns 'true' if the given string is an integer.
	//If it is, then it stores that integer in 'number'.
	//If 'check_for_overflow' is 'true', then we also check if that integer
	//won't overflow an 'int'. If it does - we throw NumericOverflowException().
	bool isInteger(const std::string& str, int& number, bool check_for_overflow);

	//returns the greatest common divisor of both the numers from the input.
	int gcd(int num1, int num2);

	/*
	Returns the sign of the integer:

	1 if positive
	-1 if negative
	0 if zero.
	*/
	int sign(int num);
}

#endif