#pragma once
/**/

/*

FileAccess Class

NAME

	 FileAccess - Access text file containing assembly language code

DESCRIPTION

	 Efficient access rewinding and error reporting of file containing assembly code to be translated 

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/
#ifndef _FILEACCESS_H  // This is the way that multiple inclusions are defended against often used in UNIX
#define _FILEACCESS_H // We use pramas in Visual Studio.  See other include files
#include <fstream>
#include <stdlib.h>
#include <string>

class FileAccess {

public:

	// Opens the file.
	FileAccess(int argc, char *argv[]);

	// Closes the file.
	~FileAccess();

	// Get the next line from the source file.
	bool GetNextLine(string &a_buff);

	// Put the file pointer back to the beginning of the file.
	void rewind();

private:
	
	std::ifstream m_sfile;		// Source file object.
};
#endif
