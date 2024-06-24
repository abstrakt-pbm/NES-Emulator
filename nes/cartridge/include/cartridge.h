#pragma once
#ifndef CARTRIDGE_H
#define CARTDIGE_H
#include <vector>
#include <string>

using Address = short int;
using Byte = unsigned char;

class Cartridge {
private:
	std::string path;
	std::vector<Byte> pgrRom;
	std::vector<Byte> chrRom;
	Byte mapperType;
	Byte nameTableMirroring;

	bool isUsingChrRam;
	bool hasExtendedRam;

public:
	Cartridge(std::string pathToCartridge);
	std::vector<Byte> getPgrRom();
	std::vector<Byte> getChr();
	Byte getMapperType();
	Byte getNameTableMirroringType();
	bool isHasExtendedRam();

	void load();
};


#endif
