#include "../include/cpu.h"
#include <iostream>

bool isInArray(const Byte* arr, Byte value) {
	bool result = false;
	int arraySize = sizeof(arr) / sizeof(Byte);
	for (int i = 0; i < arraySize; i++) {
		if (arr[i] == value) {
			result = true;
		}
	}
	return result;
}


CPU::CPU(Bus* bus) {
	this->bus = bus;
	reg_A = reg_X = reg_Y = 0;
	reg_PC = 0xFFFC;
	reg_S = 0xFD;
	flag_C = flag_Z = flag_D = flag_V = flag_N = false;
	flag_I = true;
	waitingIRQ = waitingNMI = false;
}

void CPU::reset(Address address) {
	reg_S -= 3;
	flag_I = true;
	reg_PC = 0xFFFC;
	bus->writeMemory(0x4015, 0);
}

void CPU::step() {
	if (waitingNMI) {
		executeInterrupt(OperationCodes::InterruptTypes::NMI);
		waitingNMI = waitingIRQ = false;
	}
	else if (waitingIRQ) {
		executeInterrupt(OperationCodes::InterruptTypes::IRQ);
		waitingNMI = waitingIRQ = false;
	}
	Byte opcommand = bus->readMemory(reg_PC++);
	executeCommand(opcommand);
}

void CPU::executeCommand(Byte opcode) {
	if (isInArray(impliedOps, opcode)) {
		executeImplied(opcode);
	} else if (isInArray(branchOps, opcode)) {
		executeBranch(opcode);
	}
	else {
		executeGroupCommand(opcode);
	}

}

void CPU::executeGroupCommand(Byte opcode) {
	switch (opcode & OperationCodes::Masks::COMMAND_GROUP) {
	case 0b01:
		executeCm01(opcode);
		break;
	case 0b10:
		executeCm10(opcode);
		break;
	case 0b00:
		executeCm00(opcode);
		break;
	}
}

void CPU::executeImplied(Byte opcode)
{
	switch (static_cast<OperationCodes::ImpiedOperations>(opcode)) {
	case OperationCodes::ImpiedOperations::PHP: {
		Byte flags = flag_N << 7 | flag_V << 6 | 1 << 5 | 1 << 4 | flag_D << 3 | flag_I << 2 | flag_Z << 1 | flag_C;
		pushStack(flags);
		break;
	}
	case OperationCodes::ImpiedOperations::PLP: {
		Byte flags = pullStack();
		flag_N = flags & 0x80;
		flag_V = flags & 0x40;
		flag_D = flags & 0x8;
		flag_I = flags & 0x4;
		flag_Z = flags & 0x2;
		flag_C = flags & 0x1;
		break;
	}
	case OperationCodes::ImpiedOperations::BRK: {
		executeInterrupt(OperationCodes::InterruptTypes::BRK);
		break;
	}
	case OperationCodes::ImpiedOperations::PHA: {
		pushStack(reg_A);
		break;
	}
	case OperationCodes::ImpiedOperations::JSR: {
		pushStack((reg_PC + 1) >> 8);
		pushStack(reg_PC + 1);
		reg_PC = readAddr(reg_PC);
		break;
	}
	case OperationCodes::ImpiedOperations::RTI: {
		Byte flags = pullStack();
		flag_N = flags & 0x80;
		flag_V = flags & 0x40;
		flag_D = flags & 0x8;
		flag_I = flags & 0x4;
		flag_Z = flags & 0x2;
		flag_C = flags & 0x1;
		reg_PC = pullStack();
		reg_PC |= pullStack() << 8;
		break;
	}
	case OperationCodes::ImpiedOperations::RTS: {
		reg_PC = pullStack();
		reg_PC |= pullStack() << 8;
		++reg_PC;
		break;
	}
	case OperationCodes::ImpiedOperations::PLA: {
		reg_A = pullStack();
		setupZFlag(reg_A);
		break;
	}
	case OperationCodes::ImpiedOperations::DEY: {
		--reg_Y;
		setupZFlag(reg_Y);
		break;
	}
	case OperationCodes::ImpiedOperations::TAY: {
		reg_Y = reg_A;
		setupZFlag(reg_Y);
		break;
	}
	case OperationCodes::ImpiedOperations::INY: {
		++reg_Y;
		setupZFlag(reg_Y);
		break;
	}
	case OperationCodes::ImpiedOperations::INX: {
		++reg_X;
		setupZFlag(reg_X);
		break;
	}
	case OperationCodes::ImpiedOperations::CLC: {
		flag_C = false;
		break;
	}
	case OperationCodes::ImpiedOperations::SEC: {
		flag_C = true;
		break;
	}
	case OperationCodes::ImpiedOperations::CLI: {
		flag_I = false;
		break;
	}
	case OperationCodes::ImpiedOperations::SEI: {
		flag_I = true;
		break;
	}
	case OperationCodes::ImpiedOperations::TYA: {
		reg_A = reg_Y;
		setupZFlag(reg_A);
		break;
	}
	case OperationCodes::ImpiedOperations::CLV: {
		flag_V = false;
		break;
	}
	case OperationCodes::ImpiedOperations::CLD: {
		flag_D = false;
		break;
	}
	case OperationCodes::ImpiedOperations::SED: {
		flag_D = true;
		break;
	}
	case OperationCodes::ImpiedOperations::TXA: {
		reg_A = reg_X;
		setupZFlag(reg_A);
		break;
	}
	case OperationCodes::ImpiedOperations::TXS: {
		reg_S = reg_X;
		setupZFlag(reg_S);
		break;
	}
	case OperationCodes::ImpiedOperations::TAX: {
		reg_X = reg_A;
		setupZFlag(reg_X);
		break;
	}
	case OperationCodes::ImpiedOperations::TSX: {
		reg_X = reg_S;
		setupZFlag(reg_X);
		break;
	}
	case OperationCodes::ImpiedOperations::DEX: {
		--reg_X;
		setupZFlag(reg_X);
		break;
	}
	case OperationCodes::ImpiedOperations::NOP: {
		break;
	}
	}
}

