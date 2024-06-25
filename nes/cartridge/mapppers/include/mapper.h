#ifndef MAPPER_H
#define MAPPER_H

using Address = short int;
using Byte = unsigned char;

class Mapper {
public:
	void writePrg(Address address, Byte value);
	Byte readPrg(Byte value);

	void writeChr(Address address, Byte value);
	Byte readChr(Address address);
};

#endif