#pragma once

/**/

/*

Instruction Class

NAME

	 Instruction

DESCRIPTION

	 Instruction class - Parse each line to determine type of instruction

AUTHOR

	 Niraj Bhattarai

DATE

	 12/12/2018

*/

/**/


#include "stdafx.h"
#include <stdlib.h>
using namespace std;
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
// The elements of an instruction.
class Instruction {

public:

	Instruction() { };
	~Instruction() { };

	// Codes to indicate the type of instruction we are processing.  Why is this inside the
	// class?
	enum InstructionType {
		ST_MachineLanguage, // A machine language instruction.
		ST_AssemblerInstr,  // Assembler Language instruction.
		ST_Comment,          // Comment or blank line
		ST_End,
		ST_Unknown // end instruction.
	};
	// Parse the Instruction.
	InstructionType ParseInstruction(std::string &a_buff);

	// Compute the location of the next instruction.
	int LocationNextInstruction(int a_loc);

	// To access the label
	inline std::string &GetLabel() {

		return m_Label;
	};
	// To determine if a label is blank.
	inline bool isLabel() {

		return !m_Label.empty();
	};

	inline std::string &GetOpcode() {
		return m_OpCode;
	}
	inline std::string &GetOperand() {
		return m_Operand;
	}
	inline int &GetOpCodeValue(std::string opCode) {
		return assem_opcodes_value[opCode];
		
	}
	bool isMachineCode(std::string opCode); // this was changed recently rkpc

	enum convert_error { SUCCESS, OVERFLOW_1, UNDERFLOW_2, INCONVERTIBLE };
	// will be used for string to int conversion
	static convert_error str2int(int &i, char const *s, int base);
private:
	

	// The elemements of a instruction
	string m_Label;            // The label.
	string m_OpCode;       // The symbolic op code.
	string m_Operand;      // The operand.


	string m_instruction;    // The original instruction.

							 // Derived values.
	int m_NumOpCode;     // The numerical value of the op code.
	InstructionType m_type; // The type of instruction.

	bool m_IsNumericOperand;// == true if the operand is numeric.
	int m_OperandValue;   // The value of the operand if it is numeric.
	
	

	vector <string> assem_opcodes = { "add", "sub", "mult", "div", "load", "store", "read", "write", "b", "bm", "bz", "bp", "halt" };
	/*vector<string> AssemblerInstrcutions_arr = { "DC", "DS", "ORG", "END" };*/

	map <string, int> assem_opcodes_value = { {"add",1}, {"sub",2}, {"mult", 3}, {"div",4}, {"load",5}, {"store",6}, {"read",7}, {"write",8}, {"b",9},{"bm",10},{"bz",11},{"bp",12},{"halt",13} };
};

