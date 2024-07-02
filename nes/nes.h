#ifndef NES_H
#define NES_H

#include "cartridge/mapppers/include/nrom.h"
#include "cartridge/include/cartridge.h"
#include "processing-units/include/apu.h"
#include "processing-units/include/bus.h"
#include "processing-units/include/ppu.h"
#include "processing-units/include/cpu.h"



class NES {
private:
	Bus* bus;
	APU* apu;
	PPU* ppu;
	CPU* cpu;
	NROMMapper* mapper;

	bool isInWork;

public:
	NES(Cartridge* cartridge);
	Byte* getRawPicture();
	void start();
	void stop();
};

#endif // !NES_H
