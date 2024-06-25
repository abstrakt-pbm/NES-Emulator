#include <iostream>
#include "dependencies/logger/clogs.h"
#include "nes/cartridge/include/cartridge.h"

int main(){
	LogStasher* logStasher = new LogStasher();
	Logger* logger = new Logger(logStasher);
	Cartridge* cartridge = new Cartridge(logger, "C:\\Users\\pyumi\\source\\repos\\Nemo\\resources\\cartridges\\Super_mario_brothers.nes");
	cartridge->load();
	logStasher->bringOut();

}