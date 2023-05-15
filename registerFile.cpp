

#include "registerFile.h"
#include <iostream>
using std::string;
using std::cout;
using std::endl;

RegisterFile::RegisterFile() : address1(0), address2(0), address3(0)
{
	int value = -1;
	registerFile[ZERO] = ZERO;
	for(int i = 1; i < NUM_REGISTERS - 1; ++i)
	{
		registerFile[i] = value;
	}
	registerFile[STACK_POINTER] = 8;
}

bool RegisterFile::readAddress1(int reg)
{
	bool flag = false;
	if(reg > 0 && reg < NUM_REGISTERS)
	{
		address1 = reg;
		flag = true;
	}
	return flag;
}

bool RegisterFile::readAddress2(int reg)
{
	bool flag = false;
	if(reg > 0 && reg < NUM_REGISTERS)
	{
		address2 = reg;
		flag = true;
	}
	return flag;
}

bool RegisterFile::writeAddress(int reg)
{
	bool flag = false;
	if(reg > 0 && reg < NUM_REGISTERS)
	{
		address3 = reg;
		flag = true;
	}
	return flag;
}

void RegisterFile::writeData(int value)
{
	registerFile[address3] = value;
}

int RegisterFile::readData1() const
{
	return registerFile[address1];
}

int RegisterFile::readData2() const
{
	return registerFile[address2];
}

void RegisterFile::printContents() const
{
	cout << "Contents of Register File" << endl << endl;
	for(int i = 0; i < NUM_REGISTERS; ++i)
	{
		cout << "   Register " << i << ": " << registerFile[i] << endl;
	}
	cout << endl;
}


