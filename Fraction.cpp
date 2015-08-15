#include "Fraction.hpp"
#include "SafeArithmetic.hpp"
#include "DivisionByZeroException.hpp"
#include <iostream>
#include <string>

Fraction& Fraction::operator= (Fraction frac) {
	swap(*this, frac);
	return *this;
}

Fraction& Fraction::operator= (int number) {
	swap(*this, Fraction(number));
	return *this;
}


const Fraction Fraction::operator+ () const {
	return *this;
}


const Fraction Fraction::operator- () const {
	return *this * (-1);
}


bool Fraction::operator== (const Fraction& frac) const { 
	return (this->m_numerator == frac.m_numerator && this->m_denominator == frac.m_denominator);
}

bool Fraction::operator== (int number) const {
	return *this==Fraction(number);
}

bool operator== (int number, const Fraction& frac) {
	return frac==number;
}


bool Fraction::operator!= (const Fraction& frac) const {
	return !(*this==frac);
}

bool Fraction::operator!= (int number) const {
	return !(*this==number);
}

bool operator!= (int number, const Fraction& frac) {
	return !(number==frac);
}


bool Fraction::operator< (const Fraction& frac) const {
	return (*this-frac).sign() < 0;
}

bool Fraction::operator< (int number) const {
	return (*this-number).sign() < 0;
}

bool operator< (int number, const Fraction& frac) {
	return (number-frac).sign() < 0;
}


bool Fraction::operator<= (const Fraction& frac) const {
	return !(frac < *this);
}

bool Fraction::operator<= (int number) const {
	return !(number < *this);
}

bool operator<= (int number, const Fraction& frac) {
	return !(frac < number);
}


bool Fraction::operator> (const Fraction& frac) const {
	return frac < *this;
}

bool Fraction::operator> (int number) const {
	return number < *this;
}

bool operator> (int number, const Fraction& frac) {
	return frac < number;
}


bool Fraction::operator>= (const Fraction& frac) const {
	return !(*this < frac);
}

bool Fraction::operator>= (int number) const {
	return !(*this < number);
}

bool operator>= (int number, const Fraction& frac) {
	return !(number < frac);
}


const Fraction Fraction::operator+ (const Fraction& frac) const {
	// a/b + c/d = (ad+bc)/bd
	if (this->m_overflowProtection) {
		int numerator1 = SafeArithmetic::multiply(this->m_numerator, frac.m_denominator);
		int numerator2 = SafeArithmetic::multiply(this->m_denominator, frac.m_numerator);
		int numerator = SafeArithmetic::add(numerator1, numerator2);

		int denominator = SafeArithmetic::multiply(this->m_denominator,frac.m_denominator);
		return Fraction(numerator, denominator, this->m_overflowProtection);
	}
	else {
		int numerator = this->m_numerator*frac.m_denominator + frac.m_numerator*this->m_denominator;
		int denominator = this->m_denominator * frac.m_denominator;
		return Fraction(numerator, denominator, this->m_overflowProtection);
	}
}

const Fraction Fraction::operator+ (int number) const {
	return (*this) + Fraction(number);
}

const Fraction operator+ (int number, const Fraction& frac) {
	//number+frac == frac+number
	return frac+number;
}


Fraction& Fraction::operator+= (const Fraction& frac) {
	Fraction new_frac = (*this) + frac;
	return (*this) = new_frac;
}

Fraction& Fraction::operator+= (int number) {
	Fraction new_frac = (*this) + number;
	return (*this) = new_frac;
}


const Fraction Fraction::operator- (const Fraction& frac) const {
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

const Fraction Fraction::operator- (int number) const {
	return (*this) - Fraction(number);
}

const Fraction operator- (int number, const Fraction& frac) {
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


const Fraction Fraction::operator* (const Fraction& frac) const {
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

const Fraction Fraction::operator* (int number) const {
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


const Fraction Fraction::operator/ (const Fraction& frac) const {
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

const Fraction Fraction::operator/ (int number) const {
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

	if (0 == numerator && 0 == denominator)
		return os << "NaN";
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


Fraction::operator float() const {
	if (0==this->m_denominator)
		throw DivisionByZeroException();

	return (float)this->m_numerator / (float)this->m_denominator;
}


void swap(Fraction& frac1, Fraction& frac2) {
		std::swap(frac1.m_numerator, frac2.m_numerator);
		std::swap(frac1.m_denominator, frac2.m_denominator);
}