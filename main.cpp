#include "Fraction.hpp"
#include <iostream>

int main() {
	Fraction frac(2,3,true);
	Fraction frac2 = 5 - frac;
	//std::cin >> frac;

	std::cout << "frac = " << frac << std::endl;
}
