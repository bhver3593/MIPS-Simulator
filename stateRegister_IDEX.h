
/*
 * RegisterIDEX represents the ID/EX state register.
 * This class stores:
 *  1. programCounter - address of the next instruction (int)
 *  2. regValue1 - value from read data 1 (int)
 *  3. regValue2 - value from read data 2 (int)
 *  4. immediate - offset address or a constant (int)
 *  5. regDst1 - register destination needed for write back (string)
 *  6. regDst2 - register destination needed for write back (string)
 *  7. controlIDEX - 7 control bits that are stored in ID/EX
 */

#ifndef STATE_REGISTER_ID_EX
#define STATE_REGISTER_ID_EX

#include <iostream>
#include <string>

#include "controlUnit.h"

using std::cout;
using std::endl;
using std::string;

class RegisterIDEX {
    public:
        RegisterIDEX();
        
        void saveProgramCounter(int pc);
        int getProgramCounter();

        void saveRegValue1(int reg1);
        int getRegValue1();

        void saveRegValue2(int reg2);
        int getRegValue2();

        void saveImmediate(int imm);
        int getImmediate();

        void saveRegDst(int reg);
        int getRegDst();
        
		  void saveOpcode(string op);
        string getOpcode();

        void printContents();

    private:
        int programCounter; 
        int regValue1;
        int regValue2; 
        int immediate; 
        int regDst;
        string opcode;
};

#endif  // STATE_REGISTER_ID_EX_H
