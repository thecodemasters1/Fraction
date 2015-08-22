#include "Fraction.hpp"
#include <iostream>

int main() {
	//int x = 46342 * 46340;
	//std::cout << x << std::endl;
	fraction::Fraction frac;
	std::cin >> frac;
	std::cout << "frac= " << frac << std::endl;
	/*
	try {
		fraction::Fraction frac(1073741823, 1, true);
		fraction::Fraction frac2(1073741824, 1, true);
		std::cout << (frac + frac2) << std::endl;
	}
	catch (...) {
		std::cout << "HERE" << std::endl;
	}
	*/
	//std::cout << "frac = " << frac << std::endl;
}
