#pragma once 
#include "Emulator.h"
/**/

/*

bool emulator::insertMemory(int a_location, int a_contents)

NAME

	emulator::insertMemory(int a_location, int a_contents)

SYNOPSIS

	bool emulator::insertMemory(int a_location, int a_contents)

	a_location -> Address in VC 3600
	a_contents -> Value to be stored in address of VC3600

DESCRIPTION

	Insert numeric value in VC3600 address

RETURNS

	bool - true if successful and false if unsuccessful

AUTHOR

	Niraj Bhattarai

DATE

	12/12/2018

*/

/**/

bool emulator::insertMemory(int a_location, int a_contents) {
	// If the location to be stored in is greater than 10000, then, return false
	if (a_location >= MEMSZ) {
		return false;
	}

	m_memory[a_location] = a_contents;

	return true;
}

/**/

/*

bool emulator::runProgram()

NAME

	emulator::runProgram()

SYNOPSIS

	bool emulator::runProgram()

DESCRIPTION

	Runs the emulator

RETURNS

	bool - true if successful and false if unsuccessful

AUTHOR

	Niraj Bhattarai

DATE

	12/12/2018

*/

/**/


bool emulator::runProgram() {

	for (int index = 0; index < MEMSZ; ++index) {
		if (m_memory[index] != 0) {
			int opCode = m_memory[index] / 10000;
			int address = m_memory[index] % 10000;
			switch (opCode) {
			case 1:
				// Add content of accumulator and memory location 
				accumulator += m_memory[address];
				break;
			case 2:
				// Substract content of accumulator and memory location
				accumulator -= m_memory[address];
				break;
			case 3:
				// Multiply content of accumulator and memory location
				accumulator *= m_memory[address];
				break;
			case 4:
				// Divide content of accumulator and memory location
				accumulator = accumulator / m_memory[address];
				break;
			case 5:
				// Load content of address into accumulator
				accumulator = m_memory[address];
				break;
			case 6:
				// Store the content of accumulator in address given
				m_memory[address] = accumulator;
				break;
			case 7:
				// Read line and place the first 6 digits in specified address
				cout << "?";
				int userInput;
				cin >> userInput;
				userInput = userInput % 1000000;
				m_memory[address] = userInput;
				break;
			case 8:
				// Display content of address
				cout << m_memory[address] << endl;
				break;
			case 9:
				// Jump to address for next instruction
				index = address;
				break;
			case 10:
				// Jump to address under condition
				if (accumulator < 0) index = address - 1;
				break;
			case 11:
				// Jump to address under condition
				if (accumulator == 0) index = address - 1;
				break;
			case 12:
				// Jump to address under condition
				if (accumulator > 0) index = address - 1;
				break;
			case 13:
				index = 10000;
				break;
			}
		}
	}

	return true;
}