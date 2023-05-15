

/*
 * RegisterIFID represents the IF/ID state register.
 * This class stores:
 *  1. instruction - current instruction (string)
 *  2. programCounter - address of the next instruction (int)
 */

#ifndef STATE_REGISTER_IF_ID_H
#define STATE_REGISTER_IF_ID_H

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class RegisterIFID {
    public:
        RegisterIFID();

        void saveInstruction(string instr);
        string getInstruction();

        void saveProgramCounter(int pc);
        int getProgramCounter();

        void printContents();
    
    private:
        string instruction;  // current instruction
        int programCounter;  // address of the next instruction
};

#endif  // STATE_REGISTER_IF_ID
