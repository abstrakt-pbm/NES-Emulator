#ifndef PPU_H
#define PPU_H

#include "../../cartridge/mapppers/include/nrom.h"

using Address = unsigned short int;
using Byte = unsigned char;

enum PPUState {
	PRE_RENDER,
	RENDER,
	POST_RENDER,
	VBLANK
};

enum SpriteSize {
	s8x8,
	s8x16
};

class PPU {
private:

	NROMMapper* mapper;

	PPUState currentState;
	int cycles;
	bool isSecondSameCall;

	Byte reg_v;
	Byte reg_t;
	Byte reg_x;
	Byte reg_w;

	Byte videoMemory[2048];
	Byte oamMemory[256];
	Byte paletteMemory[8192];

	Byte oamAddr;
	Byte vRamAddr;

	Address baseNameTableAddr;
	Byte vRamAddrGrow;
	SpriteSize spriteSize;
	Address spritePattrenTableAddr8x8;
	bool isGenerateNMI;

	bool isUseGreyscaleMode;
	bool showEdgeBackground;
	bool showEdgeSprites;
	bool showBackground;
	bool showSprites;

	

	void preRenderStep();
	void renderStep();
	void postRenderStep();
	void vblankStep();



public:
	PPU(NROMMapper* mapper);
	Byte* getRawPicture();

	void step();

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

	void writeOamDma(Byte* page);

};

#endif