#include <iostream>
#include "dependencies/logger/clogs.h"
#include "nes/cartridge/include/cartridge.h"

int main(){
	Cartridge* cartridge = new Cartridge("C:\\Users\\pyumi\\source\\repos\\Nemo\\resources\\cartridges\\Legend of Zelda, The (USA).nes");
	cartridge->load();
	LoggerManager::getInstance()->getLogStasherInstance()->bringOut();
}