#pragma once
#ifndef CPU_H
#define CPU_H

#include "cpu-op-codes.h"
#include "bus.h"


class CPU {
protected:
	Bus* bus;

	Byte reg_A;
	Byte reg_X;
	Byte reg_Y;
	Address reg_PC;
	Byte reg_S;

	bool flag_C;
	bool flag_Z;
	bool flag_I;
	bool flag_D;
	bool flag_B;
	bool flag_V;
	bool flag_N;

	bool waitingNMI;
	bool waitingIRQ;

	void setInterrupt(OperationCodes::InterruptTypes interruptType);
	void executeInterrupt(OperationCodes::InterruptTypes interruptType);

	void pushStack(Byte value);
	Byte pullStack();

	void setupZFlag(Byte value);
	
	void executeImplied(Byte opcode);
	void executeBranch(Byte opcode);
	void executeGroupCommand(Byte opcode);
	void executeCm01(Byte opcode);
	void executeCm10(Byte opcode);
	void executeCm00(Byte opcode);

	Address calculateAbsoluteAddress(Byte opcode);
	Address calculateAbsAddr01(Byte opcode);
	Address calculateAbsAddr10(Byte opcode);
	Address calculateAbsAddr00(Byte opcode);
	Address calculateAddr(AddressingModes addrMode);
	Address readAddr(Address addr);

public:
	CPU(Bus* bus);
	void executeCommand(Byte opcode);
	void step();
	void reset(Address address);
	void reset();
};

#endif