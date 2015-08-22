#include "DivisionByZeroException.hpp"


DivisionByZeroException::DivisionByZeroException()
{
}

const char* DivisionByZeroException::what() const noexcept {
	return NULL;
}

DivisionByZeroException::~DivisionByZeroException()
{
}
