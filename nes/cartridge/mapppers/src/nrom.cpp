#include "../include/nrom.h"
#include <iostream>
NROMMapper::NROMMapper(Cartridge* cart) {
	this->cartridge = cart;
	cartridge->load();
	if (cartridge->getPrgRomSize() == 0x4000) {
		isUseOneBank = true;
	}
	else {
		isUseOneBank = false;
	}

	if (cartridge->getChrRomSize() == 0) {
		isUseChrRam = true;
		chrRam = new Byte[0x2000];
	}
	else {
		isUseChrRam = false;
	}
}

void NROMMapper::writePrg(Address address, Byte value) {

}

Byte NROMMapper::readPrg(Address address) {
	if (isUseOneBank) {
		return cartridge->getPrgRom()[address - 0x8000];
	}
	else {
		return cartridge->getPrgRom()[(address - 0x8000) & 0x3FFF];
	}
}

void NROMMapper::writeChr(Address address, Byte value) {
	if (isUseChrRam) {
		chrRam[address] = value;
	}
}

Byte NROMMapper::readChr(Address address) {
	if (isUseChrRam) {
		return chrRam[address];
	} else {
		return cartridge->getChrRom()[address];
	}
}