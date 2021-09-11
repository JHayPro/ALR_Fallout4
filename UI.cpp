#include "pch.h"

#ifndef GLOB_H
#define GLOB_H

class message {
public:

	static void displayCOMErrorMessage(HRESULT hr)
	{
		_com_error err(hr);
		MessageBox(NULL, err.ErrorMessage(), "ALR_ERROR", MB_SETFOREGROUND);
		exit(EXIT_FAILURE);
	}

	static void displayErrorMessage(string title, string message)
	{
		MessageBox(NULL, message.c_str(), title.c_str(), MB_SETFOREGROUND);
		exit(EXIT_FAILURE);
	}

	static void displayMessage(string title, string message)
	{
		MessageBox(NULL, message.c_str(), title.c_str(), MB_SETFOREGROUND);
	}
};
#endif