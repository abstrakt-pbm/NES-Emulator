#include "../include/log-stasher.h"
#include "iostream"

LogStasher::LogStasher() {
	this->logBuffer = std::vector<Log*>();
}

LogStasher::LogStasher(std::string pathToLogFile) {
	this->logBuffer = std::vector<Log*>();
	this->pathToLogFile = pathToLogFile;
}


void LogStasher::saveLog(Log* log) {
	this->logBuffer.push_back(log);
}

void LogStasher::bringOut() {
	for (Log* log : this->logBuffer) {
		std::cout << log->toString() << '\n';
	}
}