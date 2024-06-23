#include <iostream>
#include "nes/processing-units/include/bus.h"
#include "nes/processing-units/include/cpu.h"
#include "nes/cartridge/include/cartridge.h"
int main(){
	/*
	Bus* bus = new Bus();
	CPU* cpu = new CPU(bus);
	cpu->step();
	*/
	Cartridge theLegendOfZelda("C:\\Users\\pyumi\\source\\repos\\Nemo\\resources\\cartridges\\Legend of Zelda, The (USA).nes");
	theLegendOfZelda.load();
	std::cout << (int)theLegendOfZelda.getMapperType();
}