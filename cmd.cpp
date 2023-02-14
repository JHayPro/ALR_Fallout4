#include "pch.h"

#ifndef GLOB_H
#define GLOB_H

class message {
public:

	static void displayCOMErrorMessage(HRESULT _hr)
	{
		_com_error err(_hr);
		MessageBox(NULL, err.ErrorMessage(), "ALR_ERROR", MB_SETFOREGROUND);
		exit(EXIT_FAILURE);
	}

	static void displayErrorMessage(string _title, string _message)
	{
		MessageBox(NULL, _message.c_str(), _title.c_str(), MB_SETFOREGROUND);
		exit(EXIT_FAILURE);
	}

	static void displayMessage(string _title, string _message)
	{
		MessageBox(NULL, _message.c_str(), _title.c_str(), MB_SETFOREGROUND);
	}

	static void checkForError(HRESULT _hr) {
		if (FAILED(_hr))
			message::displayCOMErrorMessage(_hr);
	}

	static void checkForFalseError(bool _r, string _message) {
		if (!_r)
			message::displayErrorMessage("ALR_ERROR", _message);
	}

	static void checkForFalse(bool _r, string _message) {
		if (!_r)
			message::displayMessage("ALR_WARNING", _message);
	}
};

class path {
public:

	static bool verifyPath(string _path)
	{
		return filesystem::exists(_path);
	}

	static void verifyPathError(string _path, string _errorMsg)
	{
		if (!verifyPath(_path)) message::displayErrorMessage("ALR_ERROR", _errorMsg);
	}

	static string toLower(string _input)
	{
		transform(_input.begin(), _input.end(), _input.begin(), [](unsigned char _c) { return tolower(_c); });
		return _input;
	}

	static wstring to_wstring(string _input)
	{
		return wstring(_input.begin(), _input.end());
	}

	static string to_string(wstring _input)
	{
		return string(_input.begin(), _input.end());
	}

	static string getDirectory(string _path)
	{
		return findPrecedingToChar(_path, '\\');
	}

	static string getDirectoryFromBegin(string _path, int _distance)
	{
		return _path.substr(0, _path.size() - _distance);
	}

	static string getDirectoryFromEnd(string _path, int _distance)
	{
		return _path.substr(_path.size() - _distance, _path.size());
	}

	static wstring getExtension(wstring _path)
	{
		return findPrecedingToChar(_path, '.');
	}

	template <typename T> static T findPrecedingToChar(T _path, char _desChar)
	{
		if (_path.back() == _desChar)
			_path.pop_back();

		T tempS;
		int tempI;
		for (tempI = 1; _path.at(_path.size() - tempI) != _desChar; tempI++) {}
		for (int i = 1; i < tempI; i++)
			tempS.push_back(_path.at(_path.size() - tempI + i));
		return tempS;
	}
};
#endif