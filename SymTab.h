
#pragma once

/**/

/*

SymbolTable Class

NAME

	 SymbolTable

DESCRIPTION

	 SymbolTable class - Constructs a symbol table from location and symbol

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/

class SymbolTable {

public:
	// Get rid of constructor and destructor if you don't need them.
	SymbolTable() {};
	~SymbolTable() {};

	const int multiplyDefinedSymbol = -999;

	// Add a new symbol to the symbol table.
	void AddSymbol(string &a_symbol, int a_loc);

	// Display the symbol table.
	void DisplaySymbolTable();

	// Lookup a symbol in the symbol table.
	bool LookupSymbol(string &a_symbol, int &a_loc);

private:

	// This is the actual symbol table.  The symbol is the key to the map.
	map<string, int> m_symbolTable;

};