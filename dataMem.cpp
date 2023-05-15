

#include"dataMem.h"
#include <iostream>
#include <random>
using std::string;
using std::cout;
using std::endl;

DataMem::DataMem() : memSize(MEM_SIZE)
{
	int initial = 0;
	int value = 10;
	for (int i = 0; i < memSize; i++)
	{
		dataMem.emplace(initial, getRandNum());
		initial += 4;
		value += 10;
	}
}

void DataMem::readAddress(int address)
{
	dataAddress = address;
}

void DataMem::writeData(int regValue)
{
	dataMem.at(dataAddress) = regValue;
}

int DataMem::accessData() const
{
	return dataMem.at(dataAddress);
}

void DataMem::printContents() const
{
	cout << "Contents of Data Memory" << endl << endl;
	int address = 0;
	for(int i = 0; i < memSize; i++)
	{
		cout << "   Address " << address << ": " << dataMem.at(address) << endl;
		address += 4;  
	}
	cout << endl;
}

int DataMem::getRandNum()
{
	const int from = 0;
	const int to = 100;
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int> distr(from, to);
	return(distr(generator));
}
