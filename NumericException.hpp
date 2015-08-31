/**
* Author: Lahav Schlesinger
**/

/*
* In this file we have the declaration of the NumericException class
*/

#ifndef NUMERICEXCEPTION_HPP_
#define NUMERICEXCEPTION_HPP_

#include <exception>
#include <string>

/*
This class represents a generic numeric exception, to which other numeric exceptions
are to be derived from.
Note that this class is abstract.
*/
class NumericException : public std::exception
{
public:
	//-- constructors/destructor --//

	/* constructor */

	//Returns the error message as a C string.
	virtual const char* what() const noexcept { return this->m_err_msg.c_str(); }

	/* destructor */
	virtual ~NumericException() = 0;

protected:

	//-- protected data members --//

	//The error message
	std::string m_err_msg;
};

#endif