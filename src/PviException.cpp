#include "PviException.h"

/*****************************************************************************
Constructor:      PviException

Description:      The default constructor for the PviException

Parameters:       None

Return            None
*****************************************************************************/
PviException::PviException () 
{
	std::string errorMessage = "PviException";

	mpszMessage = new char[errorMessage.size () + 1];

	strncpy_s (mpszMessage, errorMessage.size () + 1, errorMessage.c_str (),
		errorMessage.size () + 1);
};

/*****************************************************************************
Constructor:      PviException

Description:      The copy constructor for the PviException

Parameters:       rcPVIException - The Exception to copy.

Return            None
*****************************************************************************/
PviException::PviException (const PviException& rcPVIException)
{
	std::size_t size;

	if (nullptr != rcPVIException.mpszMessage)
	{
		size = strlen (rcPVIException.mpszMessage) + 1;
		mpszMessage = new char[size];

		strncpy_s (mpszMessage, size, rcPVIException.mpszMessage, size);
	}
}

/*****************************************************************************
Constructor:      PviException

Description:      A constructor which accepts a string message in which to
					construct the PviException message.

Parameters:       message - The string exception message to copy.

Return            None
*****************************************************************************/
PviException::PviException (std::string message)
{
	std::size_t size;
	if (!message.empty ())
	{
		size = message.size () + 1;

		mpszMessage = new char[size];
		strncpy_s (mpszMessage, size, message.c_str (), size);
	}
}

/*****************************************************************************
Destructor:       PviException

Description:      The default destructor for the PviException

Parameters:       None

Return            None
*****************************************************************************/
PviException::~PviException ()
{
	if (nullptr != mpszMessage)
	{
		delete[] mpszMessage;
		mpszMessage = nullptr;
	}
}

/*****************************************************************************
Method:		      operator=

Description:      An overloading of the copy assignment operator

Parameters:       pviException - The pviException in which to assign to this
									pviException.

Return            A reference to this PviException
*****************************************************************************/
PviException& PviException::operator= (PviException pviException)
{
	using std::swap;

	std::swap (this->mpszMessage, pviException.mpszMessage);

	return *this;
}

/*****************************************************************************
Method:		      what

Description:      Returns the internal message to be displayed.

Parameters:       None

Return            The internal message
*****************************************************************************/
const char* PviException::what () const
{
	return mpszMessage;
}