#pragma once
#ifndef BUS_H
#define BUS_H

#include "cpu-op-codes.h"
#include "ppu.h"
#include "apu.h"
#include "../../cartridge/mapppers/include/mapper.h"

class Bus {
private:

	PPU* ppu;
	APU* apu;
	Mapper* mapper;
	Byte* memory;

	Byte ppuGetCalls(Address address);
	void ppuPostCalls(Address address, Byte value);

	Byte mapperGetCalls(Address address);
	void mapperPostCalls(Address address, Byte value);

	Byte ioGetCalls(Address address);
	void ioPostCalls(Address address, Byte value);

public:
	Bus(PPU* ppu, APU* apu, Mapper* mappper);
	Byte readMemory(Address address);
	void writeMemory(Address address, Byte value);

};

#endif