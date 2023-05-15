

#include "stateRegister_EXMEM.h"

RegisterEXMEM::RegisterEXMEM() {
    branchTargetAddress = 0;
    aluResult = 0;
    zeroBit = false;
    regValue2 = 0;
    regDest = 0;
}

void RegisterEXMEM::saveBranchTargetAddress(int addr) { branchTargetAddress = addr; }
int RegisterEXMEM::getBranchTargetAddress() { return branchTargetAddress; }

void RegisterEXMEM::saveALUResult(int result) { aluResult = result; }
int RegisterEXMEM::getALUResult() { return aluResult; }

void RegisterEXMEM::setZeroBit(bool signal) { zeroBit = signal; }
bool RegisterEXMEM::getZeroBit() { return zeroBit; }

void RegisterEXMEM::saveRegValue2(int value) { regValue2 = value; }
int RegisterEXMEM::getRegValue2() { return regValue2; }

void RegisterEXMEM::saveRegDest(int reg) { regDest = reg; }
int RegisterEXMEM::getRegDest() { return regDest; }

void RegisterEXMEM::printContents() {
	 cout << "Contents of State Register EX/MEM " << endl << endl;
    cout << "   ALU result: " << aluResult << endl;
    cout << "   Store Register Value: " << regValue2 << endl;
    cout << "   Zero Bit: " << zeroBit << endl;
    cout << "   Branch Target Address: " << branchTargetAddress << endl;
    cout << "   Register Destination Number: " << regDest << endl << endl;
}
