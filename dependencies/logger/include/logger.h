#ifndef LOGGER_H
#define LOGGER_H

#include "log-stasher.h"
#include "log.h";

class Logger {
private:
	LogStasher* logStasher;
	LogLevel minimalLogLevel;
public:
	Logger(LogStasher* logStasher);
	void logNormal(std::string moduleName, std::string message);
	void logWarning(std::string moduleName, std::string message);
	void logFatal(std::string moduleName, std::string message);

};

#endif // !LOGGER_H
