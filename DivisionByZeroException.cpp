#include "DivisionByZeroException.hpp"


DivisionByZeroException::DivisionByZeroException()
{
}

const char* DivisionByZeroException::what() const {
	return NULL;
}

DivisionByZeroException::~DivisionByZeroException()
{
}
