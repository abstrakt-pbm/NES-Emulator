#include "../include/cartridge.h"
#include "../include/mapper.h"
#include <format>
#include <fstream>

Cartridge::Cartridge(Logger* logger, std::string path) {
	this->logger = logger;
	this->pathToInesFile = path;
}

Cartridge::~Cartridge() {
	delete[] pgrRom;
	delete[] chrRom;
} 

Byte* Cartridge::getPgrRom() {
	return this->pgrRom;
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
		logger->logFatal("Cartridge", std::format("INESFile can't be open ({})", pathToInesFile));
		iNesFile.close();
		return;
	}

	Byte headers[16];
	if (!iNesFile.read((char*)headers, 16)) {
		logger->logFatal("Cartridge", "Error while reading iNES headers");
		iNesFile.close();
		return;
	}
	if (std::string(&headers[0], &headers[4]) != "NES\x1A") {
		logger->logFatal("Cartridge", "Error while checking iNES signature");
		iNesFile.close();
		return;
	}

	if (!headers[4]) {
		logger->logFatal("Cartridge", "INes hasn't PGR ROM Banks");
		iNesFile.close();
		return;
	}


	pgrRom = new Byte[16384 * headers[4]];
	chrRom = new Byte[8192 * headers[5]];

	nameTableMirroring = headers[6] & 0b00000001;
	isUsingExtendedRam = headers[6] & 0b00000010;

	mapperType = headers[6] & 0b11110000 >> 4 | headers[7] & 0b11110000;

	if (!iNesFile.read((char*)pgrRom, 16384 * headers[4])) {
		logger->logFatal("Cartridge", "Error while reading PGR data");
	}

	if (headers[5]) {
		if (!iNesFile.read((char*)chrRom, 16384 * headers[5])) {
			logger->logFatal("Cartridge", "Error while reading CHR data");
		}
	}
	
	iNesFile.close();
}