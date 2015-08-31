/**
* Author: Lahav Schlesinger
**/

/*
* In this file we have the declaration of the DivisionByZeroException class
*/


#ifndef NUMERICOVERFLOWEXCEPTION_HPP_
#define NUMERICOVERFLOWEXCEPTION_HPP_

#include "NumericException.hpp"


/*
This class represents an exception class that should be thrown whenever a
numeric overflow occurs.
*/
class NumericOverflowException : public NumericException
{
public:
	//-- constructors/destructor --//

	/* constructor */

	//Sets the error message to "numeric overflow detected".
	NumericOverflowException() {
		this->m_err_msg = "numeric overflow detected";
	}
};

#endif
