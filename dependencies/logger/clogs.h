#pragma once
#ifndef CLOGS_H
#define CLOGS_H

#include "include/logger-manager.h"
#include "include/log-stasher.h"
#include "include/logger.h"
#include "include/log.h"

LoggerManager* LoggerManager::loggerManager = nullptr;
std::mutex LoggerManager::mtx = std::mutex();


#endif