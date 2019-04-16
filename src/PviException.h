#pragma once

#include <exception>
#include <string>

class PviException : public std::exception
{
private:
	char *mpszMessage = nullptr;

public:
	PviException ();
	PviException (const PviException&);
	PviException (std::string);
	~PviException ();

	PviException& operator= (PviException);
	const char* what () const override;
};