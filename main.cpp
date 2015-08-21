#include "Fraction.hpp"
#include <iostream>
#include <vector>
#include <memory>

int main() {
	fraction::Fraction frac(2,3);
	fraction::Fraction frac2(2,4);
	std::cout << (frac+frac2) << std::endl;

	//std::cout << "frac = " << frac << std::endl;
}
