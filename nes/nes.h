#ifndef NES_H
#define NES_H

#include "processing-units/include/cpu.h"
#include "processing-units/include/ppu.h"
#include "processing-units/include/apu.h"
#include "processing-units/include/bus.h"
#include "cartridge/include/cartridge.h"


class NES {
private:
	CPU* cpu;
	PPU* ppu;
	Bus* bus; 
	Cartridge* cartridge;
public:
	NES(Cartridge* cartridge);
	void start();
};

#endif // !NES_H
1