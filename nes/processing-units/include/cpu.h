#ifndef CPU_H
#define CPU_H

#include "cpu-op-codes.h"
#include "bus.h"


class CPU {
private:
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

	void interrupt(OperationCodes::InterruptTypes interruptType);
	void executeInterrupt(OperationCodes::InterruptTypes interruptType);

	void pushStack(Byte value);
	Byte pullStack();

	void setupZFlag(Byte value);
	
	void executeImplied(int opcode);
	void executeBranch(int opcode);
	void executeGroupCommand(int opcode);
	void executeCm01(int opcode);
	void executeCm10(int opcode);
	void executeCm00(int opcode);

	Address calculateAbsoluteAddress(int opcode);
	Address calculateAbsAddr01(int opcode);
	Address calculateAbsAddr10(int opcode);
	Address calculateAbsAddr00(int opcode);
	Address calculateAddr(AddressingModes addrMode);
	Address readAddr(Address addr);

public:
	CPU(Bus* bus);
	void reset();
};

#endif