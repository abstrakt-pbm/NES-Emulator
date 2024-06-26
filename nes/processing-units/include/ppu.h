#pragma once
#ifndef PPU_H
#define PPU_H

using Address = short int;
using Byte = unsigned char;

class PPU {
private:
public:
	PPU();
	void control(Byte value);
	void writeMask(Byte value);
	Byte readStatus();
	void writeOamAddr(Byte value);

	Byte readOamData();
	void writeOamData(Byte value);

	void writeScroll(Byte value);

	void writeAddr(Byte value);
	Byte readData();
	void writeData(Byte value);

	void writeOamDma(Byte value);

};

#endif