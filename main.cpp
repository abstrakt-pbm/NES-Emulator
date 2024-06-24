#include <iostream>
#include "dependencies/logger/include/log-stasher.h"
#include "dependencies/logger/include/logger.h"

int main(){
	LogStasher* stasher = new LogStasher();
	Logger* logger = new Logger(stasher);
	logger->logFatal("CPU", "Bad");
	logger->logWarning("PPU", "May be better");
	logger->logNormal("Cartridge", "All loaded");
	stasher->bringOut();

}