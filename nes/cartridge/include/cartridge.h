#ifndef CARTRIDGE_H
#define CARTRIDGE_H
#include <vector>
#include <string>


using Address = unsigned short int;
using Byte = unsigned char;


class Cartridge {
private:

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
	Cartridge(std::string pathToCartridge);
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
