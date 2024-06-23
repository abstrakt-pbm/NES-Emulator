#include "nes.h"

NES::NES(Cartridge* cartridge) {
	this->cartridge = cartridge;
	bus = new Bus();
	cpu = new CPU(bus);
	ppu = new PPU(bus);
}

void NES::start() {
	
	cpu->step();
	ppu->step();
}
