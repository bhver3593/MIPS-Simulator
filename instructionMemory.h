

#ifndef INSTRUCTION_MEMORY_H
#define INSTRUCTION_MEMORY_H

#include <iostream>
#include <unordered_map>
using std::string;
using std::unordered_map;

class InstructionMemory
{
	public:
		InstructionMemory();
		bool addInstruction(int, string);
		string getInstruction(int) const;
		int getLastAddress() const;
		void printContents() const;
		
	private:
		unordered_map<int, string> memory;
		int lastAddress;
	
};

#endif
