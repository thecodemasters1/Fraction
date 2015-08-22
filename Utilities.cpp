/**
* Author: Lahav Schlesinger
**/

/* 
* In this file we implement all the functions in the Utilities namespace.
*/

#include "Utilities.hpp"
#include <string>
#include <iostream>
#include <cctype> //for isspace
#include <errno.h>
#include <limits>
#include <cmath> //for HUGE_VAL


/***
*bool Utilities::isInteger() - Returns whether the given string is an integer.
*
*Purpose:
*		Checks if the given string is an integer.
*		If not, returns false, and 'number' is not changed.
*		If it's an integer, returns true, and stored that integer in 'number'.
*
*		The check is performed by calling the strtol() function.
*		strtol() accepts a pointer to char*, and it makes that pointer to point
*		at the first char *after* the first non-digit char (in general, strtol() also
*		skips white spaces, but we make sure that the first char in the string is
*		not a white space.
*		If the char the pointer points at is the null bytes terminator, then
*		that means that all the chars in the string are digits, and therefore
*		the string is an integer.
*		If not, then the string is not an integer, and we return false.
*
*		Also, at the end, if the string is an integer, we make sure that the
*		integer won't overflow an 'int', by checking errno.
*
*Entry:
*		const std::string&	str    - The string we want to check if its an integer
*       int&                number - If the given string is an integer, this 
*									 reference would hold that number.
*
*Exit:
*		true if the string is in fact an integer and if the integer
*		won't overflow an int.
*
*Exceptions:
*		
*******************************************************************************/
bool Utilities::isInteger(const std::string& str, int& number)
{
	//makes sure that the string is not empty, and that there are no 
	//leading white spaces in 'str'.
    if(str.empty() || isspace(str[0]))
	    return false;

    //A poitner used in strtol().
    char* p;

    errno = 0;
    long int string_to_long = strtol(str.c_str(), &p, 10);

    /*
    The first char in 'str' is either a base 10 digit, or '+' or '-' signs.
    If it is '+' or '-', strtol skips them.
    After the call for strtol, 'p' points at the first non base 10 digit.
    So if there are only base 10 digits in 'str', then the first non base 10 digit
    is the null terminator. i.e. '\0' == *p.
    But, if after the first char, there are non base 10 chars, then 'p' would point at 
    the first one, and therefore *p wouldn't be '\0'.

    So overall, '\0' == *p if and only if 'str' is in fact an integer.

    Also, we're making sure that the number in 'str' won't overflow, by checking ERANGE != errno.

    Note: even though strtol returns LONG_MIN or LONG_MAX if an overflow occurred, it's still possible
    that 'str' would hold LONG_MAX and strtol would of course succeed, but return LONG_MAX.
    Therefore, checking the return type of strtol can't conclusively tell if there was an overflow.
    You can manually check if 'str' is in fact LONG_MIN or LONG_MAX, and if not - then there
    was an overflow, but checking errno is simpler.

    Afterwards we check if the given long int can be stored in an int.
    */
    if (('\0' == *p) && (ERANGE != errno)) {
	    if ((string_to_long <= std::numeric_limits<int>::max()) && (string_to_long >= std::numeric_limits<int>::min())) {
	 	   number = string_to_long;
	 	   return true;
	    }
    }
    return false;
}