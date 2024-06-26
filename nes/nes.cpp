#include "nes.h"

NES::NES(Cartridge* cartridge) {
	this->ppu = new PPU();
	this->apu = new APU();
	this->mapper = new NROMMapper(cartridge);
	this->bus = new Bus(ppu, apu, mapper);
	isInWork = false;
}

void NES::start() {
	isInWork = true;
	while (isInWork) {
		cpu->step();
	}
}

void NES::stop() {
	isInWork = false;
}