void CPU::executeBranch(Byte opcode) {
	bool branchState = opcode & OperationCodes::BRANCH_COMPARE;

	switch (static_cast<OperationCodes::BrenchFlags>(opcode & OperationCodes::Masks::BRANCH_FLAG >> 6)) {
	case OperationCodes::BrenchFlags::NEGATIVE: {
		branchState = !(branchState ^ flag_N);
		break;
	}
	case OperationCodes::BrenchFlags::OVERFLOW_: {
		branchState = !(branchState ^ flag_V);
		break;
	}
	case OperationCodes::BrenchFlags::CARRY: {
		branchState = !(branchState ^ flag_C);
		break;
	}
	case OperationCodes::BrenchFlags::ZERO: {
		branchState = !(branchState ^ flag_Z);
		break;
	}
	}

	if (branchState) {
		Byte offset = bus->readMemory(reg_PC++);
		int nextPC = reg_PC + offset;
		reg_PC = nextPC;
	}
	else {
		++reg_PC;
	}

}

void CPU::executeCm01(Byte opcode) {
	Address address = calculateAbsoluteAddress(opcode);
	switch (static_cast<OperationCodes::OperationsGroup01>(opcode & OperationCodes::Masks::OP_CODE >> 5)) {
	case OperationCodes::OperationsGroup01::ORA: {
		reg_A |= bus->readMemory(address);
		setupZFlag(reg_A);
		break;
	}
	case OperationCodes::OperationsGroup01::AND:{
		reg_A &= bus->readMemory(address);
		setupZFlag(reg_A);
		break;
	}
	case OperationCodes::OperationsGroup01::EOR: { 
		reg_A ^= bus->readMemory(address);
		setupZFlag(reg_A);
		break; 
	}
	case OperationCodes::OperationsGroup01::ADC: {
		Byte operand = bus->readMemory(address);
		int summ = reg_A + flag_C + operand;
		flag_C = summ & 0x100;
		flag_V = (reg_A ^ summ) & (operand ^ summ);
		reg_A = static_cast<Byte>(summ);
		setupZFlag(reg_A);
		break;
	}
	case OperationCodes::OperationsGroup01::STA: { 
		bus->writeMemory(address, reg_A);
		break;
	}
	case OperationCodes::OperationsGroup01::LDA: { 
		reg_A = bus->readMemory(address);
		setupZFlag(reg_A);
		break;
	}
	case OperationCodes::OperationsGroup01::CMP: {
		Byte difference = reg_A - bus->readMemory(address);
		flag_C = !(difference & 0x100);
		break;
	}
	case OperationCodes::OperationsGroup01::SBC: {
		int operand = bus->readMemory(address);
		int difference = reg_A - operand - !flag_C;
		flag_C = !(difference & 0x100);
		flag_V = (reg_A ^ difference) & (~operand ^ difference) & 0x80;
		reg_A = difference;
		setupZFlag(difference);
		break;
	}
	}
}

