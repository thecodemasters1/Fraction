#include "SafeArithmetics.hpp"
#include "NumericOverflowException.hpp"
#include <climits> //for INT_MIN, INT_MAX
#include <utility> //for std::swap

int SafeArithmetics::add(int num1, int num2) {
	if ((num1 > 0) && (num2 > INT_MAX - num1))
		throw NumericOverflowException();
	else if ((num1 < 0) && (num2 < INT_MIN - num1))
		throw NumericOverflowException();

	return num1 + num2;
}

int SafeArithmetics::multiply(int num1, int num2) {
	
	if (0 == num1 || 0 == num2)
		return 0;

	if ((num1 > 0 && num2 > 0) || (num1 < 0 && num2 < 0)) {
		if (num1 < 0 && num2 < 0) {
			if (INT_MIN == num1 || INT_MIN == num2)
				throw NumericOverflowException();
			num1 *= -1;
			num2 *= -1;
		}

		//Here num1>0 && num2>0

		if (num1 > INT_MAX / num2)
			throw NumericOverflowException();
	}
	else {
		if (num1 > 0 && num2 < 0)
			std::swap(num1,num2);
		
		//here num1<0 and num2>0

		if (num1 < INT_MIN / num2)
			throw NumericOverflowException();
	}
	return num1*num2;
	
}

int SafeArithmetics::divide(int num1, int num2) {

	if (INT_MIN == num1 && -1 == num2)
		throw NumericOverflowException();

	return num1 / num2;
}