#pragma once
#ifndef BUS_H
#define BUS_H

#include "cpu-op-codes.h"

class Bus {
private:
	Byte* memory;
public:
	Bus();
	Byte readMemory(Address address);
	void writeMemory(Address address, Byte value);

};

#endif