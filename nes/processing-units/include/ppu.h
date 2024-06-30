#ifndef PPU_H
#define PPU_H

using Address = unsigned short int;
using Byte = unsigned char;

class PPU {
private:
	Byte reg_v;
	Byte reg_t;
	Byte reg_x;
	Byte reg_w;
	Byte* memory;
	Address baseNameTableAddr;
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