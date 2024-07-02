#include "../include/ppu.h"
#include "../../cartridge/mapppers/include/nrom.h"
#include <iostream>

PPU::PPU(NROMMapper* mapper) {
	this->mapper = mapper;
}

void PPU::step() {
	switch (currentState) {
	case PRE_RENDER: {
		preRenderStep();
		break;
	}
	case RENDER: {
		renderStep();
		break;
	}
	case POST_RENDER: {
		postRenderStep();
		break;
	}
	case VBLANK: {
		vblankStep();
		break;
	}
	};
}

void PPU::preRenderStep() {

}

void PPU::renderStep() {

}

void PPU::postRenderStep(){

}

void PPU::vblankStep() {

}

void PPU::control(Byte value) {
		
}

void PPU::writeMask(Byte value) {
	std::cout << "Call ppu write mask" << '\n';
}

Byte PPU::readStatus() {
	std::cout << "Call ppu read status" << '\n';
	return 0;
}

void PPU::writeOamAddr(Byte value) {
	this->oamAddr = value;
}

Byte PPU::readOamData() {
	if (currentState == PPUState::VBLANK) {

		return oamMemory[oamAddr];
	}
	return 0;
}

void PPU::writeOamData(Byte value) {
	this->oamMemory[oamAddr++] = value;
}

void PPU::writeScroll(Byte value) {
	std::cout << "Call write scroll" << '\n';
}

void PPU::writeAddr(Byte value) {
	Byte tmp = vRamAddr;
	if (!isSecondSameCall) {
		tmp &= 0xff;
		vRamAddr = tmp;
		isSecondSameCall = true;
	}
	else {
		tmp &= 0xff00;
		tmp |= (value & 0x3f) << 8;
		isSecondSameCall = false;
	}
}

Byte PPU::readData() {
	Byte dataValue = this->videoMemory[vRamAddr];
	vRamAddr += vRamAddrGrow;
	return dataValue;
}

void PPU::writeData(Byte value) {
	this->videoMemory[vRamAddr] = value;
	vRamAddr += vRamAddrGrow;
}

void PPU::writeOamDma(Byte* page) {
	for (auto i = 0; i < 256; i++) {
		oamMemory[i] = page[i];
	}
}