

#ifndef STATE_REGISTER_MEM_WB
#define STATE_REGISTER_MEM_WB

#include <iostream>

using std::cout;
using std::endl;

class RegisterMEMWB {
    public:
        RegisterMEMWB();

        void saveReadData(int data);
        int getReadData();

        void saveALUResult(int result);
        int getALUResult();

        void saveRegDst(int reg);
        int getRegDst();
        
        void printContents();
        
    private:
        int readData;
        int aluResult;
        int regDst;
};

#endif // STATE_REGISTER_MEM_WB
