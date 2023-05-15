

#ifndef ALU_H
#define ALU_H

class ALU {
    public:
        int addValues(int src1, int src2) const;
        int subtractValues(int src1, int src2) const;
        bool compareValues(int src1, int src2) const;
        int multValues(int src1, int src2) const;
        int bitWiseAnd(int src1, int src2) const;
        int bitWiseOr(int src1, int src2) const;
        int shiftLeftLogical(int src, int shift_amount) const;
        int shiftRightLogical(int src, int shift_amount) const;
};

#endif // ALU_H
