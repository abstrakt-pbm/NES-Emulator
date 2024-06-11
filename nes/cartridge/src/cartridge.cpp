#include "../include/Cartridge.h"
#include <fstream>
#include <iostream>

Cartridge::Cartridge(std::string path) {
	this->path = path;
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

	inesFile.close();
}