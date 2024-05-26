#include "../include/bus.h"

Bus::Bus() {
	memory = new Byte[0xFFFF];
	for (auto i = 0; i < 0xFFFF; i++) {
		memory[i] = 0;
	}
}

Byte Bus::readMemory(Address address) {
	return memory[address];
}

void Bus::writeMemory(Address address, Byte value) {
	memory[address] = value;
}

