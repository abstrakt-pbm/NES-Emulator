#include "../include/log-stasher.h"
#include <iostream>
LogStasher::LogStasher() {
	this->logBuffer = std::vector<Log*>();
}

void LogStasher::saveLog(Log* log) {
	this->logBuffer.push_back(log);
}

void LogStasher::unloadLogs() {
	for (Log* log : this->logBuffer) {
		std::cout << log->toString() << '\n';
	}
}