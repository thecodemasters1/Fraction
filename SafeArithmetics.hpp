/**
* Author: Lahav Schlesinger
**/

/*
* In this file we have the declaration of the SafeArithmetics namespace
*/

#ifndef SAFEARITHMETICS_HPP_
#define SAFEARITHMETICS_HPP_


/*
This namespace holds functions return the value they suppose to (e.g. add()
returns the sum), but first check if the operation would cause an integer overflow.
If an integer overflow would occur, it throws NumericOverflowException().
*/
namespace SafeArithmetics {
	
	/*
	Returns num1+num2, or throws NumericOverflowException() if the sum would
	overflow.
	*/
	int add(int num1, int num2);

	/*
	Returns num1*num2, or throws NumericOverflowException() if the multiplication
	would overflow.
	*/
	int multiply(int num1, int num2);

	/*
	Returns num1/num2, or throws NumericOverflowException() if the division would
	overflow
	*/
	int divide(int num1, int num2);
}

#endif