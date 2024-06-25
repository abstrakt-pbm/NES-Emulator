#pragma once
#ifndef CARTRIDGE_H
#define CARTDIGE_H
#include <vector>
#include <string>

using Address = short int;
using Byte = unsigned char;

enum TvSystem {
	NTSC,
	PAL
};

class Cartridge {
private:
	std::string pathToInesFile;
	Byte* pgrRom;
	Byte* pgrRam;
	Byte* chrRom;
	Byte* trainer;
	Byte mapperType;
	Byte nameTableMirroring;
	TvSystem usedTvSystem;

	bool isTvSystemPresented;
	bool isUsingTrainer;
	bool isUsingChrRam;
	bool isUsingPgrRam;
	bool isUsingExtendedRam;
	bool isUsingAlternativeNametableLayout;

public:
	Cartridge(std::string pathToCartridge);
	Byte* getPgrRom();
	Byte* getChr();
	Byte getMapperType();
	Byte getNameTableMirroringType();
	bool isHasExtendedRam();

	void load();
};


#endif
