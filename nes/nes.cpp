#include "nes.h"
#include <iostream>

NES::NES(Cartridge* cartridge) {
	this->mapper = new NROMMapper(cartridge);
	this->ppu = new PPU(mapper);
	this->apu = new APU();
	this->bus = new Bus(ppu, apu, mapper);
	this->cpu = new CPU(bus);
	isInWork = false;
}

void NES::start() {
	isInWork = true;
	while (isInWork) {
		ppu->step();
		ppu->step();
		ppu->step();

		cpu->step();
	}
}

void NES::stop() {
	isInWork = false;
}
