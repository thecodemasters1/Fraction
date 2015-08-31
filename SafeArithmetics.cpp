/**
* Author: Lahav Schlesinger
**/

/*
* In this file we implement all the functions in the SafeArithmetics namespace.
*/


#include "SafeArithmetics.hpp"
#include "NumericOverflowException.hpp"
#include <climits> //for INT_MIN, INT_MAX
#include <utility> //for std::swap



/***
*int SafeArithmetics::add() - Returns the sum of num1 and num2, or throws
*                             NumericOverflowException() if it would overflow.
*
*Purpose:
*       Checks if the sum would cause a numeric overflow.
*       If it would - throws NumericOverflowException().
*       Else, it returns num1+num2.
*
*       If num1>0, and overflow could happen only if 'num1+num2 > INT_MAX',
*       which is the same as 'num2 > INT_MAX-num1'.
*       Note that we don't check 'num1 > INT_MAX - num2', since 'num2' might
*       be negative, and therefore 'INT_MAX - num2' would overflow.
*
*      If num1<0, then an overflow could happen only if 'num1+num2 < INT_MAX', 
*      which is the same as 'num2 < INT_MIN-num1'.
*
*Entry:
*       int num1 - The left operand of the sum
*       int num2 - The right operand of the sum
*
*Exit:
*       Success - num1+num2.
*
*Exceptions:
*       NumericOverflowException() - if the sum would overflow
*
*******************************************************************************/
int SafeArithmetics::add(int num1, int num2) {

	//If num1>0, an overflow could only occur if 'num1+num2 > INT_MAX', which is
	//equivalent to 'num2 > INT_MAX - num1'.
	//Note that we didn't check 'num1 > INT_MAX - num2', since 'num2' might
	//be negative, and therefore 'INT_MAX - num2' would overflow.
	if ((num1 > 0) && (num2 > INT_MAX - num1))
		throw NumericOverflowException();
	else if ((num1 < 0) && (num2 < INT_MIN - num1)) {

		//If num1<0, an overflow could only occur if 'num1+num2 < INT_MAX', which
		//is the same as 'num2 < INT_MIN-num1'.
		throw NumericOverflowException();
	}

	//If no overflow would occur - return num1+num2
	return num1 + num2;
}



/***
*int SafeArithmetics::multiply() - Returns the multiplication of num1 and num2,
*                                  or throws NumericOverflowException() if it 
*                                  would overflow.
*
*Purpose:
*       Checks if the multiplication would cause a numeric overflow.
*       If it would - throws NumericOverflowException().
*       Else, it returns num1*num2.
*
*       We check for an overflow by:
*       0) If num1 or num2 is 0 - no overflow could happen
*
*       1) If num1 and num2 are positive - an overflow could only occur if
*          'num1*num2 > INT_MAX', which is mathematically the same as 'num1 > INT_MAX/num2'.
*           note that INT_MAX/num2 would never overflow.
*
*       2) If num1 and num2 are negative - Similar check to (1), except that instead
*          of checking 'num1 > INT_MAX/num2'. we check 'num1 < INT_MAX/num2'
*          We flip the inequality since 'num2' is negative.
*          note that INT_MAX/num2 would never overflow.
*
*       3) If num1 is negative, and num2 is positive - then an overflow could 
*          only happen if 'num1*num2 < INT_MIN' which is mathematically the same as
*          'num1 < INT_MIN/num2'.
*          note that INT_MIN/num2 would never overflow because 'num2' can't be -1.
*
*       4) If num1 is positive, and num2 is negative - then an overflow could 
*          only happen if 'num1*num2 < INT_MIN' which is mathematically the same as
*          'num2 < INT_MIN/num1'.
*          We swapped 'num1' and 'num2' from (3) since now 'num1' is the positive.
*          note that INT_MIN/num1 would never overflow because 'num1' can't be -1.
*
*Entry:
*       int num1 - The left operand of the multiplication
*       int num2 - The right operand of the multiplication
*
*Exit:
*       Success - num1*num2.
*
*Exceptions:
*       NumericOverflowException() - if the multiplication would overflow
*
*******************************************************************************/
int SafeArithmetics::multiply(int num1, int num2) {
	
	if (0 == num1 || 0 == num2)
		return 0;

	if (num1 > 0 && num2 > 0) {
		if (num1 > INT_MAX / num2)
			throw NumericOverflowException();
	}
	else if (num1 < 0 && num2 < 0) {
		if (num1 < INT_MAX / num2)
			throw NumericOverflowException();
	}
	else if (num1 > 0 && num2 < 0) {
		if (num2 < INT_MIN / num1)
			throw NumericOverflowException();
	}
	else { // num1 < 0 && num2 > 0
		if (num1 < INT_MIN / num2)
			throw NumericOverflowException();
	}

	//If no overflow would occur - return num1+num2
	return num1*num2;
	
}



/***
*int SafeArithmetics::divide() - Returns the division of num1 and num2, or throws
*                                NumericOverflowException() if it would overflow.
*
*Purpose:
*       Checks if the division would cause a numeric overflow.
*       If it would - throws NumericOverflowException().
*       Else, it returns num1/num2.
*
*       A numeric overflow in division could only occurs if the numerator is 
*       INT_MIN and the denominator is -1.
*
*Entry:
*       int num1 - The numerator
*       int num2 - The denominator 
*
*Exit:
*       Success - num1/num2.
*
*Exceptions:
*       NumericOverflowException() - if the division would overflow
* 
*******************************************************************************/
int SafeArithmetics::divide(int num1, int num2) {

	//A division can overflow only if the numerator is INT_MIN, and the
	//denominator is -1.
	if (INT_MIN == num1 && -1 == num2)
		throw NumericOverflowException();

	//If no overflow would occur - return num1/num2
	return num1 / num2;
}