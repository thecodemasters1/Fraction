#ifndef DIVISIONBYZEROEXCEPTION_HPP_
#define DIVISIONBYZEROEXCEPTION_HPP_

#include <exception>

class DivisionByZeroException : public std::exception
{
public:
	DivisionByZeroException();

	virtual const char* what() const noexcept; 
	~DivisionByZeroException();
};

#endif