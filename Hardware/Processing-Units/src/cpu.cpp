#include "../include/cpu.h"

CPU::CPU(Bus* bus) {
	reg_A, reg_X, reg_Y = 0;
	reg_S = 0xFD;
	flag_C, flag_Z, flag_D, flag_V, flag_N = false;
	flag_I = true;

}

void CPU::reset() {
	reg_S -= 3;
	flag_I = true;
	bus->writeMemory(0x4015, 0);

}

void CPU::executeCommand(int opcode) {
	Address address = calculateAbsoluteAddress(opcode);

	switch (opcode && OperationCodes::Masks::COMMAND_GROUP) {
	case 0b01:
		break;
	case 0b10:
		break;
	case 0b00:
		break;
	}
}

void CPU::executeCm01(int opcode) {

}

void CPU::executeCm10(int opcode) {

}

void CPU::executeCm00(int opcode) {

}

Address CPU::calculateAbsoluteAddress(int opcode) {
	Address addr = 0;
	switch (opcode && OperationCodes::Masks::COMMAND_GROUP) {
	case 0b01:
		addr = calculateAbsAddr01(opcode);
		break;
	case 0b10:
		addr = calculateAbsAddr10(opcode);
		break;
	case 0b00:
		addr = calculateAbsAddr00(opcode);
		break;
	}
	return addr;
}


Address CPU::calculateAbsAddr01(int opcode) {
	switch (opcode && OperationCodes::Masks::ADDR_MODE) {
	case OperationCodes::AddressingModes01::INDIRECT_X:

	}
	return 0;
}

Address CPU::calculateAbsAddr10(int opcode) {
	return 0;
}

Address CPU::calculateAbsAddr00(int opcode) {
	return 0;
}