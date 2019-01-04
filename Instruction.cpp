#pragma once
#include "Instruction.h"

using namespace std;

/**/

/*

Instruction::ParseInstruction(string & a_buff)

NAME

	Instruction::ParseInstruction

SYNOPSIS

	 Instruction::InstructionType Instruction::ParseInstruction(string & a_buff);
     a_buff --> line from assembly code file

DESCRIPTION

	 Parses the line to determine type of instruction i.e. end, comment, unknown, assembly languge,
	 and machine language.

RETURNS

	 Instruction::InstructionType which is an enum in declared publicly in Instruction.h file

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/

Instruction::InstructionType Instruction::ParseInstruction(std::string & a_buff)
{

	m_Label = "";
	m_OpCode = "";
	m_Operand = "";
	m_instruction = a_buff;

	string word;
	vector <string> tempInstr;

	//Removing comment from input string 
	size_t cPos = a_buff.find(';');

	if (cPos != string::npos) {
		a_buff = a_buff.substr(0, cPos);
	}
	istringstream iss(a_buff);

	/*InstructionType returnIType;*/


	while (iss >> word) {  
		if (!word.empty()) {
			
			tempInstr.push_back(word);
		}
	}

	if (tempInstr.empty()) {
		return ST_Comment; // denotes either comment or blank line statemenet
	}
	
	//At this point the instruction should have at most 3 fields
	if (tempInstr.size() > 3) {
		return ST_Unknown; // for statements that have greater than 3 fields after removing ignoring comment and blank lines
	}

	 //Deal with standalone statements
	

	if (tempInstr.size() == 1) {
		string firstWord = *tempInstr.begin();
		if (firstWord == "end") {
			m_OpCode = firstWord;
			return ST_End;
		}
		
		if (firstWord == "halt") {
			m_OpCode = firstWord;
			return ST_MachineLanguage;
		}
		return ST_Unknown;
	}
	  
	 //Deal with statements with two words

	if (tempInstr.size() == 2) {
		// since only end and halt may have labels when size statement has two words
		if (tempInstr[1] == "end") {
			m_Label = tempInstr[0];
			m_OpCode = tempInstr[1];
			return ST_End;
		}

		if (tempInstr[1] == "halt") {
			m_Label = tempInstr[0];
			m_OpCode = tempInstr[1];
			return ST_MachineLanguage;
		}
		if (*tempInstr.begin() == "org") {
			m_OpCode = tempInstr[0];
			m_Operand = tempInstr[1];
			return ST_AssemblerInstr;
		}
		if (isMachineCode(tempInstr[0])) {
			m_OpCode = tempInstr[0];
			m_Operand = tempInstr[1];
			return ST_MachineLanguage;
		}
		
		return ST_Unknown; // sice org is already dealt with 
	}
	// Assuming end halt and org are not allowed to have labels
	 //Deal with statements with more than two words
	if (tempInstr.size() == 3) {
		if (tempInstr[1] == "dc" || tempInstr[1] == "ds"|| tempInstr[1]=="org" ) {
			m_Label = *tempInstr.begin();
			m_OpCode = tempInstr[1];
			m_Operand = tempInstr[2];
			return ST_AssemblerInstr;
		}
		if (isMachineCode(tempInstr[1])) {
			m_Label = *tempInstr.begin();
			m_OpCode = tempInstr[1];
			m_Operand = tempInstr[2];
			return ST_MachineLanguage;
		}
		return ST_Unknown;
	}
	return ST_Unknown;
}

/**/

/*

Instruction::LocationNextInstruction(int a_loc)

NAME

	Instruction::LocationNextInstruction

SYNOPSIS

	int Instruction::LocationNextInstruction(int a_loc);
    a_loc    --> address of VC3600 

DESCRIPTION

	 Determines the location of next instruction

RETURNS

	 int - integer value that contains location of next instruction

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/


int Instruction::LocationNextInstruction(int a_loc)
{
	if (m_OpCode == "ds") {
		int numOperand;
		const char *operandcstr = m_Operand.c_str();
		if (str2int(numOperand, operandcstr, 10) == SUCCESS) {
			return a_loc + numOperand;
		}
		
	}
	if (m_OpCode == "org") {
		int numOperand;
		const char *operandcstr = m_Operand.c_str();
		if (str2int(numOperand, operandcstr, 10) == SUCCESS) {
			return a_loc + numOperand;
		}
		
	}
	return ++a_loc;
}

/**/

/*

bool Instruction::isMachineCode(string opCode)

NAME
	Instruction::isMachineCode

SYNOPSIS

	bool Instruction::isMachineCode(string opCode);
	opCode	--> operation code of assembly instruction

DESCRIPTION

	Check whether assembly code has machine language equivalent or not

RETURNS

	 bool - true if operation code is machine language equivalent

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/


bool Instruction::isMachineCode(string opCode)
{
	bool reuturnBool = false;
	int i = 0;
	while (i < assem_opcodes.size()) {
		if (assem_opcodes[i] == opCode) {
			reuturnBool = true;
		}
		i++;
	}
	return reuturnBool;
}

/**/

/*

Instruction::convert_error Instruction::str2int(int &i, char const *s, int base = 10)

NAME
	Instruction::str2int

SYNOPSIS

	Instruction::convert_error Instruction::str2int(int &i, char const *s, int base = 10);
	i	--> address of integer value of the string translated
	s	--> address of char string array to be translated to int
	base	--> base of number system - in this case we want decimal so 10

DESCRIPTION

	Convert char array that contains numbers in the form of character to int of requested base

RETURNS

	 Instruction::convert_error which is an enum that has different values to determine successful or 
	 unsuccessful conversion

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/

Instruction::convert_error Instruction::str2int(int &i, char const *s, int base = 10) {
	char *end;
	long  l;
	errno = 0;
	l = strtol(s, &end, base);
	if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
		return OVERFLOW_1;
	}
	if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
		return UNDERFLOW_2;
	}
	if (*s == '\0' || *end != '\0') {
		return INCONVERTIBLE;
	}
	i = l;
	return SUCCESS;
}

