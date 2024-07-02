#ifndef PPU_H
#define PPU_H

using Address = unsigned short int;
using Byte = unsigned char;

enum PPUState {
	PRE_RENDER,
	RENDER,
	POST_RENDER,
	VBLANK
};


class PPU {
private:

	NROMMapper* mapper;

	PPUState currentState;
	int cycles;

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
	Address patterTableAddrFor8x8;
	Address backgroundPatternTableAddress;
	Byte spriteSize;

	bool isSecondSameCall;

	bool isUseGreyscaleMode;
	bool isShowBackgroundLeft;
	bool isShowSpritesLeft;
	bool isShowBackground;
	bool isShowSprites;
	bool emphasizeRed;
	bool emphasizeGreen;
	bool emphasizeBlue;

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