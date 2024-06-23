#include "../include/cartridge.h"
#include "../include/mapper.h"
#include <fstream>
#include <iostream>

Cartridge::Cartridge(std::string path) {
	this->path = path;
}

std::vector<Byte> Cartridge::getPgrRom() {
	return this->pgrRom;
}

std::vector<Byte> Cartridge::getChr() {
	return this->chrRom;
}
Byte Cartridge::getMapperType() {
	return this->mapperType;
}

Byte Cartridge::getNameTableMirroringType() {
	return this->nameTableMirroring;
}

bool Cartridge::isHasExtendedRam() {
	return this->hasExtendedRam;
}

void Cartridge::load() {
	std::ifstream inesFile(path, std::ios::in | std::ios::binary);
	if (!inesFile.is_open()) {
		std::cout << "INes file not opened" << '\n';
		return;
	}
	std::vector<Byte> header(16);
	inesFile.read(reinterpret_cast<char*>(&header[0]), 16);

	pgrRom = std::vector<Byte>(header[4] * 16 * 1024);
	chrRom = std::vector<Byte>(header[5] * 8 * 1024);

	if ( header[6] & 0x8 ) {
		nameTableMirroring = NameTableMirroring::FOUR_SCREEN;
	}
	else {
		nameTableMirroring = header[6] & 0x1;
	}

	mapperType = ((header[6] >> 4) & 0xf) | (header[7] & 0xf0);

	hasExtendedRam = header[6] & 0x2;

	if ( !inesFile.read(reinterpret_cast<char*>(&pgrRom[0]), 0x4000 * header[4] )) {
		std::cout << "Error while reading pgr data" << '\n';
	}

	if (header[5]) {
		if (!inesFile.read(reinterpret_cast<char*>(&chrRom[0]), 0x2000 * header[5])) {
			std::cout << "Error while reading chr data";
		}
	}

	inesFile.close();
}