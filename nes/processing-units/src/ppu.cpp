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
	switch (value & 0b00000011) {
	case 0: {
		baseNameTableAddr = 0x2000;
		break;
	} 
	case 1: {
		baseNameTableAddr = 0x2400;
		break;
	}
	case 2: {
		baseNameTableAddr = 0x2800;
		break;
	}
	case 3: {
		baseNameTableAddr = 0x2C00;
		break;
	}
	}

	if ((value & 0b00000100) >> 2) {
		vRamAddrGrow = 1;
	}
	else {
		vRamAddrGrow = 32;
	}
	spriteSize = static_cast<SpriteSize>((value & 0b00100000) >> 5);

	if (!spriteSize) {
		if (value & 0b00001000) {
			spritePattrenTableAddr8x8 = 0;
		}
		else {
			spritePattrenTableAddr8x8 = 0x1000;
		}
	}

	isGenerateNMI = value & 0b10000000;
}

void PPU::writeMask(Byte value) {
	isUseGreyscaleMode = value & 0b00000001;
	showEdgeBackground = value & 0b00000010;
	showEdgeSprites = value & 0b00000100;
	showBackground = value & 0b00001000;
	showSprites = value & 0b00010000;
}

Byte PPU::readStatus() {
	Byte status = 0;
	if (currentState == PPUState::VBLANK) {
		status &= 0b10000000;
	}

	return status;
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
	if (!isSecondSameCall) {
		isSecondSameCall = true;
	}
	else {
		isSecondSameCall = false;
	}
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