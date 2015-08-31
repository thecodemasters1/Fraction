/**
* Author: Lahav Schlesinger
**/

/* 
* In this file we implement all the functions in the Utilities namespace.
*/

#include "Utilities.hpp"
#include "NumericOverflowException.hpp"
#include <string>
#include <cstdlib>
#include <errno.h>
#include <climits>


/***
*bool Utilities::isInteger() - Returns whether the given string is an integer.
*
*Purpose:
*       Checks if the given string is an integer.
*       If not, returns false, and 'number' is not changed.
*       If it's an integer, returns true, and stored that integer in 'number'.
*
*       The check is performed by calling the strtol() function.
*       strtol() accepts a pointer to char*, and it makes that pointer to point
*       at the first char *after* the first non-digit char (in general, strtol() also
*       skips white spaces, but we make sure that the first char in the string is
*       not a white space.
*       If the char the pointer points at is the null bytes terminator, then
*       that means that all the chars in the string are digits, and therefore
*       the string is an integer.
*       If not, then the string is not an integer, and we return false.
*
*       Also, at the end, if the string is an integer, depends on the value of
*       'check_for_overflow', we we make sure that the integer won't overflow an 'int' 
*       by checking:
*       1) if errno is ERANGE
*	    2) if the integer we got is larger than INT_MAX
*		3) if the integer we got is less than INT_MIN
*
*       If atleast on of those happen - then the integer would overflow an 'int', so
*       we throw NumericOverflowException()
*
*Entry:
*       const std::string&  str    - The string we want to check if its an integer
*       int&                number - If the given string is an integer, this 
*                                    reference would hold that number.
*       bool    check_for_overflow - indicates whether or not we need to check for
&                                    numeric overflows.
*
*Exit:
*       true if the string is in fact an integer and if that integer
*       won't overflow an int.
*
*Exceptions:
*       NumericOverflowException() - If 'check_for_overflow' is 'true', and if the
*                                    given string is in fact an integer, but it 
*                                    would overflow an 'int'.
*
*******************************************************************************/
bool Utilities::isInteger(const std::string& str, int& number, bool check_for_overflow)
{
	//makes sure that the string is not empty, and that there are no 
	//leading white spaces in 'str'.
    if(str.empty() || isspace(str[0]))
	    return false;

    //A pointer used in strtol().
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

    Afterwards:
    1) if we're checking for numeric overflow, then we check the following things:
          a) if errno is ERANGE
          b) if the integer we got is larger than INT_MAX
          c) if the integer we got is less than INT_MIN
      If atleast one of those criterions are matched, then a numeric overflow
      would occur - so we throw NumericOverflowException().

      If we're not checking for numeric overflows, then we skip this test

      2) At the end, we just set 'number' to that integer we got, and return 'true'.


    Note: even though strtol returns LONG_MIN or LONG_MAX if an overflow occurred,
    it's still possible that 'str' would hold LONG_MAX and strtol would of course
    succeed, but return LONG_MAX. Therefore, checking the return type of strtol 
    can't conclusively tell if there was an overflow. You can manually check if 
    'str' is in fact LONG_MIN or LONG_MAX, and if not - then there was an overflow,
    but checking errno is simpler.
    */
    if ('\0' == *p) {

		if (check_for_overflow) {
			if ((ERANGE == errno) || (string_to_long > INT_MAX) || (string_to_long < INT_MIN))
				throw NumericOverflowException();	
		}

		number = string_to_long;
		return true;
    }
    return false;
}

/***
*int Utilities::gcd() - Returns the gcd()
*
*Purpose:
*      Returns the greatest common divisor of 'a' and 'b'.
*      Simple Euclidean algorithm.
*
*Entry:
*       int num1 - The first integer
*       int num2 - The second integer
*
*Exit:
*       int      - The greates common divisor of 'num1' and 'num2'.
*
*Exceptions:
*
*******************************************************************************/
int Utilities::gcd(int num1, int num2) {
	if (0 == num2)
		return num1;
	return gcd(num2, num1 % num2);
}


/***
*int Utilities::sign() - Returns the sign
*
*Purpose:
*      Returns the sign of 'num':
*      1 if positive
*      -1 if negative
*      0 if zero.
*
*Entry:
*      int num   -  The integer we return its sign.
*
*Exit:
*       int      - 1 if 'num' is positive, -1 if negative, 0 if zero.
*
*Exceptions:
*
*******************************************************************************/
int Utilities::sign(int num) {
	if (num > 0)
		return 1;
	else if (num < 0)
		return -1;
	return 0;
}