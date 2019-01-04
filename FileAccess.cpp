
#include "stdafx.h"
#include "FileAccess.h"

/**/

/*

FileAccess::FileAccess( int argc, char *argv[] )

NAME

	FileAccess::FileAccess

SYNOPSIS

	FileAccess::FileAccess( int argc, char *argv[] );
    argc    --> number of arguments that is passed through terminal
    *argv[] --> array containing the arguments


DESCRIPTION

	 Initializes class to prepare for file input output by using array of arguments

RETURNS

	 N/A - constructor

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/
FileAccess::FileAccess(int argc, char *argv[])
{
	// Check that there is exactly one run time parameter.
	if (argc != 2) {
		cerr << "Usage: Assem <FileName>" << endl;
		exit(1);
	}
	// Open the file.  One might question if this is the best place to open the file.
	// One might also question whether we need a file access class.
	m_sfile.open(argv[1], ios::in);

	// If the open failed, report the error and terminate.
	if (!m_sfile) {
		cerr << "Source file could not be opened, assembler terminated."
			<< endl;
		exit(1);
	}
}

/**/

/*

FileAccess::~FileAccess()

NAME

	FileAccess::~FileAccess

SYNOPSIS

	FileAccess::~FileAccess( );

DESCRIPTION

	 Destrutor of class. Also, closes file stream.

RETURNS

	 N/A - constructor

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/


FileAccess::~FileAccess()
{
	// Not that necessary in that the file will be closed when the program terminates.
	m_sfile.close();
}

/**/

/*

FileAccess::GetNextLine(string &a_buff)

NAME

	FileAccess::GetNextLine

SYNOPSIS

	bool FileAccess::GetNextLine(string &a_buff);
    a_buff    --> address of string that stores a line from file

DESCRIPTION

	 Stores next line from file in a_buff

RETURNS

	 bool - true if successful, otherwise false

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/

bool FileAccess::GetNextLine(string &a_buff)
{
	// If there is no more data, return false.
	if (m_sfile.eof()) {

		return false;
	}
	getline(m_sfile, a_buff);

	// Return indicating success.
	return true;
}

/**/

/*

FileAccess::rewind()

NAME

	FileAccess::rewind

SYNOPSIS

	void FileAccess::rewind();

DESCRIPTION

	rewinds file obj by setting ios flags to the beginning

RETURNS

	 void

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/



void FileAccess::rewind()
{
	// Clean all file flags and go back to the beginning of the file.
	m_sfile.clear();
	m_sfile.seekg(0, ios::beg);
}
