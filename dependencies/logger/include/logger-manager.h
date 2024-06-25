#ifndef LOGGER_MANAGER_H
#define LOGGER_MANAGER_H

#include "log-stasher.h"
#include "logger.h"
#include <mutex>


class LoggerManager {
private:
	static  std::mutex mtx;
	static LoggerManager* loggerManager;
	LogStasher* logStasher;
	Logger* logger;
	LoggerManager();
public:
	static LoggerManager* getInstance();
	LogStasher* getLogStasherInstance();
	Logger* getLoggerInstance();

};

#endif