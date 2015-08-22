#include "Fraction.hpp"
#include "SafeArithmetics.hpp"
#include "DivisionByZeroException.hpp"
#include "Utilities.hpp" //For Utilities::isInteger()
#include <iostream>
#include <string>


namespace fraction {

static bool getOverallProtection(const Fraction& frac1, const Fraction& frac2) {
	return frac1.getOverflowProtection() || frac2.getOverflowProtection();
}

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
bool Fraction::operator< (const Fraction& rhs) const { //lhs<rhs
	return ((*this)-rhs).sign() < 0;
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
	return !(number < lhs);
}

bool operator<= (int number, const Fraction& rhs) { //number<=rhs
	return !(rhs < number);
}


// > operators
bool operator> (const Fraction& lhs, const Fraction& rhs) { //lhs>rhs
	return rhs < lhs;
}

bool operator> (const Fraction& lhs, int number) { //lhs>number
	return number < lhs;
}

bool operator> (int number, const Fraction& rhs) { //number>rhs
	return rhs < number;
}


// >= operators
bool operator>= (const Fraction& lhs, const Fraction& rhs) { //lhs>=rhs
	return !(lhs < rhs);
}

bool operator>= (const Fraction& lhs, int number) { //lhs>=number
	return !(lhs < number);
}

bool operator>= (int number, const Fraction& rhs) { //number>=rhs
	return !(number < rhs);
}


// + operators
Fraction operator+ (Fraction lhs, const Fraction& rhs) { //lhs+rhs
	lhs.setOverflowProtection(getOverallProtection(lhs,rhs));
	lhs+=rhs;
	return lhs;
}

Fraction operator+ (Fraction lhs, int number) { //lhs+number
	lhs+=number;
	return lhs;
}

Fraction operator+ (int number, const Fraction& rhs) { //number+rhs
	return rhs+number;
}


// += operators
Fraction& Fraction::operator+= (const Fraction& rhs) {

	/* 

	 
                    ad+bc
    a/b + c/d =  ------------
                     b*d

	OR:

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
	bool overflow_protection = this->m_overflow_protection;

	int a = this->m_numerator;
	int b = this->m_denominator;

	int c = rhs.m_numerator;
	int d = rhs.m_denominator;

	int gcd = this->gcd(b, d);

	if (overflow_protection) {

		// d/gcd
		int d_gcd = SafeArithmetics::divide(d, gcd);

		//a*d/gcd
		int numerator1 = SafeArithmetics::multiply(a, d_gcd);
		//c*b/gcd
		int numerator2 = SafeArithmetics::multiply(c, SafeArithmetics::divide(b,gcd));

		//a*d/gcd + c*b/gcd
		int numerator = SafeArithmetics::add(numerator1, numerator2);

		//lcm = b*d/gcd
		int denominator = SafeArithmetics::multiply(b, d_gcd);

		*this = Fraction(numerator, denominator, overflow_protection);
		return *this;
	}
	else {
		int d_gcd = d / gcd;

		int numerator = a*d_gcd + c*(b / gcd);
		int denominator = b*d_gcd;
		*this = Fraction(numerator, denominator, overflow_protection);
		return *this;
	}
}

Fraction& operator+= (Fraction& lhs, int number) { //lhs+=number
	lhs += Fraction(number);
	return lhs;
}


// - operators
Fraction operator- (Fraction lhs, const Fraction& rhs) { //lhs+rhs
	lhs.setOverflowProtection(getOverallProtection(lhs, rhs));
	lhs -= rhs;
	return lhs;
}

Fraction operator- (Fraction lhs, int number) { //lhs-number
	lhs -= Fraction(number);
	return lhs;
}

Fraction operator- (int number, const Fraction& rhs) { //number-rhs
	Fraction number_frac = Fraction(number);
	number_frac -= rhs;
	return number_frac;
}


// -= operators
Fraction& operator-= (Fraction& lhs, const Fraction& frac) { //lhs-=rhs
	lhs += (-frac);
	return lhs;
}

Fraction& operator-= (Fraction& lhs, int number) { //lhs-=number
	lhs += (-Fraction(number));
	return lhs;
}


// * operators
Fraction operator* (Fraction lhs, const Fraction& rhs) { //lhs*rhs
	lhs.setOverflowProtection(getOverallProtection(lhs, rhs));
	lhs *= rhs;
	return lhs;
}

Fraction operator* (Fraction lhs, int number) { //lhs*number
	lhs *= Fraction(number);
	return lhs;
}

Fraction operator* (int number, const Fraction& rhs) { //number*rhs
	return rhs*number;
}


// *= operators
Fraction& Fraction::operator*= (const Fraction& lhs) { //rhs*=lhs

	// a/b * c/d = ac/bd
	bool overflow_protection = this->m_overflow_protection;

	if (overflow_protection) {
		int numerator = SafeArithmetics::multiply(this->m_numerator, lhs.m_numerator);

		int denominator = SafeArithmetics::multiply(this->m_denominator, lhs.m_denominator);
		*this = Fraction(numerator, denominator, overflow_protection);
		return *this;
	}
	else {
		int numerator = this->m_numerator * lhs.m_numerator;
		int denominator = this->m_denominator * lhs.m_denominator;

		*this = Fraction(numerator, denominator, overflow_protection);
		return *this;
	}

}

Fraction& operator*= (Fraction& lhs, int number) { //lhs*=number
	lhs *= Fraction(number);
	return lhs;
}


// / operators
Fraction operator/ (Fraction lhs, const Fraction& rhs) { // lhs/rhs
	lhs.setOverflowProtection(getOverallProtection(lhs, rhs));
	lhs /= rhs;
	return lhs;

}

Fraction operator/ (Fraction lhs, int number) { // lhs/number
	lhs /= Fraction(number);
	return lhs;
}

Fraction operator/ (int number, const Fraction& rhs) { // number/rhs
	Fraction number_frac = Fraction(number);
	number_frac /= rhs;
	return number_frac;
}


// /= operators
Fraction& Fraction::operator/= (const Fraction& rhs) { // lhs/=rhs
	*this *= Fraction(rhs.getDenominator(), rhs.getNumerator());
	return *this;
}

Fraction& operator/= (Fraction& lhs, int number) { // lhs/=number
	lhs /= Fraction(number);
	return lhs;
}


// ++ operators
Fraction& operator++ (Fraction& frac) { //prefix ++frac
	frac += 1;
	return frac;
}

Fraction operator++ (Fraction& frac, int) { //postfix ++frac
	Fraction new_frac = frac;
	++frac;
	return new_frac;
}


// -- operators
Fraction& operator-- (Fraction& frac) { //prefix --frac
	frac -= 1;
	return frac;
}

Fraction operator-- (Fraction& frac, int) { //postfix --frac
	Fraction new_frac = frac;
	--frac;
	return new_frac;
}


std::ostream& operator<< (std::ostream& os, const Fraction& frac) {
	int numerator = frac.getNumerator();
	int denominator = frac.getDenominator();

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
		std::string input;
		std::getline(is, input);

		std::size_t div_sign_index = input.find('/');

		//Get the numerator
		try {
			if (!Utilities::isInteger(input.substr(0, div_sign_index), numerator))
				continue;
		}
		catch (...) {
			continue;
		}

		//Get the denominator
		if (std::string::npos == div_sign_index)
			denominator = 1;
		else {
			try {
				if (!Utilities::isInteger(input.substr(div_sign_index + 1), denominator))
					continue;
			}
			catch (...) {
				continue;
			}
		}
		break;
	}

	frac.setNumerator(numerator);
	frac.setDenominator(denominator);
	return is;
}


Fraction::operator float() const {
	if (0==this->m_denominator)
		throw DivisionByZeroException();

	return (float)this->m_numerator / (float)this->m_denominator;
}


} //namespace fraction { 