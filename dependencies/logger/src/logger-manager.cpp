#include "../include/logger-manager.h"

LoggerManager::LoggerManager() {
	this->logStasher = new LogStasher();
	this->logger = new Logger(this->logStasher);
}

Logger* LoggerManager::getLoggerInstance() {
	return this->logger;
}

LogStasher* LoggerManager::getLogStasherInstance() {
	return this->logStasher;
}

LoggerManager* LoggerManager::getInstance() {
	mtx.lock();
	if (loggerManager == nullptr) {
		loggerManager = new LoggerManager();
	}
	else {
		return loggerManager;
	}
	mtx.unlock();
	return LoggerManager::loggerManager;
}