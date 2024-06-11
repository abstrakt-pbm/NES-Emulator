#ifndef NES_H
#define NES_H

#include "Processing-Units/include/cpu.h"
#include "Processing-Units/include/ppu.h"
#include "Processing-Units/include/apu.h"




class NES {
private:
	CPU* cpu;
	PPU* ppu;

public:
	NES();
	void start();
};

#endif // !NES_H
