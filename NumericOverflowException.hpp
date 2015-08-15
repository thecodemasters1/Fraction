#if !defined NUMERICOVERFLOWEXCEPTION_HPP_
#define NUMERICOVERFLOWEXCEPTION_HPP_

#include <exception>

class NumericOverflowException : public std::exception
{
public:
	NumericOverflowException();

	virtual const char* what() const; 
	~NumericOverflowException();
};

#endif
