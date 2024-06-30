#include <iostream>
#include "dependencies/logger/clogs.h"
#include "nes/nes.h"


int main(){
	LogStasher* logStasher = new LogStasher();
	Logger* logger = new Logger(logStasher);
	Cartridge* cartridge = new Cartridge(logger, "/home/pablo/dev/Nemo/resources/cartridges/Super_mario_brothers.nes");
	cartridge->load();
	NES* nes = new NES(cartridge);
	nes->start();
}

int main1 () {
	LogStasher* logStasher = new LogStasher();
	Logger* logger = new Logger(logStasher);
	Cartridge* cartridge = new Cartridge(logger, "/home/pablo/dev/Nemo/resources/cartridges/Super_mario_brothers.nes");
	cartridge->load();
	NROMMapper* mapper = new NROMMapper(cartridge);
	Bus* bus = new Bus(nullptr, nullptr, mapper);
	CPU* cpu = new CPU(bus);
	bus->readMemory(0x2002);
}