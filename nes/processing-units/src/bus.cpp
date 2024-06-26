#include "../include/bus.h"

Bus::Bus(PPU* ppu, APU* apu, NROMMapper* mappper) {
	this->ppu = ppu;
	this->apu = apu;
	this->mapper = mapper;

	for (auto i = 0; i < 0xFFFF; i++) {
		memory[i] = 0;
	}
	for (auto i = 0; i < 0x2000; i++) {
		extendedMemory[i] = 0;
	}
}

Byte Bus::readMemory(Address address) {
	if (address < 0x2000) {
		return memory[address & 0x7FF];
	}
	else if (address < 0x4000) {
		return ppuOutputCalls(address);
	}
	else if (address < 0x4020) {
		return ioOutputCalls(address);
	}
	else {
		mapperOutputCalls(address);
	}
}

void Bus::writeMemory(Address address, Byte value) {
	if (address < 0x2000) {
		memory[address & 0x7FF];
	}
	else if (address < 0x4000) {
		ppuInputCalls(address, value);
	}
	else if (address < 0x4020) {
		ioInputCalls(address, value);
	}
	else {
		mapperInputCalls(address, value);
	}
}

Byte Bus::ppuOutputCalls(Address address) {
	switch (address & 0x7) {
	case 2: {
		return ppu->readStatus();
		break;
	}
	case 4: {
		return ppu->readOamData();
		break;
	}
	case 7: {
		return ppu->readData();
		break;
	}
	}
	return 0;
}

void Bus::ppuInputCalls(Address address, Byte value) {
	switch (address & 0x7) {
	case 0: {
		ppu->control(value);
		break;
	}
	case 1: {
		ppu->writeMask(value);
		break;
	}
	case 3: {
		ppu->writeOamAddr(value);
		break;
	}
	case 4: {
		ppu->writeOamData(value);
		break;
	}
	case 5: {
		ppu->writeScroll(value);
		break;
	}
	case 6: {
		ppu->writeAddr(value);
		break;
	}
	case 7: {
		ppu->writeData(value);
		break;
	}
	}
}

Byte Bus::mapperOutputCalls(Address address) {
	return mapper->readPrg(address);
}

void Bus::mapperInputCalls(Address address, Byte value) {
	extendedMemory[address - 0x6000] = value;
}

Byte Bus::ioOutputCalls(Address address) {
	return 0;
}

void Bus::ioInputCalls(Address address, Byte value) {
	
}
