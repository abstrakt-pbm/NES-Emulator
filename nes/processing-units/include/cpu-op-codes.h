#ifndef CPU_OP_H
#define CPU_OP_H
using Address = short int;
using Byte = unsigned char;

/*
Machine opperation bit pattern - aaabbbcc
Where: aaa - operation code,
bbb - Addressing mode,
cc - Command group
*/

/*
Branch instruction bit pattern - xxy10000
Where: xx - flag,
y - compared with
*/


namespace OperationCodes {

    enum Masks {
        OP_CODE = 0b11100000,
        ADDR_MODE = 0b00011100,
        COMMAND_GROUP = 0b00000011,
        BRANCH_INSTRUCTION = 0b00011111,
        BRANCH_FLAG = 0b11000000,
        BRANCH_COMPARE = 0b00100000
    };
    
    enum System_Vectors {
        NMI = 0xFFFA,
        RES = 0xFFFC,
        IRQ = 0xFFFE
    };

    enum class AddressingModes01{
        INDIRECT_X,
        ZERO_PAGE,
        IMMEDIATE,
        ABSOLUTE,
        INDIRECT_Y,
        ZERO_PAGE_X,
        ABSOLUTE_Y,
        ABSOLUTE_X
    };

    enum class OperationsGroup01 {
        ORA,
        AND,
        EOR,
        ADC,
        STA,
        LDA,
        CMP,
        SBC
    };

    enum class AddressingModes10 {
        IMMEDIATE,
        ZERO_PAGE,
        ACCUMULATOR,
        ABSOLUTE,
        ZERO_PAGE_X = 0b101,
        ABSOLUTE_X = 0b111
    };

    enum class OperationsGroup10 {
        ASL,
        ROL,
        LSR,
        ROR,
        STX,
        LDX,
        DEC,
        INC
    };

    enum class AddressingModes00 {
        IMMEDIATE,
        ZERO_PAGE,
        ABSOLUTE = 0b011,
        ZERO_PAGE_X = 0b101,
        ABSOLUTE_X = 0b111
    };

    enum class OperationsGroup00 {
        BIT = 1,
        JMP,
        JMP_ABS,
        STY,
        LDY,
        CPY,
        CPX
    };

    enum class BrenchFlags {
        NEGATIVE,
        OVERFLOW_,
        CARRY,
        ZERO
    };

    enum class BranchInstructions {
        BPL,
        BMI,
        BVC,
        BVS,
        BCC,
        BCS,
        BNE,
        BEQ
    };

    enum class ImpiedOperations {
        NOP = 0xea,
        BRK = 0x00,
        JSR = 0x20,
        RTI = 0x40,
        RTS = 0x60,
        PHP = 0x08,
        PLP = 0x28,
        PHA = 0x48,
        PLA = 0x68,
        DEY = 0x88,
        DEX = 0xca,
        TAY = 0xa8,
        INY = 0xc8,
        INX = 0xe8,
        CLC = 0x18,
        SEC = 0x38,
        CLI = 0x58,
        SEI = 0x78,
        TYA = 0x98,
        CLV = 0xb8,
        CLD = 0xd8,
        SED = 0xf8,
        TXA = 0x8a,
        TXS = 0x9a,
        TAX = 0xaa,
        TSX = 0xba,
    };

    enum class InterruptTypes {
        IRQ,
        NMI,
        BRK
    };
};

enum class AddressingModes {
    INDIRECT_X,
    ZERO_PAGE,
    IMMEDIATE,
    ABSOLUTE,
    INDIRECT_Y,
    ZERO_PAGE_X,
    ABSOLUTE_Y,
    ABSOLUTE_X,
    ACCUMULATOR
};

static const int CYCLES[0x100] = {
            7, 6, 0, 0, 0, 3, 5, 0, 3, 2, 2, 0, 0, 4, 6, 0,
            2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
            6, 6, 0, 0, 3, 3, 5, 0, 4, 2, 2, 0, 4, 4, 6, 0,
            2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
            6, 6, 0, 0, 0, 3, 5, 0, 3, 2, 2, 0, 3, 4, 6, 0,
            2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
            6, 6, 0, 0, 0, 3, 5, 0, 4, 2, 2, 0, 5, 4, 6, 0,
            2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
            0, 6, 0, 0, 3, 3, 3, 0, 2, 0, 2, 0, 4, 4, 4, 0,
            2, 6, 0, 0, 4, 4, 4, 0, 2, 5, 2, 0, 0, 5, 0, 0,
            2, 6, 2, 0, 3, 3, 3, 0, 2, 2, 2, 0, 4, 4, 4, 0,
            2, 5, 0, 0, 4, 4, 4, 0, 2, 4, 2, 0, 4, 4, 4, 0,
            2, 6, 0, 0, 3, 3, 5, 0, 2, 2, 2, 0, 4, 4, 6, 0,
            2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
            2, 6, 0, 0, 3, 3, 5, 0, 2, 2, 2, 2, 4, 4, 6, 0,
            2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
};

#endif