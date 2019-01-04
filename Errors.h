/**/

/*

Error Class

NAME

	 Errors - Handle any errors encountered while translating assembly code into machine language

DESCRIPTION

	 Any errors that occurs while translating are recorded to be used during emulation by assembler class

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/
#ifndef _ERRORS_H
#define _ERRORS_H
#include "stdafx.h"

class Errors {

public:

	// Initializes error reports.
	static void InitErrorReporting();

	// Records an error message.
	static void RecordError(std::string &a_emsg);

	// Displays the collected error message.
	static void DisplayErrors();

	inline static bool hasErrors() {
		return !m_ErrorMsgs.empty();
	}

private:

	static vector<string> m_ErrorMsgs;
};
#endif