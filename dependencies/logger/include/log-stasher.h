#ifndef LOG_STASHER_H
#define LOG_STASHER_H

#include "log.h"


class LogStasher {
private:
	std::vector<Log*> logBuffer;
	std::string pathToLogFile;
public:
	LogStasher();
	LogStasher(std::string pathToLogFile);
	void saveLog(Log* log);
	void bringOut();
};

#endif