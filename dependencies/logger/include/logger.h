#ifndef LOGGER_H
#define LOGGER_H

#include "log.h"
#include "log-stasher.h"

class Logger {
private:
	LogStasher* connectedLogStasher;
	LogLevel minimalLogLevel;
public:
	Logger(LogStasher* logStasher);
	void logNormal(std::string message);
	void logWarning(std::string message);
	void logFatal(std::string message);

};

#endif // !LOGGER_H
