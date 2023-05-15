

#ifndef STATE_REGISTER_EX_MEM
#define STATE_REGISTER_EX_MEM

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class RegisterEXMEM {
    public:

        RegisterEXMEM();

        void saveBranchTargetAddress(int address);
        int getBranchTargetAddress();
        
        void saveALUResult(int result);
        int getALUResult();
        
        void setZeroBit(bool zeroBit);
        bool getZeroBit();

        void saveRegValue2(int value);
        int getRegValue2();

        void saveRegDest(int reg);
        int getRegDest();
		  
		  void printContents();
			
    private:
        int branchTargetAddress;
        int aluResult;
        bool zeroBit;
        int regValue2;
        int regDest;
};

#endif  // STATE_REGISTER_EX_MEM
