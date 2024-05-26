#ifndef CPU_OP_H
#define CPU_OP_H
using Address = short int;
using Byte = unsigned char;

/*
Machine code bit pattern - aaabbbcc
Where: aaa - operation code,
bbb - Addressing mode,
cc - Command group
*/

/*
Machine code bit pattern - xxy10000
Where: xx - flag,
y - compared with
*/


namespace OperationCodes {

    enum Masks {
        OP_CODE = 0b11100000,
        ADDR_MODE = 0b00011100,
        COMMAND_GROUP = 0b00000011
    };
    
    enum System_Vectors {
        NMI = 0xFFFA,
        RES = 0xFFFC,
        IRQ = 0xFFFE
    };

    enum class AddressingModes01 : Byte {
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
        BIT,
        JMP,
        JMP_ABS,
        STY,
        LDY,
        CPY,
        CPX
    };

    enum class Flags {
        NEGATIVE,
        OVERFLOW,
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
        PHP = 0x08,
        PLP = 0x28,
        PHA = 0x48,
        PLA = 0x68,
        DEY = 0x88,
        TAY = 0xA8,
        INY = 0xC8,
        INX = 0xE8,
        CLC = 0x18,
        SEC = 0x38,
        CLI = 0x58,
        SEI = 0x78,
        TYA = 0x98,
        CLV = 0xB8,
        CLD = 0xD8,
        SED = 0xF8,
        TXA = 0x8A,
        TXS = 0x9A,
        TAX = 0xAA,
        TSX = 0xBA,
        DEX = 0xCA,
        NOP = 0xEA
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
    ABSOLUTE_X
};


#endif