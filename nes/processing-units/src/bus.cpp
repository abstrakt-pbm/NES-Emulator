#include "../include/bus.h"

Bus::Bus(PPU* ppu, APU* apu, Mapper* mappper) {
	this->ppu = ppu;
	this->apu = apu;
	this->mapper = mapper;

	memory = new Byte[0xFFFF];
	for (auto i = 0; i < 0xFFFF; i++) {
		memory[i] = 0;
	}
}

Byte Bus::readMemory(Address address) {
	if (address < 0x2000) {
		return memory[address & 0x7FF];
	}
	else if (address < 0x4000) {
		return ppuGetCalls(address);
	}
	else if (address < 0x4020) {
		return ioGetCalls(address);
	}
	else {
		mapperGetCalls(address);
	}
}

void Bus::writeMemory(Address address, Byte value) {
	if (address < 0x2000) {
		memory[address & 0x7FF];
	}
	else if (address < 0x4000) {
		ppuPostCalls(address, value);
	}
	else if (address < 0x4020) {
		ioPostCalls(address, value);
	}
	else {
		mapperPostCalls(address, value);
	}
}

Byte Bus::ppuGetCalls(Address address) {

	return 0;
}

void Bus::ppuPostCalls(Address address, Byte value) {

}

Byte Bus::ioGetCalls(Address address) {
	return 0;
}

void Bus::ioPostCalls(Address address, Byte value) {
	
}
