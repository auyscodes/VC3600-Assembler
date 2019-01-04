/**/
/*
Assem

NAME
	Assem - Driver code containing main method

DESCRIPTION

	Assem - the main function contains instance of Assembler class. Different methods in the Assembler class are
	then used to make the program run

AUTHOR

	Niraj Bhattarai

DATE

	12/12/2018
*/
/**/
#include "stdafx.h"     


#include "Assembler.h"

int main( int argc, char *argv[] )
{
    Assembler assem( argc, argv );

     //Establish the location of the labels:
    assem.PassI();

     //Display the symbol table.
    assem.DisplaySymbolTable();

     //Output the symbol table and the translation.
    assem.PassII();
    
     //Run the emulator on the VC3600 program that was generated in Pass II.
	assem.RunEmulator();
	 
   
     //Terminate indicating all is well.  If there is an unrecoverable error, the 
     //program will terminate at the point that it occurred with an exit(1) call.
	system("pause");
    return 0;
}