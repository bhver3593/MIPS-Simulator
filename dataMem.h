
#pragma once
#ifndef DATA_MEM_H
#define DATA_MEM_H

#include <iostream>
#include <map>
#include <unordered_map>
using std::string;
using std::unordered_map;

class DataMem
{
public:
	DataMem();
	void readAddress(int address);
	void writeData(int data);
	int accessData() const;
	void printContents() const;
	const static int MEM_SIZE = 32;

private:
	std::unordered_map<int, int> dataMem;
	int dataAddress;
	int memSize;
	
	// private member function
	int getRandNum();

};
	
#endif // DATA_MEM_H
