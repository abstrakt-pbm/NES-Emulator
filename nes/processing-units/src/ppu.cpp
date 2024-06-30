#include "../include/ppu.h"
#include <iostream>

PPU::PPU() {
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
	std::cout << "Call write oam addr" << '\n';
}

Byte PPU::readOamData() {
	std::cout << "Call read oam data" << '\n';
	return 0;
}

void PPU::writeOamData(Byte value) {
	std::cout << "Call write oam data" << '\n';
}

void PPU::writeScroll(Byte value) {
	std::cout << "Call write scroll" << '\n';
}

void PPU::writeAddr(Byte value) {
	std::cout << "Call write addr" << '\n';
}

Byte PPU::readData() {
	std::cout << "Call read ppu data" << '\n';
	return 0;
}

void PPU::writeData(Byte value) {
	std::cout << "Call write ppu data" << '\n';
}

void PPU::writeOamDma(Byte byte) {
	std::cout << "Call write oam dma" << '\n';
}