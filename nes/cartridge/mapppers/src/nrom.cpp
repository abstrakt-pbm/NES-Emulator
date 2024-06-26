#include "../include/nrom.h"

NROMMapper::NROMMapper(Cartridge* cartridge) {
	this->cartridge = cartridge;
	cartridge->load();
}