void CPU::executeCm10(Byte opcode) {
	Address address = calculateAbsoluteAddress(opcode);
	OperationCodes::AddressingModes10 addresationMode = static_cast<OperationCodes::AddressingModes10>((opcode & OperationCodes::Masks::ADDR_MODE) >> 2);
	switch (static_cast<OperationCodes::OperationsGroup10>(opcode & OperationCodes::Masks::OP_CODE >> 5)) {
	case OperationCodes::OperationsGroup10::ASL: {
		break;
	}
	case OperationCodes::OperationsGroup10::ROL: { 
		bool previous_C_flag = flag_C;
		if (addresationMode == OperationCodes::AddressingModes10::ACCUMULATOR) {
			flag_C = reg_A & 0x80;
			reg_A <<= 1;
			reg_A = reg_A | (previous_C_flag);
			setupZFlag(reg_A);
		}
		else {
			Byte operand = bus->readMemory(address);
			flag_C = operand & 0x80;
			operand = operand << 1 | (previous_C_flag);
			setupZFlag(operand);
			bus->writeMemory(address, operand);
		}
		break; 
	}
	case OperationCodes::OperationsGroup10::LSR: {
		break;
	}
	case OperationCodes::OperationsGroup10::ROR: {
		bool previous_C_flag = flag_C;
		if (addresationMode == OperationCodes::AddressingModes10::ACCUMULATOR) {
			flag_C = reg_A & 1;
			reg_A >>= 1;
			reg_A = reg_A | (previous_C_flag) << 7;
			setupZFlag(reg_A);
		}
		else {
			Byte operand = bus->readMemory(address);
			flag_C = operand & 1;
			operand = operand >> 1 | (previous_C_flag) << 7;
			setupZFlag(operand);
			bus->writeMemory(address, operand);
		}
		break;
	}
	case OperationCodes::OperationsGroup10::STX: {
		bus->writeMemory(address, reg_X);
		break;
	}
	case OperationCodes::OperationsGroup10::LDX: {
		reg_X = bus->readMemory(address);
		setupZFlag(reg_X);
		break;
	}
	case OperationCodes::OperationsGroup10::DEC: {
		Byte decrementedValue = bus->readMemory(address) - 1;
		setupZFlag(decrementedValue);
		bus->writeMemory(address, decrementedValue);
		break;
	}
	case OperationCodes::OperationsGroup10::INC: {
		Byte incrementedValue = bus->readMemory(address) + 1;
		setupZFlag(incrementedValue);
		bus->writeMemory(address, incrementedValue);
		break;
	}
	}
}

void CPU::executeCm00(Byte opcode) {
	Address address = calculateAbsoluteAddress(opcode);
	switch (static_cast<OperationCodes::OperationsGroup00>(opcode & OperationCodes::Masks::OP_CODE >> 5)) {
	case OperationCodes::OperationsGroup00::BIT: {
		int operand = bus->readMemory(address);
		flag_Z = !(reg_A & operand);
		flag_V = operand & 0x40;
		flag_N = operand & 0x80;
		break;
	}
	case OperationCodes::OperationsGroup00::JMP: {
		reg_PC = readAddr(reg_PC);
		break;
	}
	case OperationCodes::OperationsGroup00::JMP_ABS: {
		address = readAddr(reg_PC);
		Address page = address & 0xff00;
		reg_PC = bus->readMemory(address) | bus->readMemory(page | ((address + 1) & 0xff)) << 8;
		break;
	}
	case OperationCodes::OperationsGroup00::STY: {
		bus->writeMemory(address, reg_Y);
		break;
	}
	case OperationCodes::OperationsGroup00::LDY: {
		reg_Y = bus->readMemory(address);
		setupZFlag(reg_Y);
		break;
	}
	case OperationCodes::OperationsGroup00::CPY: {
		int difference = reg_Y - bus->readMemory(address);
		flag_C = !(difference & 0x100);
		setupZFlag(difference);
		break;
	}
	case OperationCodes::OperationsGroup00::CPX: {
		int difference = reg_X - bus->readMemory(address);
		flag_C = !(difference & 0x100);
		setupZFlag(difference);
		break;
	}
	}
}

