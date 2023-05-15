

#include "instructionMemory.h"
#include "registerFile.h"
#include "alu.h"
#include "dataMem.h"
#include "controlUnit.h"
#include "stateRegister_IFID.h"
#include "stateRegister_IDEX.h"
#include "stateRegister_EXMEM.h"
#include "stateRegister_MEMWB.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::stringstream;

// Uncomment to turn on DEBUG mode
//#define DEBUG

// Function prototypes
void readFile(string, InstructionMemory&);
void fetchInstruction(RegisterIFID&, InstructionMemory& ,int&);
void decodeInstruction(RegisterIFID&, RegisterIDEX&, ControlUnit&, RegisterFile&);
void execute(RegisterIDEX&, RegisterEXMEM&, ControlUnit&, ALU&);
void accessMemory(RegisterEXMEM&, RegisterMEMWB&, ControlUnit&, DataMem&, int&);
void writeBack(RegisterMEMWB&, ControlUnit&, RegisterFile&);
void resetControlUnit(ControlUnit&);
int convertStringToInt(string);
int aluOperation(ALU, string, int, int);
void printControlAndStateRegs(RegisterIFID, RegisterIDEX, RegisterEXMEM, 
	RegisterMEMWB, ControlUnit);

int main(int argc, char **argv)
{
	InstructionMemory IM;
	RegisterFile regFile;
	ALU alu;
	DataMem DM;
	ControlUnit control;
	RegisterIFID stateIfId;
	RegisterIDEX stateIdEx;
	RegisterEXMEM stateExMem;
	RegisterMEMWB stateMemWb;
	
	try
	{
		if(argc != 2)
		{
			int error = 0;
			throw error;
		}
		else
		{
			// Retrieve assembly file from command line argument
			string filename = argv[1];
			
			// Read instructions from assembly file and save to instruction memory
			readFile(filename, IM);
				
			// Print contents of instruction memory
			cout << endl;
			IM.printContents();
			cout << endl;
			
			int programCounter = 0;
			while(programCounter < IM.getLastAddress() + 1)
			{	
				
				// Instruction fetch stage
				fetchInstruction(stateIfId, IM, programCounter);
				
				// Instruction decode stage
				decodeInstruction(stateIfId, stateIdEx, control, regFile);
				
				// Instruction execute stage
				execute(stateIdEx, stateExMem, control, alu);
				
				// Memory access stage
				accessMemory(stateExMem, stateMemWb, control, DM, programCounter);
	
				// Write back stage
				writeBack(stateMemWb, control, regFile);
	
				// Print contents of register file and data memory
				regFile.printContents();
				DM.printContents();
				
				
				// DEBUG mode prints emmitted control signals and contents of state registers
				#ifdef DEBUG
					printControlAndStateRegs(stateIfId, stateIdEx, stateExMem, stateMemWb, control);
					cout << endl;
				#endif
				
				// Reset control signals
				resetControlUnit(control);
			}
		}
	}
	catch(int e)
	{
		cout << "\nERROR: Assembly file not entered correctly" << endl << endl;
	}
	
	return EXIT_SUCCESS;
}

void readFile(string assemblyFileName, InstructionMemory& IM) {

	const int CARRIAGE_RETURN_ASCII = 13;
	ifstream assemblyFile;
	string line = "";
	string instruction = "";
	
	assemblyFile.open(assemblyFileName.c_str());
	if(!assemblyFile)
	{
		int error = 0;
		throw error;
	}
	else
	{
		// Read instructions from assembly file and add to instruction memory
		int count = 0;
		while(assemblyFile)
		{
			getline(assemblyFile, line);
			instruction = line.substr(0, line.find("#"));
			if(instruction != "" && instruction[0] != CARRIAGE_RETURN_ASCII)
			{
				IM.addInstruction(count, instruction);
				count += 4;
			}
		}
		assemblyFile.close();
	}

}

void fetchInstruction(RegisterIFID& stateIfId, InstructionMemory& IM, int& programCounter) {
	
	// Fetch instruction from instruction memory
	string newInst = IM.getInstruction(programCounter);
	cout << "Instruction " << programCounter << ": " << newInst << endl << endl;

	// Increment program counter
	programCounter += 4;

	// Store PC and instruction in state register IF/ID
	stateIfId.saveProgramCounter(programCounter);
	stateIfId.saveInstruction(newInst);
	
}

