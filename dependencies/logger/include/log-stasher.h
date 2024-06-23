#ifndef LOG_STASHER_H
#define LOG_STASHER_H

#include <string>
#include <memory>
#include <vector>
#include "log.h"

class LogStasher {
private:
	std::vector<Log*> logBuffer;
public:
	LogStasher();
	void saveLog(Log* log);
	void unloadLogs();
	
};

#endif