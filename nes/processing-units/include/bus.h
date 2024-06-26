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

	Byte ppuOutputCalls(Address address);
	void ppuInputCalls(Address address, Byte value);

	Byte mapperOutputCalls(Address address);
	void mapperInputCalls(Address address, Byte value);

	Byte ioOutputCalls(Address address);
	void ioInputCalls(Address address, Byte value);

public:
	Bus(PPU* ppu, APU* apu, Mapper* mappper);
	Byte readMemory(Address address);
	void writeMemory(Address address, Byte value);

};

#endif