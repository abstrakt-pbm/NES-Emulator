#include "../include/cartridge.h"
#include <format>
#include <fstream>

Cartridge::Cartridge(std::string path) {
	this->pathToInesFile = path;
}

Cartridge::~Cartridge() {
	delete[] prgRom;
	delete[] chrRom;
} 

Byte* Cartridge::getPrgRom() {
	return this->prgRom;
}

Byte* Cartridge::getChrRom() {
	return this->chrRom;
}
Byte Cartridge::getMapperType() {
	return this->mapperType;
}

Byte Cartridge::getNameTableMirroringType() {
	return this->nameTableMirroring;
}

bool Cartridge::isHasExtendedRam() {
	return this->isUsingExtendedRam;
}

void Cartridge::load() {
	std::ifstream iNesFile (pathToInesFile, std::ios::in | std::ios::binary);
	if (!iNesFile.is_open()) {
		iNesFile.close();
		return;
	}

	Byte headers[16];
	if (!iNesFile.read((char*)headers, 16)) {
		iNesFile.close();
		return;
	}
	if (std::string(&headers[0], &headers[4]) != "NES\x1A") {
		iNesFile.close();
		return;
	}

	if (!headers[4]) {
		iNesFile.close();
		return;
	}

	prgRomSize = 16384 * headers[4];
	chrRomSize = 8192 * headers[5];

	prgRom = new Byte[prgRomSize];
	chrRom = new Byte[chrRomSize];
	

	nameTableMirroring = headers[6] & 0b00000001;
	isUsingExtendedRam = headers[6] & 0b00000010;

	mapperType = headers[6] & 0b11110000 >> 4 | headers[7] & 0b11110000;

	if (!iNesFile.read((char*)prgRom, 16384 * headers[4])) {
	}
	
	if ( headers[5]) {
		if (!iNesFile.read((char*)chrRom, 8192 * headers[5])) {
		}
	}
	iNesFile.close();
}

int Cartridge::getPrgRomSize() {
	return prgRomSize;
}

int Cartridge::getChrRomSize() {
	return chrRomSize;
}

