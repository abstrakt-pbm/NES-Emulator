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

	bool isUsingChrRam;
	bool isHasExtendedRam;



public:
	Cartridge(std::string);
	void load();
};


#endif
