

#include "stateRegister_MEMWB.h"

RegisterMEMWB::RegisterMEMWB() {
    readData = 0;
    aluResult = 0;
    regDst = 0;
}

void RegisterMEMWB::saveReadData(int data) { readData = data; }
int RegisterMEMWB::getReadData() { return readData; }

void RegisterMEMWB::saveALUResult(int result) { aluResult = result; }
int RegisterMEMWB::getALUResult() { return aluResult; }

void RegisterMEMWB::saveRegDst(int reg) { regDst = reg; }
int RegisterMEMWB::getRegDst() { return regDst; }

void RegisterMEMWB::printContents()
{
	cout << "Contents of State Register MEM/WB " << endl << endl;
	cout << "   Read Memory Data: " << readData << endl;
	cout << "   ALU Result: " << aluResult << endl;
	cout << "   Register Destination Number: " << regDst << endl << endl;
}
