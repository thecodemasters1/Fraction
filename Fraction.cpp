/**
* Author: Lahav Schlesinger
**/

/*
* In this file we have the implementation and definition of the protectedvector namespace
* and the ProtectedVector class
*/

#include "Fraction.hpp"
#include "SafeArithmetics.hpp"
#include "DivisionByZeroException.hpp"
#include "NumericOverflowException.hpp"
#include "Utilities.hpp" //For Utilities::isInteger() and Utilities::gcd()
#include <iostream>
#include <string> //Used in operator>>
#include <cstddef> //for std::size_t


namespace fraction {


//The overall numeric overflow protection of 2 Fractions is 'true' if atleast
//one of the Fractions has the protection.
static bool getOverallProtection(const Fraction& frac1, const Fraction& frac2) {
	return frac1.getOverflowProtection() || frac2.getOverflowProtection();
}


/***
* bool getFractionPart()
*
*Purpose:
*        used in operator>> to check if the numerator and denominator are 'int's.
*        It does so by looking at the substring, whos starting and ending indices are
*        given in the parameters, calls Utilities::isInteger with that string.
* 
*       The resulted 'int' from the substring is stored in 'num' (which would be the
*       numerator or denominator).
*
*       If Utilities::isInteger() throws, and if the numeric overflow detector of the
*       Fraction object we read into is on, then it sets 'true' to a bool given in the
*       parameters (which indicates to operator>> that a numeric overflow occured.
*
*Entry:
*       const std::string&        input - The input from the user
*
*       std::size_t         start_index - The starting index of the 
*                                         numerator/denominator.
*
*       std::size_t           end_index - The ending index of the 
*                                         numerator/denominator.
*
*       int&                        num - If the substring between the given
*                                         indices fits in an 'int', then 'num'
*                                         would hold that 'int'.
*
*       bool        overflow_protection - The numeric overflow protction of the
*                                         Fraction object we're reading into.
*
*       bool&  numeric_overflow_occured - Would be 'true' if the substring is
*                                         an integer but it would overflow an 
*                                         'int', and if the numeric overflow
*                                         detector is on.
*
*Exit:
*       bool - true if the substring between the starting and ending indices
*              is an 'int'.
*
*Exceptions:
*
*******************************************************************************/
static bool getFractionPart(const std::string& input, std::size_t start_index,
	std::size_t end_index, int& num, bool overflow_protection, bool& numeric_overflow_occured)
{
	try {
		return Utilities::isInteger(input.substr(start_index, end_index), num,
			overflow_protection);
	}
	catch (...) {
		if (overflow_protection)
			numeric_overflow_occured = true;

		return true;
	}
}


//unary operators


// + operator
Fraction operator+ (const Fraction& frac) {
	return frac;
}

//- operator
Fraction operator- (const Fraction& frac) {
	return frac * (-1);
}


//logical operators


//== operators


//Returns 'true' if the calling object and the one from the input have the
//numerators and denominators.
bool Fraction::operator== (const Fraction& frac) const { //frac1==frac2
	return (this->m_numerator == frac.m_numerator && this->m_denominator == frac.m_denominator);
}


//Transforms the integer to Fraction, and calls operator== on Fraction objects.
bool operator== (const Fraction& lhs, int number) { //lhs==number
	return lhs==Fraction(number);
}


//number == rhs iff rhs == number.
bool operator== (int number, const Fraction& rhs) { //number==rhs
	return rhs==number;
}


// != operators


//lhs != rhs iff !(lhs == rhs)
bool operator!= (const Fraction& lhs, const Fraction& rhs) { //lhs!=rhs
	return !(lhs==rhs);
}


//lhs != number iff !(lhs == number)
bool operator!= (const Fraction& lhs, int number) { //lhs==number
	return !(lhs==number);
}


//number != rhs iff !(number == rhs)
bool operator!= (int number, const Fraction& rhs) { //number==rhs
	return !(rhs==number);
}


// < operators


//lhs < rhs iff (lhs-rhs) < 0.
//lhs-rhs is negative iff its sign() is -1.
bool Fraction::operator< (const Fraction& rhs) const { //lhs<rhs
	return ((*this)-rhs).sign() < 0;
}


//Transforms the integer to Fraction, and calls operator< on both
//Fractions.
bool operator< (const Fraction& lhs, int number) { //lhs<number
	return lhs < Fraction(number);
}


//Transforms the integer to Fraction, and calls operator< on both
//Fractions.
bool operator< (int number, const Fraction& rhs) { //number<rhs
	return Fraction(number) < rhs;
}


// <= operators


//(lhs <= rhs) iff !(rhs < lhs)
bool operator<= (const Fraction& lhs, const Fraction& rhs) { //lhs<=rhs
	return !(rhs < lhs);
}


//(lhs <= number) iff !(number < lhs)
bool operator<= (const Fraction& lhs, int number) { //lhs<=number
	return !(number < lhs);
}


//lhs <= rhs iff !(rhs < lhs)
bool operator<= (int number, const Fraction& rhs) { //number<=rhs
	return !(rhs < number);
}


// > operators


//(lhs > rhs) iff (rhs < lhs)
bool operator> (const Fraction& lhs, const Fraction& rhs) { //lhs>rhs
	return rhs < lhs;
}


//(lhs > number) iff (number < lhs)
bool operator> (const Fraction& lhs, int number) { //lhs>number
	return number < lhs;
}

//(number > rhs) iff (rhs < number)
bool operator> (int number, const Fraction& rhs) { //number>rhs
	return rhs < number;
}


// >= operators


//(lhs >= rhs) iff !(lhs < rhs)
bool operator>= (const Fraction& lhs, const Fraction& rhs) { //lhs>=rhs
	return !(lhs < rhs);
}

//(lhs >= number) iff !(lhs < number)
bool operator>= (const Fraction& lhs, int number) { //lhs>=number
	return !(lhs < number);
}

//(number >= rhs) iff !(number < rhs)
bool operator>= (int number, const Fraction& rhs) { //number>=rhs
	return !(number < rhs);
}


//arithmetic operators


// + operators


//First it sets the overflow protection of 'lhs' to be the overall
//protection of the 2 Fractions.
//Then it call 'lhs+=rhs', and returns 'lhs'.
Fraction operator+ (Fraction lhs, const Fraction& rhs) { //lhs+rhs
	lhs.setOverflowProtection(getOverallProtection(lhs,rhs));
	lhs+=rhs;
	return lhs;
}

//Simply calls 'lhs+=number' - we don't change the overflow protection.
Fraction operator+ (Fraction lhs, int number) { //lhs+number
	lhs+=number;
	return lhs;
}

//(number+rhs) is the same as (rhs+number)
Fraction operator+ (int number, const Fraction& rhs) { //number+rhs
	return rhs+number;
}



// - operators


//First it sets the overflow protection of 'lhs' to be the overall
//protection of the 2 Fractions.
//Then it call 'lhs-=rhs', and returns 'lhs'.
Fraction operator- (Fraction lhs, const Fraction& rhs) { //lhs+rhs
	lhs.setOverflowProtection(getOverallProtection(lhs, rhs));
	lhs -= rhs;
	return lhs;
}

//Simply calls 'lhs-=number' - we don't change the overflow protection.
Fraction operator- (Fraction lhs, int number) { //lhs-number
	lhs -= Fraction(number);
	return lhs;
}

//We create a copy of 'number', and call operator-= on that object.
//So (number -= rhs) will be (Fraction(number) -= rhs).
Fraction operator- (int number, const Fraction& rhs) { //number-rhs
	Fraction number_frac = Fraction(number);
	number_frac -= rhs;
	return number_frac;
}


// * operators


//First it sets the overflow protection of 'lhs' to be the overall
//protection of the 2 Fractions.
//Then it call 'lhs*=rhs', and returns 'lhs'.
Fraction operator* (Fraction lhs, const Fraction& rhs) { //lhs*rhs
	lhs.setOverflowProtection(getOverallProtection(lhs, rhs));
	lhs *= rhs;
	return lhs;
}

//Simply calls 'lhs*=number' - we don't change the overflow protection.
Fraction operator* (Fraction lhs, int number) { //lhs*number
	lhs *= Fraction(number);
	return lhs;
}

//(number * rhs) is the same as (rhs * number)
Fraction operator* (int number, const Fraction& rhs) { //number*rhs
	return rhs*number;
}


// / operators


//First it sets the overflow protection of 'lhs' to be the overall
//protection of the 2 Fractions.
//Then it call 'lhs/=rhs', and returns 'lhs'.
Fraction operator/ (Fraction lhs, const Fraction& rhs) { // lhs/rhs
	lhs.setOverflowProtection(getOverallProtection(lhs, rhs));
	lhs /= rhs;
	return lhs;

}

//Simply calls 'lhs/=number' - we don't change the overflow protection.
Fraction operator/ (Fraction lhs, int number) { // lhs/number
	lhs /= Fraction(number);
	return lhs;
}


//We create a copy of 'number', and call operator/= on that object.
//So (number /= rhs) will be (Fraction(number) /= rhs).
Fraction operator/ (int number, const Fraction& rhs) { // number/rhs
	Fraction number_frac = Fraction(number);
	number_frac /= rhs;
	return number_frac;
}


//compound assignment operators


// += operators


/*
We know that a/b + c/d = (ad + bc)/bd.
A different way to write it is:

       d               b
a * -------- + c * --------
    gcd(b,d)       gcd(b,d)
----------------------------
      (b*d)/gcd(b,d)

The benefit of calculating this way is that it reduces the chances of an overflow
to occur.

So the new numerator would be 'a * (d/gcd(b,d)) + c * (b/gcd(b,d))'
and the denominator would be '(b * d)/gcd(b,d)'.


Note that we're using 'SafeArithmetics' if the numeric overflow protection is
on.
Else, we're using normal operators.
*/
Fraction& Fraction::operator+= (const Fraction& rhs) & {

	/* 

	 
                    ad+bc
    a/b + c/d =  ------------
                     b*d

	OR:

                     ad+bc
                    -------
    a/b + c/d =     gcd(b,d)
                  ------------
                  (b*d)/gcd(b,d)

    OR:

                        d               b
                 a * -------- + c * --------
    a/b + c/d =      gcd(b,d)       gcd(b,d)
				 ----------------------------
                         (b*d)/gcd(b,d)
	*/

	int a = this->m_numerator;
	int b = this->m_denominator;

	int c = rhs.m_numerator;
	int d = rhs.m_denominator;

	int gcd = Utilities::gcd(b, d);

	int numerator, denominator;

	if (this->m_overflow_protection) {

		// d/gcd
		int d_gcd = SafeArithmetics::divide(d, gcd);

		//a*d/gcd
		int numerator1 = SafeArithmetics::multiply(a, d_gcd);
		//c*b/gcd
		int numerator2 = SafeArithmetics::multiply(c, SafeArithmetics::divide(b,gcd));

		//a*d/gcd + c*b/gcd
		numerator = SafeArithmetics::add(numerator1, numerator2);

		//b*d/gcd
		denominator = SafeArithmetics::multiply(b, d_gcd);
	}
	else {
		int d_gcd = d / gcd;

		numerator = a*d_gcd + c*(b / gcd);
		denominator = b*d_gcd;
	}

	//Set the calling object's numerator and denominator to the ones we computed.
	this->setNumerator(numerator);
	this->setDenominator(denominator);

	//And finally, return *this.
	return *this;
}


//Transforms the integer to a Fraction, and call operator+= with that object.
Fraction& Fraction::operator+= (int number) & { //lhs+=number
	*this += Fraction(number);
	return *this;
}


// -= operators


//(lhs -= rhs) is the same as (lhs += (-rhs)).
Fraction& Fraction::operator-= (const Fraction& rhs) & { //lhs-=rhs
	*this += (-rhs);
	return *this;
}

//Transforms the integer to a Fraction, and then we call 
//(lhs -= Fraction(number)).
Fraction& Fraction::operator-= (int number) & { //lhs-=number
	*this -= (Fraction(number));
	return *this;
}


// *= operators


/*
We know that a/b * c/d = ac/bd
So in order to compute the numerator of the product, we compute the product
of the Fraction's numerators.
We do a similar thing while computing the denominator.

Note that we're using 'SafeArithmetics' if the numeric overflow protection is
on.
Else, we're using normal multiplication.
*/
Fraction& Fraction::operator*= (const Fraction& lhs) & { //rhs*=lhs

	//The new numerator and denominator of the calling object.
	int numerator, denominator;

	if (this->m_overflow_protection) {
		numerator = SafeArithmetics::multiply(this->m_numerator, lhs.m_numerator);

		denominator = SafeArithmetics::multiply(this->m_denominator, lhs.m_denominator);

	}
	else {
		numerator = this->m_numerator * lhs.m_numerator;
		denominator = this->m_denominator * lhs.m_denominator;
	}

	//Set the calling object's numerator and denominator to the ones we computed.
	this->setNumerator(numerator);
	this->setDenominator(denominator);

	//And finally, return *this.
	return *this;

}

//Transforms the integer to a Fraction, and call operator*= with that object.
Fraction& Fraction::operator*= (int number) & { //lhs*=number
	*this *= Fraction(number);
	return *this;
}


// /= operators


//We know that
// a/b / c/d =  a/b * (d/c).
//So we create a Fraction which is (1/rhs).
//i.e. its numerator is rhs's denominator, and its denominator is rhs's numerator.
Fraction& Fraction::operator/= (const Fraction& rhs) & { // lhs/=rhs
	*this *= Fraction(rhs.getDenominator(), rhs.getNumerator());
	return *this;
}


//Transforms the integer to a Fraction, and then we call 
//(lhs /= Fraction(number)).
Fraction& Fraction::operator/= (int number) & { // lhs/=number
	*this /= Fraction(number);
	return *this;
}


//Self increment and decrement operators


// ++ operators


/*
Prefix operator++

Calls operator+=(1) on *this.
Returns *this.
*/
Fraction& Fraction::operator++ () & { //prefix ++frac
	*this += 1;
	return *this;
}


/*
Postfix operator++

Creates a copy of *this.
Calls operator++ prefix on *this.
Returns the copy.
*/
Fraction Fraction::operator++ (int) & { //postfix frac++
	Fraction new_frac = *this;
	++*this;
	return new_frac;
}


// -- operators


/*
Prefix operator--

Calls operator-=(1) on *this.
Returns *this.
*/
Fraction& Fraction::operator-- () & { //prefix --frac
	*this -= 1;
	return *this;
}

/*
Postfix operator--

Creates a copy of *this.
Calls operator-- prefix on *this.
Returns the copy.
*/
Fraction Fraction::operator-- (int) & { //postfix frac--
	Fraction new_frac = *this;
	--*this;
	return new_frac;
}


// << operator


/*
Prints the fraction in the following way:

1) If the denomintor is 0, it prints NaN.
2) If the numerator is 0, it prints 0 (to avoid prints "0/5")
3) If the denominator is 1, it print the 'numerator' (to avoid printing "5/1" -
                                                      print "5" instead)
4) Else, it print "'numerator'/'denominator'".
*/
std::ostream& operator<< (std::ostream& os, const Fraction& frac) {
	int numerator = frac.getNumerator();
	int denominator = frac.getDenominator();

	if (0 == denominator)
		return os << "NaN";
	else if (0 == numerator)
		return os << "0";
	else if (1 == denominator)
		return os << numerator;
	return os << numerator << "/" << denominator;
}


// >> operators


/***
*std::istream& operator>>() - Reads a fraction from given istream
*
*Purpose:
*       It reads a Fraction from the given istream in the following format:
*       "numerator/denominator", or "numerator" (in which case, the denominator
*       would be 1).
*
* 
*       We do by so by keeping reading lines from the istream, and then find '/' in
*       that string.
*       The string that comes before the '/' is treated as the numerator, and
*       the string that comes after the '/' is treated as the denominator.
*
*       If the numerator or the denominator are not integers - we read a new line.
*       If the numerator or the denominator are integers, but would cause an overflow
*       if attempted to store them in a 'int', *AND* if we have the numeric overflow
*       detector on, then we throw NumericOverflowException().
*
*       Finally, when we read the numerator and denominator, and they both fit inside
*       an 'int', then we check if the denominator is 0 - If it is, we throw 
*       DivisionByZeroException().
*
*       Else, we simply set the calling Fraction object's numerator and denominator
*       to be the ones we just read, and finally return the given istream.
*
*Entry:
*      std::istream&  is - The istream we'll read from
*      Fraction&    frac - The Fraction object we'll store the numerator and 
*                          denominator we'll read.
*
*Exit:
*       std::istream& - the istream from the input.
*
*Exceptions:
*       NumericOverflowException() - if by storing the numerator or denominator
*                                    in an 'int', it would cause a numeric overflow.
*
*       DivisionByZeroException()  - If the denominator is 0.
*
*******************************************************************************/
std::istream& operator>> (std::istream& is, Fraction& frac) {

	//The numerator and denomirator we'll read.
	int numerator, denominator;

	bool overflow_protection = frac.getOverflowProtection();

	//Becomes 'true' if by storing the numerator or denominator in an 'int', it would
	//cause a numeric overflow.
	bool numeric_overflow_occured = false;

	
	//Keep reading lines from the istream until we successfully read 2 integers
	while (true) {

		//Read the line from the user
		std::string input;
		std::getline(is, input);

		//Get the index of the '/'.
		std::size_t div_sign_index = input.find('/');

		//Get the numerator - the string that comes before the '\'.
		if (!getFractionPart(input, 0, div_sign_index, numerator, overflow_protection,
			numeric_overflow_occured))
		{
			continue;
		}

		//If there is not '/' in the fraction, then the denominator is 1.
		if (std::string::npos == div_sign_index)
			denominator = 1;
		else {

			//Get the denominator - the string that comes after the '\'.
			if (!getFractionPart(input, div_sign_index + 1, std::string::npos, denominator,
				overflow_protection, numeric_overflow_occured))
			{
				continue;
			}
		}


		/*
		If the numerator or the denominator would cause a numeric overflow
		if they would be stored in an 'int' - throw NumericOverflowException().
		Note that we didn't throw this exception even if the numerator would cause
		and overflow, since the denominator might not be an integer at all, and in
		this case we don't wish to throw an exception.
		*/
		if (numeric_overflow_occured)
			throw NumericOverflowException();

		break;

	} //while (true) {


	//If the denominator is 0 - throw DivisionByZeroException().
	if (0 == denominator)
		throw DivisionByZeroException();

	//Set the calling Fraction object's numerator and denominator to be the ones
	//we just read
	frac.setNumerator(numerator);
	frac.setDenominator(denominator);

	return is;

} //std::istream& operator>> (std::istream& is, Fraction& frac) {


//Casting operator


//Casts to float.
//If the denominator is not 0, it returns numerator/denominator.
//Else, it throws DivisionByZeroException().
Fraction::operator float() const {
	if (0==this->m_denominator)
		throw DivisionByZeroException();

	return (float)this->m_numerator / (float)this->m_denominator;
}


} //namespace fraction {