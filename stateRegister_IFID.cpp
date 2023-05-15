

#include "stateRegister_IFID.h"

RegisterIFID::RegisterIFID() {
    instruction = "";
    programCounter = 0;
}

void RegisterIFID::saveInstruction(string instr) { instruction = instr; }

string RegisterIFID::getInstruction() { return instruction; }

void RegisterIFID::saveProgramCounter(int pc) { programCounter = pc; }

int RegisterIFID::getProgramCounter() { return programCounter; }

void RegisterIFID::printContents() {
	 cout << "Contents of State Register IF/ID " << endl << endl;
    cout << "   Current instruction: " << instruction << endl;
    cout << "   PC + 4: " << programCounter << endl << endl;
}
