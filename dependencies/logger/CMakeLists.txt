cmake_minimum_required (VERSION 3.8)

project("Logger")

set ( LOGGER_HEDERS
	
	"include/log-stasher.h"
	"include/logger.h"
	"include/log.h"
	
)

set ( LOGGER_SOURCES
	"src/log-stasher.cpp"
	"src/logger.cpp"
	"src/log.cpp"
	
 )


add_library(Logger STATIC ${LOGGER_HEDERS} ${LOGGER_SOURCES})