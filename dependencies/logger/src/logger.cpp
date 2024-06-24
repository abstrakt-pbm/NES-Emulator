#include "../include/logger.h"
#include <iostream>

Logger::Logger(LogStasher* logStasher) {
	this->logStasher = logStasher;
	this->minimalLogLevel = LogLevel::NORMAL;
}

void Logger::logNormal(std::string moduleName, std::string message) {
	Log* log = new Log(LogLevel::NORMAL, moduleName, message);
	this->logStasher->saveLog(log);
}

void Logger::logWarning(std::string moduleName, std::string message) {
	Log* log = new Log(LogLevel::WARRNING, moduleName, message);
	this->logStasher->saveLog(log);
}

void Logger::logFatal(std::string moduleName, std::string message) {
	Log* log = new Log(LogLevel::FATAL, moduleName, message);
	this->logStasher->saveLog(log);
}