void decodeInstruction(RegisterIFID& stateIfId, RegisterIDEX& stateIdEx, 
	ControlUnit& control, RegisterFile& regFile) {

	string strAddress1, strAddress2, strAddress3;
	string strOffset;
	int address1, address2, address3;
	int offset;

	// Retrieve PC and instruction from state register IF/ID
	string newInst = stateIfId.getInstruction();
	int programCounter = stateIfId.getProgramCounter();
	
	// Instruction decoding
	string opcode = newInst.substr(0, newInst.find(" "));
	
	int firstR = newInst.find("r");
	int firstComma = newInst.find(",");
	int secondR = newInst.find("r", firstR+1);
	int secondComma = newInst.find(",", firstComma + 1);
	int leftBracket = newInst.find("(");
	
	if(opcode == "ADD" || opcode == "SUB" || opcode == "MUL" ||
		opcode == "AND" || opcode == "OR")
	{
		strAddress3 = newInst.substr(firstR + 1, firstComma - firstR - 1);
		strAddress1 = newInst.substr(secondR + 1, secondComma - secondR - 1);
		strAddress2 = newInst.substr(secondComma + 4);
		
		// Convert strings to integers
		address1 = convertStringToInt(strAddress1);
		address2 = convertStringToInt(strAddress2);
		address3 = convertStringToInt(strAddress3);
		
		// Control signals
		control.regDst = true;
		control.regWrite = true;
		control.memToReg = true;
		
	}
	else if(opcode == "ADDI" || opcode == "SLL" || opcode == "SRL")
	{
		strAddress2 = newInst.substr(firstR + 1, firstComma - firstR - 1);
		strAddress1 = newInst.substr(secondR + 1, secondComma - secondR - 1);
		strOffset = newInst.substr(secondComma + 2);
		
		// Convert strings to integers
		address2 = convertStringToInt(strAddress2);
		address1 = convertStringToInt(strAddress1);
		offset = convertStringToInt(strOffset);
		
		// Control signals
		control.aluSrc = true;
		control.regWrite = true;
		control.memToReg = true;
		
	}
	else if(opcode == "LW" || opcode == "SW")
	{
		strAddress2 = newInst.substr(firstR + 1, firstComma - firstR - 1);
		strOffset = newInst.substr(firstComma + 2, leftBracket - firstComma + 1);
		strAddress1 = newInst.substr(leftBracket + 2, 2);
		
		// Convert strings to integers
		address2 = convertStringToInt(strAddress2);
		offset = convertStringToInt(strOffset);
		address1 = regFile.STACK_POINTER;
		
		// Control signals
		control.aluSrc = true;
		if(opcode == "LW")
		{
			control.regWrite = true;
			control.memRead = true;
		}
		else if(opcode == "SW")
		{
			control.memWrite = true;
		}

	}
	else if(opcode == "BEQ")
	{
		strAddress1 = newInst.substr(firstR + 1, firstComma - firstR - 1);
		strAddress2 = newInst.substr(secondR + 1, secondComma - secondR - 1);
		strOffset = newInst.substr(secondComma + 2);
		
		// Convert strings to integers
		address1 = convertStringToInt(strAddress1);
		address2 = convertStringToInt(strAddress2);
		offset = convertStringToInt(strOffset);
		
		// Control signals
		control.pcSrc = true;
		
	}
	else if(opcode == "J")
	{
		strOffset = newInst.substr(2);
		
		// Convert string to integer
		offset = convertStringToInt(strOffset);
		
		// Control signals
		control.jump = true;
		
	}

	// Addresses read into register file
	regFile.readAddress1(address1);
	regFile.readAddress2(address2);
	
	// Data read from register file
	int data1 = regFile.readData1();
	int data2 = regFile.readData2();
	
	// Store PC, data1, data2, offset, opcode, write address in state register ID/EX
	stateIdEx.saveProgramCounter(programCounter);
	stateIdEx.saveRegValue1(data1);
	stateIdEx.saveRegValue2(data2);
	stateIdEx.saveImmediate(offset);
	stateIdEx.saveOpcode(opcode);
	if(control.regDst) { stateIdEx.saveRegDst(address3); }
	else { stateIdEx.saveRegDst(address2); }
	
}

void execute(RegisterIDEX& stateIdEx, RegisterEXMEM& stateExMem, 
	ControlUnit& control, ALU& alu) {
		
	bool zeroBit;
	int aluResult;
	
	// Retrieve data from state register ID/EX
	int programCounter = stateIdEx.getProgramCounter();
	int data1 = stateIdEx.getRegValue1();
	int data2 = stateIdEx.getRegValue2();
	int offset = stateIdEx.getImmediate();
	int registerDst = stateIdEx.getRegDst();
	string opcode = stateIdEx.getOpcode();
	
	// Branch instruction
	if(!control.aluSrc && control.pcSrc)
	{
		zeroBit = alu.compareValues(data1, data2);
	}
	// Load or store instruction
	else if(control.aluSrc && !control.pcSrc)
	{
		aluResult = aluOperation(alu, opcode, data1, offset);
	}
	// ALU instruction
	else if(!control.aluSrc && !control.pcSrc)
	{
		aluResult = aluOperation(alu, opcode, data1, data2);
	}
	// Compute branch target address in parallel
	int shiftedOffset = alu.shiftLeftLogical(offset, 2);
	int branchAddress = alu.addValues(programCounter, shiftedOffset) - 4;
	
	// Store ALU result, register value (for SW instruction), register destination, 
	// branch target address, and zero bit in state reg EX/MEM
	stateExMem.saveALUResult(aluResult);
	stateExMem.saveRegValue2(data2);
	stateExMem.saveRegDest(registerDst);
	stateExMem.saveBranchTargetAddress(branchAddress);
	stateExMem.setZeroBit(zeroBit);
	
}

