#ifndef FRACTION_HPP_
#define FRACTION_HPP_

#include "DivisionByZeroException.hpp"
#include "SafeArithmetic.hpp"
#include <iostream>

namespace fraction {

class Fraction
{
public:
	explicit Fraction (int numerator=0, int denominator=1, bool overflowProtection = false) : m_numerator(numerator), 
		m_denominator(denominator), m_overflowProtection(overflowProtection) {
			if (0==denominator)
				throw DivisionByZeroException();
			this->reduce();
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

	// += operators
	Fraction& operator+= (const Fraction& frac); //frac1+=frac2

	// - operators
	Fraction operator- (const Fraction& frac) const; //frac1+frac2
	Fraction operator- (int number) const; //frac-number
	friend Fraction operator- (int number, const Fraction& frac); //number-frac

	// -= operators
	Fraction& operator-= (const Fraction& frac); //frac1+=frac2
	Fraction& operator-= (int number); //frac-=number

	// * operators
	Fraction operator* (const Fraction& frac) const; //frac1*frac2
	Fraction operator* (int number) const; //frac*number
	friend const Fraction operator* (int number, const Fraction& frac); //number*frac

	// *= operators
	Fraction& operator*= (const Fraction& frac); //frac1*=frac2
	Fraction& operator*= (int number); //frac*=number

	// / operators
	Fraction operator/ (const Fraction& frac) const; //frac1/frac2
	Fraction operator/ (int number) const; //frac/number
	friend const Fraction operator/ (int number, const Fraction& frac); //number/frac

	// /= operators
	Fraction& operator/= (const Fraction& frac); //frac1/=frac2
	Fraction& operator/= (int number); //frac/=number

	friend std::ostream& operator<< (std::ostream& os, const Fraction& frac);
	friend std::istream& operator>> (std::istream& is, Fraction& frac);

	void swap(Fraction& other) {
		std::swap(this->m_numerator, other.m_numerator);
		std::swap(this->m_denominator, other.m_denominator);
	}

	inline int sign() const {
		return Fraction::sign(this->m_numerator) * Fraction::sign(this->m_denominator);
	}

	inline int setNumerator(int numerator) {
		this->m_numerator = numerator;
		this->reduce();
	}

	inline int getNumerator() const {
		return this->m_numerator;
	}

	inline int setDenominator(int denominator) {
		this->m_denominator = denominator;
		this->reduce();
	}

	inline int getDenominator() const {
		return this->m_denominator;
	}

	float toFloat() const;

private:
	int m_numerator;
	int m_denominator;
	bool m_overflowProtection;

	void reduce() {
		if (0==this->m_denominator && this->m_overflowProtection)
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
			if (this->m_overflowProtection) {
				this->m_numerator = SafeArithmetic::multiply(this->m_numerator, -1);
				this->m_denominator = SafeArithmetic::multiply(this->m_denominator, -1);
			}
			else {
				this->m_numerator *= -1;
				this->m_denominator *= -1;
			}
		}
	}

	static inline int gcd(int a, int b) {
		if (0 == b)
			return a;
		return gcd(b, a % b);
	}

	static inline int sign(int x) {
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

bool operator< (const Fraction& lhs, const Fraction& rhs); //lhs<rhs
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

} //namespace fraction {
#endif