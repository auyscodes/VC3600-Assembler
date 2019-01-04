
#pragma once
#include "Assembler.h"


/**/
/*
Assembler::Assembler( int argc, char *argv[] )

NAME

	Assembler::Assembler(int argc, char *argv[])

SYNOPSIS

	Assembler::Assembler( int argc, char *argv[] );

	argc              --> total number of arguments received in the command line.
	*argv[]           --> a pointer to the array of arguments passed through the command line.

DESCRIPTION

	Constructor of Assembler class

RETURNS

	N/A - Constructor

AUTHOR

	Niraj Bhattarai

DATE

	12/12/2018

*/
/**/
Assembler::Assembler(int argc, char *argv[])
	: m_facc(argc, argv)
{
	// Nothing else to do here at this point.
}



// Destructor currently does nothing.  You might need to add something as you develope this project.
Assembler::~Assembler()
{
}


/**/
/*
void Assembler::PassI()

NAME

	Assembler::PassI() - Creates symbol table 

SYNOPSIS

	void Assembler::PassI()

DESCRIPTION

	Parses through the text file containing assembly language code to construct symbol table

RETURNS

	Void

AUTHOR

	Niraj Bhattarai

DATE
	12/12/2018

*/
	
/**/

void Assembler::PassI()
{
	int loc = 0;        // Tracks the location of the instructions to be generated.

	//					// Successively process each line of source code.
	for (; ; ) {

		// Read the next line from the source file.
		string buff;
		if (!m_facc.GetNextLine(buff)) {

			// If there are no more lines, we are missing an end statement.
			// We will let this error be reported by Pass II.
			return;
		}
		
		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);
		
		// If this is an end statement, there is nothing left to do in pass I.
		// Pass II will determine if the end is the last statement.
		if (st == Instruction::ST_End) return;
		
		// Labels can only be on machine language and assembler language
		// instructions.  So, skip other instruction types.
		// ST_Comment and ST_Unknown will be filtered out.
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr)
		{
			continue;
		}
		// If the instruction has a label, record it and its location in the
		// symbol table.
		
		if (m_inst.isLabel()) {
			m_symtab.AddSymbol(m_inst.GetLabel(), loc);
		}

		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}
	
}

/**/
/*
void Assembler::PassII()

NAME

	Assembler::PassII() - Creates symbol table

SYNOPSIS

	void Assembler::PassII()

DESCRIPTION

	Parses through the text file object containing assembly language code to construct translate instruction using
	symbol table constructed in pass I

RETURNS

	Void

AUTHOR

	Niraj Bhattarai

DATE
	12/12/2018

*/

/**/



void Assembler::PassII()
{
	m_facc.rewind();
	cout << "Translation of Program:" << endl;
	cout << setw(10) << "Location" << setw(10) << "Contents" << setw(10) << "Original Statement" << endl;
	
	int loc = 0;   

	for ( ; ; ) {

		string buff; // stores next line from source file

		if (!m_facc.GetNextLine(buff)) {
			Errors::RecordError(string("Missing end statement"));
			return;
		}
		
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		if (st == Instruction::ST_End) {
			cout << setw(30) << right  << buff << endl;
			break;
		}

		if (st == Instruction::ST_Unknown) {
			Errors::RecordError(string("Error encountered while translating statement"));
			cout << setw(30) << right <<  "Error translating the statement (check opcodes and number of words in statement) : " << buff << endl;
			continue;
		}

		if (st == Instruction::ST_Comment) {
			cout <<setw(30) << right  << buff << endl;
			continue;
		}
		
		// Handles errors in labels first
		if (!m_inst.GetLabel().empty()) {
			if (m_inst.GetLabel().length() > 10) {
				Errors::RecordError("Size of " + m_inst.GetLabel() + " is greater than 10"); continue;
			}
			if (isdigit(m_inst.GetLabel()[0])) {
				Errors::RecordError(m_inst.GetLabel() + " should not start with number");	continue;
			}
		}

		
		// Deal with statements with assembler statements first
		// End is already dealt with
		if (m_inst.GetOpcode() == "org" || m_inst.GetOpcode() == "ds") {
			int numOperand;
			const char *operandcstr = m_inst.GetOperand().c_str();

			if (Instruction::str2int(numOperand, operandcstr, 10) == Instruction::SUCCESS) {
				if (numOperand > 9999) {
					Errors::RecordError(string("Numeric operand should not be greater than 9999 in ") + buff);
				}
				cout << left << setw(10) << loc << setw(25) << right << buff << endl;
			}
			else {
				cout << left << setw(10) << loc << setw(25) << right << "Conversion failed : " << buff << endl;
				Errors::RecordError(string("Operand must be numeric in ") + buff);
			}
			
		}

		if (m_inst.GetOpcode() == "dc") {
			int numOperand;
			const char *operandcstr = m_inst.GetOperand().c_str() ;
			
			if (Instruction::str2int(numOperand, operandcstr, 10) == Instruction::SUCCESS) {
				if (numOperand > 999999) {
					Errors::RecordError(string("Number is greater than 6 digits in : ") + buff);
				}
				cout << left << setw(10) << loc << right << setfill('0') << setw(6) << numOperand << setw(4) << setfill(' ') << "" << left << setw(10) << buff << endl;
				if (!m_emul.insertMemory(loc, numOperand)) { 
					Errors::RecordError(string("VC3600 out of memory"));
				}
			}
			else {
				Errors::RecordError(string("Operands must be numeric in : ") + buff);
			}
			
		}


		// Deal with machine language statement after
		if (m_inst.GetOpcode() == "halt") {
			cout << setw(10) << left << loc << right << setfill('0') << setw(6) << m_inst.GetOpCodeValue(m_inst.GetOpcode()) * 10000 << setw(4) << setfill(' ') << "" << left << setw(10) << buff << endl;
			loc = m_inst.LocationNextInstruction(loc);
			continue;
		}

		
		if (m_inst.isMachineCode(m_inst.GetOpcode())) { // unnecessary as any other statement type is already dealt with or recorded as St_Unknown
			string opcode = m_inst.GetOpcode();
			int machineInstr = m_inst.GetOpCodeValue(opcode) * 10000;
			int machineAddr = 0; // if machine address not found then it will be set 0 value
			if (!m_symtab.LookupSymbol(m_inst.GetOperand(), machineAddr)) {
				Errors::RecordError(string("Operand") + m_inst.GetOperand() + string("was not found"));
			}
			machineInstr += machineAddr;
			cout << left << setw(10) << loc << right << setfill('0') << setw(6) << machineInstr << setw(4) << setfill(' ') << "" << left << setw(10) << buff << endl;
			if (!m_emul.insertMemory(loc, machineInstr)) {
				Errors::RecordError(string("VC3600 out of memory in : ") + buff);
			}
		}
		loc = m_inst.LocationNextInstruction(loc);
	}

	system("pause");
	cout << endl;
}


/**/
/*
void Assembler::RunEmulator()

NAME

	Assembler::RunEmulator()

SYNOPSIS

	void Assembler::RunEmulator()

DESCRIPTION

	Emulates successfully translated VC600 machine code in PassII

RETURNS

	Void

AUTHOR

	Niraj Bhattarai

DATE
	12/12/2018

*/

/**/


void Assembler::RunEmulator()
{

	if (Errors::hasErrors()) {
		Errors::DisplayErrors();
		cout << "Remove existing errors to run emulator" << endl;
	}
	else {
		cout << "Results from the emulating program : " << endl;
		m_emul.runProgram();
	}

	cout << "End of emulation" << endl;
}
