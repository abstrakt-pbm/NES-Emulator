#include "../include/cartridge.h"
#include "../include/mapper.h"
#include "../../../dependencies/logger/clogs.h"
#include <fstream>

Cartridge::Cartridge(std::string path) {
	this->pathToInesFile = path;
}

Byte* Cartridge::getPgrRom() {
	return this->pgrRom;
}

Byte* Cartridge::getChr() {
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
		LoggerManager::getInstance()->getLoggerInstance()->logFatal("Cartridge", "Can't open iNes file");
		iNesFile.close();
		return;
	}

	Byte* headers = new Byte[16];
	if (!iNesFile.read((char*)headers, 16)) {
		LoggerManager::getInstance()->getLoggerInstance()->logFatal("Cartridge", "Error while reading iNes headers");
		iNesFile.close();
		delete headers;
		return;
	}
	if (std::string(headers[0], headers[4]) != "NES\x1A") {
		LoggerManager::getInstance()->getLoggerInstance()->logWarning("Cartridge", "Failed to check NES signature");
		iNesFile.close();
		delete headers;
		return;
	}

	pgrRom = new Byte[16384 * headers[4]];
	chrRom = new Byte[8192 * headers[5]];

	nameTableMirroring = headers[6] & 0b00000001;
	isUsingExtendedRam = headers[6] & 0b00000010;
	isUsingTrainer = headers[6] & 0b00000100;
	isUsingAlternativeNametableLayout = headers[6] & 0b00001000;
	mapperType = headers[6] & 0b11110000 >> 4 | headers[7] & 0b11110000;
	
	iNesFile.close();
}