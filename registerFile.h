

#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include <iostream>
using std::string;

class RegisterFile
{
	public:
		RegisterFile();
		bool readAddress1(int);
		bool readAddress2(int);
		bool writeAddress(int);
		void writeData(int);
		int readData1() const;
		int readData2() const;
		void printContents() const;
		const static int NUM_REGISTERS = 32;
		const static int ZERO = 0;
		const static int STACK_POINTER = 31;
		
	private:
		int registerFile[NUM_REGISTERS];
		int address1;
		int address2;
		int address3;	
};

#endif
