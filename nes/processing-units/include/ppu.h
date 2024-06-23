#ifndef PPU_H
#define PPU_H
#include "../include/bus.h "

class PPU {
private:
	Bus* bus;
public:
	PPU(Bus* bus);
};

#endif