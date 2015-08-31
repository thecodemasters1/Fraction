#include "Fraction.hpp"
#include "NumericException.hpp"
#include <iostream>
#include <climits>

int main() {

	try {
		fraction::Fraction frac((INT_MAX / 2) + 1, 1);
		fraction::Fraction frac2((INT_MAX / 2) + 1, 1, true);
		std::cout << (frac + frac2) << std::endl;
	}
	catch (NumericException& err) {
		std::cout << err.what() << std::endl;
	}
}
