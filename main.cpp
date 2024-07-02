#include <iostream>
#include "dependencies/logger/clogs.h"
#include "nes/nes.h"


int main(){
	LogStasher* logStasher = new LogStasher();
	Logger* logger = new Logger(logStasher);
	Cartridge* cartridge = new Cartridge(logger, "C:\\Users\\pyumi\\source\\repos\\Nemo\\resources\\cartridges\\Super_mario_brothers.nes");
	cartridge->load();
	NES* nes = new NES(cartridge);
	nes->start();
	return 0;
}

int main1 () {
	LogStasher* logStasher = new LogStasher();
	Logger* logger = new Logger(logStasher);
	Cartridge* cartridge = new Cartridge(logger, "C:\\Users\\pyumi\\source\\repos\\Nemo\\resources\\cartridges\\Super_mario_brothers.nes");
	cartridge->load();
	NROMMapper* mapper = new NROMMapper(cartridge);
	Bus* bus = new Bus(nullptr, nullptr, mapper);
	CPU* cpu = new CPU(bus);
	bus->readMemory(0x2002);
	return 0;
}