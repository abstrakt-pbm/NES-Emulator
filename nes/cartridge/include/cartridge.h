#pragma once
#ifndef CARTRIDGE_H
#define CARTDIGE_H
#include <vector>
#include <string>
#include "../../../dependencies/logger/clogs.h"

using Address = short int;
using Byte = unsigned char;


class Cartridge {
private:
	Logger* logger;

	std::string pathToInesFile;
	Byte* prgRom;
	Byte* chrRom;
	Byte mapperType;
	Byte nameTableMirroring;

	int prgRomSize;
	int chrRomSize;

	bool isUsingChrRam;
	bool isUsingExtendedRam;

public:
	Cartridge(Logger* logger, std::string pathToCartridge);
	~Cartridge();

	int getPrgRomSize();
	int getChrRomSize();

	Byte* getPrgRom();
	Byte* getChrRom();
	Byte getMapperType();
	Byte getNameTableMirroringType();
	bool isHasExtendedRam();

	void load();
};


#endif
