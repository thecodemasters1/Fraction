/**
* Author: Lahav Schlesinger
**/

/*
* In this file we have the declaration of the DivisionByZeroException class
*/


#ifndef DIVISIONBYZEROEXCEPTION_HPP_
#define DIVISIONBYZEROEXCEPTION_HPP_

#include "NumericException.hpp"


/*
This class represents an exception class that should be thrown whenever a
division by 0 occured.
*/
class DivisionByZeroException : public NumericException
{
public:
	//-- constructors/destructor --//

	/* constructor */

	//Sets the error message to "error dividing by 0".
	DivisionByZeroException() {
		this->m_err_msg = "error dividing by 0";
	}
};

#endif