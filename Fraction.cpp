#include "Fraction.hpp"
#include "SafeArithmetic.hpp"
#include "DivisionByZeroException.hpp"
#include <iostream>
#include <string>

namespace fraction {

// + operator
Fraction operator+ (const Fraction& frac) {
	return frac;
}

//- operator
Fraction operator- (const Fraction& frac) {
	return frac * (-1);
}

bool Fraction::operator== (const Fraction& frac) const { //frac1==frac2
	return (this->m_numerator == frac.m_numerator && this->m_denominator == frac.m_denominator);
}

bool operator== (const Fraction& lhs, int number) { //lhs==number
	return lhs==Fraction(number);
}

bool operator== (int number, const Fraction& rhs) { //number==rhs
	return rhs==number;
}

// != operators
bool operator!= (const Fraction& lhs, const Fraction& rhs) { //lhs!=rhs
	return !(lhs==rhs);
}

bool operator!= (const Fraction& lhs, int number) { //lhs==number
	return !(lhs==number);
}

bool operator!= (int number, const Fraction& rhs) { //number==rhs
	return !(rhs==number);
}


// < operators
bool operator< (const Fraction& lhs, const Fraction& rhs) { //lhs<rhs
	return (lhs-rhs).sign() < 0;
}

bool operator< (const Fraction& lhs, int number) { //lhs<number
	return lhs < Fraction(number);
}

bool operator< (int number, const Fraction& rhs) { //number<rhs
	return Fraction(number) < rhs;
}


// <= operators
bool operator<= (const Fraction& lhs, const Fraction& rhs) { //lhs<=rhs
	return !(rhs < lhs);
}

bool operator<= (const Fraction& lhs, int number) { //lhs<=number
	return lhs<=Fraction(number);
}

bool operator<= (int number, const Fraction& rhs) { //number<=rhs
	return Fraction(number) <= rhs;
}


// > operators
bool operator> (const Fraction& lhs, const Fraction& rhs) { //lhs>rhs
	return rhs < lhs;
}

bool operator> (const Fraction& lhs, int number) { //lhs>number
	return lhs > Fraction(number);
}

bool operator> (int number, const Fraction& rhs) { //number>rhs
	return Fraction(number) > rhs;
}


// >= operators
bool operator>= (const Fraction& lhs, const Fraction& rhs) { //lhs>=rhs
	return rhs <= lhs;
}

bool operator>= (const Fraction& lhs, int number) { //lhs>=number
	return lhs >= Fraction(number);
}

bool operator>= (int number, const Fraction& rhs) { //number>=rhs
	return Fraction(number) >= rhs;
}


// + operators
Fraction operator+ (Fraction lhs, const Fraction& rhs) { //lhs+rhs
	lhs+=rhs;
	return lhs;
}

Fraction operator+ (Fraction lhs, int number) { //lhs+number
	lhs+=number;
	return lhs;
}

Fraction operator+ (int number, const Fraction& rhs) { //number+rhs
	//number+frac == frac+number
	return rhs+number;
}


Fraction& Fraction::operator+= (const Fraction& frac) {
	/* 
				   ad+bc
				  -------
	a/b + c/d =   gcd(b,d)
				------------
				  lcm(b,d)

	OR:

				        d               b
				 a * -------- + c * --------
	a/b + c/d =      gcd(b,d)       gcd(b,d)
				 ----------------------------
				            lcm(b,d)
	*/
	int a = this->m_numerator;
	int b = this->m_denominator;

	int c = frac.m_numerator;
	int d = frac.m_denominator;

	int gcd = this->gcd(b, d);

	if (this->m_overflowProtection) {
		//a*d/gcd
		int numerator1 = SafeArithmetic::multiply(a, SafeArithmetic::divide(d,gcd));
		//c*b/gcd
		int numerator2 = SafeArithmetic::multiply(c, SafeArithmetic::divide(b,gcd));

		//a*d/gcd + c*b/gcd
		int numerator = SafeArithmetic::add(numerator1, numerator2);

		int denominator = SafeArithmetic::multiply(b, SafeArithmetic::divide(d,gcd));

		*this = Fraction(numerator, denominator, this->m_overflowProtection);
		return *this;
	}
	else {
		int lcm = b*(d/gcd);

		int numerator = a*d/gcd + c*b/gcd;
		int denominator = lcm;
		*this = Fraction(numerator, denominator, this->m_overflowProtection);
		return *this;
	}
}

Fraction& operator+= (Fraction& lhs, int number) { //lhs+=number
	lhs+=Fraction(number);
	return lhs;
}


Fraction Fraction::operator- (const Fraction& frac) const {
	// a/b - c/d = (ad-bc)/bd
	if (this->m_overflowProtection) {
		int numerator1 = SafeArithmetic::multiply(this->m_numerator, frac.m_denominator);
		int numerator2 = SafeArithmetic::multiply(this->m_denominator, frac.m_numerator);
		int numerator = SafeArithmetic::subtract(numerator1, numerator2);

		int denominator = SafeArithmetic::multiply(this->m_denominator,frac.m_denominator);
		return Fraction(numerator, denominator, this->m_overflowProtection);
	}
	else {
		int numerator = this->m_numerator*frac.m_denominator - frac.m_numerator*this->m_denominator;
		int denominator = this->m_denominator * frac.m_denominator;
		return Fraction(numerator, denominator, this->m_overflowProtection);
	}
}

Fraction Fraction::operator- (int number) const {
	return (*this) - Fraction(number);
}

Fraction operator- (int number, const Fraction& frac) {
	//number-frac = -(frac-number);
	return -(frac-number);
}


Fraction& Fraction::operator-= (const Fraction& frac) {
	Fraction new_frac = (*this) - frac;
	return (*this) = new_frac;
}

Fraction& Fraction::operator-= (int number) {
	Fraction new_frac = (*this) - number;
	return (*this) = new_frac;
}


Fraction Fraction::operator* (const Fraction& frac) const {
	// a/b * c/d = ac/bd
	if (this->m_overflowProtection) {
		int numerator = SafeArithmetic::multiply(this->m_numerator, frac.m_numerator);

		int denominator = SafeArithmetic::multiply(this->m_denominator,frac.m_denominator);
		return Fraction(numerator, denominator, this->m_overflowProtection);
	}
	else {
		int numerator = this->m_numerator * frac.m_numerator;
		int denominator = this->m_denominator * frac.m_denominator;
		return Fraction(numerator, denominator, this->m_overflowProtection);
	}
}

Fraction Fraction::operator* (int number) const {
	return (*this) * Fraction(number);
}

const Fraction operator* (int number, const Fraction& frac) {
	//number*frac = frac*number;
	return frac*number;
}


Fraction& Fraction::operator*= (const Fraction& frac) {
	Fraction new_frac = (*this) * frac;
	return (*this) = new_frac;
}

Fraction& Fraction::operator*= (int number) {
	Fraction new_frac = (*this) * number;
	return (*this) = new_frac;
}


Fraction Fraction::operator/ (const Fraction& frac) const {
	// a/b / c/d = ad/bc
	if (this->m_overflowProtection) {
		int numerator = SafeArithmetic::multiply(this->m_numerator, frac.m_denominator);

		int denominator = SafeArithmetic::multiply(this->m_denominator,frac.m_numerator);
		return Fraction(numerator, denominator, this->m_overflowProtection);
	}
	else {
		int numerator = this->m_numerator * frac.m_denominator;
		int denominator = this->m_denominator * frac.m_numerator;
		return Fraction(numerator, denominator, this->m_overflowProtection);
	}
}

Fraction Fraction::operator/ (int number) const {
	return (*this) / Fraction(number);
}

const Fraction operator/ (int number, const Fraction& frac) {
	//number / a/b = b/a * number
	return Fraction(frac.m_denominator, frac.m_numerator, frac.m_overflowProtection) * number;
}


Fraction& Fraction::operator/= (const Fraction& frac) {
	Fraction new_frac = (*this) / frac;
	return (*this) = new_frac;
}

Fraction& Fraction::operator/= (int number) {
	Fraction new_frac = (*this) / number;
	return (*this) = new_frac;
}


std::ostream& operator<< (std::ostream& os, const Fraction& frac) {
	int numerator = frac.m_numerator;
	int denominator = frac.m_denominator;

	if (0 == numerator) {
		if (0== denominator)
			return os << "NaN";
		else
			return os << "0";
	}
	else if (1 == denominator)
		return os << numerator;
	return os << numerator << "/" << denominator;
}

std::istream& operator>> (std::istream& is, Fraction& frac) {

	int numerator, denominator;
	while (true) {
		std::string line;
		std::getline(is, line);

		std::size_t div_sign_index = line.find('/');
		if (std::string::npos == div_sign_index)
			continue;

		//Get the numerator
		try {
			numerator = stoi(line.substr(0, div_sign_index));
		}
		catch (...) {
			continue;
		}

		/* 
		Checks if, for example, the numerator is "5a".
		stoi() would return 5, but the length of "5" and "5a" are not the same
		*/
		if (std::to_string(numerator).length() != div_sign_index)
			continue;

		//Get the denominator
		try {
			denominator = stoi(line.substr(div_sign_index+1, line.length()));
		}
		catch (...) {
			continue;
		}

		/* 
		Checks if, for example, the denominator is "5a".
		stoi() would return 5, but the length of "5" and "5a" are not the same
		*/
		if (std::to_string(denominator).length() != line.length()-(div_sign_index+1))
			continue;

		break;
	}
	frac = Fraction(numerator, denominator, frac.m_overflowProtection);
	return is;
}


float Fraction::toFloat() const {
	if (0==this->m_denominator)
		throw DivisionByZeroException();

	return (float)this->m_numerator / (float)this->m_denominator;
}

//namespace fraction { 
} 