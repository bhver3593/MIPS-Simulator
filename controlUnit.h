

#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

struct ControlUnit
{
    bool regDst = false;
    bool regWrite = false;
    bool aluSrc = false;
    bool memWrite = false;
    bool memToReg = false;
    bool memRead = false;
    bool pcSrc = false;
    bool jump = false;
};

#endif // CONTROL_UNIT_H

