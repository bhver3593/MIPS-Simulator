

#include "stateRegister_IDEX.h"

RegisterIDEX::RegisterIDEX() {
    programCounter = 0;
    regValue1 = regValue2 = 0;
    immediate = 0;
    regDst = 0;
}

void RegisterIDEX::saveProgramCounter(int pc) { programCounter = pc; }
int RegisterIDEX::getProgramCounter() { return programCounter; }

void RegisterIDEX::saveRegValue1(int reg1) { regValue1 = reg1; }
int RegisterIDEX::getRegValue1() { return regValue1; }

void RegisterIDEX::saveRegValue2(int reg2) { regValue2 = reg2; }
int RegisterIDEX::getRegValue2() { return regValue2; }

void RegisterIDEX::saveImmediate(int imm) { immediate = imm; }
int RegisterIDEX::getImmediate() { return immediate; }

void RegisterIDEX::saveRegDst(int reg1) { regDst = reg1; }
int RegisterIDEX::getRegDst() { return regDst; }

void RegisterIDEX::saveOpcode(string op) { opcode = op; }
string RegisterIDEX::getOpcode() { return opcode; }

void RegisterIDEX::printContents() {
	 cout << "Contents of State Register ID/EX " << endl << endl;
    cout << "   PC + 4: " << programCounter << endl;
    cout << "   Opcode: " << opcode << endl;
    cout << "   Read Data 1: " << regValue1 << endl;
    cout << "   Read Data 2: " << regValue2 << endl;
    cout << "   Immediate: " << immediate << endl;
    cout << "   Register Destination Number: " << regDst << endl << endl;
}
