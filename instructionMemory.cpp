

#include "instructionMemory.h"
#include <iostream>
using std::string;
using std::cout;
using std::endl;


InstructionMemory::InstructionMemory() : lastAddress(0) {}

bool InstructionMemory::addInstruction(int address, string instruction)
{
	bool flag = false;
	if(address % 4 == 0 && instruction != "")
	{
		lastAddress = address; 
		memory[address] = instruction;
		flag = true;
	}
	return flag;
}

string InstructionMemory::getInstruction(int address) const
{
	string instruction = "";
	if(address % 4 == 0)
	{
		instruction = memory.at(address);
	}
	return instruction;
}

int InstructionMemory::getLastAddress() const
{
	return lastAddress;
}

void InstructionMemory::printContents() const
{
	cout << "Contents of Instruction Memory" << endl << endl;
	for(int i = 0; i < lastAddress + 1; i += 4)
	{
		cout << "   Address " << i << ": " << memory.at(i) << endl;  
	}
	cout << endl;
}






























