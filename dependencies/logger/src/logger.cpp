#include "../include/logger.h"
#include <iostream>

Logger::Logger(LogStasher* logStasher) {
	this->connectedLogStasher = logStasher;
	this->minimalLogLevel = LogLevel::NORMAL;
}

void Logger::logNormal(std::string message) {
	Log* log = new Log(LogLevel::NORMAL, message);
	this->connectedLogStasher->saveLog(log);
}

void Logger::logWarning(std::string message) {
	Log* log = new Log(LogLevel::WARRNING, message);
	this->connectedLogStasher->saveLog(log);
}

void Logger::logFatal(std::string message) {
	Log* log = new Log(LogLevel::FATAL, message);
	this->connectedLogStasher->saveLog(log);
}