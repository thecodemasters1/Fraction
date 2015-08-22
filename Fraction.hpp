#ifndef FRACTION_HPP_
#define FRACTION_HPP_

#include "DivisionByZeroException.hpp"
#include "SafeArithmetics.hpp"
#include <iostream>
#include <utility> //for std::swap

namespace fraction {

class Fraction
{
public:
	explicit Fraction (int numerator=0, int denominator=1, bool overflowProtection = false) : 
		m_numerator(numerator), 
		m_denominator(denominator), 
		m_overflow_protection(overflowProtection)
	{
			if (0==denominator)
				throw DivisionByZeroException();
			this->reduce();
	}

	void setOverflowProtection(bool protection) {
		this->m_overflow_protection = protection;
	}

	bool getOverflowProtection() const {
		return this->m_overflow_protection;
	}

	Fraction& operator= (Fraction frac) {
		this->swap(frac);
		return *this;
	}

	Fraction& operator= (int number) {
		this->swap(Fraction(number));
		return *this;
	}

	// == operators
	bool operator== (const Fraction& rhs) const; //frac1==rhs

	// < operator
	bool operator< (const Fraction& rhs) const; //lhs<rhs

	// += operators
	Fraction& operator+= (const Fraction& rhs); //frac+=rhs

	// *= operators
	Fraction& operator*= (const Fraction& rhs); //frac*=rhs

	// /= operators
	Fraction& operator/= (const Fraction& rhs); // lhs/=rhs

	void swap(Fraction& other) {
		std::swap(this->m_numerator, other.m_numerator);
		std::swap(this->m_denominator, other.m_denominator);
	}

	void setNumerator(int numerator) {
		this->m_numerator = numerator;
		this->reduce();
	}

	int getNumerator() const {
		return this->m_numerator;
	}

	void setDenominator(int denominator) {
		this->m_denominator = denominator;
		this->reduce();
	}

	int getDenominator() const {
		return this->m_denominator;
	}

	explicit operator float() const;

private:
	int m_numerator;
	int m_denominator;
	bool m_overflow_protection;

	int sign() const {
		return Fraction::sign(this->m_numerator) * Fraction::sign(this->m_denominator);
	}

	void reduce() {
		if (0==this->m_denominator && this->m_overflow_protection)
			throw DivisionByZeroException();

		int gcd = Fraction::gcd(this->m_numerator, this->m_denominator);

		if (0!=gcd) {
			this->m_numerator /= gcd;
			this->m_denominator /= gcd;
		}

		//Might also throw badStateException().
		this->fix_sign();
	}

	void fix_sign() {
		int numerator_sign = Fraction::sign(this->m_numerator);
		int denominator_sign = Fraction::sign(this->m_denominator);

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

	static int gcd(int a, int b) {
		if (0 == b)
			return a;
		return gcd(b, a % b);
	}

	static int sign(int x) {
		if (x > 0)
			return 1;
		else if (x < 0)
			return -1;
		return 0;
	}
}; //class Fraction {


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

Fraction& operator+= (Fraction& lhs, int number); //lhs+=number

Fraction operator- (Fraction lhs, const Fraction& rhs); //lhs+rhs
Fraction operator- (Fraction lhs, int number); //lhs-number
Fraction operator- (int number, const Fraction& rhs); //number-rhs

Fraction& operator-= (Fraction& lhs, const Fraction& frac); //lhs-=rhs
Fraction& operator-= (Fraction& lhs, int number); //lhs-=number

Fraction operator* (Fraction lhs, const Fraction& rhs); //lhs*rhs
Fraction operator* (Fraction lhs, int number); //lhs*number
Fraction operator* (int number, const Fraction& rhs); //number*rhs

Fraction& operator*= (Fraction& lhs, int number); //lhs*=number

Fraction operator/ (Fraction lhs, const Fraction& rhs); // lhs/rhs
Fraction operator/ (Fraction lhs, int number); // lhs/number
Fraction operator/ (int number, const Fraction& rhs); // number/rhs

Fraction& operator/= (Fraction& lhs, int number); // lhs/=number

Fraction& operator++ (Fraction& frac); //prefix ++frac
Fraction operator++ (Fraction& frac, int); //postfix ++frac

Fraction& operator-- (Fraction& frac); //prefix --frac
Fraction operator-- (Fraction& frac, int); //postfix --frac

std::ostream& operator<< (std::ostream& os, const Fraction& frac);
std::istream& operator>> (std::istream& is, Fraction& frac);

} //namespace fraction {
#endif