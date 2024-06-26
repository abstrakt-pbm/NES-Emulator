cmake_minimum_required (VERSION 3.8)

project ("Nintendo Entertainment System Emulator")

set(NES_HEDERS
	"nes.h"
	"cartridge/include/cartridge.h"
	"processing-units/include/apu.h"
	"processing-units/include/bus.h"
	"processing-units/include/cpu-op-codes.h"
	"processing-units/include/cpu.h"
	"processing-units/include/ppu.h"
	"cartridge/mapppers/include/mapper.h"
	"cartridge/mapppers/include/nrom.h")

set(NES_SOURCES
	"nes.cpp"
	"cartridge/src/cartridge.cpp"
	"processing-units/src/apu.cpp"
	"processing-units/src/bus.cpp"
	"processing-units/src/cpu.cpp"
	"processing-units/src/ppu.cpp"
	"cartridge/mapppers/src/mapper.cpp" 
	"cartridge/mapppers/src/nrom.cpp"
)

add_library(NES STATIC ${NES_HEDERS} ${NES_SOURCES})
