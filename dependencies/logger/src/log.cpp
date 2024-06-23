#include "../include/log.h"

Log::Log(LogLevel logLevel, std::string message) {
	this->creationTime =  std::chrono::system_clock::now();
	this->logLevel = logLevel;
	this->message = message;
}

std::string Log::toString() {
	std::string result = std::format(
		"[ {:%d-%m-%Y %H:%M} ] [ {} ] {} ",
		this->creationTime,
		logLevelConverter(this->logLevel),
		message
	);
	return result;
}

std::string logLevelConverter(LogLevel logLevel) {
	switch (logLevel) {
	case NORMAL:
		return "Normal";
	case WARRNING:
		return "Warning";
	case FATAL: 
		return "Fatal";
	default:
		return "Unrecognized loglevel";
	}
}