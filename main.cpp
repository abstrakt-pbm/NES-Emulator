#include <iostream>
#include "dependencies/logger/clogs.h"

int main(){
	LoggerManager::getInstance()->getLoggerInstance()->logFatal("CPU", "Error in CPY");
	LoggerManager::getInstance()->getLogStasherInstance()->bringOut();
}