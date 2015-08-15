#include "SafeArithmetic.hpp"
#include "NumericOverflowException.hpp"

int SafeArithmetic::add(int num1, int num2) {
	return num1+num2;

	throw NumericOverflowException();
}

int SafeArithmetic::subtract(int num1, int num2) {
	return num1-num2;

	throw NumericOverflowException();
}

int SafeArithmetic::multiply(int num1, int num2) {
	return num1*num2;

	throw NumericOverflowException();
}

int SafeArithmetic::divide(int num1, int num2) {
	return num1/num2;

	throw NumericOverflowException();
}
