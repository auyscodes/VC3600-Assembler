#pragma once
/**/
/*
Assembler Class

NAME

	 Assembler - Translate and Run VC3600 assembler

DESCRIPTION
	 
	 Assembler - Utilizes fileaccess, instruction, emulator, error class to pass through 
	             assembler code in text file to translate and report error. If no error are reported
				 then this class has instance of emulator class to run the VC3600 code translated.

AUTHOR
	 
	 Niraj Bhattarai.

DATE

	 12/12/2018
*/
/**/
#include "stdafx.h"
#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"
#include "Errors.h"


class Assembler {

public:
	Assembler(int argc, char *argv[]);
	~Assembler();
	
	// Pass I - establish the locations of the symbols
	void PassI();

	// Display the symbols in the symbol table.
	void DisplaySymbolTable() { m_symtab.DisplaySymbolTable(); }

	// Pass II - generate a translation
	void PassII();

	// Run emulator on the translation.
	void RunEmulator();
	

private:
	
	


	FileAccess m_facc;	    // File Access object
	SymbolTable m_symtab; // Symbol table object 
	Instruction m_inst;	    // Instruction object 
	emulator m_emul;        // Emulator object
	
	
	
};