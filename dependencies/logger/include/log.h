#ifndef LOG_H
#define LOG_H

#include <chrono>
#include <string>
#include <format>


enum LogLevel {
	NORMAL,
	WARRNING,
	FATAL
};


std::string logLevelConverter(LogLevel logLevel);

class Log {
private:
	std::chrono::time_point<std::chrono::system_clock> creationTime;
	LogLevel logLevel;
	std::string message;

public:
	Log(LogLevel logLevel, std::string message);
	std::string toString();
};
#endif