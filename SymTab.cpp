//
//		Implementation of the symbol table class.
//
#pragma once
#include "stdafx.h"
#include "SymTab.h"
#include <iomanip>

/**/

/*

SymbolTable::AddSymbol(string &a_symbol, int a_loc)

NAME

	SymbolTable::AddSymbol

SYNOPSIS

	 void SymbolTable::AddSymbol(string &a_symbol, int a_loc);
	 a_symbol --> string containg symbol
	 a_loc --> location of instruction in assembly code

DESCRIPTION

	 This function will place the symbol "a_symbol" and its location "a_loc"
     in the symbol table.

RETURNS

	 void

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/

void SymbolTable::AddSymbol(string &a_symbol, int a_loc)
{
	// If the symbol is already in the symbol table, record it as multiply defined.
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);
	if (st != m_symbolTable.end()) {

		st->second = multiplyDefinedSymbol;
		return;
	}
	// Record a the  location in the symbol table.
	m_symbolTable[a_symbol] = a_loc;
}

/**/

/*

SymbolTable::DisplaySymbolTable()

NAME

	SymbolTable::DisplaySymbolTable

SYNOPSIS

	void SymbolTable::DisplaySymbolTable();

DESCRIPTION

	Function displays the symbol and location stored in the symbol table

RETURNS

	 void

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/

void SymbolTable::DisplaySymbolTable() {
	map<string, int>::iterator st;
	cout << "Symbol Table: " << endl;
	cout << endl;
	cout << left << setw(10) << "Symbol#" << setw(10) << "Symbol" << "Location" << endl;
	int symbolNumber = 0;
	for (st = m_symbolTable.begin(); st != m_symbolTable.end(); ++st) {
		cout << left << setw(10) << symbolNumber++ << setw(10) << st->first << st->second << endl;
	}
	system("pause");
}

/**/

/*

SymbolTable::LookupSymbol(string &a_symbol, int &a_loc)

NAME

	SymbolTable::LookupSymbol

SYNOPSIS

	bool SymbolTable::LookupSymbol(string &a_symbol, int &a_loc);
	a_symbol	--> symbol stored in symbol table
	a_loc	--> location of symbol stored

DESCRIPTION

	Looks up the symbol string in a_symbol and saves the location in a_loc

RETURNS

	 bool - true if symbol is present

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/

bool SymbolTable::LookupSymbol(string &a_symbol, int &a_loc) {
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);
	if (st != m_symbolTable.end()) {
		a_loc = st->second;
		return true;
	}

	return false;

}