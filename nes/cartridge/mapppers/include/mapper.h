#ifndef MAPPER_H
#define MAPPER_H



using Address = unsigned short int;
using Byte = unsigned char;

class Mapper {
public:
	virtual void writePrg(Address address, Byte value) = 0;
	virtual Byte readPrg(Byte value) = 0;

	virtual void writeChr(Address address, Byte value) = 0;
	virtual Byte readChr(Address address) = 0;
};

#endif