Address CPU::calculateAbsoluteAddress(Byte opcode) {
	Address addr = 0;
	switch (opcode & OperationCodes::Masks::COMMAND_GROUP) {
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


Address CPU::calculateAbsAddr01(Byte opcode) {
	Address absAddr = 0;
	switch (static_cast<OperationCodes::AddressingModes01>(opcode & OperationCodes::Masks::ADDR_MODE >> 2)) {
	case OperationCodes::AddressingModes01::INDIRECT_X:
		absAddr = calculateAddr(AddressingModes::INDIRECT_X);
		break;
	case OperationCodes::AddressingModes01::ZERO_PAGE:
		absAddr = calculateAddr(AddressingModes::ZERO_PAGE);
		break;
	case OperationCodes::AddressingModes01::IMMEDIATE:
		absAddr = calculateAddr(AddressingModes::IMMEDIATE);
		break;
	case OperationCodes::AddressingModes01::ABSOLUTE:
		absAddr = calculateAddr(AddressingModes::ABSOLUTE);
		break;
	case OperationCodes::AddressingModes01::INDIRECT_Y:
		absAddr = calculateAddr(AddressingModes::INDIRECT_Y);
		break;
	case OperationCodes::AddressingModes01::ZERO_PAGE_X:
		absAddr = calculateAddr(AddressingModes::ZERO_PAGE_X);
		break;
	case OperationCodes::AddressingModes01::ABSOLUTE_Y:
		absAddr = calculateAddr(AddressingModes::ABSOLUTE_Y);
		break;
	case OperationCodes::AddressingModes01::ABSOLUTE_X:
		absAddr = calculateAddr(AddressingModes::ABSOLUTE_X);
		break;
	}
	return absAddr;
}

Address CPU::calculateAbsAddr10(Byte opcode) {
	Address absAddr = 0;
	switch (static_cast<OperationCodes::AddressingModes10>(opcode & OperationCodes::Masks::ADDR_MODE >> 2)) {
	case OperationCodes::AddressingModes10::IMMEDIATE:
		absAddr = calculateAddr(AddressingModes::IMMEDIATE);
		break;
	case OperationCodes::AddressingModes10::ZERO_PAGE:
		absAddr = calculateAddr(AddressingModes::ZERO_PAGE);
		break;
	case OperationCodes::AddressingModes10::ACCUMULATOR:
		absAddr = calculateAddr(AddressingModes::ACCUMULATOR);
		break;
	case OperationCodes::AddressingModes10::ABSOLUTE:
		absAddr = calculateAddr(AddressingModes::ABSOLUTE);
		break;
	case OperationCodes::AddressingModes10::ZERO_PAGE_X:
		absAddr = calculateAddr(AddressingModes::ZERO_PAGE_X);
		break;
	case OperationCodes::AddressingModes10::ABSOLUTE_X:
		absAddr = calculateAddr(AddressingModes::ABSOLUTE_X);
		break;
	}
	return absAddr;
}

Address CPU::calculateAbsAddr00(Byte opcode) {
	Address absAddr = 0;
	switch (static_cast<OperationCodes::AddressingModes00>(opcode & OperationCodes::Masks::ADDR_MODE >> 2)) {
	case OperationCodes::AddressingModes00::IMMEDIATE:
		absAddr = calculateAddr(AddressingModes::IMMEDIATE);
		break;
	case OperationCodes::AddressingModes00::ZERO_PAGE:
		absAddr = calculateAddr(AddressingModes::ZERO_PAGE);
		break;
	case OperationCodes::AddressingModes00::ABSOLUTE:
		absAddr = calculateAddr(AddressingModes::ABSOLUTE);
		break;
	case OperationCodes::AddressingModes00::ZERO_PAGE_X:
		absAddr = calculateAddr(AddressingModes::ZERO_PAGE_X);
		break;
	case OperationCodes::AddressingModes00::ABSOLUTE_X:
		absAddr = calculateAddr(AddressingModes::ABSOLUTE_X);
		break;
	}
	return absAddr;
}

Address CPU::calculateAddr(AddressingModes addrMode) {
	Address absAddr = 0;
	switch (addrMode) {
	case AddressingModes::INDIRECT_X: {
		Byte baseAddr = bus->readMemory(reg_PC++) + reg_X;
		absAddr = bus->readMemory(baseAddr & 0xff) | bus->readMemory((baseAddr + 1) & 0xff) << 8;
		break;
	}
	case AddressingModes::ZERO_PAGE: {
		absAddr = bus->readMemory(reg_PC++);
		break;
	}
	case AddressingModes::IMMEDIATE: {
		absAddr = reg_PC++;
		break;
	}
	case AddressingModes::ABSOLUTE: {
		absAddr = readAddr(reg_PC);
		reg_PC += 2;
	}
		break;
	case AddressingModes::INDIRECT_Y: {
		Byte baseAddr = bus->readMemory(reg_PC++);
		absAddr = bus->readMemory(baseAddr & 0xff) | bus->readMemory((baseAddr + 1) & 0xff) << 8;
		break;
	}
	case AddressingModes::ZERO_PAGE_X: {
		absAddr = (bus->readMemory(reg_PC++) + reg_X) & 0xff;
		break;
	}
	case AddressingModes::ABSOLUTE_Y: {
		absAddr = readAddr(reg_PC);
		reg_PC += 2;
		absAddr += reg_Y;
		break;
	}
	case AddressingModes::ABSOLUTE_X: {
		absAddr = readAddr(reg_PC);
		reg_PC += 2;
		break;
	}
	case AddressingModes::ACCUMULATOR:
		absAddr = -1;
	}
	return absAddr;
}


Address CPU::readAddr(Address addr) {
	return bus->readMemory(addr) | bus->readMemory(addr + 1) << 8;
}

void CPU::setupZFlag(Byte value) {
	flag_Z = !value;
	flag_N = value & 0x80;
}

void CPU::setInterrupt(OperationCodes::InterruptTypes interruptType) {
	switch (interruptType) {
	case OperationCodes::InterruptTypes::NMI: {
		waitingNMI = true;
		break;
	}
	case OperationCodes::InterruptTypes::IRQ: {
		waitingIRQ = true;
		break;
	}
	}
}

void CPU::executeInterrupt(OperationCodes::InterruptTypes interruptType) {
	if (flag_I && interruptType != OperationCodes::InterruptTypes::NMI && interruptType != OperationCodes::InterruptTypes::BRK)
		return;

	if (interruptType == OperationCodes::InterruptTypes::BRK)
		++reg_PC;

	pushStack(reg_PC >> 8);
	pushStack(reg_PC);

	Byte flags = flag_N << 7 | flag_V << 6 | 1 << 5 | (interruptType == OperationCodes::InterruptTypes::BRK) << 4 | flag_D << 3 | flag_I << 2 | flag_Z << 1 | flag_C;
	pushStack(flags);

	flag_I = true;

	switch (interruptType)
	{
	case OperationCodes::InterruptTypes::IRQ:
	case OperationCodes::InterruptTypes::BRK: {
		reg_PC = readAddr(OperationCodes::System_Vectors::IRQ);
		break;
	}
	case OperationCodes::InterruptTypes::NMI: {
		reg_PC = readAddr(OperationCodes::System_Vectors::NMI);
		break;
	}
	}
}

void CPU::pushStack(Byte value) {
	bus->writeMemory(0x100 | reg_S, value);
	--reg_S;
}

Byte CPU::pullStack() {
	return bus->readMemory(0x100 | ++reg_S);
}

