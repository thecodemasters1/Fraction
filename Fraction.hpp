/**
* Author: Lahav Schlesinger
**/

/*
* In this file we have the (partial) implementation and definition of the 
* fraction namespace and the Fraction class
*/


#ifndef FRACTION_HPP_
#define FRACTION_HPP_

#include "DivisionByZeroException.hpp"
#include "SafeArithmetics.hpp"
#include <iostream>
#include <utility> //for std::swap
#include "Utilities.hpp"


/*
This namesapce holds the Fraction class, with all its non-friend non-member 
operators.
*/
namespace fraction {


/*
This class represents a fraction - it stores the numerator and denominator, both
intgers.

The constructor also excepts a 'bool' that indicates whether or not we want to
perform checks for numeric overflows whenever we use an operator:
If we have the overflow protection, then if an operator would cause a numeric
overflow, then it would throw NumericOverflowException().

It throws DivisionByZeroException() when there's an attemp to divide by 0.
Note that if the numeric overflow detector is off, then it would throw
DivisionByZeroException() only in the float() cast operator ,and in operator>>.

It works on operators with the following rules:

1)+=, -=, *=, /= operators:
There would be a check for a numeric overflow only if the object the operator
is called on has the protection.

2)++, -- operators:
There would be a check for a numeric overflow only if the object the operator
is called on has the protection.

3) +, -, *, / operators:
There would be a check for a numeric overflow only if atleast one of the objects
in the operators has the protection.
*/
class Fraction
{
public:
	//-- constructors/destructor --//

	/*
	The constructor.

	Assign the numerator, denominator and numeric overflow detector to the ones
	from the input.

	If the denominator is 0, it throws DivisionByZeroException().

	Afterwards, it 'reduces' the numerator and denominator (i.e. makes them co-prime).
	*/
	explicit Fraction (int numerator=0, int denominator=1, bool overflowProtection = false) : 
		m_numerator(numerator), 
		m_denominator(denominator), 
		m_overflow_protection(overflowProtection)
	{
			if (0==denominator)
				throw DivisionByZeroException();
			this->reduce();
	}

	//-- operators --//

	/*
	The assignment operator.

	simple copy and swap implementation.

	we use lvalue reference qualifier in order to prevent usage such as frac+1 = frac2.
	*/
	Fraction& operator= (Fraction frac) & {
		this->swap(frac);
		return *this;
	}

	//An assigment operator that accepts an integer.
	//Turns the integer to a fraction, and sets the calling object to that one.
	Fraction& operator= (int number) & {
		Fraction frac_number(number);
		this->swap(frac_number);
		return *this;
	}


	//logical operators


	/* 
	== operator

	Checks if the numerator and denominator are equal.
	It doesn't check the numeric overflow detector 'bool'.
	*/
	bool operator== (const Fraction& rhs) const; //frac1==rhs

	// < operator
	bool operator< (const Fraction& rhs) const; //lhs<rhs


	//compound assignment operators


	// += operators
	Fraction& operator+= (const Fraction& rhs) &; //lhs+=rhs
	Fraction& operator+= (int number) &; //lhs+=number

	// -= operators
	Fraction& operator-= (const Fraction& frac) &; //lhs-=rhs
	Fraction& operator-= (int number) &; //lhs-=number

	// *= operators
	Fraction& operator*= (const Fraction& rhs) &; //lhs*=rhs
	Fraction& operator*= (int number) &; //lhs*=number

	// /= operators
	Fraction& operator/= (const Fraction& rhs) &; // lhs/=rhs
	Fraction& operator/= (int number) &; // lhs/=number


	//Self increment and decrement operators


	// ++ operators
	Fraction& operator++ () &; //prefix ++frac
	Fraction operator++ (int) &; //postfix frac++

	// -- operators
	Fraction& operator-- () &; //prefix --frac
	Fraction operator-- (int) &; //postfix frac--



	 //-- public methods --//


	//Swaps the content of the calling object, and the one from the input.
	void swap(Fraction& other) {
		std::swap(this->m_numerator, other.m_numerator);
		std::swap(this->m_denominator, other.m_denominator);
		std::swap(this->m_overflow_protection, other.m_overflow_protection);
	}

	//Setter for the numeric overflow
	void setOverflowProtection(bool protection) {
		this->m_overflow_protection = protection;
	}

	//Getter for the numeric overflow
	bool getOverflowProtection() const {
		return this->m_overflow_protection;
	}

	//Setter for the numerator
	void setNumerator(int numerator) {
		this->m_numerator = numerator;
		this->reduce();
	}

	//Getter for the numerator
	int getNumerator() const {
		return this->m_numerator;
	}

	//Setter for the denominator
	void setDenominator(int denominator) {
		this->m_denominator = denominator;
		this->reduce();
	}

	//Getter for the denominator
	int getDenominator() const {
		return this->m_denominator;
	}