void accessMemory(RegisterEXMEM& stateExMem, RegisterMEMWB& stateMemWb, 
	ControlUnit& control, DataMem& dataMem, int& programCounter) {
		
	int memData;

	// Retrieve data from state register EX/MEM
	int aluResult = stateExMem.getALUResult();
	int data2 = stateExMem.getRegValue2();
	int registerDst = stateExMem.getRegDest();
	int branchAddress = stateExMem.getBranchTargetAddress();
	bool zeroBit = stateExMem.getZeroBit();
	
	dataMem.readAddress(aluResult);
	// Load instruction
	if(control.memRead)
	{
		memData = dataMem.accessData();
	}
	// Store instruction
	else if(control.memWrite)
	{
		dataMem.writeData(data2);
	}
	
	// Branch or jump instruction, update program counter
	if(control.pcSrc && zeroBit || control.jump)
	{
		programCounter = branchAddress;	
	}
	
	// Store ALUresult, memData (for LW instruction), write address in state reg MEM/WB
	stateMemWb.saveALUResult(aluResult);
	stateMemWb.saveReadData(memData);
	stateMemWb.saveRegDst(registerDst);
	
}

void writeBack(RegisterMEMWB& stateMemWb, ControlUnit& control, RegisterFile& regFile) {

	// Retrieve data from state register MEM/WB
	int aluResult = stateMemWb.getALUResult();
	int memData = stateMemWb.getReadData();
	int registerDst = stateMemWb.getRegDst();
	
	// ALU instruction
	if(control.memToReg && control.regWrite)
	{
		regFile.writeAddress(registerDst);
		regFile.writeData(aluResult);
	}

	// Load instruction
	else if(!control.memToReg && control.regWrite)
	{
		regFile.writeAddress(registerDst);
		regFile.writeData(memData);
	}
	
}

int convertStringToInt(string str)
{
	stringstream ss;
	int number;
	ss << str;
	ss >> number;
	return number;
}

int aluOperation(ALU alu, string opcode, int value1, int value2)
{
	int result = 0;
	if(opcode == "ADD" || opcode == "ADDI" || opcode == "LW" || opcode == "SW") {
		result = alu.addValues(value1, value2);	
	}
	else if(opcode == "SUB") {
		result = alu.subtractValues(value1, value2);
	}
	else if(opcode == "MUL") {
		result = alu.multValues(value1, value2);
	}
	else if(opcode == "AND") {
		result = alu.bitWiseAnd(value1, value2);
	}
	else if(opcode == "OR") {
		result = alu.bitWiseOr(value1, value2);
	}
	else if(opcode == "SLL") {
		result = alu.shiftLeftLogical(value1, value2);
	}
	else if(opcode == "SRL") {
		result = alu.shiftRightLogical(value1, value2);
	}
	return result;
}

void resetControlUnit(ControlUnit& control) {
	
	control.regDst = false;
	control.regWrite = false;
	control.aluSrc = false;
	control.memWrite = false;
	control.memToReg = false;
	control.memRead = false;
	control.pcSrc = false;
	control.jump = false;
	
}

// Debugging function prints emmitted control signals and contents of state registers
void printControlAndStateRegs(RegisterIFID ifid, RegisterIDEX idex, RegisterEXMEM exmem, 
	RegisterMEMWB memwb, ControlUnit control)
{
	cout << "Emmitted Control Signals: " << endl << endl;
	cout << "   RegDst: " << control.regDst << endl;
	cout << "   RegWrite: " << control.regWrite << endl;
	cout << "   ALUSrc: " << control.aluSrc << endl;
	cout << "   MemWrite: " << control.memWrite << endl;
	cout << "   MemtoReg: " << control.memToReg << endl;
	cout << "   MemRead: " << control.memRead << endl << endl;
	cout << "   PCSrc: " << control.pcSrc << endl << endl;
	
	ifid.printContents();
	idex.printContents();
	exmem.printContents();
	memwb.printContents();
	
}
























