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