	//Casts to float().
	//If the denominator is 0, it throws DivisionByZeroException().
	explicit operator float() const;

private:
	//-- private data members --//

	//The numerator
	int m_numerator;

	//The denominator
	int m_denominator;

	//The overflow protection 'bool'
	bool m_overflow_protection;


	//-- private methods --//


	/*
	Returns the sign of the fraction:

	1 if positive
	-1 if negative
	0 if zero.
	*/
	int sign() const {
		//A fraction is positive iff both the numerator and denominator are positive and negative.
		//It's negative iff one of the numerator and denominator are negative
		//0 if the numerator is zero.
		return Utilities::sign(this->m_numerator) * Utilities::sign(this->m_denominator);
	}


	/*
	Makes the numerator and denominator to be co-prime.

	Note that it doesn't change the value of the fraction, it merely tries
	to make the numerator and denominator to be smaller, so that the chance
	of a numeric overflow to occur on future operators would be smaller.
	*/
	void reduce() {
		if (0==this->m_denominator && this->m_overflow_protection)
			throw DivisionByZeroException();

		//Get the gcd of the numerator and denominator.
		int gcd = Utilities::gcd(this->m_numerator, this->m_denominator);

		//If the gcd is not 0, then divide the numerator and denominator by the
		//gcd - effectively making them co-prime.
		if (0!=gcd) {
			this->m_numerator /= gcd;
			this->m_denominator /= gcd;
		}

		//At the end, fix the sign of the fraction.
		this->fix_sign();
	}


	/*
	Fixes the sign of the fraction:
	It makes it so only the numerator would be the negative value:
	If the denominator is negative, then it changes the signs of the
	numerator and denominator.
	i.e. if the fraction is (5/-2), it turns it to (-5/2).

	Note that it doesn't change the value of the Fraction.
	*/
	void fix_sign() {
		int denominator_sign = Utilities::sign(this->m_denominator);

		//If the denominator is negative, then multiply the numerator and
		//denominator by -1.
		//Note that this multiplication can cause a numeric overflow.
		if (denominator_sign < 0) {
			if (this->m_overflow_protection) {
				this->m_numerator = SafeArithmetics::multiply(this->m_numerator, -1);
				this->m_denominator = SafeArithmetics::multiply(this->m_denominator, -1);
			}
			else {
				this->m_numerator *= -1;
				this->m_denominator *= -1;
			}
		}
	}

}; //class Fraction {


/* declarations of the non-member non-friend operators */
Fraction operator+ (const Fraction& frac);
Fraction operator- (const Fraction& frac);

bool operator== (const Fraction& lhs, int number); //lhs==number
bool operator== (int number, const Fraction& rhs); //number==rhs

bool operator!= (const Fraction& lhs, const Fraction& rhs); //lhs!=rhs
bool operator!= (const Fraction& lhs, int number); //lhs==number
bool operator!= (int number, const Fraction& rhs); //number==rhs

bool operator< (const Fraction& lhs, int number); //lhs<number
bool operator< (int number, const Fraction& rhs); //number<rhs

bool operator<= (const Fraction& lhs, const Fraction& rhs); //lhs<=rhs
bool operator<= (const Fraction& lhs, int number); //lhs<=number
bool operator<= (int number, const Fraction& rhs); //number<=rhs

bool operator> (const Fraction& lhs, const Fraction& rhs); //lhs>rhs
bool operator> (const Fraction& lhs, int number); //lhs>number
bool operator> (int number, const Fraction& rhs); //number>rhs

bool operator>= (const Fraction& lhs, const Fraction& rhs); //lhs>=rhs
bool operator>= (const Fraction& lhs, int number); //lhs>=number
bool operator>= (int number, const Fraction& rhs); //number>=rhs

Fraction operator+ (Fraction lhs, const Fraction& rhs); //lhs+rhs
Fraction operator+ (Fraction lhs, int number); //lhs+number
Fraction operator+ (int number, const Fraction& rhs); //number+rhs

Fraction operator- (Fraction lhs, const Fraction& rhs); //lhs+rhs
Fraction operator- (Fraction lhs, int number); //lhs-number
Fraction operator- (int number, const Fraction& rhs); //number-rhs

Fraction operator* (Fraction lhs, const Fraction& rhs); //lhs*rhs
Fraction operator* (Fraction lhs, int number); //lhs*number
Fraction operator* (int number, const Fraction& rhs); //number*rhs

Fraction operator/ (Fraction lhs, const Fraction& rhs); // lhs/rhs
Fraction operator/ (Fraction lhs, int number); // lhs/number
Fraction operator/ (int number, const Fraction& rhs); // number/rhs

std::ostream& operator<< (std::ostream& os, const Fraction& frac);
std::istream& operator>> (std::istream& is, Fraction& frac);

} //namespace fraction {

#endif