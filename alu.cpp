
#include "alu.h"

int ALU::addValues(int src1, int src2) const {
    return (src1 + src2);
}

int ALU::subtractValues(int src1, int src2) const {
    return (src1 - src2);
}

bool ALU::compareValues(int src1, int src2) const {
    return (src1 == src2);
}

int ALU::multValues(int src1, int src2) const {
    return (src1 * src2);
}

int ALU::bitWiseAnd(int src1, int src2) const {
    return (src1 & src2);
}

int ALU::bitWiseOr(int src1, int src2) const {
    return (src1 | src2);
}

int ALU::shiftLeftLogical(int src, int shift_amount) const {
    return (src << shift_amount);
}

int ALU::shiftRightLogical(int src, int shift_amount) const {
    return (src >> shift_amount);
}
