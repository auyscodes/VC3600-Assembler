
#include "Errors.h"
vector<string> Errors::m_ErrorMsgs;

/**/

/*

Errors::InitErrorReporting()

NAME

	Errors::InitErrorReporting

SYNOPSIS

	void Errors::InitErrorReporting();

DESCRIPTION

	 Initialized class by clearing vector that contains error messages

RETURNS

	 void

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/

void Errors::InitErrorReporting() {
	m_ErrorMsgs.clear();
}

/**/

/*

Errors::RecordError(string & a_emsg)

NAME

	Errors::RecordError

SYNOPSIS

	void Errors::RecordError(string & a_emsg);
    a_emsg        --> string message that error class records


DESCRIPTION

	 Logs error by recording it into vector

RETURNS
	
	void

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/


void Errors::RecordError(string &a_emsg) {
	m_ErrorMsgs.push_back(a_emsg);
}

/**/

/*

Errors::DisplayErrors()

NAME

	Errors::DisplayErrors

SYNOPSIS

	void Errors::DisplayErrors();

DESCRIPTION

	 Print out errors recorded

AUTHOR

	 Niraj Bhattarai

RETURNS

	 void

DATE

	 12/12/2018

*/

/**/


void Errors::DisplayErrors() {
	if (!m_ErrorMsgs.empty()) {
		for (int i = 0; i < m_ErrorMsgs.size(); i++) {
			cout << m_ErrorMsgs[i] << endl;
		}
	}
	
}